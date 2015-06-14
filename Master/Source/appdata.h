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

#ifndef APPDATA_H_
#define APPDATA_H_

#include <jendefs.h>

#include "config.h"
#include "ToCoNet.h"
#include "flash.h"
#include "sensor_driver.h"
#include "btnMgr.h"

#include "adc.h"

/** @ingroup MASTER
 * 使用する無線チャネル数の最大値 (複数設定すると Channel Agility を利用する)
 */
#define MAX_CHANNELS 3

/** @ingroup MASTER
 * ネットワークのモード列挙体 (ショートアドレス管理か中継ネットワーク層を使用したものか)
 */
typedef enum {
	E_NWKMODE_MAC_DIRECT,//!< ネットワークは構成せず、ショートアドレスでの通信を行う
	E_NWKMODE_LAYERTREE  //!< 中継ネットワークでの通信を行う(これは使用しない)
} teNwkMode;

/** @ingroup MASTER
 * IO の状態
 */
typedef struct {
	uint32 u32BtmBitmap; //!< (0xFFFFFFFF: 未確定)
	uint32 u32BtmUsed; //!< 利用対象ピンかどうか (0xFFFFFFFF: 未確定)
	uint32 u32BtmChanged; //!< (0xFFFFFFFF: 未確定)

	uint16 au16InputADC[4]; //!< (0xFFFF: 未確定) 入力ポートの ADC 値 [mV]
	uint16 au16OutputDAC[4]; //!< (0xFFFF: 未確定) 送られてきた ADC 値 [mV]
#ifdef JN514x
	uint16 au16OutputDAC_val[2]; //!< (0xFFFF: 未確定) 送られてきた ADC 値 [12bit スケール値]
#endif
	uint16 u16Volt; //!< 12bits, 0xFFFF: 未確定
	int16 i16Temp; //!< 12bits
#ifdef USE_DO4_AS_STATUS_LED
	uint16 u16Volt_LastRx;
#endif

	uint8 au8Input[4]; //!< 入力ポート (0: Hi, 1: Lo, 0xFF: 未確定)
	uint8 au8Output[4]; //!< 出力ポート (0: Hi, 1:Lo, 0xFF: 未確定)

	uint16 au16OutputPWMDuty[4]; //!< 無線経由で送られた DUTY 比 (0xFFFF: 未設定、無効)
	uint16 au16InputPWMDuty[4]; //!< 入力された AD に基づく DUTY 比の計算値 (0xFFFF: 未設定、無効)

	uint8 u8Volt; //!< i16Volt から変換

	uint32 u32TxLastTick; //!< 最後に送った時刻
	uint16 au16InputADC_LastTx[4]; //!< 最後に送信したデータ
	uint32 u32RxLastTick; //!< 最後に受信した時刻

	uint16 au16InputADC_History[4][4]; //!< ADCデータ履歴
	uint16 u16Volt_LastTx; //!< 最後に送信した電圧
	uint16 au16Volt_History[32]; //!< ADCデータ電圧履歴
	uint8 u8HistIdx; //!< 履歴情報のインデックス
	int16 i16TxCbId; //!< 送信時のID
} tsIOData;

#define HIST_VOLT_SCALE 5 //!< 電圧履歴数のスケーラ (2^HIST_VOLT_SCALE)  @ingroup MASTER
#define HIST_VOLT_COUNT (1UL << HIST_VOLT_SCALE) //!< 電圧履歴数 @ingroup MASTER


/** @ingroup MASTER
 * IO 設定要求
 */
typedef struct {
	uint8 u8IOports;          //!< 出力IOの状態 (1=Lo, 0=Hi)
	uint8 u8IOports_use_mask; //!< 設定を行うポートなら TRUE
	uint16 au16PWM_Duty[4];      //!< PWM DUTY 比 (0～1024)
	uint8 au16PWM_use_mask[4];   //!< 設定を行うPWMポートなら TRUE
} tsIOSetReq;

/** @ingroup MASTER
 * アプリケーションの情報
 */
