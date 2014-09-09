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

// 本ファイルは、Interactive.h からインクルードされる

/*************************************************************************
 * OPTION 設定
 *************************************************************************/
#define VERSION_CODE 0

/*************************************************************************
 * OPTION 設定
 *************************************************************************/

#define E_APPCONF_OPT_LOW_LATENCY_INPUT 0x0001UL //!< Hi>Lo を検知後直ぐに送信する。 @ingroup FLASH
#define E_APPCONF_OPT_REGULAR_PACKET_NO_TRANSMIT 0x0002UL //!< 定期送信を行わない(1秒置き)
#define E_APPCONF_OPT_REGULAR_PACKET_NO_DISP 0x0004UL //!< 定期送信パケットを表示しない(1秒置きと連射)
#define E_APPCONF_OPT_NO_ADC_BASED_TRANSMIT 0x0010 //!< ADCの変化に応じた送信を禁止する。 @ingroup FLASH
#define E_APPCONF_OPT_DISABLE_ADC 0x0020 //!< ADCを計測しない。 @ingroup FLASH
#define E_APPCONF_OPT_ON_PRESS_TRANSMIT 0x0100UL //!< 押し下げ時のみ送信する特殊動作モード。 @ingroup FLASH
#define E_APPCONF_OPT_ROUTING_CHILD 0x8000UL //!< 中継可能な子機設定。 @ingroup FLASH
#define E_APPCONF_OPT_ROUTING_HOP2 0x1000UL //!< 中継段数を２にする。 @ingroup FLASH
#define E_APPCONF_OPT_ROUTING_HOP3 0x2000UL //!< 中継段数な３にする。 @ingroup FLASH
#define E_APPCONF_OPT_PWM_INVERT 0x10000UL //!< PWMをDUTYを反転する
#define E_APPCONF_OPT_PWM_INIT_LOW 0x20000UL //!< PWMを起床時にLOとする
#define E_APPCONF_OPT_DIO_LOW_ON_BOOT 0x100000 //!< 起床時にDIOを２秒だけLOにする (LED点灯)
#define E_APPCONF_OPT_PWM_LOW_ON_BOOT 0x200000 //!< 起床時にPWMを２秒だけ(AI=100%値)にする (LED点灯)

#define IS_APPCONF_OPT_LOW_LATENCY_INPUT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_LOW_LATENCY_INPUT) //!< E_APPCONF_OPT_LOW_LATENCY_INPUT 判定 @ingroup FLASH
#define IS_APPCONF_OPT_REGULAR_PACKET_NO_TRANSMIT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_REGULAR_PACKET_NO_TRANSMIT) //!< E_APPCONF_OPT_REGULAR_PACKET_NO_TRANSMIT 判定 @ingroup FLASH
#define IS_APPCONF_OPT_REGULAR_PACKET_NO_DISP() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_REGULAR_PACKET_NO_DISP) //!< E_APPCONF_OPT_REGULAR_PACKET_NO_DISP 判定 @ingroup FLASH
#define IS_APPCONF_OPT_NO_ADC_BASED_TRANSMIT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_NO_ADC_BASED_TRANSMIT) //!< E_APPCONF_OPT_NO_ADC_BASED_TRANSMIT判定 @ingroup FLASH
#define IS_APPCONF_OPT_DISABLE_ADC() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_DISABLE_ADC) //!< E_APPCONF_OPT_DISABLE_ADC判定 @ingroup FLASH
#define IS_APPCONF_OPT_ON_PRESS_TRANSMIT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_ON_PRESS_TRANSMIT) //!< E_APPCONF_OPT_ON_PRESS_TRANSMIT判定 @ingroup FLASH
#define IS_APPCONF_OPT_ROUTING_CHILD() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_ROUTING_CHILD) //!< E_APPCONF_OPT_ROUTING_END_DEVICE判定 @ingroup FLASH
#define IS_APPCONF_OPT_ROUTING_HOP2() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_ROUTING_HOP2) //!< E_APPCONF_OPT_ROUTING_HOP2判定 @ingroup FLASH
#define IS_APPCONF_OPT_ROUTING_HOP3() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_ROUTING_HOP3) //!< E_APPCONF_OPT_ROUTING_HOP3判定 @ingroup FLASH
#define IS_APPCONF_OPT_PWM_INVERT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_PWM_INVERT) //!< E_APPCONF_OPT_PWM_INVERT判定 @ingroup FLASH
#define IS_APPCONF_OPT_PWM_INIT_LOW() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_PWM_INIT_LOW) //!< E_APPCONF_OPT_PWM_INIT_LOW判定 @ingroup FLASH
#define IS_APPCONF_OPT_DIO_LOW_ON_BOOT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_DIO_LOW_ON_BOOT) //!< E_APPCONF_OPT_DIO_LOW_ON_BOOT判定 @ingroup FLASH
#define IS_APPCONF_OPT_PWM_LOW_ON_BOOT() (sAppData.sFlash.sData.u32Opt & E_APPCONF_OPT_PWM_LOW_ON_BOOT) //!< E_APPCONF_OPT_PWM_LOW_ON_BOOT判定 @ingroup FLASH

/** サイレントモードの判定マクロ  @ingroup FLASH */
#define IS_APPCONF_ROLE_SILENT_MODE() (sAppData.sFlash.sData.u8role == E_APPCONF_ROLE_SILENT)

/** PWM値の反転を考慮した値を設定する */
#define _PWM(c) (IS_APPCONF_OPT_PWM_INVERT() ? (1024-c) : c)
