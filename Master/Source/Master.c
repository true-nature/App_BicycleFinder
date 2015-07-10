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
#include <stdlib.h>
#include <AppHardwareApi.h>

#include "Master.h"

#include "ccitt8.h"
#include "Interrupt.h"

#include "Version.h"

#include "utils.h"
#include "flash.h"

#include "common.h"
#include "config.h"

// IO Read Options
#include "btnMgr.h"
// ADC
#include "adc.h"
// I2C
#include "SMBus.h"
#include "I2C_impl.h"

// MML 対応
#include "melodies.h"

// 重複チェッカ
#include "duplicate_checker.h"

// Serial options
#include <serial.h>
#include <fprintf.h>
#include <sprintf.h>

#include "sercmd_gen.h"
#include "Interactive.h"

/****************************************************************************/
/***        ToCoNet Definitions                                           ***/
/****************************************************************************/
// Select Modules (define befor include "ToCoNet.h")
#define ToCoNet_USE_MOD_TXRXQUEUE_BIG

// includes
#include "ToCoNet.h"
#include "ToCoNet_mod_prototype.h"

#include "app_event.h"

// 実験的な実装
#include "Experimental.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define BATTERY_LOW_ALARM_VOLT 2400
#define BATTERY_REPEAT_TX_VOLT 2350

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
static void vProcessEvCore(tsEvent *pEv, teEvent eEvent, uint32 u32evarg);
static void vProcessEvCoreSlpSender(tsEvent *pEv, teEvent eEvent, uint32 u32evarg);
static void vProcessEvCorePwr(tsEvent *pEv, teEvent eEvent, uint32 u32evarg);

static void vInitHardware(int f_warm_start);

static void vSerialInit(uint32, tsUartOpt *);
void vProcessSerialCmd(tsSerCmd_Context *pSer);

extern void vHandleSerialInput();
void vSerInitMessage();
extern void vSerUpdateScreen();

static void vReceiveSerMsg(tsRxDataApp *pRx);
static void vReceiveIoData(tsRxDataApp *pRx);
static void vReceiveIoSettingRequest(tsRxDataApp *pRx);

static bool_t bCheckDupPacket(tsDupChk_Context *pc, uint32 u32Addr,
		uint16 u16TimeStamp);

static int16 i16TransmitIoData(bool_t bQuick, bool_t bRegular);
static int16 i16TransmitButtonData(bool_t bQuick, bool_t bRegular, uint8 *bm);
static int16 i16TransmitIoSettingRequest(uint8 u8DstAddr, tsIOSetReq *pReq);
static void vTransmitMmlData(void);

static uint16 u16GetAve(uint16 *pu16k, uint8 u8Scale);
static bool_t bUpdateAdcValues();

static void vSleep(uint32 u32SleepDur_ms, bool_t bPeriodic, bool_t bDeep);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
tsAppData sAppData; //!< アプリケーションデータ  @ingroup MASTER

tsFILE sSerStream; //!< シリアル出力ストリーム  @ingroup MASTER
tsSerialPortSetup sSerPort; //!< シリアルポートの設定  @ingroup MASTER

tsSerSeq sSerSeqTx; //!< 分割パケット管理構造体（送信用）  @ingroup MASTER
tsSerSeq sSerSeqRx; //!< 分割パケット管理構造体（受信用）  @ingroup MASTER
uint8 au8SerBuffRx[SERCMD_MAXPAYLOAD + 32]; //!< sSerSeqRx 用に確保  @ingroup MASTER
tsInpStr_Context sSerInpStr; //!< 文字列入力  @ingroup MASTER

extern uint16 u16HoldUpdateScreen; //!< スクリーンアップデートを行う遅延カウンタ  @ingroup MASTER

tsTimerContext sTimerApp; //!< タイマー管理構造体  @ingroup MASTER
tsTimerContext sTimerPWM[4]; //!< タイマー管理構造体  @ingroup MASTER

uint8 au8SerOutBuff[128]; //!< シリアルの出力書式のための暫定バッファ  @ingroup MASTER

tsDupChk_Context sDupChk_IoData; //!< 重複チェック(IO関連のデータ転送)  @ingroup MASTER
tsDupChk_Context sDupChk_SerMsg; //!< 重複チェック(シリアル関連のデータ転送)  @ingroup MASTER

/****************************************************************************/
/***        FUNCTIONS                                                     ***/
/****************************************************************************/

/** @ingroup MASTER
 * アプリケーションの基本制御状態マシン。
 * - 特別な処理は無い。
 *
 * @param pEv
 * @param eEvent
 * @param u32evarg
 */
static void vProcessEvCore(tsEvent *pEv, teEvent eEvent, uint32 u32evarg) {
	switch (pEv->eState) {
	case E_STATE_IDLE:
		if (eEvent == E_EVENT_START_UP) {
#ifdef USE_BROWN_OUT_DETECT
# ifdef JN516x
			// BrownOut 検出の有効化
			vAHI_BrownOutConfigure(
					1,// 1:2.0V, 4:2.3V
					TRUE,
					TRUE,
					FALSE,
					FALSE);

			//
			vAHI_WatchdogStop();
			vAHI_WatchdogStart(4);
# endif
#endif

			if (IS_APPCONF_ROLE_SILENT_MODE()) {
				vfPrintf(&sSerStream, LB"!Note: launch silent mode."LB);
				ToCoNet_Event_SetState(pEv, E_STATE_RUNNING);
			} else {
				// LayerNetwork で無ければ、特別な動作は不要。
				// run as default...

				// 始動メッセージの表示
				if (!(u32evarg & EVARG_START_UP_WAKEUP_MASK)) {
					vSerInitMessage();
				}

				// RUNNING 状態へ遷移
				ToCoNet_Event_SetState(pEv, E_STATE_RUNNING);
			}

			break;
		}

		break;

	case E_STATE_RUNNING:
		break;
	default:
		break;
	}
}

/** @ingroup MASTER
 * アプリケーション制御（電源常時 ON モード）
 * - 機能概要
 *   - 起動時にランダムで処理を保留する（同時起動による送信パケットの競合回避のため）
 *   - 初回のDI/AD状態確定まで待つ
 *   - 実行状態では E_EVENT_APP_TICK_A (64fps タイマーイベント) を起点に処理する。
 *     - 32fps のタイミングで送信判定を行う
 *     - 定期パケット送信後は、次回のタイミングを乱数によってブレを作る。
 *
 * - 状態一覧
 *   - E_STATE_IDLE\n
 *     起動直後に呼び出される状態で、同時起動によるパケット衝突を避けるためランダムなウェイトを置き、次の状態に遷移する。
 *   - E_STATE_APP_WAIT_IO_FIRST_CAPTURE\n
 *     初回に DI および AI の入力値が確定するまでの待ちを行い、E_STATE_RUNNING に遷移する。
 *   - E_STATE_RUNNING
 *     秒６４回のタイマー割り込み (E_EVENT_TICK_A) を受けて、入力状態の変化のチェックを行い、無線パケットの送信要求を
 *     発行する。各種判定条件があるので、詳細はコード中のコメント参照。
 *
 * @param pEv
 * @param eEvent
 * @param u32evarg
 */
void vProcessEvCorePwr(tsEvent *pEv, teEvent eEvent, uint32 u32evarg) {
	switch (pEv->eState) {
	case E_STATE_IDLE:
		if (eEvent == E_EVENT_START_UP) {
			sAppData.u16CtRndCt = 0;

			/* Initialize the Interactive mode */
			Interactive_vInit();
		}

		if (eEvent == E_EVENT_TICK_TIMER) {
			static bool_t bStarted = FALSE;

			if (!sAppData.u16CtRndCt) {
				sAppData.u8AdcState = 0; // ADC の開始
				bStarted = TRUE;
				sAppData.u16CtRndCt = (ToCoNet_u16GetRand() & 0xFF) + 10; // 始動時にランダムで少し待つ（同時電源投入でぶつからないように）
			}
		}

		// 始動時ランダムな待ちを置く
		if (sAppData.u16CtRndCt
				&& PRSEV_u32TickFrNewState(pEv) > sAppData.u16CtRndCt) {
			ToCoNet_Event_SetState(pEv, E_STATE_APP_WAIT_IO_FIRST_CAPTURE);
			sAppData.u16CtRndCt = 32; // この変数は定期送信のタイミング用に再利用する。
		}

		break;

	case E_STATE_APP_WAIT_IO_FIRST_CAPTURE:
		// 起動直後の未確定状態
		if (eEvent == E_EVENT_APP_TICK_A) {
			if (sAppData.u8IOFixState == 0x03) {
				if (IS_APPCONF_OPT_DIO_LOW_ON_BOOT() || IS_APPCONF_OPT_PWM_LOW_ON_BOOT()) {
					ToCoNet_Event_SetState(pEv, E_STATE_APP_SET_INITIAL_ON);
				} else {
					ToCoNet_Event_SetState(pEv, E_STATE_RUNNING);
				}
			} else {
				int i;

				// 起動後から最初の定期送信までの間 au16InputADC_LastTx[] に値が入らない。
				for (i = 0; i < 4; i++) {
					sAppData.sIOData_now.au16InputADC_LastTx[i] =
							sAppData.sIOData_now.au16InputADC[i];
				}
			}
		}
		break;

	case E_STATE_APP_SET_INITIAL_ON:
		// 始動時に一定時間全ポートをLoに設定する
		if (eEvent == E_EVENT_NEW_STATE) {
			if (IS_APPCONF_OPT_DIO_LOW_ON_BOOT()) {
				vPortSetLo(PORT_OUT1);
				vPortSetLo(PORT_OUT2);
				vPortSetLo(PORT_OUT3);
				vPortSetLo(PORT_OUT4);
			}

			if (IS_APPCONF_OPT_PWM_LOW_ON_BOOT()) {
				int i;
				for (i = 0; i < 4; i++) {
					sTimerPWM[i].u16duty = _PWM(0);
					vTimerStart(&sTimerPWM[i]); // DUTY比だけ変更する
				}
			}
		}

		if (PRSEV_u32TickFrNewState(pEv) > 2000) {
			if (IS_APPCONF_OPT_DIO_LOW_ON_BOOT()) {
				vPortSetHi(PORT_OUT1);
				vPortSetHi(PORT_OUT2);
				vPortSetHi(PORT_OUT3);
				vPortSetHi(PORT_OUT4);
			}

			if (IS_APPCONF_OPT_PWM_LOW_ON_BOOT()) {
				int i;
				for (i = 0; i < 4; i++) {
					sTimerPWM[i].u16duty = _PWM(1024);
					vTimerStart(&sTimerPWM[i]); // DUTY比だけ変更する
				}
			}

			ToCoNet_Event_SetState(pEv, E_STATE_RUNNING);
		}
		break;

	case E_STATE_RUNNING:

#ifdef INCREASE_ADC_INTERVAL_ms
#define APPT_TICK_A_MASK ~0
#else
#define APPT_TICK_A_MASK 1
#endif
		if (eEvent == E_EVENT_APP_TICK_A // 秒64回のタイマー割り込み
		&& (sAppData.u32CtTimer0 & APPT_TICK_A_MASK) // 秒32回にする
				) {
			// 変更が有った場合は送信する
			int i;
			bool_t bCond = FALSE;
			bool_t bRegular = FALSE;

			if (sAppData.u16CtRndCt)
				sAppData.u16CtRndCt--; // 定期パケット送信までのカウントダウン

			// ボタンに変化あり
			if (!bCond && sAppData.sIOData_now.u32BtmChanged) {
				bCond = TRUE;
			}

			// ADC に変化あり
			if (!bCond && !IS_APPCONF_OPT_NO_ADC_BASED_TRANSMIT() && sAppData.bUpdatedAdc) {
				bCond = TRUE;
			}

			// レギュラー送信  // TODO レギュラー送信しないオプション
			if (!bCond && (sAppData.u16CtRndCt == 0)) {
				if (!IS_APPCONF_OPT_REGULAR_PACKET_NO_TRANSMIT()) {
					bCond = TRUE;
					bRegular = TRUE;
				}
			}

			// 送信
			if (bCond) {
				// デバッグ出力
				DBGOUT(5,
						"A(%02d/%04d)%d%d: v=%04d A1=%04d/%04d A2=%04d/%04d B=%d%d%d%d %08x"LB,
						sAppData.u32CtTimer0, u32TickCount_ms & 8191,
						sAppData.bUpdatedAdc ? 1 : 0,
						sAppData.sIOData_now.u32BtmChanged ? 1 : 0,
						sAppData.sIOData_now.u16Volt,
						sAppData.sIOData_now.au16InputADC[0],
						sAppData.sIOData_now.au16InputPWMDuty[0] >> 2,
						sAppData.sIOData_now.au16InputADC[1],
						sAppData.sIOData_now.au16InputPWMDuty[1] >> 2,
						sAppData.sIOData_now.au8Input[0] & 1,
						sAppData.sIOData_now.au8Input[1] & 1,
						sAppData.sIOData_now.au8Input[2] & 1,
						sAppData.sIOData_now.au8Input[3] & 1,
						sAppData.sIOData_now.u32BtmBitmap);

				// 低遅延送信が必要かどうかの判定
				bool_t bQuick = FALSE;
				if (sAppData.sIOData_now.u32BtmChanged
						&& (sAppData.sFlash.sData.u32Opt
								& E_APPCONF_OPT_LOW_LATENCY_INPUT)) {
					bQuick = TRUE;
				}

				// 送信要求
				sAppData.sIOData_now.i16TxCbId = i16TransmitIoData(bQuick, bRegular);

				// 変更フラグのクリア
				sAppData.bUpdatedAdc = FALSE;
				sAppData.sIOData_now.u32BtmChanged = 0;

				// AD履歴の保存
				for (i = 0; i < 4; i++) {
					sAppData.sIOData_now.au16InputADC_LastTx[i] =
							sAppData.sIOData_now.au16InputADC[i];
				}

				// 次の定期パケットのタイミングを仕込む
				sAppData.u16CtRndCt = (ToCoNet_u16GetRand() & 0xF) + 24;
			}
		}
		break;

	default:
		break;
	}
}

void vUpdateMmlIndex() {
	// 次の選曲インデックスを更新
	sAppData.sFlash.sData.u8MML_idx++;
	if (sAppData.sFlash.sData.u8MML_idx >= MMLBANK_COUNT) {
		sAppData.sFlash.sData.u8MML_idx = 0;
	}
	bool_t bRet = bFlash_Write(&sAppData.sFlash, FLASH_SECTOR_NUMBER - 1, 0);
	V_PRINT("!INF FlashWrite %s"LB, bRet ? "Success" : "Failed");
}

/**  @ingroup MASTER
 * アプリケーション制御（自転車発見器モード、リモコン側）\n
  * @param pEv
 * @param eEvent
 * @param u32evarg
 */
