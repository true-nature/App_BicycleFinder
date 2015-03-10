/****************************************************************************
 * (C) Tokyo Cosmos Electric, Inc. (TOCOS) - all rights reserved.
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
#include <stdlib.h>

#include <jendefs.h>
#include <AppHardwareApi.h>

#include "appdata.h"

#include "utils.h"
#include "flash.h"

#include "common.h"

// Serial options
#include <serial.h>
#include <fprintf.h>
#include <sprintf.h>

#include "Interactive.h"

#include "config.h"

// MML 対応
#ifdef BICYCLEFINDER_SLAVE
#include "mml.h"
#endif
#include "melody_defs.h"

#include "sercmd_gen.h"
#include "sercmd_plus3.h"

/****************************************************************************/
/***        MACROs                                                        ***/
/****************************************************************************/
#define MAX_CHANNELS 3

/****************************************************************************/
/***        Imported variables/functions                                  ***/
/****************************************************************************/
extern tsFILE sSerStream;
extern tsSerialPortSetup sSerPort;

extern tsAppData sAppData; //!< アプリケーションデータ  @ingroup MASTER

#ifdef BICYCLEFINDER_SLAVE
extern tsMML sMML; //!< MML 関連 @ingroup MASTER
#endif

//tsModbusCmd sSerCmd; //!< シリアル入力系列のパーサー (modbus もどき)  @ingroup MASTER
tsInpStr_Context sSerInpStr; //!< 文字列入力  @ingroup MASTER
uint16 u16HoldUpdateScreen = 0; //!< スクリーンアップデートを行う遅延カウンタ  @ingroup MASTER

tsSerCmdPlus3_Context sSerCmd_P3; //!< シリアル入力系列のパーサー (+ + +)  @ingroup MASTER
static tsSerCmd_Context sSerCmd; //!< シリアル入力系列のパーサー   @ingroup MASTER

uint8 au8SerBuffInput[(SERCMD_MAXPAYLOAD + 32) * 2]; //!< 入力バッファ用に確保  @ingroup MASTER

static tsFlashApp sConfig_UnSaved; //!< 未セーブ状態の設定情報

static bool_t bInitInteractive = FALSE;

extern void vSerInitMessage();
extern void vProcessSerialCmd(tsSerCmd_Context *);

#ifdef PARENT
static void vSerPrintUartOpt(uint8 u8conf);
#endif

static void vProcessInputByte_Command(int16 i16Char);
static void vProcessInputByte(uint8 u8Byte);
static void vProcessInputString(tsInpStr_Context *pContext);

static void vConfig_SaveAndReset();
static void vConfig_UnSetAll(tsFlashApp *p);
void Config_vSetDefaults(tsFlashApp *p);
void vSerUpdateScreen();

void vProcessSerialCmd();

/****************************************************************************/
/***        Procedures                                                    ***/
/****************************************************************************/

/**
 * インタラクティブモードの初期化
 */
void Interactive_vInit() {
	memset(&sConfig_UnSaved, 0xFF, sizeof(tsFlashApp));
#ifdef ENDDEVICE_INPUT
	sConfig_UnSaved.i16param = INIT_VAL_i16;
#endif

	INPSTR_vInit(&sSerInpStr, &sSerStream);

	static uint8 au8SerialBuffCmd[256];
	sSerCmd.au8data = au8SerialBuffCmd;
	sSerCmd.u16maxlen = sizeof(au8SerialBuffCmd);

	// シリアルコマンド処理関数
	memset(&sSerCmd_P3, 0x00, sizeof(sSerCmd_P3));
	memset(&sSerCmd, 0x00, sizeof(sSerCmd));

	// 入力コマンド形式の設定
	SerCmdAscii_vInit(&sSerCmd, au8SerBuffInput, sizeof(au8SerBuffInput)); //!< modbus ASCII

	bInitInteractive = TRUE;
	u16HoldUpdateScreen = 100;
}


/**
 * インタラクティブモードの再初期化
 * (UART 初期化前に呼び出す)
 */
void Interactive_vReInit() {
	while (!SERIAL_bRxQueueEmpty(sSerPort.u8SerialPort)) {
		(void)SERIAL_i16RxChar(sSerPort.u8SerialPort);
	}

	sSerCmd.u8state = E_SERCMD_EMPTY;
	sSerCmd_P3.u8state = E_SERCMD_EMPTY;
}

