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

// 本ファイルは Interactive.c から include される

/** @ingroup FLASH
 * フラッシュ設定構造体をデフォルトに巻き戻します。
 * - ここでシステムのデフォルト値を決めています。
 *
 * @param p 構造体へのアドレス
 */
void Config_vSetDefaults(tsFlashApp *p) {
	p->u32appid = APP_ID;
	p->u32chmask = CHMASK;
	p->u8ch = CHANNEL;
	p->u8pow = 3;

	p->u8role = E_APPCONF_ROLE_MAC_NODE;
	p->u8layer = 1;

	p->u16SleepDur_ms = MODE4_SLEEP_DUR_ms;
	p->u16SleepDur_s = (MODE7_SLEEP_DUR_ms / 1000);
	p->u8Fps = 32;

	p->u32PWM_Hz = 1000;

	p->u32baud_safe = UART_BAUD_SAFE;
	p->u8parity = 0; // none

#ifdef USE_TOCOSTICK
	p->u32Opt = E_APPCONF_OPT_DISABLE_ADC;  // ToCoStick では AI 入力は未接続なので無効化しておく
	p->u8id = 121; // ToCoStick では親機をデフォルトにする
#else
	p->u8id = 0;
	p->u32Opt = 0x00000120;
#endif

	p->u32Opt2 = 0;

	p->u8MML_idx = 0;
}