static void vProcessEvCoreSlpSender(tsEvent *pEv, teEvent eEvent, uint32 u32evarg) {
	static uint8 u8bm;
	switch (pEv->eState) {
	case E_STATE_IDLE:
		if (eEvent == E_EVENT_START_UP) {
			// vfPrintf(&sSerStream, "START_UP eEvent=%X, evarg=%X, button=%X"LB, eEvent, u32evarg, sAppData.bWakeupByButton);
			if (u32evarg & EVARG_START_UP_WAKEUP_MASK) {
				// スリープからの復帰時の場合
				vfPrintf(&sSerStream, "!INF %s WAKE UP. @%dms"LB,
						sAppData.bWakeupByButton ? "DI" : "TIMER", u32TickCount_ms);
			}
			sAppData.u8AdcState = 0; // ADC の開始
			sAppData.u32AdcLastTick = u32TickCount_ms;
			u8bm = 0;	// ボタン状態をクリア

			ToCoNet_Event_SetState(pEv, E_STATE_RUNNING);
		}
		break;

	case E_STATE_RUNNING:
		DBGOUT(3, "%d", sAppData.u8IOFixState);

		// IO状態の確定後、チャタリングが落ち着くのを待って送信する。
		if (sAppData.u8IOFixState == 0x3 && PRSEV_u32TickFrNewState(pEv) > 20) {
			if (sAppData.sIOData_now.u32BtmBitmap != 0) {
				vfPrintf(&sSerStream,
						"!INF DI1-4:%d%d%d%d A1-4:%04d/%04d/%04d/%04d @%dms"LB,
						sAppData.sIOData_now.au8Input[0] & 1,
						sAppData.sIOData_now.au8Input[1] & 1,
						sAppData.sIOData_now.au8Input[2] & 1,
						sAppData.sIOData_now.au8Input[3] & 1,
						sAppData.sIOData_now.au16InputADC[0] == 0xFFFF ?
								9999 : sAppData.sIOData_now.au16InputADC[0],
						sAppData.sIOData_now.au16InputADC[1] == 0xFFFF ?
								9999 : sAppData.sIOData_now.au16InputADC[1],
						sAppData.sIOData_now.au16InputADC[2] == 0xFFFF ?
								9999 : sAppData.sIOData_now.au16InputADC[2],
						sAppData.sIOData_now.au16InputADC[3] == 0xFFFF ?
								9999 : sAppData.sIOData_now.au16InputADC[3], u32TickCount_ms);

				sAppData.sIOData_now.i16TxCbId = i16TransmitButtonData(TRUE, FALSE, &u8bm);
				// 完了待ちをするため CbId を保存する。
				// TODO: この時点で失敗した場合は、次の状態のタイムアウトで処理されるが非効率である。
				ToCoNet_Event_SetState(pEv, E_STATE_WAIT_TX);
			} else {
				// ボタンが押されていなければチャタリングとみなす
				vfPrintf(&sSerStream, "!Detected bounce. @%dms"LB, u32TickCount_ms);
				ToCoNet_Event_SetState(pEv, E_STATE_FINISHED);
			}
		}
		break;
	case E_STATE_WAIT_TX:
		if (eEvent == E_EVENT_APP_TX_COMPLETE) {
			if (sAppData.u32SleepDur == 0					// ボタンで起床
				&& sAppData.sIOData_now.u16Volt >= BATTERY_REPEAT_TX_VOLT) {
				// 電圧が低い(==EDLC充電不足)ならば連続送信しない。
				// stay this state
			} else {
				// 点灯を抑止
				ToCoNet_Event_SetState(pEv, E_STATE_FINISHED);
			}
		} else if (eEvent == E_EVENT_APP_TICK_A  // 秒64回のタイマー割り込み
				&& (sAppData.u32CtTimer0 & 1) // 秒32回にする
				) {
			// 対抗のスリープ間隔を跨いで連続送信
			sAppData.sIOData_now.i16TxCbId = i16TransmitButtonData(TRUE, FALSE, &u8bm);
		} else if (eEvent == E_EVENT_APP_SEND_MML) {
			// HwEventから発せられたMML書き換え要求
			ToCoNet_Event_SetState(pEv, E_STATE_APP_SEND_MML);
		}
		_C {
			static uint32 mask, duty;
			if (eEvent == E_EVENT_NEW_STATE) {
				vfPrintf(&sSerStream, "!INF BATTTERY SELF:%dmV"LB, sAppData.sIOData_now.u16Volt, u32TickCount_ms);
				// 送信中は約1秒周期でDO4のLED点滅, 自機の電池残量が少なければ250ms周期の早い点滅
				mask = (1 << (sAppData.sIOData_now.u16Volt < 2500 ? 8 : 10)) - 1;
				duty = mask >> 2;
			}
			vPortSet_TrueAsLo(PORT_OUT4, (u32TickCount_ms & mask) <= duty);
		}
		int duration = (u8bm == 0x08 ? 100UL : (sAppData.sFlash.sData.u16SleepDur_ms + 500));
		if ((u32TickCount_ms - sAppData.u32AdcLastTick) >  duration) {
			vfPrintf(&sSerStream, "!INF WAIT_TX TIMEOUT %d > %d. @%dms"LB, (u32TickCount_ms - sAppData.u32AdcLastTick), duration, u32TickCount_ms);
			ToCoNet_Event_SetState(pEv, E_STATE_FINISHED);
		}
		break;

	case E_STATE_APP_SEND_MML:
		// MML書き換え要求
		if (eEvent == E_EVENT_NEW_STATE) {
			DBGOUT(1, LB"E_STATE_APP_SEND_MML E_EVENT_NEW_STATE");
		}
		else if (eEvent == E_EVENT_APP_TICK_A && PRSEV_u32TickFrNewState(pEv) > 100) {
			DBGOUT(1, LB"E_STATE_APP_SEND_MML vTransmitMmlData()");
			vTransmitMmlData();
			ToCoNet_Event_SetState(pEv, E_STATE_APP_WAIT_TX_MML);
		}
		break;

	case E_STATE_APP_WAIT_TX_MML:
		// MML書き換え要求
		if (eEvent == E_EVENT_NEW_STATE) {
			// 次の選曲インデックスを更新
			vUpdateMmlIndex();
		}
		else if (eEvent == E_EVENT_APP_TX_COMPLETE ) {
			DBGOUT(1, LB"E_STATE_APP_WAIT_TX_MML E_EVENT_APP_TX_COMPLETE");
			ToCoNet_Event_SetState(pEv, E_STATE_FINISHED);
		}
		else if (E_EVENT_APP_TICK_A && PRSEV_u32TickFrNewState(pEv) > 500) {
			DBGOUT(1, LB"E_STATE_APP_WAIT_TX_MML expiration");
			ToCoNet_Event_SetState(pEv, E_STATE_FINISHED);
		}
		break;

	case E_STATE_FINISHED:
		_C {
			if (eEvent == E_EVENT_NEW_STATE) {
				vfPrintf(&sSerStream, "!INF SLEEP %dms @%dms."LB,
						sAppData.u32SleepDur, u32TickCount_ms);
				SERIAL_vFlush(sSerStream.u8Device);
				vPortSetHi(PORT_OUT4);
			}
			ToCoNet_Event_SetState(pEv, E_STATE_APP_SLEEPING);
		}
		break;

	case E_STATE_APP_SLEEPING:
		if (eEvent == E_EVENT_NEW_STATE) {
			vSleep(sAppData.u32SleepDur, TRUE, (sAppData.u32SleepDur == 0));
		}

		break;

	default:
		break;
	}
}

/** @ingroup MASTER
 * 電源投入時・リセット時に最初に実行される処理。本関数は２回呼び出される。初回は u32AHI_Init()前、
 * ２回目は AHI 初期化後である。
 *
 * - 各種初期化
 * - ToCoNet ネットワーク設定
 * - 設定IO読み取り
 * - 緊急フラッシュ消去処理
 * - 設定値の計算
 * - ハードウェア初期化
 * - イベントマシンの登録
 * - 本関数終了後は登録したイベントマシン、および cbToCoNet_vMain() など各種コールバック関数が
 *   呼び出される。
 *
 * @param bStart TRUE:u32AHI_Init() 後の呼び出し FALSE: 前
 */
void cbAppColdStart(bool_t bStart) {
	if (!bStart) {
		// Module Registration
		ToCoNet_REG_MOD_ALL();
	} else {
		// disable brown out detect
		vAHI_BrownOutConfigure(0,//0:1.95V 1:2.0V(default), 2:2.1V, 3:2.2V, 4:2.3V
				FALSE,	// bVboRestEn
				FALSE,	// bVboEn
				FALSE,	// bVboIntEnFalling, bVboIntEnRising
				FALSE);

#ifdef ENABLE_BICYCLE_FINDER
		// リセットICの無効化
		vPortSetLo(DIO_VOLTAGE_CHECKER);
		vPortAsOutput(DIO_VOLTAGE_CHECKER);
		vPortDisablePullup(DIO_VOLTAGE_CHECKER);
#endif

		// メモリのクリア
		memset(&sAppData, 0x00, sizeof(sAppData));
		memset(&sAppData.sIOData_now, 0xFF, sizeof(tsIOData));
		memset(&sAppData.sIOData_reserve, 0xFF, sizeof(tsIOData));
		Interactive_vInit();

		// デフォルトのネットワーク指定値
		sToCoNet_AppContext.u8TxMacRetry = 3; // MAC再送回数（JN516x では変更できない）
		sToCoNet_AppContext.u32AppId = APP_ID; // アプリケーションID
		sToCoNet_AppContext.u32ChMask = CHMASK; // 利用するチャネル群（最大３つまで）
		sToCoNet_AppContext.u8Channel = CHANNEL; // デフォルトのチャネル

		// フラッシュの読み出し
		sAppData.bFlashLoaded = Config_bLoad(&sAppData.sFlash);

		// Version String のチェック
		if (sAppData.bFlashLoaded
				&& ((APP_ID != sAppData.sFlash.sData.u32appkey)
						|| (VERSION_U32 != sAppData.sFlash.sData.u32ver))) {
			sAppData.bFlashLoaded = FALSE;
		}

		// フラッシュ設定値の反映
		if (sAppData.bFlashLoaded) {
			sToCoNet_AppContext.u32AppId = sAppData.sFlash.sData.u32appid;
			sToCoNet_AppContext.u8Channel = sAppData.sFlash.sData.u8ch; // チャネルマネージャで決定するので設定不要とされているが復帰
			sToCoNet_AppContext.u32ChMask = sAppData.sFlash.sData.u32chmask;
			sToCoNet_AppContext.u8TxPower = sAppData.sFlash.sData.u8pow; // 出力の設定

			if (sAppData.sFlash.sData.u8role == E_APPCONF_ROLE_MAC_NODE) {
				sAppData.eNwkMode = E_NWKMODE_MAC_DIRECT;
			} else if (sAppData.sFlash.sData.u8role == E_APPCONF_ROLE_SILENT) {
				sAppData.eNwkMode = E_NWKMODE_MAC_DIRECT;
			} else {
				sAppData.bFlashLoaded = 0;
			}

			if (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_LOW_LATENCY_INPUT) {
				sToCoNet_AppContext.u16TickHz = 1000; // 低レイテンシモードでは 1KHz 動作
			}
		}

		// ヘッダの１バイト識別子を AppID から計算
		sAppData.u8AppIdentifier = u8CCITT8(
				(uint8*) &sToCoNet_AppContext.u32AppId, 4); // APP ID の CRC8

		// IOより状態を読み取る (ID など)
		sAppData.u32DIO_startup = ~u32PortReadBitmap(); // この時点では全部入力ポート

		// 緊急のフラッシュ消去モード
		if ((0 == (sAppData.u32DIO_startup & (1UL << PORT_CONF1)))
				&& (sAppData.u32DIO_startup & (1UL << PORT_CONF2))
				&& (sAppData.u32DIO_startup & (1UL << PORT_CONF3))
				&& (sAppData.u32DIO_startup & (1UL << 15))
				&& (sAppData.u32DIO_startup & (1UL << PORT_INPUT4))) {
			//中継機設定で、I2C ポートが Lo で起動する
			uint32 u32ct = 0;

			vPortAsOutput(PORT_OUT1);

			for (;;) {
				sAppData.u32DIO_startup = ~u32PortReadBitmap();

				if ((sAppData.u32DIO_startup & (1UL << 15))
						&& (sAppData.u32DIO_startup & (1UL << PORT_INPUT4))) {
					u32ct++;

					vPortSet_TrueAsLo(PORT_OUT1, u32ct & 0x8000);

					if (u32ct > 800000) { // some seconds
						bFlash_Erase(FLASH_SECTOR_NUMBER - 1); // SECTOR ERASE

						vPortSetHi(PORT_OUT1);

						while (1) {
							u32ct++;
							vPortSet_TrueAsLo(PORT_OUT1, u32ct & 0x80000);
						}
					}
				} else {
					// may launch as normal mode
					break;
				}
			}
		}

		// version info
		sAppData.u32ToCoNetVersion = ToCoNet_u32GetVersion();

		// ToCoNet の制御 Tick [ms]
		sAppData.u16ToCoNetTickDelta_ms = 1000 / sToCoNet_AppContext.u16TickHz;

		// その他ハードウェアの初期化
		vInitHardware(FALSE);

		// 論理IDの設定チェック、その他設定値のチェック
		//  IO の設定を優先し、フラッシュ設定で矛盾するものについてはデフォルト値を書き直す。
		if (IS_LOGICAL_ID_CHILD(au8IoModeTbl_To_LogicalID[sAppData.u8Mode])) {
			// 子機IDはフラッシュ値が設定されていれば、これを採用
			if (sAppData.bFlashLoaded) {
				sAppData.u8AppLogicalId = sAppData.sFlash.sData.u8id;
			}
		}

		// 各モード依存の初期値の設定など
		if (!sAppData.u32SleepDur) {
			if (sAppData.bFlashLoaded) {
				sAppData.u32SleepDur = sAppData.sFlash.sData.u16SleepDur_s
						* 1000L;
			} else {
				sAppData.u32SleepDur = MODE7_SLEEP_DUR_ms;
			}
		}

		// その他設定
		if (IS_APPCONF_OPT_ROUTING_HOP2()) {
			sAppData.u8max_hops = 2;
		} else if (IS_APPCONF_OPT_ROUTING_HOP3()) {
			sAppData.u8max_hops = 3;
		} else {
			sAppData.u8max_hops = 1;
		}

		// ショートアドレスの設定(決めうち)
		sToCoNet_AppContext.u16ShortAddress =
				SERCMD_ADDR_CONV_TO_SHORT_ADDR(sAppData.u8AppLogicalId);

		// UART の初期化
		ToCoNet_vDebugInit(&sSerStream);
		ToCoNet_vDebugLevel(0);

		// その他の初期化
		DUPCHK_vInit(&sDupChk_IoData); // 重複チェック用
		DUPCHK_vInit(&sDupChk_SerMsg); // 重複チェック用

		if (!(IS_APPCONF_ROLE_SILENT_MODE())) {
			// 状態遷移マシンの登録
			if (sAppData.bConfigMode) {
				ToCoNet_Event_Register_State_Machine(vProcessEvCorePwr); // 常時通電用の処理
				sAppData.prPrsEv = (void*) vProcessEvCorePwr;
				sToCoNet_AppContext.bRxOnIdle = TRUE;
			} else {
				ToCoNet_Event_Register_State_Machine(vProcessEvCoreSlpSender); // スリープ用の処理
				sAppData.prPrsEv = (void*) vProcessEvCoreSlpSender;
				sToCoNet_AppContext.bRxOnIdle = FALSE;
			}

			// MAC の初期化
			ToCoNet_vMacStart();

			// 主状態遷移マシンの登録
			sAppData.u8Hnd_vProcessEvCore = ToCoNet_Event_Register_State_Machine(vProcessEvCore);
		}
	}
}


