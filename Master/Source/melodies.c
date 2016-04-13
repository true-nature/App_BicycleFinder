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
#include <jendefs.h>
#include <utils.h>

#ifdef JN516x
# define USE_EEPROM //!< JN516x でフラッシュを使用する
#endif

#include "Master.h"

#include "ccitt8.h"
#include "mml.h"
#include "common.h"
#include "config.h"
#include "sercmd_gen.h"

#ifdef USE_EEPROM
# include "eeprom_6x.h"
#endif

#include "melodies.h"

#define FLASH_MAGIC_NUMBER (0xA501EF5A ^ APP_ID) //!< フラッシュ書き込み時のマジック番号  @ingroup FLASH

#define MML_OPER_WRITE 1
#define MML_OPER_READ 2
#define MML_EEPROM_START (EEPROM_6X_SEGMENT_SIZE)

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
 * - >: 1オクターブ上げる
 * - <: 1オクターブ下げる
 *
 */

// ちょうちょ
const uint8 au8Mml_Butterfly[] =
		"O6T96 GEE2 FDD2 CDEF GGG2 GEEE FDDD CEGG EE2";
// Happy Birthday
const uint8 au8Mml_HappyBirthday[] =
		"O6T96 C8.C16D8.D16C4 F4E4.R8 C8.C16D8.D16C4 G4F4.R8 C8.C16>C8.C16<A4 F8.F16E16.E16.E16.D2 R2 B-8.B-16A8.A16F4 G4F4.R8";
// Canon (Johann Pachelbel)
const uint8 au8Mml_Canon[] =
		"O5T180L8"
		"A4F#GA4F#G A<AB>C#DEF#G F#4DEF#4<F#G ABAGAF#GA G4BAG4F#E F#EDEF#GAB G4BAB4>C#D C#<B>C#DEF#GA"
		"A4F#GA4F#G A<AB>C#DEF#G F#4DEF#4<F#G ABAGA>DC#D <B4>DC#<B4AG AGF#GAB >C#D <B4>DC#D4C#<B >C#DEDC#D<B>C#";
// Canon (arranged)
const uint8 au8Mml_Canon2[] =
		"O5T180L8"
		"A4F#GA4F#G R<AB>C#DEF#G F#4DEF#4<F#G RBAGAF#GA G4BAG4F#E REDEF#GAB G4BAB4>C#D R<B>C#DEF#GA"
		"A4F#GA4F#G A<AB>C#DEF#G F#4DEF#4<F#G ABAGA>DC#D <B4>DC#<B4AG AGF#GAB >C#D <B4>DC#D4C#<B >C#DEDC#D<B>C# ";
// Jingle Bells
const uint8 au8Mml_JingleBells[] =
		"O5T220L4 G G>EDC <G2.G G>EDC <A2.A A>FED <B2B2 >GGFD E2.<G G>EDC <G2.G G>EDC <A2.A A>FED"
		"GGGG8G8 AGFD C1 EEE2 EEE2 EGC.D8 E1 FFFF8F8 FEEE EDDE D2G2 EEE2 EEE2 EGC.D8 E1 FFFF FEEE GGFD C1";
// Twinkle Twinkle Little Star
const uint8 au8Mml_TwincleStar[] =
		"O6T120L4 CCGGAAG2 FFEEDDC2 GGFFEED2 GGFFEED2 CCGGAAG2 FFEEDDC2";
// When The Saints Go Marching In
const uint8 au8Mml_SaintsMarch[] =
		"O6T200L4 CEFG1&G CEFG1&G CEFG2E2C2E2 D1&D EEDC2.C E2G2 GF2.&F2 EFG2E2C2D2C1";
// Silent(無音)
const uint8 au8Mml_Silent[] =
		"O6T96L2 RR RR RR RR RR RR";

const uint8 *au8MmlBank[MMLBANK_COUNT] = {
		au8Mml_Butterfly,
		au8Mml_HappyBirthday,
		au8Mml_Canon,
		au8Mml_JingleBells,
		au8Mml_TwincleStar,
		au8Mml_SaintsMarch,
		au8Mml_Silent,
};

