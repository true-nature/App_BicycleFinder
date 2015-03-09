/****************************************************************************
 * (C) Tokyo Cosmos Electric, Inc. (TOCOS) - 2013 all rights reserved.
 *
 * Condition to use: (refer to detailed conditions in Japanese)
 *   - The full or part of source code is limited to use for TWE (TOCOS
 *     Wireless Engine) as compiled and flash programmed.
 *   - The full or part of source code is prohibited to distribute without
 *     permission from TOCOS.
 *
 * 利用条件:
 *   - 本ソースコードは、別途ソースコードライセンス記述が無い限り東京コスモス電機が著作権を
 *     保有しています。
 *   - 本ソースコードは、無保証・無サポートです。本ソースコードや生成物を用いたいかなる損害
 *     についても東京コスモス電機は保証致しません。不具合等の報告は歓迎いたします。
 *   - 本ソースコードは、東京コスモス電機が販売する TWE シリーズ上で実行する前提で公開
 *     しています。他のマイコン等への移植・流用は一部であっても出来ません。
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <string.h>
#include <AppHardwareApi.h>

#include "Master.h"

#include "common.h"
#include "config.h"

#include <utils.h>

// I2C
#include "SMBus.h"
#include "I2C_impl.h"

// Serial options
#include <serial.h>
#include <fprintf.h>
#include <sprintf.h>

#include "sercmd_gen.h"

// 実験的な実装
#include "Experimental.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern tsAppData sAppData; //!< アプリケーションデータ  @ingroup MASTER
extern tsFILE sSerStream;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        FUNCTIONS                                                     ***/
/****************************************************************************/

/** @ingroup MASTER
 * I2C のコマンドを実行して、応答を返します。
 * 無線経由ので要求の場合は、応答は送信元へ無線パケットで戻されます。
 * アドレスが0xDBの場合は、要求は自身のモジュールで実行された上 UART に応答します。
 *
 * - 入力フォーマット
 *   - OCTET: ネットワークアドレス(宛先,0xDBは自身のモジュールで実行してUARTに出力)
 *   - OCTET: 0x88
 *   - OCTET: 要求番号
 *   - OCTET: コマンド (0x1: Write, 0x2: Read, 0x3: Write and Increment, 0x4: Write and Read)
 *   - OCTET: I2Cアドレス
 *   - OCTET: I2Cコマンド
 *   - OCTET: データサイズ (無い時は 0)
 *   - OCTET[N]: データ (データサイズが0のときは、本フィールドは無し)
 *
 * - 出力フォーマット
 *   - OCTET: ネットワークアドレス
 *   - OCTET: 0x89
 *   - OCTET: 要求番号、入力フォーマットの値がコピーされる
 *   - OCTET: コマンド (0x1: Write, 0x2: Read)
 *   - OCTET: 0:FAIL, 1:SUCCESS
 *   - OCTET: データサイズ (無い時は 0)
 *   - OCTET[N]: データ (データサイズが0のときは、本フィールドは無し)
 *
 * @param p 入力書式のバイト列
 * @param u16len バイト列長
 * @param u8AddrSrc 要求元のネットワークアドレス
 */