/** @ingroup MASTER
 * スリープ復帰後に呼び出される関数。\n
 * 本関数も cbAppColdStart() と同様に２回呼び出され、u32AHI_Init() 前の
 * 初回呼び出しに於いて、スリープ復帰要因を判定している。u32AHI_Init() 関数は
 * これらのレジスタを初期化してしまう。
 *
 * - 変数の初期化（必要なもののみ）
 * - ハードウェアの初期化（スリープ後は基本的に再初期化が必要）
 * - イベントマシンは登録済み。
 *
 * @param bStart TRUE:u32AHI_Init() 後の呼び出し FALSE: 前
 */
void cbAppWarmStart(bool_t bStart) {
	if (!bStart) {
		// before AHI init, very first of code.
		//  to check interrupt source, etc.

		sAppData.bWakeupByButton = FALSE;
		if (u8AHI_WakeTimerFiredStatus()) {
			;
		} else if (u32AHI_DioWakeStatus()
				& ((1UL << PORT_INPUT1) | (1UL << PORT_INPUT2)
						| (1UL << PORT_INPUT3) | (1UL << PORT_INPUT4))) {
			// woke up from DIO events
			sAppData.bWakeupByButton = TRUE;
		}

	} else {
		// データ領域の初期化
		memset(&sAppData.sIOData_now, 0xFF, sizeof(tsIOData));

		// いくつかのデータは復元
		sAppData.sIOData_now.u32BtmUsed = sAppData.sIOData_reserve.u32BtmUsed;
		memcpy(sAppData.sIOData_now.au16InputADC_LastTx,
				sAppData.sIOData_reserve.au16InputADC_LastTx,
				sizeof(sAppData.sIOData_now.au16InputADC_LastTx));
#ifdef INCREASE_ADC_INTERVAL_ms
		sAppData.sIOData_now.u16Volt = sAppData.sIOData_reserve.u16Volt;
#endif

		// 変数の初期化（必要なものだけ）
		sAppData.u16CtTimer0 = 0; // このカウンタは、起動時からのカウントとする
		sAppData.u8IOFixState = FALSE; // IO読み取り状態の確定待ちフラグ
		sAppData.bUpdatedAdc = 0; // ADCの変化フラグ

		// その他ハードウェアの初期化（基本、起動時に毎回実行する）
		vInitHardware(TRUE);

		// UART の初期化
		ToCoNet_vDebugInit(&sSerStream);
		ToCoNet_vDebugLevel(0);

		// その他の初期化
		DUPCHK_vInit(&sDupChk_IoData);
		DUPCHK_vInit(&sDupChk_SerMsg);

		// MAC の開始
		ToCoNet_vMacStart();
	}
}

/** @ingroup MASTER
 * 本関数は ToCoNet のメインループ内で必ず１回は呼び出される。
 * ToCoNet のメインループでは、CPU DOZE 命令を発行しているため、割り込みなどが発生した時に
 * 呼び出されるが、処理が無い時には呼び出されない。
 * しかし TICK TIMER の割り込みは定期的に発生しているため、定期処理としても使用可能である。
 *
 * - シリアルの入力チェック
 */
void cbToCoNet_vMain(void) {
	vHandleSerialInput(); // シリアルポートの処理
}

/** @ingroup MASTER
 * パケットの受信完了時に呼び出されるコールバック関数。\n
 * パケットの種別によって具体的な処理関数にディスパッチしている。
 * データ種別は psRx->u8Cmd (ToCoNet のパケットヘッダに含まれます) により識別される。
 *
 * - パケット種別
 *   - TOCONET_PACKET_CMD_APP_DATA : シリアル電文パケット
 *   - TOCONET_PACKET_CMD_APP_USER_IO_DATA : IO状態の伝送
 *   - TOCONET_PACKET_CMD_APP_USER_IO_DATA_EXT : シリアル電文による IO 状態の伝送
 *   - TOCONET_PACKET_CMD_APP_USER_MML_DATA : シリアル電文による MMLデータの伝送
 *
 * @param psRx 受信パケット
 */
void cbToCoNet_vRxEvent(tsRxDataApp *psRx) {
	//uint8 *p = pRx->auData;

	DBGOUT(3, "Rx packet (cm:%02x, fr:%08x, to:%08x)"LB, psRx->u8Cmd,
			psRx->u32SrcAddr, psRx->u32DstAddr);

	if (IS_APPCONF_ROLE_SILENT_MODE()
			// SILENTでは受信処理はしない。
			|| sAppData.u8Mode == E_IO_MODE_CHILD_SLP_10SEC
			// 10秒スリープでは受信処理はしない。
			// TODO: 受信機の電池切れを送信機で検出するための受信処理
			) {
		return;
	}

	switch (psRx->u8Cmd) {
	case TOCONET_PACKET_CMD_APP_DATA: // シリアルメッセージのパケット
		vReceiveSerMsg(psRx);
		break;
	case TOCONET_PACKET_CMD_APP_USER_IO_DATA: // IO状態の伝送
		if (PRSEV_eGetStateH(sAppData.u8Hnd_vProcessEvCore) == E_STATE_RUNNING) { // 稼動状態でパケット処理をする
			vReceiveIoData(psRx);
		}
		break;
	case TOCONET_PACKET_CMD_APP_USER_IO_DATA_EXT: // IO状態の伝送(UART経由)
		if (PRSEV_eGetStateH(sAppData.u8Hnd_vProcessEvCore) == E_STATE_RUNNING) { // 稼動状態でパケット処理をする
			vReceiveIoSettingRequest(psRx);
		}
		break;
	}
}

/** @ingroup MASTER
 * 送信完了時に呼び出されるコールバック関数。
 *
 * - IO 送信完了イベントはイベントマシンにE_EVENT_APP_TX_COMPLETEイベントを伝達する。
 * - シリアルメッセージの一連のパケット群の送信完了も検出しsSerSeqTx.bWaitComplete
 *   フラグをリセットする。
 *
 * @param u8CbId 送信時に設定したコールバックID
 * @param bStatus 送信ステータス
 */
void cbToCoNet_vTxEvent(uint8 u8CbId, uint8 bStatus) {
	//uint8 *q = au8SerOutBuff;
	if (IS_APPCONF_ROLE_SILENT_MODE()) {
		return;
	}

	// IO 関連の送信が完了した
	if (sAppData.sIOData_now.i16TxCbId >= 0
			&& u8CbId == sAppData.sIOData_now.i16TxCbId) {
		// スリープを行う場合は、このイベントを持ってスリープ遷移
		ToCoNet_Event_Process(E_EVENT_APP_TX_COMPLETE, u8CbId,
				sAppData.prPrsEv);
	}

	// UART 送信の完了チェック
	if (sSerSeqTx.bWaitComplete) {
		if (u8CbId >= sSerSeqTx.u8Seq
				&& u8CbId < sSerSeqTx.u8Seq + sSerSeqTx.u8PktNum) {
			uint8 idx = u8CbId - sSerSeqTx.u8Seq;
			if (bStatus) {
				sSerSeqTx.bPktStatus[idx] = 1;
			} else {
				if (sSerSeqTx.bPktStatus[idx] == 0) {
					sSerSeqTx.bPktStatus[idx] = -1;
				}
			}
		}

		int i, isum = 0;
		for (i = 0; i < sSerSeqTx.u8PktNum; i++) {
			if (sSerSeqTx.bPktStatus[i] == 0)
				break;
			isum += sSerSeqTx.bPktStatus[i];
		}

		if (i == sSerSeqTx.u8PktNum) {
			/* 送信完了 (MAC レベルで成功した) */
			sSerSeqTx.bWaitComplete = FALSE;

			// VERBOSE MESSAGE
			DBGOUT(3, "* >>> MacAck%s(tick=%d,req=#%d) <<<" LB,
					(isum == sSerSeqTx.u8PktNum) ? "" : "Fail",
					u32TickCount_ms & 65535, sSerSeqTx.u8ReqNum);
		}
	}

	return;
}

/** @ingroup MASTER
 * ネットワーク層などのイベントが通達される。\n
 * 本アプリケーションでは特別な処理は行っていない。
 *
 * @param ev
 * @param u32evarg
 */
void cbToCoNet_vNwkEvent(teEvent ev, uint32 u32evarg) {
	if (IS_APPCONF_ROLE_SILENT_MODE()) {
		return;
	}

	switch (ev) {
	case E_EVENT_TOCONET_NWK_START:
		break;

	case E_EVENT_TOCONET_NWK_DISCONNECT:
		break;

	default:
		break;
	}
}

/** @ingroup MASTER
 * ハードウェア割り込み時に呼び出される。本処理は割り込みハンドラではなく、割り込みハンドラに登録された遅延実行部による処理で、長い処理が記述可能である。
 * 本アプリケーションに於いては、ADC/DIの入力状態のチェック、64fps のタイマーイベントの処理などを行っている。
 *
 * - E_AHI_DEVICE_SYSCTRL
 *   - DI割り込みの処理を行う。これは、低レイテンシモードでの処理である。
 *
 * - E_AHI_DEVICE_TICK_TIMER : このイベントは ToCoNet 組み込みで、ToCoNet の制御周期 (sToCoNet_AppContext.u16TickHz) を
 *   実現するためのタイマーです。ユーザが TickTimer の制御を変更したりすると ToCoNet は動作しなくなります。
 *
 *   - Di入力の変化の確認。変化が有れば、sAppData.sIOData_now 構造体に結果を格納する。
 *     低レイテンシモードの時は、この判定を起点として送信を行う。
 *
 * - E_AHI_DEVICE_TIMER0 : TICK_TIMER から分周して制御周期を作っても良いのですが、TIMER_0 を使用しています。
 *   - カウンタのインクリメント処理
 *   - ADC の完了確認
 *   - パケット重複チェックアルゴリズムのタイムアウト処理
 *   - DIのカウンタ処理 (インタラクティブモードでカウンタ終了時にもパケットを送信する処理を行う）
 *   - イベントマシンに TIMER0 イベントを発行
 *   - インタラクティブモード時の画面再描画
 *
 * @param u32DeviceId
 * @param u32ItemBitmap
 */
void cbToCoNet_vHwEvent(uint32 u32DeviceId, uint32 u32ItemBitmap) {
	switch (u32DeviceId) {
	case E_AHI_DEVICE_SYSCTRL:
		if (sAppData.u8IOFixState) {
			int i;
			bool_t bTransmit = FALSE;

			/* DIの入力ピンの番号を調べる。
			 *
			 *  ボタンを猿みたいに押してみたが DIO の割り込みは同時に２ビット報告されることは無く、
			 *  順 次処理されるようだ。しかしながら、同時処理されても良いようなコードにしておく。
			 */
			DBGOUT(1, LB"BTN: ");
			for (i = 0; i < 4; i++) {
				/* DI検知したポートについては sAppData.sIOData_now.au8Input[] に値を設定する。
				 *
				 * この値の下位１ビットが、１になると Lo 判定したことを意味する。
				 * この値の上位４ビットは、再度の割り込みを検知しても無視するためのカウンタとして
				 * 用いる。このカウンタは E_AHI_DEVICE_TIMER0 イベントで処理する。
				 */
				DBGOUT(1, "%c",
						u32ItemBitmap & (1UL << au8PortTbl_DIn[i]) ? '1' : '0');

				if (u32ItemBitmap & (1UL << au8PortTbl_DIn[i])) { // 押し下げを検知したポート
					uint8 u8stat = sAppData.sIOData_now.au8Input[i]; // 元の値を取り出す。
					uint8 u8ct = (u8stat & 0xF0) >> 4; // 上位４ビットは、前回の同様の割り込み受信からの 64fps カウンタ

					// カウンタ値が無い場合は、個の割り込みを有効とする。
					if (u8ct == 0) {
						sAppData.sIOData_now.au8Input[i] =
								(LOW_LATENCY_DELAYED_TRANSMIT_COUNTER * 0x10)
										+ 1;
						bTransmit = TRUE;
					} else {
						// カウンタ値が有る場合は、直前に押されたためチャタリングなどが考えられ処理しない
						;
					}
				}
			}

			// いずれかのポートの割り込みが有効であった場合。
			if (bTransmit) {
				/* 速やかに送信する
				 *   ポートの変更対象フラグを、この割り込みで入力検知したものとする。
				 *   そうしないと、関係ないビットが変更されてしまう
				 */
				uint32 u32used = sAppData.sIOData_now.u32BtmUsed; // 関数呼び出し中だけ値を変更する
				sAppData.sIOData_now.u32BtmUsed = u32ItemBitmap
						& PORT_INPUT_MASK; // 割り込みでLoになったDINだけ変更対照として送信する
				int i;
				uint8 u8bm = 0;

				for (i = 0; i < 4; i++) {
					uint8 u8ct = sAppData.sIOData_now.au8Input[i] >> 4;

					if (u8ct >= LOW_LATENCY_DELAYED_TRANSMIT_COUNTER - 3) { // カウンタ値が残っている場合は 1 を送る
						u8bm |= (1 << i);
					} else {
						u8bm |= (sAppData.sIOData_now.au8Input[i] & 1) ? (1 << i) : 0;
					}
				}
				DBGOUT(1, "vHwEven u8bm:%x", u8bm);
				if (u8bm == 0x09) {
					// イベント処理部分にイベントを送信
					if (sAppData.prPrsEv) {
						ToCoNet_Event_Process(E_EVENT_APP_SEND_MML, 0, sAppData.prPrsEv);
					}
				} else {
					sAppData.sIOData_now.i16TxCbId = i16TransmitButtonData(TRUE, FALSE, &u8bm); // 送信処理を行う
				}
				sAppData.sIOData_now.u32BtmUsed = u32used
						| (u32ItemBitmap & PORT_INPUT_MASK); //値を復元する
			}
		}
		break;

	case E_AHI_DEVICE_ANALOGUE: //ADC完了時にこのイベントが発生する。
		break;

	case E_AHI_DEVICE_TICK_TIMER: //比較的頻繁な処理
		// ボタンの判定を行う。
		_C {
			uint32 bmPorts, bmChanged, i;
			if (bBTM_GetState(&bmPorts, &bmChanged)) {

				// 読み出し値を格納する
				for (i = 0; i < 4; i++) {
					uint8 u8stat =
							sAppData.sIOData_now.au8Input[i] == 0xFF ?
									0 : sAppData.sIOData_now.au8Input[i];
					// LSBを設定する
					if (bmPorts & (1UL << au8PortTbl_DIn[i])) {
						u8stat |= 0x01;
					} else {
						u8stat &= 0xFE;
					}
					sAppData.sIOData_now.au8Input[i] = u8stat;
				}
				sAppData.sIOData_now.u32BtmBitmap = bmPorts; // au8Input と冗長だが両方管理する。

				if (bmChanged) { // 入力ポートの値が確定したか、変化があった
					// 利用入力ポートの判定
					if (sAppData.sIOData_now.u32BtmUsed == 0xFFFFFFFF) {
						sAppData.sIOData_now.u32BtmUsed = bmPorts; // 一番最初の確定時に Lo のポートは利用ポート
					} else {
						sAppData.sIOData_now.u32BtmUsed |= bmPorts; // 利用ポートのビットマップは一度でもLo確定したポート
					}

					// 変化ポートの判定
					if (sAppData.u8IOFixState & 1) {
						// 初回確定後
						sAppData.sIOData_now.u32BtmChanged |= bmChanged; // 変化フラグはアプリケーションタスクに変更させる
					} else {
						// 初回確定時(スリープ復帰後も含む)
						sAppData.sIOData_now.u32BtmChanged = bmChanged; // 初回は変化を報告
					}

					// IO確定ビットを立てる
					sAppData.u8IOFixState |= 0x1;
				}
			}

			// 低レイテンシモードならここで送信を行う。
			if (sAppData.u8IOFixState && sAppData.sIOData_now.u32BtmChanged
					&& (sAppData.sFlash.sData.u32Opt
							& E_APPCONF_OPT_LOW_LATENCY_INPUT)) {
				sAppData.sIOData_now.i16TxCbId = i16TransmitIoData(TRUE, FALSE);
				sAppData.sIOData_now.u32BtmChanged = 0;
			}
		}
		break;

	case E_AHI_DEVICE_TIMER0:
		// タイマーカウンタをインクリメントする (64fps なので 64カウントごとに１秒)
		sAppData.u32CtTimer0++;
		sAppData.u16CtTimer0++;

		// ADC の完了確認
		if (sAppData.u8AdcState == 0x80) {
			sAppData.u8AdcState = 0; // ADC の開始
		}

		// 重複チェックのタイムアウト処理
		if ((sAppData.u32CtTimer0 & 0xF) == 0) {
			DUPCHK_bFind(&sDupChk_IoData, 0, NULL );
			DUPCHK_bFind(&sDupChk_SerMsg, 0, NULL );
		}

		// 送信処理のタイムアウト処理
		if (sSerSeqTx.bWaitComplete) {
			if (u32TickCount_ms - sSerSeqTx.u32Tick > 1000) {
				// タイムアウトとして、処理を続行
				memset(&sSerSeqTx, 0, sizeof(sSerSeqTx));
			}
		}

		/* インタラクティブモードのカウンタ処理。
		 * カウンタが0になったときに送信フラグを立てる。
		 * 1.3.4 カウンタが0までは押し下げフラグを維持
		 */
		{
			int i;

			// Input ビットのカウンタビットをカウントダウンする。
			bool_t bUpdated = FALSE;
			for (i = 0; i < 4; i++) {
				uint8 u8stat = sAppData.sIOData_now.au8Input[i];
				if (u8stat == 0xFF)
					continue;

				uint8 u8ct = u8stat >> 4;

				if (u8ct) {
					u8ct--;
					if (u8ct == 0) {
						// 送信要求
						bUpdated = TRUE;
					}
				}

				u8stat = (u8ct << 4) + (u8stat & 0x0F);
				sAppData.sIOData_now.au8Input[i] = u8stat;
			}
			if (bUpdated) {
				sAppData.sIOData_now.u32BtmChanged |= 0x80000000;
			}
		}

		// イベント処理部分にイベントを送信
		if (sAppData.prPrsEv && (sAppData.u32CtTimer0 & 1)) {
			ToCoNet_Event_Process(E_EVENT_APP_TICK_A, 0, sAppData.prPrsEv);
		}

		// シリアル画面制御のためのカウンタ
		if (!(--u16HoldUpdateScreen)) {
			if (Interactive_bGetMode()) {
				vSerUpdateScreen();
			}
		}
		break;

	default:
		break;
	}
}