/**
 * VERBOSE モードの判定
 * @return TRUEならVERBOSEモード
 */
bool_t Interactive_bGetMode() {
	return sSerCmd_P3.bverbose;
}

/**
 * VERBOSE モードの設定
 * @param bVerbose TRUEならVERBOSEモードに設定する
 * @param u16screen_refresh 再表示までのタイマカウンタ(0なら設定しない、1カウント約16ms)
 */
void Interactive_vSetMode(bool_t bVerbose, uint16 u16screen_refresh) {
	if (!bInitInteractive) return;

	sSerCmd_P3.bverbose = bVerbose;
	if (u16screen_refresh) {
		u16HoldUpdateScreen = u16screen_refresh;
	}
}

/**
 * 書式コマンドの解釈
 * @param i16Char
 */
static void vProcessInputByte_Command(int16 i16Char) {
	// 無効処理
	if (i16Char < 0 || i16Char > 0xFF || sSerCmd.u8Parse == NULL) return;

	// verbose モードならタイムアウトは無効
	if (sSerCmd_P3.bverbose) {
		sSerCmd.u32timestamp = u32TickCount_ms;
	}

	// コマンド書式の系列解釈
	uint8 u8res = sSerCmd.u8Parse(&sSerCmd, (uint8)i16Char);

	// 完了判定
	if (u8res == E_SERCMD_COMPLETE || u8res == E_SERCMD_CHECKSUM_ERROR) {
		// 解釈完了

		if (u8res == E_SERCMD_CHECKSUM_ERROR) {
			// command complete, but CRC error
			V_PRINTF(LB "!INF CHSUM_ERR? (might be %02X)" LB, sSerCmd.u16cksum);
		}

		if (u8res == E_SERCMD_COMPLETE) {
			// process command
			vProcessSerialCmd(&sSerCmd);
		}
	} else {
		if (u8res != E_SERCMD_EMPTY) {
			if (sSerCmd.u16pos == 0) {
				V_PRINTF(LB);
			}
			// エコーバック
			V_PUTCHAR(i16Char);
		}
	}
}


/** @ingroup INTERACTIVE
 * シリアルポートからの入力を処理します。
 * - シリアルポートからの入力は uart.c/serial.c により管理される FIFO キューに値が格納されます。
 *   このキューから１バイト値を得るのが SERIAL_i16RxChar() です。
 * - 本関数では、入力したバイトに対し、アプリケーションのモードに依存した処理を行います。
 *   - 文字列入力モード時(INPSTR_ API 群、インタラクティブモードの設定値入力中)は、INPSTR_u8InputByte()
 *     API に渡す。文字列が完了したときは vProcessInputString() を呼び出し、設定値の入力処理を
 *     行います。
 *   - 上記文字列入力ではない場合は、ModBusAscii_u8Parse() を呼び出します。この関数は + + + の
 *     入力判定および : で始まる書式を認識します。
 *   - 上記書式解釈中でない場合は、vProcessInputByte() を呼び出します。この関数はインタラクティブ
 *     モードにおける１文字入力コマンドを処理します。
 *
 */
void vHandleSerialInput() {
	static uint32 u32last_tick;

	// カウンタ値のチェック
	if (u32TickCount_ms - u32last_tick >= 16) {
		if (u16HoldUpdateScreen) {
			u16HoldUpdateScreen--;
			if (!u16HoldUpdateScreen && sSerCmd_P3.bverbose) {
				vSerUpdateScreen();
			}
		}
		u32last_tick = u32TickCount_ms;
	}

	while (!SERIAL_bRxQueueEmpty(sSerPort.u8SerialPort)) {
		// UART バッファからのバイトの取り出し
		int16 i16Char = SERIAL_i16RxChar(sSerPort.u8SerialPort);


		// process
		if (i16Char >=0 && i16Char <= 0xFF) {
			//DBGOUT(0, "[%02x]", i16Char);
			if (INPSTR_bActive(&sSerInpStr)) {
				// 文字列入力モード
				uint8 u8res = INPSTR_u8InputByte(&sSerInpStr, (uint8)i16Char);

				if (u8res == E_INPUTSTRING_STATE_COMPLETE) {
					vProcessInputString(&sSerInpStr);
				} else if (u8res == E_INPUTSTRING_STATE_CANCELED) {
					V_PRINTF("(canceled)");
					u16HoldUpdateScreen = 64;
				}
				continue;
			}

			{
				// コマンド書式の系列解釈、および verbose モードの判定
				uint8 u8res;
				u8res = SerCmdPlus3_u8Parse(&sSerCmd_P3, (uint8)i16Char);

				if (u8res != E_SERCMD_PLUS3_EMPTY) {
					if (u8res == E_SERCMD_PLUS3_VERBOSE_ON) {
						// verbose モードの判定があった
						if (bInitInteractive) {
							vSerUpdateScreen();
							sSerCmd.u16timeout = 0;
						}
					}

					if (u8res == E_SERCMD_PLUS3_VERBOSE_OFF) {
						if (bInitInteractive) {
							vfPrintf(&sSerStream, "!INF EXIT INTERACTIVE MODE."LB);
							sSerCmd.u16timeout = 1000;
						}
					}

					// still waiting for bytes.
					//continue;
				} else {
					; // コマンド解釈モードではない
				}
			}

			// Verbose モードのときは、シングルコマンドを取り扱う
			if (sSerCmd_P3.bverbose) {
				// コマンドの解釈
				vProcessInputByte_Command(i16Char);

				if (sSerCmd.u8state == E_SERCMD_EMPTY) {
					// 書式入出力でなければ、１バイトコマンド
					vProcessInputByte(i16Char);
				}
			} else {
				vProcessInputByte_Command(i16Char);
			}
		}
	}
}