void vProcessI2CCommand(uint8 *p, uint16 u16len, uint8 u8AddrSrc) {
	//uint8 *p_end = p + u16len;
	uint8 au8OutBuf[256 + 32];
	uint8 *q = au8OutBuf;

	bool_t bOk = TRUE;
	uint8 n;
	static volatile uint16 x;

	// 入力データの解釈
	uint8 u8Addr = G_OCTET();
	(void) u8Addr;

	uint8 u8Command = G_OCTET();
	if (u8Command != SERCMD_ID_I2C_COMMAND) {
		return;
	}

	uint8 u8ReqNum = G_OCTET();
	uint8 u8I2C_Oper = G_OCTET();
	uint8 u8I2C_Addr = G_OCTET();
	uint8 u8I2C_Cmd = G_OCTET();
	uint8 u8DataSize = G_OCTET();

	uint8 *pu8data = p;
	//uint8 *pu8data_end = p + u8DataSize;

#if 0
	if (pu8data_end != p_end) {
		DBGOUT(1, "I2CCMD: incorrect data."LB);
		return;
	}
#endif

	// 出力用のバッファを用意しておく
	S_OCTET(sAppData.u8AppLogicalId);
	S_OCTET(SERCMD_ID_I2C_COMMAND_RESP);
	S_OCTET(u8ReqNum);
	S_OCTET(u8I2C_Oper);
	//ここで q[0] 成功失敗フラグ, q[1] データサイズ, q[2]... データ
	q[0] = FALSE;
	q[1] = 0;

	DBGOUT(1, "I2CCMD: req#=%d Oper=%d Addr=%02x Cmd=%02x Siz=%d"LB, u8ReqNum,
			u8I2C_Oper, u8I2C_Addr, u8I2C_Cmd, u8DataSize);

	switch (u8I2C_Oper) {
	case 1:
		bOk &= bSMBusWrite(u8I2C_Addr, u8I2C_Cmd, u8DataSize,
				u8DataSize == 0 ? NULL : pu8data);
		break;

	case 2:
		if (u8DataSize > 0) {
			bOk &= bSMBusSequentialRead(u8I2C_Addr, u8DataSize, &(q[2]));
			if (bOk)
				q[1] = u8DataSize;
		} else {
			bOk = FALSE;
		}
		break;

	case 3:
		for (n = 0; n < u8DataSize; n++) {
			bOk &= bSMBusWrite(u8I2C_Addr, u8I2C_Cmd + n, 1, &pu8data[n]);
			for (x = 0; x < 16000; x++)
				; //wait (e.g. for memory device)
		}
		break;

	case 4:
		if (u8DataSize > 0) {
			bOk &= bSMBusWrite(u8I2C_Addr, u8I2C_Cmd, 0, NULL );
			if (bOk)
				bOk &= bSMBusSequentialRead(u8I2C_Addr, u8DataSize, &(q[2]));
			if (bOk)
				q[1] = u8DataSize;
		} else {
			bOk = FALSE;
		}
		break;

#ifdef USE_I2C_ACM1620
	case 0x21: // ACM1620
		bDraw2LinesLcd_ACM1602((const char *) pu8data,
				(const char *) (pu8data + 16));
		break;
#endif

#ifdef USE_I2C_AQM0802A
	case 0x22: // ACM1620
		bDraw2LinesLcd_AQM0802A((const char *) pu8data,
				(const char *) (pu8data + 8));
		break;
#endif

	default:
		DBGOUT(1, "I2CCMD: unknown operation(%d)."LB, u8I2C_Oper);
		return;
	}

	q[0] = bOk; // 成功失敗フラグを書き込む
	q = q + 2 + q[1]; // ポインタ q を進める（データ末尾+1)

	if (u8AddrSrc == SERCMD_ADDR_TO_MODULE) {
		SerCmdAscii_Output_AdrCmd(&sSerStream, u8AddrSrc, au8OutBuf[1],
				au8OutBuf + 2, q - au8OutBuf - 2);
	} else {
		i16TransmitSerMsg(au8OutBuf, q - au8OutBuf, ToCoNet_u32GetSerial(),
				sAppData.u8AppLogicalId, u8AddrSrc, FALSE,
				sAppData.u8UartReqNum++);
	}
}

#ifdef USE_I2C_ACM1620
/** @ingroup MASTER
 * ACM1620 LCD モジュールに文字列を書き出す。
 * - この処理は、一定時間処理をブロックし、IO判定などTIMER_0起点の動作などに影響を及ぼします。
 * - ２つのパラメータを両方とも NULL にすると、画面クリアを行います。
 *
 * @param puUpperRow 上段に書き込む文字列
 * @param puLowerRow 下段に書き込む文字列
 * @return
 */