/** @ingroup MASTER
 * 割り込みハンドラ。ここでは長い処理は記述してはいけない。
 *
 * - TIMER_0\n
 *   - JN514x での DAC 出力
 * - TICK_TIMER\n
 *   - ADCの実行管理
 *   - ボタン入力判定管理
 */
PUBLIC uint8 cbToCoNet_u8HwInt(uint32 u32DeviceId, uint32 u32ItemBitmap) {
	uint8 u8handled = FALSE;

	switch (u32DeviceId) {
	case E_AHI_DEVICE_TIMER0:
		break;

	case E_AHI_DEVICE_ANALOGUE:
		// ADCの計測値を速やかに読みだす
		u16ADC_ReadReg(&sAppData.sObjADC);
		break;

	case E_AHI_DEVICE_TICK_TIMER:
		if (sAppData.u8AdcState != 0xFF) { // 0xFF は準備中
			switch (sAppData.u8AdcState) {
			case 0:
				vSnsObj_Process(&sAppData.sADC, E_ORDER_KICK);
				sAppData.u8AdcState++;
				break;

			case 1:
				vSnsObj_Process(&sAppData.sADC, E_ORDER_KICK);

				if (bSnsObj_isComplete(&sAppData.sADC)) {
					// ADC値を処理する。
					bool_t bUpdated = bUpdateAdcValues();

					if ((sAppData.u8IOFixState & 2) == 0) {
						sAppData.bUpdatedAdc = 0;

						// 確定情報
						sAppData.u8IOFixState |= 0x2;
					} else {
						if (!IS_APPCONF_OPT_NO_ADC_BASED_TRANSMIT()) {
							sAppData.bUpdatedAdc |= bUpdated;
						}
					}

#if defined(JN514x)
					sAppData.u8AdcState++;
#else
					sAppData.u8AdcState = 0x80; // 完了ステータス
#endif
				}
				break;

			case 2:
#if defined(JN514x)
				// DAC の出力を行う (周期的なリフレッシュ)
				if (bAHI_APRegulatorEnabled()) {
					vAHI_DacOutput(E_AHI_AP_DAC_1, sAppData.sIOData_now.au16OutputDAC_val[0]);
				}
#endif

				sAppData.u8AdcState++;
				break;

			case 3:
#if defined(JN514x)
				// DAC の出力を行う (周期的なリフレッシュ)
				if (bAHI_APRegulatorEnabled()) {
					vAHI_DacOutput(E_AHI_AP_DAC_2, sAppData.sIOData_now.au16OutputDAC_val[1]);
				}
#endif

				sAppData.u8AdcState = 0x80; // 完了ステータス
				break;

			case 0x80:
				break;

			default:
				break;
			}
		}

		// ボタンハンドラの駆動
		if (sAppData.pr_BTM_handler) {
			// ハンドラを稼働させる
			(*sAppData.pr_BTM_handler)(sAppData.u16ToCoNetTickDelta_ms);
		}
		break;

	default:
		break;
	}

	return u8handled;
}

/** @ingroup MASTER
 * ハードウェアの初期化を行う。スリープ復帰時も原則同じ初期化手続きを行う。
 *
 * - 管理構造体のメモリ領域の初期化
 * - DO出力設定
 * - DI入力設定
 * - DI割り込み設定 (低レイテンシモード)
 * - M1-M3 の読み込み
 * - UARTの初期化
 * - ADC3/4 のプルアップ停止
 * - タイマー用の未使用ポートを汎用IOに解放する宣言
 * - 秒64回のTIMER0の初期化と稼働
 * - ADC/DAC(JN514x)/PWM の初期化
 * - I2Cの初期化
 *
 * @param f_warm_start TRUE:スリープ復帰時
 */PRIVATE void vInitHardware(int f_warm_start) {
	int i;

	// メモリのクリア
	memset(&sTimerApp, 0, sizeof(tsTimerContext));
	memset(&sTimerPWM[0], 0, sizeof(tsTimerContext));
	memset(&sTimerPWM[1], 0, sizeof(tsTimerContext));
	memset(&sTimerPWM[2], 0, sizeof(tsTimerContext));
	memset(&sTimerPWM[3], 0, sizeof(tsTimerContext));

	// 出力の設定
#define INIT_PORT_OUT_START_IDX 1
	for (i = INIT_PORT_OUT_START_IDX; i < 4; i++) {
		vPortAsOutput(au8PortTbl_DOut[i]);
		if (sAppData.sIOData_reserve.au8Output[i] != 0xFF) {
			vPortSet_TrueAsLo(au8PortTbl_DOut[i],
					sAppData.sIOData_reserve.au8Output[i]);
		} else {
			vPortSetHi(au8PortTbl_DOut[i]);
		}
	}

	// 入力の設定
	for (i = 0; i < 4; i++) {
		vPortAsInput(au8PortTbl_DIn[i]);
	}

	// v1.3 低レイテンシで入力を行う処理
	if (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_LOW_LATENCY_INPUT) {
		// 割り込みを有効にする
		vAHI_DioInterruptEnable(PORT_INPUT_MASK, 0); // 割り込みの登録
		vAHI_DioInterruptEdge(0, PORT_INPUT_MASK); // 割り込みエッジの登録
	}

	// モード設定
	vPortAsInput(PORT_CONF1);
	vPortAsInput(PORT_CONF2);
	vPortAsInput(PORT_CONF3);
	sAppData.u8Mode = E_IO_MODE_CHILD_SLP_10SEC;	// 送信機は10秒スリープモードに固定
	if (!f_warm_start) {
		if (bPortRead(PORT_CONF1)) {
			sAppData.bConfigMode = TRUE;
			// モード設定ピンで Lo になっているポートはプルアップ停止
			// Lo でない場合は、プルアップ停止をするとリーク電流が発生する
			vPortDisablePullup(PORT_CONF1);
		}
	}

	// UART 設定
	{
		vPortAsInput(PORT_BAUD);

		uint32 u32baud = bPortRead(PORT_BAUD) ? UART_BAUD_SAFE : UART_BAUD;
		tsUartOpt sUartOpt;

		memset(&sUartOpt, 0, sizeof(tsUartOpt));

		// BAUD ピンが GND になっている場合、かつフラッシュの設定が有効な場合は、設定値を採用する (v1.0.3)
		if (sAppData.bFlashLoaded && bPortRead(PORT_BAUD)) {
			u32baud = sAppData.sFlash.sData.u32baud_safe;
			sUartOpt.bHwFlowEnabled = FALSE;
			sUartOpt.bParityEnabled = UART_PARITY_ENABLE;
			sUartOpt.u8ParityType = UART_PARITY_TYPE;
			sUartOpt.u8StopBit = UART_STOPBITS;

			// 設定されている場合は、設定値を採用する (v1.0.3)
			switch (sAppData.sFlash.sData.u8parity) {
			case 0:
				sUartOpt.bParityEnabled = FALSE;
				break;
			case 1:
				sUartOpt.bParityEnabled = TRUE;
				sUartOpt.u8ParityType = E_AHI_UART_ODD_PARITY;
				break;
			case 2:
				sUartOpt.bParityEnabled = TRUE;
				sUartOpt.u8ParityType = E_AHI_UART_EVEN_PARITY;
				break;
			}

			vSerialInit(u32baud, &sUartOpt);
		} else {
			vSerialInit(u32baud, NULL );
		}

	}

	// ADC3/4 のピンのプルアップを廃止する
#ifdef JN516x // v1.0.3
	vPortDisablePullup(0);
	vPortDisablePullup(1);
#endif

	// Opt2 設定によるプルアップ停止
	{
		int i;

		// DI のプルアップ停止 (Opt2 の bit0-3)
		for (i = 0; i < 4; i++) {
			if (sAppData.sFlash.sData.u32Opt2 & (1UL << i)) {
				vPortDisablePullup(au8PortTbl_DIn[i]);
			}
		}

		// DO のプルアップ停止 (Opt2 の bit4-7)
		for (i = 0; i < 4; i++) {
			if (sAppData.sFlash.sData.u32Opt2 & (1UL << (i+4))) {
				vPortDisablePullup(au8PortTbl_DOut[i]);
			}
		}
	}

	// タイマの未使用ポートの解放（汎用ＩＯとして使用するため）
#ifdef JN516x
	vAHI_TimerFineGrainDIOControl(0x7); // bit 0,1,2 をセット (TIMER0 の各ピンを解放する, PWM1..4 は使用する)
#else
#ifdef ON_PRESS_TRANSMIT
			vAHI_TimerFineGrainDIOControl(0x7F); // PWM出力は無効に
#else
			vAHI_TimerFineGrainDIOControl(0x1F); // PWM1, PWM2 のみ対応
#endif
#endif

	// 秒64回のTIMER0の初期化と稼働
	sTimerApp.u8Device = E_AHI_DEVICE_TIMER0;
	sTimerApp.u16Hz = 64;
	sTimerApp.u8PreScale = 4; // 15625ct@2^4
#if 0 //debug setting
			sTimerApp.u16Hz = 1;
			sTimerApp.u8PreScale = 10;// 15625ct@2^4
#endif
	vTimerConfig(&sTimerApp);
	vTimerStart(&sTimerApp);

	// button Manager (for Input)
	sAppData.sBTM_Config.bmPortMask = (1UL << PORT_INPUT1) | (1UL << PORT_INPUT2) | (1UL << PORT_INPUT3) | (1UL << PORT_INPUT4);

	if (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_LOW_LATENCY_INPUT) {
		sAppData.sBTM_Config.u16Tick_ms = 1;
	} else {
		sAppData.sBTM_Config.u16Tick_ms = 4;
	}
	sAppData.sBTM_Config.u8MaxHistory = 5;
	sAppData.sBTM_Config.u8DeviceTimer = 0xFF; // TickTimer を流用する。
	sAppData.pr_BTM_handler = prBTM_InitExternal(&sAppData.sBTM_Config);
	vBTM_Enable();

	// ADC
	vADC_Init(&sAppData.sObjADC, &sAppData.sADC, TRUE);
	sAppData.u8AdcState = 0xFF; // 初期化中
	if (IS_APPCONF_OPT_DISABLE_ADC()) {
		// 動作時間短縮のため電源電圧以外はAD変換しない
		sAppData.sObjADC.u8SourceMask = TEH_ADC_SRC_VOLT;
	} else {
		sAppData.sObjADC.u8SourceMask = TEH_ADC_SRC_VOLT | TEH_ADC_SRC_TEMP
				| TEH_ADC_SRC_ADC_1 | TEH_ADC_SRC_ADC_2 | TEH_ADC_SRC_ADC_3
				| TEH_ADC_SRC_ADC_4;
	}

	// DAC
#if defined(JN514x)
	vAHI_DacEnable(E_AHI_AP_DAC_1, E_AHI_AP_INPUT_RANGE_2, FALSE, 0);
	vAHI_DacEnable(E_AHI_AP_DAC_2, E_AHI_AP_INPUT_RANGE_2, FALSE, 0);
#endif

	// PWM
	uint16 u16PWM_Hz = sAppData.sFlash.sData.u32PWM_Hz; // PWM周波数
	uint8 u8PWM_prescale = 0; // prescaleの設定
	if (u16PWM_Hz < 10)
		u8PWM_prescale = 9;
	else if (u16PWM_Hz < 100)
		u8PWM_prescale = 6;
	else if (u16PWM_Hz < 1000)
		u8PWM_prescale = 3;
	else
		u8PWM_prescale = 0;

	uint16 u16pwm_duty_default = IS_APPCONF_OPT_PWM_INIT_LOW() ? 0 : 1024; // 起動時のデフォルト
	for (i = 0; i < 4; i++) {
		sTimerPWM[i].u16Hz = u16PWM_Hz;
		sTimerPWM[i].u8PreScale = u8PWM_prescale;
		sTimerPWM[i].u16duty =
				sAppData.sIOData_reserve.au16InputPWMDuty[i] == 0xFFFF ?
						u16pwm_duty_default : _PWM(sAppData.sIOData_reserve.au16InputPWMDuty[i]);
		sTimerPWM[i].bPWMout = TRUE;
		sTimerPWM[i].bDisableInt = TRUE; // 割り込みを禁止する指定
	}

#if defined(JN514x)
	// 0, 1 は使用せず DAC を使用する。
	sTimerPWM[2].u8Device = E_AHI_DEVICE_TIMER1;
	sTimerPWM[3].u8Device = E_AHI_DEVICE_TIMER2;
	vTimerConfig(&sTimerPWM[2]);
	vTimerStart(&sTimerPWM[2]);
	vTimerConfig(&sTimerPWM[3]);
	vTimerStart(&sTimerPWM[3]);
#elif defined(JN516x)
	vAHI_TimerSetLocation(E_AHI_TIMER_1, TRUE, TRUE);

	sTimerPWM[0].u8Device = E_AHI_DEVICE_TIMER1;
	sTimerPWM[1].u8Device = E_AHI_DEVICE_TIMER2;
	sTimerPWM[2].u8Device = E_AHI_DEVICE_TIMER3;
	sTimerPWM[3].u8Device = E_AHI_DEVICE_TIMER4;

	for (i = 0; i < 4; i++) {
		vTimerConfig(&sTimerPWM[i]);
		vTimerStart(&sTimerPWM[i]);
	}
#endif

	// I2C
	vSMBusInit();
}