typedef struct {
	// ToCoNet
	uint32 u32ToCoNetVersion; //!< ToCoNet のバージョン番号を保持
	uint16 u16ToCoNetTickDelta_ms; //!< ToCoNet の Tick 周期 [ms]
	uint8 u8AppIdentifier; //!< AppID から自動決定

	// メインアプリケーション処理部
	void *prPrsEv; //!< vProcessEvCoreSlpまたはvProcessEvCorePwrなどの処理部へのポインタ
	uint8 u8Hnd_vProcessEvCore; //!< vProcessEvCore のハンドル

	// DEBUG
	uint8 u8DebugLevel; //!< デバッグ出力のレベル

	// Wakeup
	bool_t bWakeupByButton; //!< TRUE なら起床時に DI 割り込みにより起床した
	uint32 u32SleepDur; //!< スリープ間隔 [ms]

	// mode3 fps
	uint8 u8FpsBitMask; //!< mode=3 連続送信時の秒間送信タイミングを判定するためのビットマスク (64fps のカウンタと AND を取って判定)

	// Network mode
	teNwkMode eNwkMode; //!< ネットワークモデル(未使用：将来のための拡張用)
	uint8 u8AppLogicalId; //!< ネットワーク時の抽象アドレス 0:親機 1~:子機, 0xFF:通信しない

	// Network context
	tsToCoNet_Nwk_Context *pContextNwk; //!< ネットワークコンテキスト(未使用)
	tsToCoNet_NwkLyTr_Config sNwkLayerTreeConfig; //!< LayerTree の設定情報(未使用)

	// 中継
	uint8 u8max_hops; //!< 最大中継ホップ数 (1-3)

	// Flash Information
	tsFlash sFlash; //!< フラッシュからの読み込みデータ
	int8 bFlashLoaded; //!< フラッシュからの読み込みが正しく行われた場合は TRUE

	uint32 u32DIO_startup; //!< 電源投入時のIO状態

	// config mode
	uint8 u8Mode; //!< 動作モード(E_IO_MODE_CHILD_SLP_10SEC)
	bool_t bConfigMode; // 設定モード

	// button manager
	tsBTM_Config sBTM_Config; //!< ボタン入力（連照により状態確定する）管理構造体
	PR_BTM_HANDLER pr_BTM_handler; //!< ボタン入力用のイベントハンドラ (TickTimer 起点で呼び出す)
	uint32 u32BTM_Tick_LastChange; //!< ボタン入力で最後に変化が有ったタイムスタンプ (操作の無効期間を作る様な場合に使用する)

	// ADC
	tsObjData_ADC sObjADC; //!< ADC管理構造体（データ部）
	tsSnsObj sADC; //!< ADC管理構造体（制御部）
	bool_t bUpdatedAdc; //!< TRUE:ADCのアップデートが有った。アップデート検出後、FALSE に戻す事。
	uint8 u8AdcState; //!< ADCの状態 (0xFF:初期化前, 0x0:ADC開始要求, 0x1:AD中, 0x2:AD完了)

	// latest state
	tsIOData sIOData_now; //!< 現時点での IO 情報
	tsIOData sIOData_reserve; //!< 保存された状態(0がデフォルトとする)
	uint8 u8IOFixState; //!< IOの読み取り確定ビット
	uint32 u32AdcLastTick; //!< 最後に ADC を開始した時刻

	// Counter
	uint32 u32CtTimer0; //!< 64fps カウンタ。スリープ後も維持
	uint16 u16CtTimer0; //!< 64fps カウンタ。起動時に 0 クリアする
	uint16 u16CtRndCt; //!< 起動時の送信タイミングにランダムのブレを作る

	uint8 u8UartReqNum; //!< UART の要求番号

	uint16 u16TxFrame; //!< 送信フレーム数
	uint8 u8SerMsg_RequestNumber; //!< シリアルメッセージの要求番号
} tsAppData;


#endif /* APPDATA_H_ */
