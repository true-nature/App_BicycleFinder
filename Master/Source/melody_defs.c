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

#include <string.h>
#include <jendefs.h>
#include <utils.h>

#ifdef JN516x
# define USE_EEPROM //!< JN516x でフラッシュを使用する
#endif

#include "Master.h"

#include "ccitt8.h"
#include "common.h"
#include "config.h"
#include "sercmd_gen.h"

#ifdef USE_EEPROM
# include "eeprom_6x.h"
#endif

#include "melody_defs.h"

#define FLASH_MAGIC_NUMBER (0xA501EF5A ^ APP_ID) //!< フラッシュ書き込み時のマジック番号  @ingroup FLASH

#define MML_OPER_WRITE 1
#define MML_OPER_READ 2

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern tsAppData sAppData; //!< アプリケーションデータ  @ingroup MASTER
extern tsFILE sSerStream;

/**
 * メロディの定義
 *
 * - A-G: 音階の指定、続けて半音階、長さ、符点、タイ記号を指定可能
 *   - +,#,-         : 半音階の指定 (+,#: 半音上げる  -: 半音下げる)
 *   - 1,2,4,8,16,32 : 長さ (1が全音符)、指定なき場合はデフォルト値(4)
 *                     ３連符は未対応です。テンポの変更で乗り切ってください。
 *   - .             : 符点 (全音符には無効)
 *   - &             : タイ記号（この音符を一杯の長さまで演奏し、次の音符と連結する)
 *   - 例
 *     - A+16.       : A（ラ)の符点付き１６分音符
 *     - G2&G8       : タイで連結する
 *
 *  - Ln: 音符の長さ指定がない場合の長さを指定する
 *    - 例
 *      - C4D16E16F16G16 は L16C4DEFG と同じ指定である
 *
 *  - (...) : 括弧内の音符を長さいっぱいで演奏する（レガート）
 *    - 例
 *      - L8(C2DEF)GA2 は、CDEFはいっぱいの長さで、Gは通常の長さとなり、GとAの間に
 *        ごく短い音の切れ目が発生する。
 *
 *  - [...], [n...] : 括弧内をリピート再生する
 *    - n を指定した場合、n 回再生する。nは2〜255まで有効。
 *    - 例
 *      - [3CDEF] は CDEFCDEFCDEF と同じである
 *
 * - Tn: テンポの指定 (n は 32〜240 まで有効)
 *
 * - On (n=3..8): オクターブの指定
 *   圧電ブザーの場合 O3,O4 の音階は、うまく出ないようです。
 *
 * - <: 1オクターブ上げる
 * - >: 1オクターブ下げる
 *
 */

const uint8 au8MML[4][256] = {
		// ちょうちょ
		"O6T96 GEE2 FDD2 CDEF GGG2 GEEE FDDD CEGG EE2",

		// トロイメライ
		"O5T88L8 C4F2&F(EFA<C)FF2(EDC)F>(GAB-)<D>(FGA)<C>G2",

		// 春の海
		//"O6T96L16 <(DE>B<D> ABGA EGDE >B<D>A)B (EGAB <DEG)A >(B<DEG AB<D)E >"
		//"R1 (D8E4. G8.E32D32>B8A8) B1 E2. (<DEGA B4.&BA) B. R2.",
		// Happy Birthday
		"O6T96 C8.C16D8.D16C4 F4E4.R8 C8.C16D8.D16C4 G4F4.R8 C8.C16<C8.C16>A4 F8.F16E16.E16.E16.D2 R2 B-8.B-16A8.A16F4 G4F4.R8",

		// 停止
		"R"
};

usUserMML sUserMMLData;


/**
 * MMLの読み出し
 * バージョン等のチェックを行い、問題が有れば FALSE を返す
 *
 * @param p
 * @return
 */
bool MML_bLoad(tsUserMML *psMml) {
	bool_t bRet = FALSE;

#ifdef USE_EEPROM
    if (EEP_6x_bRead(1, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[0])
    		&& EEP_6x_bRead(2, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[1])
    		&& EEP_6x_bRead(3, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[2])
    		&& EEP_6x_bRead(4, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[3])) {
    	bRet = TRUE;
    }
#endif
    // validate content
    if (bRet && psMml->u32Magic != FLASH_MAGIC_NUMBER) {
    	bRet = FALSE;
    }
    if (bRet && psMml->u8CRC != u8CCITT8(psMml->u8Data, sizeof(psMml->u8Data))) {
    	bRet = FALSE;
    }
    // set default
    if (!bRet) {
    	memset(psMml->u8Data, 0, sizeof(psMml->u8Data));
    	memcpy(psMml->u8Data, au8MML[0], sizeof(psMml->u8Data) - 1);
    	bRet = MML_bSave(psMml);
    }
    return bRet;
}