/** @ingroup MASTER
 * UART を初期化する
 * @param u32Baud ボーレート
 */
void vSerialInit(uint32 u32Baud, tsUartOpt *pUartOpt) {
	/* Create the debug port transmit and receive queues */
	static uint8 au8SerialTxBuffer[2560];
	static uint8 au8SerialRxBuffer[2560];

	/* Initialise the serial port to be used for debug output */
	sSerPort.pu8SerialRxQueueBuffer = au8SerialRxBuffer;
	sSerPort.pu8SerialTxQueueBuffer = au8SerialTxBuffer;
	sSerPort.u32BaudRate = u32Baud;
	sSerPort.u16AHI_UART_RTS_LOW = 0xffff;
	sSerPort.u16AHI_UART_RTS_HIGH = 0xffff;
	sSerPort.u16SerialRxQueueSize = sizeof(au8SerialRxBuffer);
	sSerPort.u16SerialTxQueueSize = sizeof(au8SerialTxBuffer);
	sSerPort.u8SerialPort = UART_PORT_MASTER;
	sSerPort.u8RX_FIFO_LEVEL = E_AHI_UART_FIFO_LEVEL_1;
	SERIAL_vInitEx(&sSerPort, pUartOpt);

	/* prepare stream for vfPrintf */
	sSerStream.bPutChar = SERIAL_bTxChar;
	sSerStream.u8Device = UART_PORT_MASTER;

	/* other initialization */
	INPSTR_vInit(&sSerInpStr, &sSerStream);
	memset(&sSerSeqTx, 0x00, sizeof(sSerSeqTx));
	memset(&sSerSeqRx, 0x00, sizeof(sSerSeqRx));
}

/** @ingroup MASTER
 * 始動時メッセージの表示を行う。
 */
void vSerInitMessage() {
	vfPrintf(&sSerStream,
			LB"!INF TOCOS TWELITE DIP APP V%d-%02d-%d, SID=0x%08X, LID=0x%02x"LB,
			VERSION_MAIN, VERSION_SUB, VERSION_VAR, ToCoNet_u32GetSerial(),
			sAppData.u8AppLogicalId);
	if (sAppData.bFlashLoaded == 0) {
		vfPrintf(&sSerStream, "!INF Default config (no save info)..." LB);
	}
#if defined(JN514x)
	vfPrintf(&sSerStream, "!INF DIO --> %021b"LB, sAppData.u32DIO_startup);
#elif defined(JN516x)
	vfPrintf(&sSerStream, "!INF DIO --> %020b"LB, sAppData.u32DIO_startup);
#endif
	if (IS_APPCONF_ROLE_SILENT_MODE()) {
		vfPrintf(&sSerStream, "!ERR SILENT MODE" LB);
	}
}

/** @ingroup MASTER
 * シリアルから入力されたコマンド形式の電文を処理します。
 *
 * - 先頭バイトがアドレス指定で、0xDB 指定の場合、自モジュールに対しての指令となります。
 * - ２バイト目がコマンドで、0x80 以降を指定します。0x7F 以下は特別な処理は割り当てられていません。
 * - コマンド(0xDB向け)
 *   - SERCMD_ID_GET_MODULE_ADDRESS\n
 *     モジュールのシリアル番号を取得する
 * - コマンド(外部アドレス向け)
 *   - SERCMD_ID_REQUEST_IO_DATA\n
 *     IO状態の設定
 *   - それ以外のコマンドID\n
 *     通常送信 (ただし 0x80 以降は今後の機能追加で意味が変わる可能性あり)
 *
 * @param pSer シリアルコマンド入力の管理構造体
 */
void vProcessSerialCmd(tsSerCmd_Context *pSer) {
	uint8 *p = pSer->au8data;

	uint8 u8addr; // 送信先論理アドレス
	uint8 u8cmd; // コマンド

	uint8 *p_end;
	p_end = &(pSer->au8data[pSer->u16len]); // the end points 1 byte after the data end.

	bool_t bTransmitRfPacket = FALSE;

	// COMMON FORMAT
	OCTET(u8addr); // [1] OCTET : 論理ID
	OCTET(u8cmd); // [1] OCTET : 要求番号

	DBGOUT(3, "* UARTCMD ln=%d cmd=%02x req=%02x %02x%0x2%02x%02x..." LB,
			pSer->u16len, u8addr, u8cmd, *p, *(p + 1), *(p + 2), *(p + 3));

	if (u8addr == SERCMD_ADDR_TO_MODULE) {
		/*
		 * モジュール自身へのコマンド (0xDB)
		 */
		switch (u8cmd) {
		case SERCMD_ID_GET_MODULE_ADDRESS:
			vModbOut_MySerial(&sSerStream);
			break;

		case SERCMD_ID_I2C_COMMAND:
			vProcessI2CCommand(pSer->au8data, pSer->u16len, SERCMD_ADDR_TO_MODULE);
			break;

#if 0 // 各種設定コマンド(未実装)
			case SERCMD_ID_SET_NETWORK_CONFIG:
			/*
			 * 設定を読み出して Flash に書き込む。
			 */
			_C {
				bool_t bRet = FALSE;

				bRet = bModbIn_Config(pSer->au8data, &sAppData.sFlash.sData);

				// フラッシュへの書き込み
				if (bRet && bFlash_Write(&sAppData.sFlash, FLASH_SECTOR_NUMBER - 1, 0)) {
					vModbOut_AckNack(&sSerStream, TRUE);
					vWait(100000);
					vAHI_SwReset(); // リセットする
				} else {
					V_PRINT(LB "Failed to flash write...");
					vModbOut_AckNack(&sSerStream, FALSE);
				}
			}
			break;

			case SERCMD_ID_GET_NETWORK_CONFIG:
			if (sAppData.bFlashLoaded) {
				vModbOut_Config(&sSerStream, &sAppData.sFlash.sData);
			} else {
				vModbOut_AckNack(&sSerStream, FALSE);
			}
			break;
#endif

		default:
			break;
		}
	} else {
		/*
		 * 外部アドレスへの送信(IO情報の設定要求)
		 */
		if (u8cmd == SERCMD_ID_REQUEST_IO_DATA) {
			/*
			 * OCTET: 書式 (0x01)
			 * OCTET: 出力状態
			 * OCTET: 出力状態マスク
			 * BE_WORD: PWM1
			 * BE_WORD: PWM2
			 * BE_WORD: PWM3
			 * BE_WORD: PWM4
			 */
			uint8 u8format = G_OCTET();

			if (u8format == 0x01) {
				tsIOSetReq sIOreq;
				memset(&sIOreq, 0, sizeof(tsIOSetReq));

				sIOreq.u8IOports = G_OCTET();
				sIOreq.u8IOports_use_mask = G_OCTET();

				int i;

				for (i = 0; i < 4; i++) {
					sIOreq.au16PWM_Duty[i] = G_BE_WORD();
				}

				if (p_end < p)
					return; // v1.1.3 (終端チェック)

				DBGOUT(1, "SERCMD:IO REQ: %02x %02x %04x:%04x:%04x:%04x"LB,
						sIOreq.u8IOports, sIOreq.u8IOports_use_mask,
						sIOreq.au16PWM_Duty[0], sIOreq.au16PWM_Duty[1],
						sIOreq.au16PWM_Duty[2], sIOreq.au16PWM_Duty[3]);

				i16TransmitIoSettingRequest(u8addr, &sIOreq);
			}

			return;
		}

		/*
		 * 書式なしデータ送信
		 */
		if (sAppData.u8AppLogicalId != u8addr) {
			// 自分宛でないなら送る
			bTransmitRfPacket = TRUE;
		}
	}

	// 無線パケットを送信する
	if (bTransmitRfPacket) {
		bool_t bDoNotTransmit = FALSE;

		p = pSer->au8data; // バッファの先頭からそのまま送る
		uint16 u16len = p_end - p;

		DBGOUT(3, "* len = %d" LB, u16len);

		if (u16len > SERCMD_SER_PKTLEN * SERCMD_SER_PKTNUM || u16len <= 1) {
			// パケットが長過ぎる、または短すぎる
			bDoNotTransmit = TRUE;
		}

		if (!bDoNotTransmit) {
			// 送信リクエスト
			i16TransmitSerMsg(p, u16len, ToCoNet_u32GetSerial(),
					sAppData.u8AppLogicalId, p[0], FALSE,
					sAppData.u8UartReqNum++);
		}
	}
}

/** @ingroup MASTER
 * 重複パケットの判定。タイムスタンプの比較で、ごく最近であって旧いパケットを除外する。
 *
 * - 注意点
 *   - DUPCHK_vInin() の初期化を行うこと
 *   - DUPCHK_bFIND(0,NULL) を一定周期で呼び出すこと
 *
 * @param pc 管理構造体
 * @param u32Addr
 * @param u16TimeStamp
 * @return TRUE:重複している FALSE:新しいパケットが来た
 */
static bool_t bCheckDupPacket(tsDupChk_Context *pc, uint32 u32Addr,
		uint16 u16TimeStamp) {
	uint32 u32Key;
	if (DUPCHK_bFind(pc, u32Addr, &u32Key)) {
		// 最後に受けたカウンタの値が得られるので、これより新しい
		uint16 u16Delta = ((uint16) u32Key - u16TimeStamp) & 0x7FFF; // 最上位ビットは設定されない
		if (u16Delta < 32) { // 32count=500ms, 500ms の遅延は想定外だが。
			// すでに処理したパケット
			return TRUE;
		}
	}

	// 新しいパケットである（時間情報を格納する）
	DUPCHK_vAdd(pc, u32Addr, u16TimeStamp);
	return FALSE;
}

/** @ingroup MASTER
 * IO 情報を送信します。
 *
 * - IO状態の変化、および１秒置きの定期送時に呼び出されます。
 *
 * - Packet 構造
 *   - OCTET: 識別ヘッダ(APP ID より生成)
 *   - OCTET: プロトコルバージョン(バージョン間干渉しないための識別子)
 *   - OCTET: 送信元論理ID
 *   - BE_DWORD: 送信元のシリアル番号
 *   - OCTET: 宛先論理ID
 *   - BE_WORD: 送信タイムスタンプ (64fps カウンタの値の下１６ビット, 約1000秒で１周する)
 *   - OCTET: 中継フラグ(中継したパケットは１、最初の送信なら０を格納）
 *   - BE_WORD: 電圧
 *   - OCTET: 温度 (int8型)  ※ TODO: 値が不正確。ADC 値から温度への変換式がメーカより開示されないため。
 *   - OCTET: ボタン (LSB から順に SW1 ... SW4, 1=Lo), 0x80ビットは通常送信の識別用フラグ
 *   - OCTET: ボタン変化 (LSB から順に SW1 ... SW4, 1=変化)
 *   - OCTET: ADC1 (MSB から 8bit)
 *   - OCTET: ADC2 (MSB から 8bit)
 *   - OCTET: ADC3 (MSB から 8bit)
 *   - OCTET: ADC4 (MSB から 8bit)
 *   - OCTET: ADC 詳細部 (MSB b8b7b6b5b4b3b2b1 LSB とすると b2b1 が ADC1 の LSB 2bit, 以下同様)
 *
 * - ADC 値の復元方法
 *   - 8bit ADC値の場合 16倍すると mV 値になります。
 *   - ADC詳細部の2bitを追加し 10bit ADC 値の場合 4 倍すると mV 値なります。
 *
 * @returns -1:ERROR, 0..255 CBID
 */
