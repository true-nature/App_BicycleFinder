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

#ifndef _MELODY_DEFS_H
#define _MELODY_DEFS_H

#include <jendefs.h>

/**
 * メロディの定義
 */
const uint8 au8MML[4][256];

/** @ingroup FLASH
 * フラッシュデータ構造体
 * - u32Magic と u8CRC により、書き込みデータが有為かどうか判定する
 * - u8CRC は データ中の CRC8 チェックサム
 */
typedef struct _tsUserMML {
	uint32 u32Magic;
	uint8 u8Data[123];
	uint8 u8CRC;
} tsUserMML;

tsUserMML sUserMMLData;

bool MML_bLoad(tsUserMML *p);
bool MML_bSave(tsUserMML *psMml);
void vProcessMmlCommand(uint8 *p, uint16 u16len, uint8 u8AddrSrc);

#endif
