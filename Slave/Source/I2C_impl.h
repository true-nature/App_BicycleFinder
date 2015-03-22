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

#ifndef I2C_IMPL_H_
#define I2C_IMPL_H_

/****************************************************************************/
/***        INCLUDES                                                      ***/
/****************************************************************************/
#include <jendefs.h>
#include <AppHardwareApi.h>

/****************************************************************************/
/***        PROTOTYPE DEFS                                                ***/
/****************************************************************************/
void vProcessI2CCommand(uint8 *p, uint16 u16len, uint8 u8AddrSrc);
#ifdef USE_I2C_ACM1620
bool_t bDraw2LinesLcd_ACM1602(const char *puUpperRow,
		const char *puLowerRow);
#endif
#ifdef USE_I2C_AQM0802A
bool_t bDraw2LinesLcd_AQM0802A(const char *puUpperRow,
		const char *puLowerRow);
#endif



#endif /* I2C_H_ */