static int16 i16TransmitIoData(bool_t bQuick, bool_t bRegular) {
	if (IS_APPCONF_ROLE_SILENT_MODE())
		return -1;

	int16 i16Ret = -1;
	tsTxDataApp sTx;
	memset(&sTx, 0, sizeof(sTx));

	uint8 *q = sTx.auData;

	int i;

	// ペイロードを構成
	S_OCTET(sAppData.u8AppIdentifier);
	S_OCTET(APP_PROTOCOL_VERSION);
	S_OCTET(sAppData.u8AppLogicalId); // アプリケーション論理アドレス
	S_BE_DWORD(ToCoNet_u32GetSerial());  // シリアル番号

	S_OCTET(LOGICAL_ID_CHILDREN); // 宛先は常に子機
	S_BE_WORD((sAppData.u32CtTimer0 & 0x7FFF) + (bQuick == TRUE ? 0x8000 : 0)); // タイムスタンプ
	// bQuick 転送する場合は MSB をセットし、優先パケットである処理を行う
	S_OCTET(0); // 中継フラグ

	S_BE_WORD(sAppData.sIOData_now.u16Volt); // 電圧

	// チップ内温度センサーの予定だったが・・・
	S_OCTET((uint8)((sAppData.sIOData_now.i16Temp + 50)/100)); //チップ内温度センサー(TWE-Liteでは正しく動作しない)

	// ボタンのビットマップ
	{
		int i;
		uint8 u8bm = 0;

		for (i = 0; i < 4; i++) {
			uint8 u8ct = sAppData.sIOData_now.au8Input[i] >> 4;

			if (u8ct >= LOW_LATENCY_DELAYED_TRANSMIT_COUNTER - 3) { // カウンタ値が残っている場合は 1 を送る
				u8bm |= (1 << i);
			} else {
				u8bm |= (sAppData.sIOData_now.au8Input[i] & 1) ? (1 << i) : 0;
			}
		}

		if (bRegular) u8bm |= 0x80; // MSB を設定

		S_OCTET(u8bm);
	}

	// ボタンのビットマップ使用フラグ (１度でもLoになったポートは１になる）
	S_OCTET(
			( (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT1) ? 1 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT2) ? 2 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT3) ? 4 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT4) ? 8 : 0) ));

	// ADC 部のエンコード
	uint8 u8LSBs = 0;
	for (i = 0; i < 4; i++) {
		// MSB 部分 (10bit目～3bit目まで)
		uint16 u16v = sAppData.sIOData_now.au16InputADC[i];
		u16v >>= 2; // ADC 値は 0...2400mV

		uint8 u8MSB = (u16v >> 2) & 0xFF;
		S_OCTET(u8MSB);

		// 下2bitを u8LSBs に詰める
		u8LSBs >>= 2;
		u8LSBs |= ((u16v << 6) & 0xC0); //
	}
	S_OCTET(u8LSBs); // 詳細ビット部分を記録

	sTx.u8Len = q - sTx.auData; // パケット長
	sTx.u8Cmd = TOCONET_PACKET_CMD_APP_USER_IO_DATA; // パケット種別

	// 送信する
	sTx.u32DstAddr = TOCONET_MAC_ADDR_BROADCAST; // ブロードキャスト
	sTx.u8Retry = 0x81; // 1回再送

	// フレームカウントとコールバック識別子の指定
	sAppData.u16TxFrame++;
	sTx.u8Seq = (sAppData.u16TxFrame & 0xFF);
	sTx.u8CbId = sTx.u8Seq;

	{
		/* MAC モードでは細かい指定が可能 */
		sTx.bAckReq = FALSE;
		sTx.u32SrcAddr = sToCoNet_AppContext.u16ShortAddress;
		sTx.u16RetryDur = bQuick ? 0 : 4; // 再送間隔
		sTx.u16DelayMax = bQuick ? 0 : 16; // 衝突を抑制するため送信タイミングにブレを作る(最大16ms)

		// 送信API
		if (ToCoNet_bMacTxReq(&sTx)) {
			i16Ret = sTx.u8CbId;
			sAppData.sIOData_now.u32TxLastTick = u32TickCount_ms;
		}
	}

	return i16Ret;
}

static int16 i16TransmitButtonData(bool_t bQuick, bool_t bRegular, uint8 *bm) {
	if (IS_APPCONF_ROLE_SILENT_MODE() || bm == NULL)
		return -1;

	int16 i16Ret = -1;
	tsTxDataApp sTx;
	memset(&sTx, 0, sizeof(sTx));

	uint8 *q = sTx.auData;

	int i;

	// ペイロードを構成
	S_OCTET(sAppData.u8AppIdentifier);
	S_OCTET(APP_PROTOCOL_VERSION);
	S_OCTET(sAppData.u8AppLogicalId); // アプリケーション論理アドレス
	S_BE_DWORD(ToCoNet_u32GetSerial());  // シリアル番号
	// 自転車発見器のリモコンは子機宛に送信
	S_OCTET(LOGICAL_ID_CHILDREN);
	S_BE_WORD((sAppData.u32CtTimer0 & 0x7FFF) + (bQuick == TRUE ? 0x8000 : 0)); // タイムスタンプ
	// bQuick 転送する場合は MSB をセットし、優先パケットである処理を行う
	S_OCTET(0); // 中継フラグ

	S_BE_WORD(sAppData.sIOData_now.u16Volt); // 電圧

	// チップ内温度センサーの予定だったが・・・
	S_OCTET((uint8)((sAppData.sIOData_now.i16Temp + 50)/100)); //チップ内温度センサー(TWE-Liteでは正しく動作しない)

	// ボタンのビットマップ
	if (*bm != 0)
	{
		// 指定値を使用
		uint8 u8bm = *bm & 0x0F;
		if (bRegular) u8bm |= 0x80; // MSB を設定

		S_OCTET(u8bm);
	} else {
		int i;
		uint8 u8bm = 0;

		for (i = 0; i < 4; i++) {
			uint8 u8ct = sAppData.sIOData_now.au8Input[i] >> 4;

			if (u8ct >= LOW_LATENCY_DELAYED_TRANSMIT_COUNTER - 3) { // カウンタ値が残っている場合は 1 を送る
				u8bm |= (1 << i);
			} else {
				u8bm |= (sAppData.sIOData_now.au8Input[i] & 1) ? (1 << i) : 0;
			}
		}
		*bm = u8bm;	// ボタン状態を通知

		if (bRegular) u8bm |= 0x80; // MSB を設定

		S_OCTET(u8bm);
	}

	// ボタンのビットマップ使用フラグ (１度でもLoになったポートは１になる）
	S_OCTET(
			( (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT1) ? 1 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT2) ? 2 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT3) ? 4 : 0) | (sAppData.sIOData_now.u32BtmUsed & (1UL << PORT_INPUT4) ? 8 : 0) ));

	// ADC 部のエンコード
	uint8 u8LSBs = 0;
	for (i = 0; i < 4; i++) {
		// MSB 部分 (10bit目～3bit目まで)
		uint16 u16v = sAppData.sIOData_now.au16InputADC[i];
		u16v >>= 2; // ADC 値は 0...2400mV

		uint8 u8MSB = (u16v >> 2) & 0xFF;
		S_OCTET(u8MSB);

		// 下2bitを u8LSBs に詰める
		u8LSBs >>= 2;
		u8LSBs |= ((u16v << 6) & 0xC0); //
	}
	S_OCTET(u8LSBs); // 詳細ビット部分を記録

	sTx.u8Len = q - sTx.auData; // パケット長
	sTx.u8Cmd = TOCONET_PACKET_CMD_APP_USER_IO_DATA; // パケット種別

	// 送信する
	sTx.u32DstAddr = TOCONET_MAC_ADDR_BROADCAST; // ブロードキャスト
	sTx.u8Retry = 0x81; // 1回再送

	// フレームカウントとコールバック識別子の指定
	sAppData.u16TxFrame++;
	sTx.u8Seq = (sAppData.u16TxFrame & 0xFF);
	sTx.u8CbId = sTx.u8Seq;

	{
		/* MAC モードでは細かい指定が可能 */
		sTx.bAckReq = FALSE;
		sTx.u32SrcAddr = sToCoNet_AppContext.u16ShortAddress;
		sTx.u16RetryDur = bQuick ? 0 : 4; // 再送間隔
		sTx.u16DelayMax = bQuick ? 0 : 16; // 衝突を抑制するため送信タイミングにブレを作る(最大16ms)

#ifdef USE_SLOW_TX
	    //ここから
	    if (bQuick == 0x10) {
	      sTx.u8Retry = 0x83; // 再送回数を３回とする
	      sTx.u16DelayMax = 100; // 初回送信は送信要求発行時～100ms の間（ランダムで決まる）
	      sTx.u16RetryDur = 20; // 20ms おきに再送する
	    }
	    //ここまで
#endif

		// 送信API
		if (ToCoNet_bMacTxReq(&sTx)) {
			i16Ret = sTx.u8CbId;
			sAppData.sIOData_now.u32TxLastTick = u32TickCount_ms;
		}
	}

	return i16Ret;
}

/** @ingroup MASTER
 * IO(DO/PWM)を設定する要求コマンドパケットを送信します。
 *
 * - Packet 構造
 *   - OCTET: 識別ヘッダ(APP ID より生成)
 *   - OCTET: プロトコルバージョン(バージョン間干渉しないための識別子)
 *   - OCTET: 送信元論理ID
 *   - BE_DWORD: 送信元のシリアル番号
 *   - OCTET: 宛先論理ID
 *   - BE_WORD: 送信タイムスタンプ (64fps カウンタの値の下１６ビット, 約1000秒で１周する)
 *   - OCTET: 中継フラグ
 *   - OCTET: 形式 (1固定)
 *   - OCTET: ボタン (LSB から順に SW1 ... SW4, 1=Lo)
 *   - OCTET: ボタン使用フラグ (LSB から順に SW1 ... SW4, 1=このポートを設定する)
 *   - BE_WORD: PWM1 (0..1024 or 0xffff) 0xffff を設定すると、このポートの設定をしない。
 *   - BE_WORD: PWM2 (0..1024 or 0xffff)
 *   - BE_WORD: PWM3 (0..1024 or 0xffff)
 *   - BE_WORD: PWM4 (0..1024 or 0xffff)
 *
 * @param u8DstAddr 送信先
 * @param pReq 設定データ
 * @return -1:Error, 0..255:CbId
 */
int16 i16TransmitIoSettingRequest(uint8 u8DstAddr, tsIOSetReq *pReq) {
	if (IS_APPCONF_ROLE_SILENT_MODE())
		return -1;

	int16 i16Ret, i;

	tsTxDataApp sTx;
	memset(&sTx, 0, sizeof(sTx));

	uint8 *q = sTx.auData;

	S_OCTET(sAppData.u8AppIdentifier);
	S_OCTET(APP_PROTOCOL_VERSION);
	S_OCTET(sAppData.u8AppLogicalId); // アプリケーション論理アドレス
	S_BE_DWORD(ToCoNet_u32GetSerial());  // シリアル番号
	S_OCTET(u8DstAddr); // 宛先
	S_BE_WORD(sAppData.u32CtTimer0 & 0xFFFF); // タイムスタンプ
	S_OCTET(0); // 中継フラグ

	S_OCTET(1); // パケット形式

	// DIO の設定
	S_OCTET(pReq->u8IOports);
	S_OCTET(pReq->u8IOports_use_mask);

	// PWM の設定
	for (i = 0; i < 4; i++) {
		S_BE_WORD(pReq->au16PWM_Duty[i]);
	}

	sTx.u8Len = q - sTx.auData; // パケット長
	sTx.u8Cmd = TOCONET_PACKET_CMD_APP_USER_IO_DATA_EXT; // パケット種別

	// 送信する
	sTx.u32DstAddr = TOCONET_MAC_ADDR_BROADCAST; // ブロードキャスト
	sTx.u8Retry = 0x81; // 1回再送

	{
		/* 送信設定 */
		sTx.bAckReq = FALSE;
		sTx.u32SrcAddr = sToCoNet_AppContext.u16ShortAddress;
		sTx.u16RetryDur = 4; // 再送間隔
		sTx.u16DelayMax = 16; // 衝突を抑制するため送信タイミングにブレを作る(最大16ms)

		// 送信API
		if (ToCoNet_bMacTxReq(&sTx)) {
			i16Ret = sTx.u8CbId;
		}
	}

	return i16Ret;
}

/** @ingroup MASTER
 * シリアルメッセージの送信要求を行います。１パケットを分割して送信します。
 *
 * - Packet 構造
 *   - OCTET    : 識別ヘッダ(APP ID より生成)
 *   - OCTET    : プロトコルバージョン(バージョン間干渉しないための識別子)
 *   - OCTET    : 送信元個体識別論理ID
 *   - BE_DWORD : 送信元シリアル番号
 *   - OCTET    : 送信先シリアル番号
 *   - OCTET    : 送信タイムスタンプ (64fps カウンタの値の下１６ビット, 約1000秒で１周する)
 *   - OCTET    : 送信フラグ(リピータ用)
 *   - OCTET    : 要求番号
 *   - OCTET    : パケット数(total)
 *   - OCTET    : パケット番号 (0...total-1)
 *   - BE_WORD  : 本パケットのバッファ位置
 *   - OCTET    : 本パケットのデータ長
 *
 * @param p ペイロードのデータへのポインタ
 * @param u16len ペイロード長
 * @param bRelay 中継フラグ TRUE:中継する
 * @return -1:失敗, 0:成功
 */
int16 i16TransmitSerMsg(uint8 *p, uint16 u16len, uint32 u32AddrSrc,
		uint8 u8AddrSrc, uint8 u8AddrDst, uint8 u8RelayLv, uint8 u8Req) {
	if (IS_APPCONF_ROLE_SILENT_MODE())
		return -1;
	DBGOUT(1, LB"i16TransmitSerMsg(p,%d,%x,%x,%x,%d,%d)"LB, u16len, u32AddrSrc, u8AddrSrc, u8AddrDst, u8RelayLv, u8Req);
	int c;
	for (c = 0; c < u16len; c++) {
		DBGOUT(1, "%02X", p[c]);
	}

	// パケットを分割して送信する。
	tsTxDataApp sTx;
	memset(&sTx, 0, sizeof(sTx));
	uint8 *q; // for S_??? macros

	// 処理中のチェック（処理中なら送信せず失敗）
	if (sSerSeqTx.bWaitComplete) {
		return -1;
	}

	// sSerSeqTx は分割パケットの管理構造体
	sSerSeqTx.u8IdSender = sAppData.u8AppLogicalId;
	sSerSeqTx.u8IdReceiver = u8AddrDst;

	sSerSeqTx.u8PktNum = (u16len - 1) / SERCMD_SER_PKTLEN + 1;
	sSerSeqTx.u16DataLen = u16len;
	sSerSeqTx.u8Seq = sSerSeqTx.u8SeqNext; // パケットのシーケンス番号（アプリでは使用しない）
	sSerSeqTx.u8SeqNext = sSerSeqTx.u8Seq + sSerSeqTx.u8PktNum; // 次のシーケンス番号（予め計算しておく）
	sSerSeqTx.u8ReqNum = u8Req; // パケットの要求番号（この番号で送信系列を弁別する）
	sSerSeqTx.bWaitComplete = TRUE;
	sSerSeqTx.u32Tick = u32TickCount_ms;
	memset(sSerSeqTx.bPktStatus, 0, sizeof(sSerSeqTx.bPktStatus));

	DBGOUT(3, "* >>> Transmit(req=%d) Tick=%d <<<" LB, sSerSeqTx.u8ReqNum,
			u32TickCount_ms & 65535);

	sTx.u8Cmd = TOCONET_PACKET_CMD_APP_DATA; // data packet.
	sTx.u8Retry = 0x81;
	sTx.u16RetryDur = sSerSeqTx.u8PktNum * 10; // application retry

	int i;
	for (i = 0; i < sSerSeqTx.u8PktNum; i++) {
		q = sTx.auData;
		sTx.u8Seq = sSerSeqTx.u8Seq + i;
		sTx.u8CbId = sTx.u8Seq; // callback will reported with this ID

		// ペイロードを構成
		S_OCTET(sAppData.u8AppIdentifier);
		S_OCTET(APP_PROTOCOL_VERSION);
		S_OCTET(u8AddrSrc); // アプリケーション論理アドレス
		S_BE_DWORD(u32AddrSrc);  // シリアル番号
		S_OCTET(sSerSeqTx.u8IdReceiver); // 宛先
		S_BE_WORD(sAppData.u32CtTimer0 & 0xFFFF); // タイムスタンプ

		S_OCTET(u8RelayLv); // 中継レベル

		S_OCTET(sSerSeqTx.u8ReqNum); // request number
		S_OCTET(sSerSeqTx.u8PktNum); // total packets
		S_OCTET(i); // packet number
		S_BE_WORD(i * SERCMD_SER_PKTLEN); // offset

		uint8 u8len_data =
				(u16len >= SERCMD_SER_PKTLEN) ? SERCMD_SER_PKTLEN : u16len;
		S_OCTET(u8len_data);

		memcpy(q, p, u8len_data);
		q += u8len_data;

		sTx.u8Len = q - sTx.auData;

		// あて先など
		sTx.u32DstAddr = TOCONET_MAC_ADDR_BROADCAST; // ブロードキャスト

		if (sAppData.eNwkMode == E_NWKMODE_MAC_DIRECT) {
			sTx.u32SrcAddr = sToCoNet_AppContext.u16ShortAddress;
			sTx.bAckReq = FALSE;
			sTx.u8Retry = 0x81; // ２回再送

			ToCoNet_bMacTxReq(&sTx);
		}

		p += u8len_data;
		u16len -= SERCMD_SER_PKTLEN;
	}

	return 0;
}