bool MML_bSave(tsUserMML *psMml) {
	bool_t bRet = FALSE;

	psMml->u32Magic = FLASH_MAGIC_NUMBER;
	psMml->u8CRC = u8CCITT8(psMml->u8Data, sizeof(psMml->u8Data));
#ifdef USE_EEPROM
    if (EEP_6x_bWrite(1, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[0])
    		&& EEP_6x_bWrite(2, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[1])
    		&& EEP_6x_bWrite(3, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[2])
    		&& EEP_6x_bWrite(4, EEPROM_6X_SEGMENT_SIZE, sUserMMLData.segment[3])) {
    	bRet = TRUE;
    }
#endif
    return bRet;
}

void cpyMmlData(tsUserMML* psMml, uint8* p, uint8 u8DataSize) {
	uint16 dstlen = sizeof(psMml->u8Data) - 1;
	uint16 len = (dstlen < u8DataSize ? dstlen : u8DataSize);
	memset(psMml->u8Data, 0, sizeof(psMml->u8Data));
	memcpy(psMml->u8Data, p, len - 1);
}

/** @ingroup MASTER
 * MML の曲データを更新します。
 * 無線経由ので要求の場合は、応答は送信元へ無線パケットで戻されます。
 * アドレスが0xDBの場合は、要求は自身のモジュールで実行された上 UART に応答します。
 *
 * - 入力フォーマット
 *   - OCTET: ネットワークアドレス(宛先,0xDBは自身のモジュールで実行してUARTに出力)
 *   - OCTET: SERCMD_ID_MML_UPDATE_CMD (=0x95)
 *   - OCTET: 要求番号
 *   - OCTET: コマンド (0x1: Write, 0x2: Read, 0x3: Write and Read)
 *   - OCTET: 0x00 (曲インデックス)
 *   - OCTET: データサイズ (無い時は 0)
 *   - OCTET[N]: データ (データサイズが0のときは、本フィールドは無し)
 *
 * - 出力フォーマット
 *   - OCTET: ネットワークアドレス
 *   - OCTET: SERCMD_ID_MML_UPDATE_RSP (=0x96)
 *   - OCTET: 要求番号、入力フォーマットの値がコピーされる
 *   - OCTET: コマンド (0x1: Write, 0x2: Read, 0x3: Write and Read)
 *   - OCTET: 0:FAIL, 1:SUCCESS
 *   - OCTET: データサイズ (無い時は 0)
 *   - OCTET[N]: データ (データサイズが0のときは、本フィールドは無し)
 *
 * @param p 入力書式のバイト列
 * @param u16len バイト列長
 * @param u8AddrSrc 要求元のネットワークアドレス
 */
void vProcessMmlCommand(uint8 *p, uint16 u16len, uint8 u8AddrSrc) {
	uint8 *p_end = p + u16len;
	uint8 au8OutBuf[256 + 32];
	uint8 *q = au8OutBuf;
	tsUserMML *psMml = &sUserMMLData;

	// 入力データの解釈
	uint8 u8Addr = G_OCTET();
	(void) u8Addr;

	uint8 u8Command = G_OCTET();
	if (u8Command != SERCMD_ID_MML_UPDATE_CMD) {
		return;
	}

	uint8 u8ReqNum = G_OCTET();
	uint8 u8MML_Oper = G_OCTET();
	uint8 u8MML_Addr = G_OCTET();
	uint8 u8DataSize = G_OCTET();

	uint8 *pu8data_end = p + u8DataSize;

#if 1
	if (pu8data_end != p_end) {
		DBGOUT(1, "MMLCMD: incorrect data."LB);
		return;
	}
#endif

	// 出力用のバッファを用意しておく
	S_OCTET(sAppData.u8AppLogicalId);
	S_OCTET(SERCMD_ID_MML_UPDATE_RSP);
	S_OCTET(u8ReqNum);
	S_OCTET(u8MML_Oper);
	//ここで q[0] 成功失敗フラグ, q[1] データサイズ, q[2]... データ
	q[0] = FALSE;
	q[1] = 0;

	DBGOUT(1, "MMLCMD: req#=%d Oper=%d Addr=%02x Siz=%d"LB, u8ReqNum,
			u8MML_Oper, u8MML_Addr, u8DataSize);

	switch (u8MML_Oper) {
	case MML_OPER_WRITE:
	// Save
		cpyMmlData(psMml, p, u8DataSize);
		q[0] = MML_bSave(psMml);
		break;

	case MML_OPER_WRITE|MML_OPER_READ:
	// Save
		cpyMmlData(psMml, p, u8DataSize);
		q[0] = MML_bSave(psMml);
		if (!q[0]) {
			break;
		}
		// no break

	case MML_OPER_READ:
	// Read
		{
			uint16 maxlen = sizeof(psMml->u8Data) - 1;
			uint16 datalen = strnlen((const char *)psMml->u8Data, maxlen);
			uint16 len = (datalen < u8DataSize - 1 ? datalen : u8DataSize - 1);
			q[1] = len + 1;
			memset(&q[2], 0, len + 1);
			memcpy(&q[2], psMml->u8Data, len);
		}
		break;

	default:
		DBGOUT(1, "MMLCMD: unknown operation(%d)."LB, u8MML_Oper);
		return;
	}

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
