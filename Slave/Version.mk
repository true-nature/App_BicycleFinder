VERSION_MAIN = 1
VERSION_SUB  = 7
VERSION_VAR  = 1

#1.7.0 2014/08/20 インタラクティブモードのファイル分離
#1.6.5 2014/06/20 通常モードのDI変化の判定で送信が行われなくなった不具合を修正
#1.6.4 2014/06/18 通常送信の抑制、出力の抑制オプションの追加
#1.6.3 2014/06/12 PWMのDuty反転、起床時にLEDを２秒点灯するオプションの追加
#1.6.2 2014/04/20 USE_SLOW_TX の実装
#1.6.1 2014/3/18 実験的機能：マルチレベルの中継に対応 (2ホップ,3ホップ), 中継子機に対応
#1.6.0 2014/2/27 新SDKに基づいたビルド
#1.5.1 2013/12/26 複数段階のホップ(3ホップまで対応)
#1.5.0  2013/12/26 1.3 系列に ToCoStick 対応ビルド定義をマージ
#1.3.13 2013/12/26 ソース整備
#1.3.12 2013/11/15 オプションビット 0x20: ADC の計測を無効化(0xFFFF)する
#1.3.11 2013/11/14 I2C ポートを用いたチャネル切り替え機能(実験的な実装)
#1.3.10 2013/10/21 実験的な実装 (SET_DO_ON_SLEEP)
#1.3.9 2013/9/26 ボタン入力の初期化に問題が有ったので修正
#1.3.8 2013/9/20 Regular/Strong の ADC/DAC のデバッグ
#1.3.7 2013/9/20 I2C コマンド追加 (LCD 用)
#1.3.6 2013/9/2  EEPROM保存対応
#1.3.5 2013/8/20 LCQ AQM0802A のテスト対応
#1.3.4 2013/8/5  低レイテンシモードの動作で、Lo 割り込み直後に Hi が通知される可能性がある点を修正
#1.3.3 2013/7/30 ボタンのモードを追加
#1.3.2 2013/7/30 デバッグ中
#1.3.1 2013/7/30 1.3系リリーステストビルド
#1.3.0 2013/7/26 機能追加開始
#  - スリープ期間を０指定とすると、タイマーは稼働せず、割り込み稼働とする (mode7のみ)
#1.2.5 2013/7/25 MML実装のコードは破棄 (コンパイルだけ完了)
#1.2.4 2013/7/10 ボタン押下時連続送信モード (ON_PRESS_TRANSMIT) の追加
#1.2.2,3 2013/7/4 特殊要求のための実装
#1.2.1 2013/7/1 some fixes, I2C functions
#1.1.1 2013/6/27 1.1 bug fixed, 2nd testing version
#1.1.0 2013/6/25 1.1 before testing.
#1.0.3 2013/6/X temporary
#1.0.2 2013/6/7 Minor fixes
#1.0.1 2013/6/5 Release
#0.9.2 2013/6/4 RC2
#0.9.1 2013/6/4 Release Candidate1