/** @ingroup MASTER
 *  MMLの曲データ更新の送信要求を行います。
 *
 */
void vTransmitMmlData(void)
{
	uint8 payload[256];
	const uint8 *src;
	uint8 *q = payload;

	src = au8MmlBank[sAppData.sFlash.sData.u8MML_idx];
#ifdef ENABLE_BICYCLE_FINDER
	// 自転車発見器のリモコンは子機宛に送信
	S_OCTET(LOGICAL_ID_CHILDREN + 4); // 宛先は子機間欠モード
#else
	S_OCTET(
			IS_LOGICAL_ID_PARENT(sAppData.u8AppLogicalId) ? LOGICAL_ID_CHILDREN : LOGICAL_ID_PARENT); // 宛先
#endif
	S_OCTET(SERCMD_ID_MML_UPDATE_CMD);
	S_OCTET(0x00);	// 要求番号
	S_OCTET(0x01);	// コマンド (0x1: Write)
	S_OCTET(0x00);	// 曲インデックス
	S_OCTET(0xFF);	// MML length (dummy)

	DBGOUT(1, LB"MML ");
	for (; *src && (q - payload) < 256; src++)
	{
		if (*src > 0x20 && *src < 0x7f) {
			S_OCTET(*src);
			DBGOUT(1, "%c", *src);
		}
	}
	payload[5] = (q - payload) - 6;	// set MML length
	i16TransmitSerMsg(payload, (q - payload), ToCoNet_u32GetSerial(),
			sAppData.u8AppLogicalId, payload[0], FALSE,
			sAppData.u8UartReqNum++);
}


/** @ingroup MASTER
 * IO状態パケットの受信処理を行います。
 *
 * - 受信したデータに格納されるIO設定要求に従いIO値(DO/PWM)を設定します。
 * - 受信したデータを UART に出力します。
 * - 中継機の場合、中継パケットを送信します。
 * - 低遅延で送信されてきたパケットの TimeStamp の MSB には１が設定される。
 *   このパケットは、タイムスタンプによる重複除去アルゴリズムとは独立して
 *   処理される。
 * - IOの設定は本受信関数でのみ行われる。
 *
 * @param pRx 受信データ
 */
static void vReceiveIoData(tsRxDataApp *pRx) {
	int i, j;
	uint8 *p = pRx->auData;

	uint8 u8AppIdentifier = G_OCTET();
	if (u8AppIdentifier != sAppData.u8AppIdentifier)
		return;

	uint8 u8PtclVersion = G_OCTET();
	if (u8PtclVersion != APP_PROTOCOL_VERSION)
		return;

	uint8 u8AppLogicalId = G_OCTET();

	uint32 u32Addr = G_BE_DWORD();

	uint8 u8AppLogicalId_Dest = G_OCTET();
	(void) u8AppLogicalId_Dest;

	uint16 u16TimeStamp = G_BE_WORD();

	/* 重複の確認を行う */
	bool_t bQuick = u16TimeStamp & 0x8000 ? TRUE : FALSE; // 優先パケット（全部処理する）
	u16TimeStamp &= 0x7FFF;
	if (bQuick == FALSE
			&& bCheckDupPacket(&sDupChk_IoData, u32Addr, u16TimeStamp)) {
		return;
	}
	static uint32 u32LastQuick;
	if (bQuick) {
		if ((u32TickCount_ms - u32LastQuick) < 20) {
			// Quickパケットを受けて一定期間未満のパケットは無視する
			return;
		} else {
			u32LastQuick = u32TickCount_ms; // タイムスタンプを巻き戻す
		}
	}

	// 中継フラグ
	uint8 u8TxFlag = G_OCTET();
	(void)u8TxFlag;

	// 親機子機の判定
	if ((IS_LOGICAL_ID_PARENT(u8AppLogicalId)
			&& IS_LOGICAL_ID_CHILD(sAppData.u8AppLogicalId))
	|| (IS_LOGICAL_ID_CHILD(u8AppLogicalId) && (IS_LOGICAL_ID_PARENT(sAppData.u8AppLogicalId) || IS_LOGICAL_ID_CHILD(u8AppLogicalId_Dest))) ){
		; // 親機⇒子機、または子機⇒親機への伝送
	} else {
		return;
	}

	/* 電圧 */
	uint16 u16Volt = G_BE_WORD();
#ifdef USE_DO4_AS_STATUS_LED
	sAppData.sIOData_now.u16Volt_LastRx = u16Volt;
#endif

	/* 温度 */
	int8 i8Temp = (int8)G_OCTET();
	(void)i8Temp;

	/* BUTTON */
	uint8 u8ButtonState = G_OCTET();
	bool_t bRegular = !!(u8ButtonState & 0x80);
	uint8 u8ButtonChanged = G_OCTET();
	// ポートの値を設定する（変更フラグのあるものだけ）
	for (i = 0, j = 1; i < 4; i++, j <<= 1) {
		if (u8ButtonChanged & j) {
			vPortSet_TrueAsLo(au8PortTbl_DOut[i], u8ButtonState & j);
			sAppData.sIOData_now.au8Output[i] = u8ButtonState & j;
		}
	}

	/* ADC 値 */
	for (i = 0; i < 4; i++) {
		// 8bit scale
		sAppData.sIOData_now.au16OutputDAC[i] = G_OCTET();
		if (sAppData.sIOData_now.au16OutputDAC[i] == 0xFF) {
			sAppData.sIOData_now.au16OutputDAC[i] = 0xFFFF;
		} else {
			// 10bit scale に拡張
			sAppData.sIOData_now.au16OutputDAC[i] <<= 2;
		}
	}
	uint8 u8DAC_Fine = G_OCTET();
	for (i = 0; i < 4; i++) {
		if (sAppData.sIOData_now.au16OutputDAC[i] != 0xFFFF) {
			// 下２ビットを復旧
			sAppData.sIOData_now.au16OutputDAC[i] |= (u8DAC_Fine & 0x03);
		}
		u8DAC_Fine >>= 2;
	}

	// ADC 値を PWM の DUTY 比に変換する
	// 下は 5%, 上は 10% を不感エリアとする。
	for (i = 0; i < 4; i++) {
		uint16 u16Adc = sAppData.sIOData_now.au16OutputDAC[i];
		u16Adc <<= 2; // 以下の計算は 12bit 精度
		if (u16Adc > ADC_MAX_THRES) { // 最大レンジの 98% 以上なら、未定義。
			sAppData.sIOData_now.au16OutputPWMDuty[i] = 0xFFFF;
		} else {
			// 10bit+1 スケール正規化
			int32 iR = (uint32) u16Adc * 2 * 1024 / u16Volt; // スケールは 0～Vcc/2 なので 2倍する
			// y = 1.15x - 0.05 の線形変換
			//   = (115x-5)/100 = (23x-1)/20 = 1024*(23x-1)/20/1024 = 51.2*(23x-1)/1024 ~= 51*(23x-1)/1024
			// iS/1024 = 51*(23*iR/1024-1)/1024
			// iS      = (51*23*iR - 51*1024)/1024
			int32 iS = 51 * 23 * iR - 51 * 1024;
			if (iS <= 0) {
				iS = 0;
			} else {
				iS >>= 10; // 1024での割り算
				if (iS >= 1024) { // DUTY は 0..1024 で正規化するので最大値は 1024。
					iS = 1024;
				}
			}

			sAppData.sIOData_now.au16OutputPWMDuty[i] = iS;

		}
	}

	// PWM の再設定
		for (i = 0; i < 4; i++) {
			if (sAppData.sIOData_now.au16OutputPWMDuty[i] != 0xFFFF) {
				sTimerPWM[i].u16duty =
						_PWM(sAppData.sIOData_now.au16OutputPWMDuty[i]);
#if defined(JN516x)
				if (sTimerPWM[i].bStarted) {
					vTimerStart(&sTimerPWM[i]); // DUTY比だけ変更する
				}
#else
				if (i >= 2) {
					vTimerStart(&sTimerPWM[i]); // DUTY比の変更
				}
#endif
			}
		}

	// DAC の出力を行う
#if defined(JN514x)
	{
		int i;
		for (i = 0; i < 2; i++) {
			if (sAppData.sIOData_now.au16OutputPWMDuty[i] != 0xFFFF) {
				int j = (sAppData.sIOData_now.au16OutputDAC[i] << 2) * 4096 / ADC_MAC_MV;
				if (j >= 4095) j = 4095;
				sAppData.sIOData_now.au16OutputDAC_val[i] = j;

				// vAHI_DacOutput(/* E_AHI_AP_DAC_1 */ i, j); // ADCとの干渉を避けるためここでは書き込まない
			}
		}
	}
#endif

	/* タイムスタンプ */
	sAppData.sIOData_now.u32RxLastTick = u32TickCount_ms;

	/* UART 出力 */
	if (!Interactive_bGetMode()) {
		if (IS_APPCONF_OPT_REGULAR_PACKET_NO_DISP() && bRegular) {
			; // 通常パケットの場合の出力抑制設定
		} else {
			// 以下のようにペイロードを書き換えて UART 出力
			pRx->auData[0] = pRx->u8Len; // １バイト目はバイト数
			pRx->auData[2] = pRx->u8Lqi; // ３バイト目(もともとは送信元の LogicalID) は LQI

			SerCmdAscii_Output_AdrCmd(&sSerStream, u8AppLogicalId,
					SERCMD_ID_INFORM_IO_DATA, pRx->auData, pRx->u8Len);
		}
	}
}

/** @ingroup MASTER
 * IO状態の設定要求を行う UART メッセージから送信されてきたパケットの処理を行います。
 * vReceiveIoData() と大まかな処理は同じですが、PWMの設定に違いが有るので独立した
 * 関数に記述しています。
 *
 * @param pRx 受信したときのデータ
 */
static void vReceiveIoSettingRequest(tsRxDataApp *pRx) {
	int i, j;
	uint8 *p = pRx->auData;

	uint8 u8AppIdentifier = G_OCTET();
	if (u8AppIdentifier != sAppData.u8AppIdentifier)
		return;

	uint8 u8PtclVersion = G_OCTET();
	if (u8PtclVersion != APP_PROTOCOL_VERSION)
		return;

	uint8 u8AppLogicalId = G_OCTET();

	uint32 u32Addr = G_BE_DWORD();

	uint8 u8AppLogicalId_Dest = G_OCTET();

	uint16 u16TimeStamp = G_BE_WORD();

	/* 重複の確認を行う */
	if (bCheckDupPacket(&sDupChk_IoData, u32Addr, u16TimeStamp)) {
		return;
	}

	// 中継フラグ
	G_OCTET();

	// 親機子機の判定
	if (IS_LOGICAL_ID_CHILD(sAppData.u8AppLogicalId)) {
		// 子機の場合は、任意の送り主から受けるが、送り先が CHILDREN(120) またはアドレスが一致している事
		if (!(u8AppLogicalId_Dest == sAppData.u8AppLogicalId
				|| u8AppLogicalId_Dest == LOGICAL_ID_CHILDREN)) {
			return;
		}
	} else if (IS_LOGICAL_ID_PARENT(sAppData.u8AppLogicalId)) {
		// 親機の場合は、子機からの送信である事
		if (!(u8AppLogicalId_Dest == LOGICAL_ID_PARENT
				&& IS_LOGICAL_ID_CHILD(u8AppLogicalId))) {
			return;
		}
	} else {
		// それ以外は処理しない
		return;
	}

	/* 書式 */
	uint8 u8Format = G_OCTET();

	if (u8Format == 1) {
		/* BUTTON */
		uint8 u8ButtonState = G_OCTET();
		uint8 u8ButtonChanged = G_OCTET();
		// ポートの値を設定する（変更フラグのあるものだけ）
		for (i = 0, j = 1; i < 4; i++, j <<= 1) {
			if (u8ButtonChanged & j) {
				vPortSet_TrueAsLo(au8PortTbl_DOut[i], u8ButtonState & j);
				sAppData.sIOData_now.au8Output[i] = u8ButtonState & j;
			}
		}

		for (i = 0; i < 4; i++) {
			uint16 u16Duty = G_BE_WORD();
			if (u16Duty <= 1024) {
				sAppData.sIOData_now.au16OutputPWMDuty[i] = u16Duty;
			} else {
				sAppData.sIOData_now.au16OutputPWMDuty[i] = 0xFFFF;
			}
		}

		DBGOUT(1, "RECV:IO REQ: %02x %02x %04x:%04x:%04x:%04x"LB, u8ButtonState,
				u8ButtonChanged, sAppData.sIOData_now.au16OutputPWMDuty[0],
				sAppData.sIOData_now.au16OutputPWMDuty[1],
				sAppData.sIOData_now.au16OutputPWMDuty[2],
				sAppData.sIOData_now.au16OutputPWMDuty[3]);

		// PWM の再設定
		for (i = 0; i < 4; i++) {
			if (sAppData.sIOData_now.au16OutputPWMDuty[i] != 0xFFFF) {
				sTimerPWM[i].u16duty =
						_PWM(sAppData.sIOData_now.au16OutputPWMDuty[i]);
#if defined(JN516x)
				if (sTimerPWM[i].bStarted)
					vTimerStart(&sTimerPWM[i]); // DUTY比だけ変更する
#else
							if (i >= 2) {
								vTimerStart(&sTimerPWM[i]); // DUTY比の変更
							}
#endif
			}
		}

#if defined(JN514x)
		// DAC の出力を行う (DUTY 比の指定なのでどうしよう？)
		{
			int i;
			for(i = 0; i < 2; i++) {
				if (sAppData.sIOData_now.au16OutputPWMDuty[i] != 0xFFFF) {
					sAppData.sIOData_now.au16OutputDAC_val[i] = sAppData.sIOData_now.au16OutputPWMDuty[i] * 4;
					if (sAppData.sIOData_now.au16OutputDAC_val[i] > 4095) sAppData.sIOData_now.au16OutputDAC_val[i] = 4095;

					// vAHI_DacOutput(/* E_AHI_AP_DAC_1 */ i, sAppData.sIOData_now.au16OutputDAC_val[i]);
				}
			}
		}
#endif
	}

	/* UART 出力 */
#if 0
	if (!Interactive_bGetMode()) {
		// 以下のようにペイロードを書き換えて UART 出力
		pRx->auData[0] = pRx->u8Len;// １バイト目はバイト数
		pRx->auData[2] = pRx->u8Lqi;// ３バイト目(もともとは送信元の LogicalID) は LQI

		SerCmdAscii_Output_AdrCmd(&sSerStream, u8AppLogicalId, SERCMD_ID_INFORM_IO_DATA, pRx->auData, pRx->u8Len);
	}
#endif
}