/** @ingroup MASTER
 * １バイト入力コマンドの処理\n
 * - 設定値の入力が必要な項目の場合、INPSTR_vStart() を呼び出して文字列入力モードに遷移します。
 * - フラッシュへのセーブ時の手続きでは、sConfig_UnSaved 構造体で入力が有ったものを
 *   sFlash.sData 構造体に格納しています。
 * - デバッグ用の確認コマンドも存在します。
 *
 * @param u8Byte 入力バイト
 */
static void vProcessInputByte(uint8 u8Byte) {
	static uint8 u8lastbyte;

	switch (u8Byte) {
	case 0x0d:
	case 'h':
	case 'H':
		// 画面の書き換え
		u16HoldUpdateScreen = 1;
		break;

	case 'a': // set application ID
		V_PRINT("Input Application ID (HEX:32bit): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_HEX, 8,
				E_APPCONF_APPID);
		break;

	case 'c': // チャネルの設定
		V_PRINT("Input Channel(s) (e.g. 11,16,21): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_STRING, 8,
				E_APPCONF_CHMASK);
		break;

	case 'i': // set application role
		V_PRINT("Input Device ID (DEC:1-100): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 3, E_APPCONF_ID);
		break;

	case 'x': // 出力の変更
		V_PRINT("Tx Power (0[min]-3[max]): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 1,
				E_APPCONF_TX_POWER);
		break;

	case 't': // set application role
		V_PRINT("Input mode4 sleep dur[ms] (DEC:100-10000): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 5,
				E_APPCONF_SLEEP4);
		break;

	case 'y': // set application role
		V_PRINT("Input mode7 sleep dur[ms] (DEC:0-10000): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 5,
				E_APPCONF_SLEEP7);
		break;

	case 'f': // set application role
		V_PRINT("Input mode3 fps (DEC:4,8,16,32): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 2,
				E_APPCONF_FPS);
		break;

	case 'z': // PWMの駆動周波数の変更
		V_PRINT("Input PWM Hz (DEC:1-64000): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 6,
				E_APPCONF_PWM_HZ);
		break;

	case 'b': // ボーレートの変更
		V_PRINT("Input baud rate (DEC:9600-230400): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_STRING, 10,
				E_APPCONF_BAUD_SAFE);
		break;

	case 'p': // パリティの変更
		V_PRINT("Input parity (N, E, O): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_STRING, 1,
				E_APPCONF_BAUD_PARITY);
		break;

	case 'o': // オプションビットの設定
		V_PRINT("Input option bits (HEX): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_HEX, 8,
				E_APPCONF_OPT);
		break;

	case 'O': // オプションビット２
		V_PRINT("Input option bits #2 (HEX): ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_HEX, 8,
				E_APPCONF_OPT2);
		break;

	case 'm': // MML選曲インデックスの変更
		V_PRINT("MML index (0[min]-%d[max]): ", (MMLBANK_COUNT - 1));
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_DEC, 1,
				E_APPCONF_MML_IDX);
		break;

	case 'S':
		// フラッシュへのデータ保存
		if (u8lastbyte == 'R') {
			// R S と連続入力された場合は、フラッシュエリアを消去する
			V_PRINT("!INF CLEAR SAVE AREA.");
			bFlash_Erase(FLASH_SECTOR_NUMBER - 1); // SECTOR ERASE

			vWait(1000000);
			vAHI_SwReset();
		} else {
			vConfig_SaveAndReset();
		}
		break;

	case 'R':
		Config_vSetDefaults(&sConfig_UnSaved);
		u16HoldUpdateScreen = 1;
		break;

	case '$':
		sAppData.u8DebugLevel++;
		if (sAppData.u8DebugLevel > 5)
			sAppData.u8DebugLevel = 0;

		V_PRINT("* set App debug level to %d." LB, sAppData.u8DebugLevel);
		break;

	case '@':
		_C {
			static uint8 u8DgbLvl;

			u8DgbLvl++;
			if (u8DgbLvl > 5)
				u8DgbLvl = 0;
			ToCoNet_vDebugLevel(u8DgbLvl);

			V_PRINT("* set NwkCode debug level to %d." LB, u8DgbLvl);
		}
		break;

	case '!':
		// リセット
		V_PRINT("!INF RESET SYSTEM.");
		vWait(1000000);
		vAHI_SwReset();
		break;

	case '#': // info
		_C {
			V_PRINT("*** ToCoNet(ver%08X) ***" LB, ToCoNet_u32GetVersion());
			V_PRINT("* AppID %08x, LongAddr, %08x, ShortAddr %04x, Tk: %d" LB,
					sToCoNet_AppContext.u32AppId, ToCoNet_u32GetSerial(),
					sToCoNet_AppContext.u16ShortAddress, u32TickCount_ms);
			if (sAppData.bFlashLoaded) {
				V_PRINT("** Conf "LB);
				V_PRINT("* AppId = %08x"LB, sAppData.sFlash.sData.u32appid);
				V_PRINT("* ChMsk = %08x"LB, sAppData.sFlash.sData.u32chmask);
				V_PRINT("* Ch=%d, Role=%d, Layer=%d"LB,
						sToCoNet_AppContext.u8Channel,
						sAppData.sFlash.sData.u8role,
						sAppData.sFlash.sData.u8layer);
			} else {
				V_PRINT("** Conf: none"LB);
			}
		}
		break;

	case 'V':
		vSerInitMessage();
		V_PRINT("---"LB);
		V_PRINT("ToCoNet lib version Core: %08x, Ext: %08x, Utils: %08x"LB,
				ToCoNet_u32GetVersion(), ToCoNet_u32GetVersion_LibEx(),
				ToCoNet_u32GetVersion_LibUtils());
		V_PRINT("ToCoNet Tick Counter: %d"LB, u32TickCount_ms);
		V_PRINT("Run Time: %d+%02d/64 sec"LB, sAppData.u32CtTimer0 >> 6,
				sAppData.u32CtTimer0 & 0x3F);
		V_PRINT(""LB);
		break;

#ifdef BICYCLEFINDER_SLAVE
	case '1':
		// テスト再生
		MML_vPlay(&sMML, sUserMMLData.u8Data);
		break;
	case '2':
	case '3':
	case '4':
		MML_vPlay(&sMML, au8MML[u8Byte - '1']);
		break;

	case 'M':
		// MML入力によるテスト再生
		V_PRINT(LB"MML: ");
		INPSTR_vStart(&sSerInpStr, E_INPUTSTRING_DATATYPE_STRING, 120, E_APPCONF_TEST);
		break;
#endif

	default:
		u8lastbyte = 0xFF;
		break;
	}

	// 一つ前の入力
	if (u8lastbyte != 0xFF) {
		u8lastbyte = u8Byte;
	}
}

