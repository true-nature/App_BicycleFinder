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


#ifndef INTERACTIVE_H_
#define INTERACTIVE_H_

#include <string.h>

#include <jendefs.h>
#include <AppHardwareApi.h>

// Serial options
#include <serial.h>
#include <fprintf.h>
#include <sprintf.h>

//#include "modbus_ascii.h"
#include "sercmd_gen.h"
#include "input_string.h"

#include "flash.h"

/*************************************************************************
 * アプリ依存度が高い定義
 *************************************************************************/
#include "../Source_User/Interactive_User.h"
#include "appsave.h"

/*************************************************************************
 * プロトタイプ宣言
 *************************************************************************/
void Interactive_vInit();
void Interactive_vReInit();
void Interactive_vSetMode(bool_t bVerbose, uint16 u16screen_refresh);
bool_t Interactive_bGetMode();

bool_t Config_bLoad(tsFlash *p);
void vHandleSerialInput();

extern void vSerInitMessage();
extern void vProcessSerialCmd(tsSerCmd_Context *pCmd);

/*************************************************************************
 * マクロ定義
 *************************************************************************/
#define V_PRINT(...) if (Interactive_bGetMode()) vfPrintf(&sSerStream,__VA_ARGS__) //!< VERBOSE モード時の printf 出力
#define V_PUTCHAR(c) if (Interactive_bGetMode()) (&sSerStream)->bPutChar(sSerStream.u8Device, c) //!< VERBOSE モード時の putchar 出力
#define V_FLUSH() if (Interactive_bGetMode()) WAIT_UART_OUTPUT(UART_PORT) //!< VERBOSE モード時の FLUSH ポーリング
#define V_PRINTF V_PRINT

#define S_PRINT(...) if(!Interactive_bGetMode()) vfPrintf(&sSerStream,__VA_ARGS__) //!< 非VERBOSE モード時の printf 出力
#define S_PUTCHAR(c) if(!Interactive_bGetMode()) sSerStream.bPutChar(sSerStream.u8Device, c) //!< 非VERBOSE モード時の putchar 出力
#define S_FLUSH() if (!Interactive_bGetMode()    ) SERIAL_vFlush(UART_PORT)//!< 非VERBOSE モード時の FLUSH ポーリング
#define S_PRINTF S_PRINT

#define A_PRINTF S_PRINT
#define A_PRINT S_PRINT
#define A_PUTCHAR S_PUTCHAR
#define A_FLUSH S_FLUSH

#define FL_MASTER_u32(c) sAppData.sFlash.sData.u32##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_u32(c) sConfig_UnSaved.u32##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_u32(c) (sConfig_UnSaved.u32##c != 0xFFFFFFFF)  //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define FL_MASTER_u16(c) sAppData.sFlash.sData.u16##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_u16(c) sConfig_UnSaved.u16##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_u16(c) (sConfig_UnSaved.u16##c != 0xFFFF)  //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define FL_MASTER_u8(c) sAppData.sFlash.sData.u8##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_u8(c) sConfig_UnSaved.u8##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_u8(c) (sConfig_UnSaved.u8##c != 0xFF) //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define FL_MASTER_i32(c) sAppData.sFlash.sData.i32##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_i32(c) sConfig_UnSaved.i32##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_i32(c) (sConfig_UnSaved.i32##c != -2147483648)  //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define FL_MASTER_i16(c) sAppData.sFlash.sData.i16##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_i16(c) sConfig_UnSaved.i16##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_i16(c) (sConfig_UnSaved.i16##c != -32768)  //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define FL_MASTER_i8(c) sAppData.sFlash.sData.i8##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_UNSAVE_i8(c) sConfig_UnSaved.i8##c //!< 構造体要素アクセス用のマクロ @ingroup FLASH
#define FL_IS_MODIFIED_i8(c) (sConfig_UnSaved.i8##c != -128)  //!< 構造体要素アクセス用のマクロ @ingroup FLASH

#define INIT_VAL_i32 -2147483648			//	符号ありint32の初期値
#define INIT_VAL_i16 -32768					//	符号ありint16の初期値
#define INIT_VAL_i8 -128					//	符号ありint8の初期値

#define VERSION_U32 ((VERSION_CODE << 24) | (VERSION_MAIN << 16) | (VERSION_SUB << 8) | (VERSION_VAR))

/*************************************************************************
 * その他マクロ
 *************************************************************************/
/* フラッシュ設定パリティ設定（マスク）*/
#define APPCONF_UART_CONF_PARITY_MASK 0x3
#define APPCONF_UART_CONF_STOPBIT_MASK 0x4
#define APPCONF_UART_CONF_WORDLEN_MASK 0x8

/*************************************************************************
 * その他マクロ
 *************************************************************************/

/****************************************************************************
 * フラッシュ設定情報
 ***************************************************************************/

/** @ingroup FLASH
 * フラッシュ設定内容の列挙体
 */
enum {
	E_APPCONF_APPID,     //!< アプリケーションID
	E_APPCONF_CHMASK,    //!< チャネルマスク
	E_APPCONF_TX_POWER,  //!< TX 出力
	E_APPCONF_ID,        //!< 8bitのID(ネットワークアドレス)
	E_APPCONF_ROLE,      //!<
	E_APPCONF_LAYER ,    //!<
	E_APPCONF_SLEEP4,    //!< mode4 のスリープ期間設定
	E_APPCONF_SLEEP7,    //!< mode7 のスリープ期間設定
	E_APPCONF_FPS,       //!< 連続送信モードの秒あたりの送信数
	E_APPCONF_PWM_HZ,    //!< PWM の周波数
	E_APPCONF_SYS_HZ,    //!<
	E_APPCONF_OPT,       //!< DIOの入力方法に関する設定
	E_APPCONF_BAUD_SAFE, //!< BPS ピンをGにしたときのボーレート
	E_APPCONF_BAUD_PARITY, //!< BPS ピンをGにしたときのパリティ設定 (0:None, 1:Odd, 2:Even)
	E_APPCONF_OPT2,      //!< オプション設定２
	E_APPCONF_TEST
};

/** @ingroup FLASH
 * フラッシュ設定で ROLE に対する要素名の列挙体
 * (未使用、将来のための拡張のための定義)
 */
enum {
	E_APPCONF_ROLE_MAC_NODE = 0,  //!< MAC直接のノード（親子関係は無し）
	E_APPCONF_ROLE_NWK_MASK = 0x10, //!< NETWORKモードマスク
	E_APPCONF_ROLE_PARENT,          //!< NETWORKモードの親
	E_APPCONF_ROLE_ROUTER,        //!< NETWORKモードの子
	E_APPCONF_ROLE_ENDDEVICE,     //!< NETWORKモードの子（未使用、スリープ対応）
	E_APPCONF_ROLE_SILENT = 0x7F, //!< 何もしない（設定のみ)
};

#endif /* INTERACTIVE_H_ */
