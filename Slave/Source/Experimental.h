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

#ifndef EXPERIMENTAL_H_
#define EXPERIMENTAL_H_

/****************************************************************************/
/***        実験的な実装定義                                              ***/
/****************************************************************************/

/** @ingroup MASTER
 * Sleep 中に IO の出力状態を設定する
 *   DO0,1を Sleep 中は Hi, 稼働中は Lo
 */
#undef SET_DO_ON_SLEEP
#ifdef SET_DO_ON_SLEEP
#warning "EXPERIMENTAL: SET_DO_ON_SLEEP"
static uint8 u8SleepControl = 0; //!< 0:事前Sleep, 1:通常
#define PRE_SLEEP_ms 50
#endif

/** @ingroup MASTER
 * BROWNOUT 検出時にリセットする。
 */
#undef USE_BROWN_OUT_DETECT
#ifdef USE_BROWN_OUT_DETECT
# warning "#define USE_BROWN_OUT_DETECT"
#endif

/** @ingroup MASTER
 * AI4 の変わりに電源電圧を読み出して送信する。
 *
 * 2.5V 以上 (PWM=0%) 2.5V 以下 (PWM=50%), 2.3V以下 (PWM=100%)
 */
#undef USE_PWM4_AS_BAT_MONITOR
#ifdef USE_PWM4_AS_BAT_MONITOR
#warning "EXPERIMENTAL: USE_PWM4_AS_BAT_MONITOR"
#endif

/** @ingroup MASTER
 * 間欠モード時にゆっくり送信する
 */
#undef USE_SLOW_TX
#ifdef USE_SLOW_TX
#warning "EXPERIMENTAL: USE_SLOW_TX"
#endif
#endif /* EXPERIMENTAL_H_ */