/** @ingroup MASTER
 * シリアルメッセージの受信処理を行います。分割パケットが全部受信できた時点で UART に出力します。
 * tsRxDataApp *pRx 受信パケット構造体
 */
static void vReceiveSerMsg(tsRxDataApp *pRx) {
	uint8 *p = pRx->auData;

	/* ヘッダ情報の読み取り */
	uint8 u8AppIdentifier = G_OCTET();
	if (u8AppIdentifier != sAppData.u8AppIdentifier) {
		return;
	}
	uint8 u8PtclVersion = G_OCTET();
	if (u8PtclVersion != APP_PROTOCOL_VERSION) {
		return;
	}
	uint8 u8AppLogicalId = G_OCTET();
	(void) u8AppLogicalId;
	uint32 u32Addr = G_BE_DWORD();
	uint8 u8AppLogicalId_Dest = G_OCTET();
	uint16 u16TimeStamp = G_BE_WORD();
	(void) u16TimeStamp;
	uint8 u8TxFlag = G_OCTET();

	/* ここから中身 */
	uint8 u8req = G_OCTET();
	uint8 u8pktnum = G_OCTET();
	uint8 u8idx = G_OCTET();
	uint16 u16offset = G_BE_WORD();
	uint8 u8len = G_OCTET();

	/* 宛先によって処理するか決める */
	if (IS_LOGICAL_ID_CHILD(sAppData.u8AppLogicalId)) {
		if (!(u8AppLogicalId_Dest == sAppData.u8AppLogicalId
				|| u8AppLogicalId_Dest == LOGICAL_ID_CHILDREN)) {
			return;
		}
	} else if (IS_LOGICAL_ID_PARENT(sAppData.u8AppLogicalId)) {
		if (!(u8AppLogicalId_Dest == LOGICAL_ID_PARENT
				&& IS_LOGICAL_ID_CHILD(u8AppLogicalId))) {
			return;
		}
	} else {
		return;
	}

	// 受信パケットのチェック。
	//  - 分割パケットが混在したような場合は、新しい系列で始める。
	//    複数のストリームを同時受信できない！
	bool_t bNew = FALSE;
	if (sSerSeqRx.bWaitComplete) {
		// exceptional check
		if (u32TickCount_ms - sSerSeqRx.u32Tick > 2000) {
			// time out check
			bNew = TRUE;
		}
		if (u8req != sSerSeqRx.u8ReqNum) {
			// different request number is coming.
			bNew = TRUE;
		}
		if (u32Addr != sSerSeqRx.u32SrcAddr) {
			// packet comes from different nodes. (discard this one!)
			bNew = TRUE;
		}
	} else {
		// 待ち状態ではないなら新しい系列
		bNew = TRUE;
	}

	if (bNew) {
		// treat this packet as new, so clean control buffer.
		memset(&sSerSeqRx, 0, sizeof(sSerSeqRx));
	}

	if (!sSerSeqRx.bWaitComplete) {
		// 新しいパケットを受信した

		// 最初にリクエスト番号が適切かどうかチェックする。
		uint32 u32key;
		if (DUPCHK_bFind(&sDupChk_SerMsg, u32Addr, &u32key)) {
			int iPrev = u32key, iNow = u8req;

			if (iNow == iPrev || (uint8) (iNow - iPrev) > 0x80) { //v1.0.4 iPrev == 255 で正しく判定していなかった
			// 最近受信したものより新しくないリクエスト番号の場合は、処理しない
				bNew = FALSE;
			}
		}

		if (bNew) {
			sSerSeqRx.bWaitComplete = TRUE;
			sSerSeqRx.u32Tick = u32TickCount_ms;
			sSerSeqRx.u32SrcAddr = u32Addr;
			sSerSeqRx.u8PktNum = u8pktnum;
			sSerSeqRx.u8ReqNum = u8req;

			sSerSeqRx.u8IdSender = u8AppLogicalId;
			sSerSeqRx.u8IdReceiver = u8AppLogicalId_Dest;

			DUPCHK_vAdd(&sDupChk_SerMsg, sSerSeqRx.u32SrcAddr, u8req);
		}
	}

	if (sSerSeqRx.bWaitComplete) {
		if (u16offset + u8len <= sizeof(au8SerBuffRx)
				&& u8idx < sSerSeqRx.u8PktNum) {
			// check if packet size and offset information is correct,
			// then copy data to buffer and mark it as received.
			if (!sSerSeqRx.bPktStatus[u8idx]) {
				sSerSeqRx.bPktStatus[u8idx] = 1;
				memcpy(au8SerBuffRx + u16offset, p, u8len);
			}

			// the last packet indicates full data length.
			if (u8idx == sSerSeqRx.u8PktNum - 1) {
				sSerSeqRx.u16DataLen = u16offset + u8len;
			}

			// 中継パケットのフラグを格納する
			if (u8TxFlag) {
				if (u8TxFlag > sSerSeqRx.bRelayPacket) {
					sSerSeqRx.bRelayPacket = u8TxFlag;
				}
			}
		}

		// check completion
		int i;
		for (i = 0; i < sSerSeqRx.u8PktNum; i++) {
			if (sSerSeqRx.bPktStatus[i] == 0)
				break;
		}
		if (i == sSerSeqRx.u8PktNum) {
			// 分割パケットが全て届いた！
#if 0
			i16TransmitSerMsgAck(); // アプリケーションACKを返す
#endif

		if (au8SerBuffRx[1] == SERCMD_ID_I2C_COMMAND) {
				// I2C の処理
				vProcessI2CCommand(au8SerBuffRx, sSerSeqRx.u16DataLen, sSerSeqRx.u8IdSender);
			} else {
				// 受信データの出力
				SerCmdAscii_Output_AdrCmd(&sSerStream,
						sSerSeqRx.u8IdSender, // v1.2.1 １バイト目は送り主に変更。他のコマンドなどとの整合性のため。
						au8SerBuffRx[1], au8SerBuffRx + 2,
						sSerSeqRx.u16DataLen - 2);
			}
		}

		memset(&sSerSeqRx, 0, sizeof(sSerSeqRx));
	}
}

/** @ingroup MASTER
 * ADCサンプルの平均化処理を行います。
 * @param pu16k 平均化データを格納した配列
 * @param u8Scale 平均化数スケーラ (2^u8Scale ヶで平均化)
 */
static uint16 u16GetAve(uint16 *pu16k, uint8 u8Scale) {
	int k, kmax;
	uint32 u32Ave = 0;
	kmax = 1 << u8Scale;

	for (k = 0; k < kmax; k++) {
		uint16 v = pu16k[k];

		if (v == 0xFFFF) {
			// 入力NGデータなので処理しない。
			u32Ave = 0xFFFFFFFF;
			break;
		}

		u32Ave += v;
	}
	if (u32Ave != 0xFFFFFFFF) {
		// 平均値が得られる。
		u32Ave >>= u8Scale; // ４で割る
	}
	return u32Ave & 0xFFFF;
}

/** @ingroup MASTER
 * ADC 入力値が有った場合の演算処理を行います。
 *
 * - ADC 値は過去４回の値で平均化して使用します。
 * - sAppData.sIOData_now.u8HistIdx >= 4 で、初回の平均化処理は完了しています。
 * - au16InputADC_LastTx[] に対して変化があるという判定は以下に基づきます。
 *   - 初回データ
 *   - 最後に送信した時と比べて ADC_DELTA_COARSE [mV] 以上の差を検知
 *   - 一定時間経過した後 ADC_DELTA_FINE[mV] 以上の差を検知
 * - 電圧値はHIST_VOLT_COUNT回で平均化します。電圧値は測定した時の負荷状況など
 *   で大きく変わり、変動が大きいためです。
 *
 * @return TRUE:変化判定あり FALSE:変化なし
 */
static bool_t bUpdateAdcValues() {
	bool_t bUpdated = FALSE;
	int i, k;

	// ADC が完了したので内部データに保存する
	sAppData.sIOData_now.au16InputADC[0] =
			(uint16) sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_1];
#if defined(JN516x)
	sAppData.sIOData_now.au16InputADC[1] =
			(uint16) sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_3];
	sAppData.sIOData_now.au16InputADC[2] =
			(uint16) sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_2];
#elif defined(JN514x)
	sAppData.sIOData_now.au16InputADC[1] = (uint16)sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_2];
	sAppData.sIOData_now.au16InputADC[2] = (uint16)sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_3];
#endif
	sAppData.sIOData_now.au16InputADC[3] =
			(uint16) sAppData.sObjADC.ai16Result[TEH_ADC_IDX_ADC_4];
	sAppData.sIOData_now.i16Temp =
			sAppData.sObjADC.ai16Result[TEH_ADC_IDX_TEMP];
	sAppData.sIOData_now.u16Volt =
			(uint16) sAppData.sObjADC.ai16Result[TEH_ADC_IDX_VOLT];

#if 0
	DBGOUT(0, LB"%04d/%04d/%04d/%04d",
			sAppData.sIOData_now.au16InputADC[0],
			sAppData.sIOData_now.au16InputADC[1],
			sAppData.sIOData_now.au16InputADC[2],
			sAppData.sIOData_now.au16InputADC[3]
	);
#endif

	// 履歴情報を保存する
	//  初期値は 0xFF なので、最初は ++ を実行して 0 からカウントする。
	//  途中で 127 で 63 に巻き戻す。4以上なら初回実行済みである判定のため。
	sAppData.sIOData_now.u8HistIdx++;
	if (sAppData.sIOData_now.u8HistIdx >= 127) {
		sAppData.sIOData_now.u8HistIdx = 63;
	}

	k = sAppData.sIOData_now.u8HistIdx & 0x3;
	for (i = 0; i < 4; i++) {
		if (IS_ADC_RANGE_OVER(sAppData.sIOData_now.au16InputADC[i])
				|| IS_APPCONF_OPT_DISABLE_ADC() // ADC無効化のフラグ
				) {
			sAppData.sIOData_now.au16InputADC[i] = 0xFFFF;
			sAppData.sIOData_now.au16InputADC_History[i][k] = 0xFFFF;
		} else {
			sAppData.sIOData_now.au16InputADC_History[i][k] =
					sAppData.sIOData_now.au16InputADC[i];
		}
	}
	sAppData.sIOData_now.au16Volt_History[sAppData.sIOData_now.u8HistIdx
			& (HIST_VOLT_COUNT - 1)] = sAppData.sIOData_now.u16Volt;

	// 電圧を先に平均化しておく
	if (sAppData.sIOData_now.u8HistIdx >= HIST_VOLT_COUNT) {
		sAppData.sIOData_now.u16Volt = u16GetAve(
				sAppData.sIOData_now.au16Volt_History, HIST_VOLT_SCALE);
	}

	// ADC1...4 の平均化処理
	for (i = 0; i < 4; i++) {
		// 過去４サンプルの平均値を保存する
		if (sAppData.sIOData_now.u8HistIdx >= 4) {
			sAppData.sIOData_now.au16InputADC[i] = u16GetAve(
					sAppData.sIOData_now.au16InputADC_History[i], 2);
		}

		// 判定0:そもそもADC値が適正でないなら処理しない。
		if (sAppData.sIOData_now.au16InputADC[i] == 0xFFFF) {
			continue;
		}

		// 判定1：送信前データが存在しない場合。
		if (sAppData.sIOData_now.au16InputADC_LastTx[i] == 0xFFFF) {
			bUpdated = FALSE;
			continue;
		}

		// 判定2：最終送信データとの差(粗)
		int iDelta = abs(
				(int) sAppData.sIOData_now.au16InputADC_LastTx[i]
						- (int) sAppData.sIOData_now.au16InputADC[i]);
		if (iDelta > ADC_DELTA_COARSE) {
			bUpdated = TRUE;
			continue;
		}

		// 判定3:最終送信データとの差(細), 経過時間が 300ms 以上
		if (iDelta > ADC_DELTA_FINE
				&& (u32TickCount_ms - sAppData.sIOData_now.u32TxLastTick
						> ADC_TIMEOUT_TO_FINE_CHECK)) {
			bUpdated = TRUE;
			continue;
		}
	}

#ifdef USE_PWM4_AS_BAT_MONITOR
	if (sAppData.sIOData_now.u16Volt != 0xFFFF) {
		if (sAppData.sIOData_now.u16Volt <= 2300) {
			sAppData.sIOData_now.au16InputADC[3] = 0;
		} else if (sAppData.sIOData_now.u16Volt <= 2400) {
			sAppData.sIOData_now.au16InputADC[3] = sAppData.sIOData_now.u16Volt / 4;
		} else {
			sAppData.sIOData_now.au16InputADC[3] = sAppData.sIOData_now.u16Volt / 2;
		}
	} else {
		sAppData.sIOData_now.au16InputADC[3] = 0xFFFF;
	}
#endif

	return bUpdated;
}

/** @ingroup MASTER
 * スリープ状態に遷移します。
 *
 * @param u32SleepDur_ms スリープ時間[ms]
 * @param bPeriodic TRUE:前回の起床時間から次のウェイクアップタイミングを計る
 * @param bDeep TRUE:RAM OFF スリープ
 */
static void vSleep(uint32 u32SleepDur_ms, bool_t bPeriodic, bool_t bDeep) {
	// print message.

	// IO 情報の保存
	memcpy(&sAppData.sIOData_reserve, &sAppData.sIOData_now, sizeof(tsIOData));

	// stop interrupt source, if interrupt source is still running.
	vAHI_DioInterruptEnable(0, PORT_INPUT_MASK); // 割り込みの解除）

	// set UART Rx port as interrupt source
	vAHI_DioSetDirection(PORT_INPUT_MASK, 0); // set as input

	(void) u32AHI_DioInterruptStatus(); // clear interrupt register
	vAHI_DioWakeEnable(PORT_INPUT_MASK, 0); // also use as DIO WAKE SOURCE
	vAHI_DioWakeEdge(0, PORT_INPUT_MASK); // 割り込みエッジ（立下りに設定）
	// vAHI_DioWakeEnable(0, PORT_INPUT_MASK); // DISABLE DIO WAKE SOURCE

	// wake up using wakeup timer as well.
	ToCoNet_vSleep(E_AHI_WAKE_TIMER_0, u32SleepDur_ms, bPeriodic, bDeep); // PERIODIC RAM OFF SLEEP USING WK0
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
