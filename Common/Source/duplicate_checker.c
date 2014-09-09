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
#include "duplicate_checker.h"

/** @ingroup DUPCHK
 * 重複チェックの初期化
 * @param p 管理構造体
 */
void DUPCHK_vInit(tsDupChk_Context *p) {
	memset(p, 0, sizeof(tsDupChk_Context));
}


/** @ingroup DUPCHK
 * リストの探索とタイムアウト処理を行う。
 *
 * @param p 管理構造体
 * @param u32Addr 探索アドレス。０の場合はタイムアウト処理のみ行う
 * @param pu32Key キー情報
 * @return
 */
bool_t DUPCHK_bFind(tsDupChk_Context *p, uint32 u32Addr, uint32 *pu32Key) {
	//bool_t bRet = FALSE;
	int i;
	for(i = 0; i < DUPCHK_MAX_HISTORY; i++) {
		if (u32TickCount_ms - p->au32ScanListTick[i] > DUPCHK_TIMEOUT) {
			p->au32ScanListTick[i] = 0;
			p->au32ScanListAddr[i] = 0;
		} else {
			if (u32Addr && (u32Addr == p->au32ScanListAddr[i])) {
				*pu32Key = p->au32ScanListKey[i];
				return TRUE;
			}
		}
	}
	return FALSE;
}

/** @ingroup DUPCHK
 * リストへの追加を行う。
 *
 * @param p 管理構造体
 * @param u32Addr 探索アドレス
 * @param u32Key キー情報
 * */
void DUPCHK_vAdd(tsDupChk_Context *p, uint32 u32Addr, uint32 u32Key) {
	int i, idxPrimary = DUPCHK_MAX_HISTORY, idxSecondary = DUPCHK_MAX_HISTORY, idxOldest = DUPCHK_MAX_HISTORY;
	uint32 u32TickDelta = 0;
	for(i = 0; i < DUPCHK_MAX_HISTORY; i++) {
		if (p->au32ScanListAddr[i] == u32Addr) {
			// 同じアドレスが見つかったら、こちらに登録する（アルゴリズム上無いはずだが）
			idxPrimary = i;
		}
		if (p->au32ScanListAddr[i] == 0) {
			// 空のエントリ
			idxSecondary = i;
		}

		if (p->au32ScanListAddr[i]) {
			// 一番古いエントリ
			uint32 u32diff = u32TickCount_ms - p->au32ScanListTick[i];
			if (u32diff >= u32TickDelta) {
				idxOldest = i;
				u32TickDelta = u32diff;
			}
		}
	}

	if (idxPrimary < DUPCHK_MAX_HISTORY) {
		i = idxPrimary;
	} else if (idxSecondary < DUPCHK_MAX_HISTORY){
		i = idxSecondary;
	} else {
		i = idxOldest;
	}

	if (i < DUPCHK_MAX_HISTORY) {
		p->au32ScanListAddr[i] = u32Addr;
		p->au32ScanListTick[i] = u32TickCount_ms;
		p->au32ScanListKey[i] = u32Key;
	}
}