/** @ingroup MASTER
 * 文字列入力モードの処理を行います。
 *
 */
static void vProcessInputString(tsInpStr_Context *pContext) {
	uint8 *pu8str = pContext->au8Data;
	uint8 u8idx = pContext->u8Idx;

	switch (pContext->u32Opt) {
	case E_APPCONF_APPID:
		_C {
			uint32 u32val = u32string2hex(pu8str, u8idx);

			uint16 u16h, u16l;
			u16h = u32val >> 16;
			u16l = u32val & 0xFFFF;

			if (u16h == 0x0000 || u16h == 0xFFFF || u16l == 0x0000
					|| u16l == 0xFFFF) {
				V_PRINT(
						"(ignored: 0x0000????,0xFFFF????,0x????0000,0x????FFFF can't be set.)");
			} else {
				sConfig_UnSaved.u32appid = u32val;
			}

			V_PRINT(LB"-> %08X"LB, u32val);
		}
		break;

	case E_APPCONF_CHMASK:
		_C {
			// チャネルマスク（リスト）を入力解釈する。
			//  11,15,19 のように１０進数を区切って入力する。
			//  以下では区切り文字は任意で MAX_CHANNELS 分処理したら終了する。
			//  末尾に指定したチャネルがデフォルトチャネルになる。

			uint8 b = 0, e = 0, i = 0, n_ch = 0;
			uint32 u32chmask = 0; // 新しいチャネルマスク

			V_PRINT(LB"-> ");

			for (i = 0; i <= pContext->u8Idx; i++) {
				if (pu8str[i] < '0' || pu8str[i] > '9') {
					e = i;
					uint8 u8ch = 0;

					// 最低２文字あるときに処理
					if (e - b > 0) {
						u8ch = u32string2dec(&pu8str[b], e - b);
						if (u8ch >= 11 && u8ch <= 26) {
							if (n_ch) {
								V_PUTCHAR(',');
							}
							V_PRINT("%d", u8ch);
							u32chmask |= (1UL << u8ch);

							sConfig_UnSaved.u8ch = u8ch; // CHANNEL

							n_ch++;
							if (n_ch >= MAX_CHANNELS) {
								break;
							}
						}
					}
					b = i + 1;
				}

				if (pu8str[i] == 0x0) {
					break;
				}
			}

			if (u32chmask == 0x0) {
				V_PRINT("(ignored)");
			} else {
				sConfig_UnSaved.u32chmask = u32chmask;
			}

			V_PRINT(LB);
		}
		break;

	case E_APPCONF_ID:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);
			V_PRINT(LB"-> ");
			if (u32val <= 0x7F) {
				sConfig_UnSaved.u8id = u32val;
				V_PRINT("%d(0x%02x)"LB, u32val, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_TX_POWER:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);
			V_PRINT(LB"-> ");
			if (u32val <= 3) {
				sConfig_UnSaved.u8pow = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_SLEEP4:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);
			V_PRINT(LB"-> ");
			if (u32val >= 100 && u32val <= 65534) {
				sConfig_UnSaved.u16SleepDur_ms = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_SLEEP7:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);

			V_PRINT(LB"-> ");
			if (u32val <= 65534) { // 0 はタイマーを使用しない (
				sConfig_UnSaved.u16SleepDur_s = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_FPS:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);

			V_PRINT(LB"-> ");
			if (u32val == 4 || u32val == 8 || u32val == 16 || u32val == 32) {
				sConfig_UnSaved.u8Fps = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_PWM_HZ:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);

			V_PRINT(LB"-> ");

			if (u32val > 0 && u32val < 0xFFFF) { // Timer API の限界は 16bit なので。
				sConfig_UnSaved.u32PWM_Hz = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_OPT:
		_C {
			uint32 u32val = u32string2hex(pu8str, u8idx);

			V_PRINT(LB"-> ");

			sConfig_UnSaved.u32Opt = u32val;
			V_PRINT("0x%08X"LB, u32val);
		}
		break;

	case E_APPCONF_OPT2:
		_C {
			uint32 u32val = u32string2hex(pu8str, u8idx);

			V_PRINT(LB"-> ");

			sConfig_UnSaved.u32Opt2 = u32val;
			V_PRINT("0x%08X"LB, u32val);
		}
		break;

#if 0 // 意味が無いのでお蔵入り
		case E_APPCONF_SYS_HZ:
		_C {
			int i = 0;
			const uint16 u8tbl[] = {
				100, 200, 250, 400, 500, 1000, 0
			};

			uint32 u32val = u32string2dec(pu8str, u8idx);

			V_PRINT(LB"-> ");

			while(u8tbl[i]) {
				if (u8tbl[i] == u32val) {
					break;
				}
				i++;
			}

			if (u8tbl[i]) {
				sConfig_UnSaved.u16Sys_Hz = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;
#endif

	case E_APPCONF_BAUD_SAFE:
		_C {
			uint32 u32val = 0;

			if (pu8str[0] == '0' && pu8str[1] == 'x') {
				u32val = u32string2hex(pu8str + 2, u8idx - 2);
			}
			if (u8idx <= 6) {
				u32val = u32string2dec(pu8str, u8idx);
			}

			V_PRINT(LB"-> ");

			if (u32val) {
				sConfig_UnSaved.u32baud_safe = u32val;
				if (u32val & 0x80000000) {
					V_PRINT("%x"LB, u32val);
				} else {
					V_PRINT("%d"LB, u32val);
				}
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_BAUD_PARITY:
		_C {
			V_PRINT(LB"-> ");

			if (pu8str[0] == 'N' || pu8str[0] == 'n') {
				sConfig_UnSaved.u8parity = 0;
				V_PRINT("None"LB);
			} else if (pu8str[0] == 'O' || pu8str[0] == 'o') {
				sConfig_UnSaved.u8parity = 1;
				V_PRINT("Odd"LB);
			} else if (pu8str[0] == 'E' || pu8str[0] == 'e') {
				sConfig_UnSaved.u8parity = 2;
				V_PRINT("Even"LB);
			} else {
				V_PRINT("(ignored)"LB);
			}
		}
		break;

	case E_APPCONF_MML_IDX:
		_C {
			uint32 u32val = u32string2dec(pu8str, u8idx);
			V_PRINT(LB"-> ");
			if (u32val >= 0 && u32val < MMLBANK_COUNT) {
				sConfig_UnSaved.u8MML_idx = u32val;
				V_PRINT("%d"LB, u32val);
			} else {
				V_PRINT("(ignored)"LB);
			}

		}
		break;

#ifdef BICYCLEFINDER_SLAVE
	// MMLデバッグ再生用
	case E_APPCONF_TEST:
		_C {
			MML_vPlay(&sMML, pu8str);
			u16HoldUpdateScreen = 0; // 画面の再描画がうっとおしいので。
			return;
		}
		break;
#endif

	default:
		break;
	}

	// 一定時間待って画面を再描画
	u16HoldUpdateScreen = 96; // 1.5sec
}

/** @ingroup FLASH
 * フラッシュ構造体の読み出し
 * バージョン等のチェックを行い、問題が有れば FALSE を返す
 *
 * @param p
 * @return
 */
bool_t Config_bLoad(tsFlash *p) {
	bool_t bRet = FALSE;

	// フラッシュの読み出し
	bRet = bFlash_Read(p, FLASH_SECTOR_NUMBER - 1, 0);

	// Version String のチェック
	if (bRet && APP_ID == p->sData.u32appkey  && VERSION_U32 == p->sData.u32ver) {
		bRet = TRUE;
	} else {
		// チェックが違っているとデフォルト値を採用する
		Config_vSetDefaults(&p->sData);
	}

	return bRet;
}

/** @ingroup FLASH
 * フラッシュ設定構造体を全て未設定状態に設定します。未設定状態は全て 0xFF と
 * なり、逆にいえば 0xFF, 0xFFFF といった設定値を格納できます。
 *
 * @param p 構造体へのアドレス
 */
static void vConfig_UnSetAll(tsFlashApp *p) {
	memset(p, 0xFF, sizeof(tsFlashApp));
}

/** @ingroup FLASH
 * フラッシュ(またはEEPROM)に保存し、モジュールをリセットする
 */
static void vConfig_SaveAndReset() {
	tsFlash sFlash = sAppData.sFlash;

	if (sConfig_UnSaved.u32appid != 0xFFFFFFFF) {
		sFlash.sData.u32appid = sConfig_UnSaved.u32appid;
	}
	if (sConfig_UnSaved.u32chmask != 0xFFFFFFFF) {
		sFlash.sData.u32chmask = sConfig_UnSaved.u32chmask;
	}
	if (sConfig_UnSaved.u8id != 0xFF) {
		sFlash.sData.u8id = sConfig_UnSaved.u8id;
	}
	if (sConfig_UnSaved.u8ch != 0xFF) {
		sFlash.sData.u8ch = sConfig_UnSaved.u8ch;
	}
	if (sConfig_UnSaved.u8pow != 0xFF) {
		sFlash.sData.u8pow = sConfig_UnSaved.u8pow;
	}
	if (sConfig_UnSaved.u8layer != 0xFF) {
		sFlash.sData.u8layer = sConfig_UnSaved.u8layer;
	}
	if (sConfig_UnSaved.u8role != 0xFF) {
		sFlash.sData.u8role = sConfig_UnSaved.u8role;
	}
	if (sConfig_UnSaved.u16SleepDur_ms != 0xFFFF) {
		sFlash.sData.u16SleepDur_ms = sConfig_UnSaved.u16SleepDur_ms;
	}
	if (sConfig_UnSaved.u16SleepDur_s != 0xFFFF) {
		sFlash.sData.u16SleepDur_s = sConfig_UnSaved.u16SleepDur_s;
	}
	if (sConfig_UnSaved.u8Fps != 0xFF) {
		sFlash.sData.u8Fps = sConfig_UnSaved.u8Fps;
	}
	if (sConfig_UnSaved.u32PWM_Hz != 0xFFFFFFFF) {
		sFlash.sData.u32PWM_Hz = sConfig_UnSaved.u32PWM_Hz;
	}
	if (sConfig_UnSaved.u32baud_safe != 0xFFFFFFFF) {
		sFlash.sData.u32baud_safe = sConfig_UnSaved.u32baud_safe;
	}
	if (sConfig_UnSaved.u8parity != 0xFF) {
		sFlash.sData.u8parity = sConfig_UnSaved.u8parity;
	}
	if (sConfig_UnSaved.u32Opt != 0xFFFFFFFF) {
		sFlash.sData.u32Opt = sConfig_UnSaved.u32Opt;
	}
	if (sConfig_UnSaved.u32Opt2 != 0xFFFFFFFF) {
		sFlash.sData.u32Opt2 = sConfig_UnSaved.u32Opt2;
	}
	if (sConfig_UnSaved.u8MML_idx != 0xFF) {
		sFlash.sData.u8MML_idx = sConfig_UnSaved.u8MML_idx;
	}

	sFlash.sData.u32appkey = APP_ID;
	sFlash.sData.u32ver = VERSION_U32;

	bool_t bRet = bFlash_Write(&sFlash, FLASH_SECTOR_NUMBER - 1, 0);
	V_PRINT("!INF FlashWrite %s"LB, bRet ? "Success" : "Failed");
	vConfig_UnSetAll(&sConfig_UnSaved);
	vWait(100000);

	V_PRINT("!INF RESET SYSTEM...");
	vWait(1000000);
	vAHI_SwReset();
}

/** @ingroup MASTER
 * インタラクティブモードの画面を再描画する。
 * - 本関数は TIMER_0 のイベント処理時に u16HoldUpdateScreen カウンタがデクリメントされ、
 *   これが0になった時に呼び出される。
 *
 * - 設定内容、設定値、未セーブマーク*を出力している。FL_... のマクロ記述を参照。
 *
 */
void vSerUpdateScreen() {
	V_PRINT("%c[2J%c[H", 27, 27); // CLEAR SCREEN
	V_PRINT(
			"--- CONFIG/TOCOS TWELITE DIP APP V%d-%02d-%d/SID=0x%08x/LID=0x%02x ---"LB,
			VERSION_MAIN, VERSION_SUB, VERSION_VAR, ToCoNet_u32GetSerial(),
			sAppData.u8AppLogicalId);

	// Application ID
	V_PRINT(" a: set Application ID (0x%08x)%c" LB,
			FL_IS_MODIFIED_u32(appid) ? FL_UNSAVE_u32(appid) : FL_MASTER_u32(appid),
			FL_IS_MODIFIED_u32(appid) ? '*' : ' ');

	// Device ID
	{
		uint8 u8DevID =
				FL_IS_MODIFIED_u8(id) ? FL_UNSAVE_u8(id) : FL_MASTER_u8(id);

		if (u8DevID == 0x00) { // unset
			V_PRINT(" i: set Device ID (--)%c"LB,
					FL_IS_MODIFIED_u8(id) ? '*' : ' ');
		} else {
			V_PRINT(" i: set Device ID (%d=0x%02x)%c"LB, u8DevID, u8DevID,
					FL_IS_MODIFIED_u8(id) ? '*' : ' ');
		}
	}

	V_PRINT(" c: set Channels (");
	{
		// find channels in ch_mask
		uint8 au8ch[MAX_CHANNELS], u8ch_idx = 0;
		int i;
		memset(au8ch, 0, MAX_CHANNELS);
		uint32 u32mask =
				FL_IS_MODIFIED_u32(chmask) ?
						FL_UNSAVE_u32(chmask) : FL_MASTER_u32(chmask);
		for (i = 11; i <= 26; i++) {
			if (u32mask & (1UL << i)) {
				if (u8ch_idx) {
					V_PUTCHAR(',');
				}
				V_PRINT("%d", i);
				au8ch[u8ch_idx++] = i;
			}

			if (u8ch_idx == MAX_CHANNELS) {
				break;
			}
		}
	}
	V_PRINT(")%c" LB, FL_IS_MODIFIED_u32(chmask) ? '*' : ' ');

	V_PRINT(" x: set Tx Power (%d)%c" LB,
			FL_IS_MODIFIED_u8(pow) ? FL_UNSAVE_u8(pow) : FL_MASTER_u8(pow),
			FL_IS_MODIFIED_u8(pow) ? '*' : ' ');

	V_PRINT(" t: set mode4 sleep dur (%dms)%c" LB,
			FL_IS_MODIFIED_u16(SleepDur_ms) ? FL_UNSAVE_u16(SleepDur_ms) : FL_MASTER_u16(SleepDur_ms),
			FL_IS_MODIFIED_u16(SleepDur_ms) ? '*' : ' ');

	V_PRINT(" y: set mode7 sleep dur (%ds)%c" LB,
			FL_IS_MODIFIED_u16(SleepDur_s) ? FL_UNSAVE_u16(SleepDur_s) : FL_MASTER_u16(SleepDur_s),
			FL_IS_MODIFIED_u16(SleepDur_s) ? '*' : ' ');

	V_PRINT(" f: set mode3 fps (%d)%c" LB,
			FL_IS_MODIFIED_u8(Fps) ? FL_UNSAVE_u8(Fps) : FL_MASTER_u8(Fps),
			FL_IS_MODIFIED_u8(Fps) ? '*' : ' ');

	V_PRINT(" z: set PWM HZ (%d)%c" LB,
			FL_IS_MODIFIED_u32(PWM_Hz) ? FL_UNSAVE_u32(PWM_Hz) : FL_MASTER_u32(PWM_Hz),
			FL_IS_MODIFIED_u32(PWM_Hz) ? '*' : ' ');

	V_PRINT(" o: set Option Bits    (0x%08X)%c" LB,
			FL_IS_MODIFIED_u32(Opt) ? FL_UNSAVE_u32(Opt) : FL_MASTER_u32(Opt),
			FL_IS_MODIFIED_u32(Opt) ? '*' : ' ');

	V_PRINT(" O: set Option Bits #2 (0x%08X)%c" LB,
			FL_IS_MODIFIED_u32(Opt2) ? FL_UNSAVE_u32(Opt2) : FL_MASTER_u32(Opt2),
			FL_IS_MODIFIED_u32(Opt2) ? '*' : ' ');

	V_PRINT(" m: set MML index (%d)%c" LB,
			FL_IS_MODIFIED_u8(MML_idx) ? FL_UNSAVE_u8(MML_idx) : FL_MASTER_u8(MML_idx),
			FL_IS_MODIFIED_u8(MML_idx) ? '*' : ' ');

	{
		uint32 u32baud =
				FL_IS_MODIFIED_u32(baud_safe) ?
						FL_UNSAVE_u32(baud_safe) : FL_MASTER_u32(baud_safe);
		if (u32baud & 0x80000000) {
			V_PRINT(" b: set UART baud (%x)%c" LB, u32baud,
					FL_IS_MODIFIED_u32(baud_safe) ? '*' : ' ');
		} else {
			V_PRINT(" b: set UART baud (%d)%c" LB, u32baud,
					FL_IS_MODIFIED_u32(baud_safe) ? '*' : ' ');
		}
	}

	{
		const uint8 au8name[] = { 'N', 'O', 'E' };
		V_PRINT(" p: set UART parity (%c)%c" LB,
				au8name[FL_IS_MODIFIED_u8(parity) ? FL_UNSAVE_u8(parity) : FL_MASTER_u8(parity)],
				FL_IS_MODIFIED_u8(parity) ? '*' : ' ');
	}

	V_PRINT("---"LB);

	V_PRINT(" S: save Configuration" LB " R: reset to Defaults" LB LB);

#ifdef BICYCLEFINDER_SLAVE
	V_PRINT("---"LB);
	V_PRINT(" M: try MML play." LB);
#endif
	//       0123456789+123456789+123456789+1234567894123456789+123456789+123456789+123456789
}

// アプリケーション依存度が高い関数を読み込み
#include "../Source_User/Interactive_User.c"
