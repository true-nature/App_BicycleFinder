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

#include <jendefs.h>
#include "melody_defs.h"

#ifdef JN516x
# define USE_EEPROM //!< JN516x でフラッシュを使用する
#endif

#include "ccitt8.h"
#include "config.h"

#ifdef USE_EEPROM
# include "eeprom_6x.h"
#endif

#define FLASH_MAGIC_NUMBER (0xA501EF5A ^ APP_ID) //!< フラッシュ書き込み時のマジック番号  @ingroup FLASH

/**
 * メロディの定義
 *
 * - A-G: 音階の指定、続けて半音階、長さ、符点、タイ記号を指定可能
 *   - +,#,-         : 半音階の指定 (+,#: 半音上げる  -: 半音下げる)
 *   - 1,2,4,8,16,32 : 長さ (1が全音符)、指定なき場合はデフォルト値(4)
 *                     ３連符は未対応です。テンポの変更で乗り切ってください。
 *   - .             : 符点 (全音符には無効)
 *   - &             : タイ記号（この音符を一杯の長さまで演奏し、次の音符と連結する)
 *   - 例
 *     - A+16.       : A（ラ)の符点付き１６分音符
 *     - G2&G8       : タイで連結する
 *
 *  - Ln: 音符の長さ指定がない場合の長さを指定する
 *    - 例
 *      - C4D16E16F16G16 は L16C4DEFG と同じ指定である
 *
 *  - (...) : 括弧内の音符を長さいっぱいで演奏する（レガート）
 *    - 例
 *      - L8(C2DEF)GA2 は、CDEFはいっぱいの長さで、Gは通常の長さとなり、GとAの間に
 *        ごく短い音の切れ目が発生する。
 *
 *  - [...], [n...] : 括弧内をリピート再生する
 *    - n を指定した場合、n 回再生する。nは2〜255まで有効。
 *    - 例
 *      - [3CDEF] は CDEFCDEFCDEF と同じである
 *
 * - Tn: テンポの指定 (n は 32〜240 まで有効)
 *
 * - On (n=3..8): オクターブの指定
 *   圧電ブザーの場合 O3,O4 の音階は、うまく出ないようです。
 *
 * - <: 1オクターブ上げる
 * - >: 1オクターブ下げる
 *
 */

const uint8 au8MML[4][256] = {
		// ちょうちょ
		"O6T96 GEE2 FDD2 CDEF GGG2 GEEE FDDD CEGG EE2",

		// トロイメライ
		"O5T88L8 C4F2&F(EFA<C)FF2(EDC)F>(GAB-)<D>(FGA)<C>G2",

		// 春の海
		//"O6T96L16 <(DE>B<D> ABGA EGDE >B<D>A)B (EGAB <DEG)A >(B<DEG AB<D)E >"
		//"R1 (D8E4. G8.E32D32>B8A8) B1 E2. (<DEGA B4.&BA) B. R2.",
		// Happy Birthday
		"O6T96 C8.C16D8.D16C4 F4E4.R8 C8.C16D8.D16C4 G4F4.R8 C8.C16<C8.C16>A4 F8.F16E16.E16.E16.D2 R2 B-8.B-16A8.A16F4 G4F4.R8",

		// 停止
		"R"
};

tsUserMML sUserMMLData;


/**
 * MMLの読み出し
 * バージョン等のチェックを行い、問題が有れば FALSE を返す
 *
 * @param p
 * @return
 */
bool MML_bLoad(tsUserMML *psMml) {
	bool_t bRet = FALSE;

#ifdef USE_EEPROM
    if (EEP_6x_bRead(1, sizeof(sUserMMLData), (uint8 *)psMml)) {
    	bRet = TRUE;
    }
#endif
    // validate content
    if (bRet && psMml->u32Magic != FLASH_MAGIC_NUMBER) {
    	bRet = FALSE;
    }
    if (bRet && psMml->u8CRC != u8CCITT8(psMml->u8Data, sizeof(psMml->u8Data))) {
    	bRet = FALSE;
    }
    // set default
    if (!bRet) {
    	memset(psMml->u8Data, 0, sizeof(psMml->u8Data));
    	strncpy(psMml->u8Data, au8MML[0], sizeof(psMml->u8Data) - 1);
    	bRet = MML_bSave(psMml);
    }
    return bRet;
}


bool MML_bSave(tsUserMML *psMml) {
	bool_t bRet = FALSE;

	psMml->u32Magic = FLASH_MAGIC_NUMBER;
	psMml->u8CRC = u8CCITT8(psMml->u8Data, sizeof(psMml->u8Data));
#ifdef USE_EEPROM
    if (EEP_6x_bWrite(1, sizeof(sUserMMLData), (uint8 *)psMml)) {
    	bRet = TRUE;
    }
#endif
    return bRet;
}