bool_t bDraw2LinesLcd_ACM1602(const char *puUpperRow,
		const char *puLowerRow) {
	bool_t bOk = TRUE;
	const uint8 *pu8data;
	const uint32 u32delay = 20000;

	// ディスプレーのクリア
	const uint8 au8data[] = { 0x01, 0x38, 0x0c, 0x06, 0x00 };
	pu8data = au8data;
	while (*pu8data) {
		bOk &= bSMBusWrite(0x50, 0x00, 1, (uint8*) pu8data);
		vWait(u32delay);

		pu8data++;
	}

	// 上段への書き込み
	if (puUpperRow) {
		uint8 u8data = 0x80; // 上段のアドレス指定
		int i = 0;

		bOk &= bSMBusWrite(0x50, 0x00, 1, &u8data);
		vWait(u32delay);

		pu8data = (uint8*) puUpperRow;

		while (*pu8data && i < 16) {
			bOk &= bSMBusWrite(0x50, 0x80, 1, (uint8*) pu8data);
			vWait(u32delay);

			pu8data++;
			i++;
		}
	}

	// 下段への書き込み
	if (puLowerRow) {
		uint8 u8data = 0xC0; // 下段のアドレス指定
		int i = 0;

		bOk &= bSMBusWrite(0x50, 0x00, 1, &u8data);
		vWait(u32delay);

		pu8data = (uint8*) puLowerRow;

		while (*pu8data && i < 16) {
			bOk &= bSMBusWrite(0x50, 0x80, 1, (uint8*) pu8data);
			vWait(u32delay);

			pu8data++;
			i++;
		}
	}

	return bOk;
}
#endif

#ifdef USE_I2C_AQM0802A
static bool_t bInit2LinesLcd_AQM0802A() {
	bool_t bOk = TRUE;
	const uint8 *pu8data;
	const uint32 u32delay = 2000;
	const uint8 u8addr = 0x3E;

	// ディスプレーのクリア
	const uint8 au8data[] = { 0x38, 0x39, 0x14, 0x70, 0x56, 0x6c, 0x00 };
	pu8data = au8data;
	while (*pu8data) {
		bOk &= bSMBusWrite(u8addr, 0x00, 1, (uint8*) pu8data);
		vWait(u32delay);

		pu8data++;
	}

	return bOk;
}

/** @ingroup MASTER
 * ACM1620 LCD モジュールに文字列を書き出す。
 * - この処理は、一定時間処理をブロックし、IO判定などTIMER_0起点の動作などに影響を及ぼします。
 * - ２つのパラメータを両方とも NULL にすると、画面クリアを行います。
 *
 * @param puUpperRow 上段に書き込む文字列
 * @param puLowerRow 下段に書き込む文字列
 * @return
 */
bool_t bDraw2LinesLcd_AQM0802A(const char *puUpperRow,
		const char *puLowerRow) {
	bool_t bOk = TRUE;
	const uint8 *pu8data;
	const uint32 u32delay = 2000;
	const uint8 u8addr = 0x3E;

	static bool_t bInit;

	// ディスプレーのクリア
	if (!bInit) {
		bOk &= bInit2LinesLcd_AQM0802A();
		vWait(400000);
		bInit = TRUE;
	}

	const uint8 au8data2[] = { 0x38, 0x0c, 0x01, 0x06, 0x00 };
	pu8data = au8data2;
	while (*pu8data) {
		bOk &= bSMBusWrite(u8addr, 0x00, 1, (uint8*) pu8data);
		vWait(u32delay);

		pu8data++;
	}

	// 上段への書き込み
	if (puUpperRow) {
		uint8 u8data = 0x80; // 上段のアドレス指定
		int i = 0;

		bOk &= bSMBusWrite(u8addr, 0x00, 1, &u8data);
		vWait(u32delay);

		pu8data = (uint8*) puUpperRow;

		while (*pu8data && i < 8) {
			bOk &= bSMBusWrite(u8addr, 0x40, 1, (uint8*) pu8data);
			vWait(u32delay);

			pu8data++;
			i++;
		}
	}

	// 下段への書き込み
	if (puLowerRow) {
		uint8 u8data = 0xC0; // 下段のアドレス指定
		int i = 0;

		bOk &= bSMBusWrite(u8addr, 0x00, 1, &u8data);
		vWait(u32delay);

		pu8data = (uint8*) puLowerRow;

		while (*pu8data && i < 8) {
			bOk &= bSMBusWrite(u8addr, 0x40, 1, (uint8*) pu8data);
			vWait(u32delay);

			pu8data++;
			i++;
		}
	}

	return bOk;
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
