[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AGS02MA

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ags02ma/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AGS02MA は、専用の ASIC チップを搭載し、特殊なデジタル モジュール取得技術とガス検知技術を採用した高性能 TVOC センサーで、高い信頼性、長期安定性、低消費電力、高感度の優れた性能を保証します。AGS02MA の出力信号は標準 I²C です。各センサーは、顧客の大規模なアプリケーションに対応するために、出荷前に完全に調整およびテストされています。

LibDriver AGS02MA は、LibDriver が開発した AGS02MA のフル機能ドライバです。TVOC の読み取り機能などを提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AGS02MAのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AGS02MA用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AGS02MAドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AGS02MAプログラミング例が含まれています。

/ docディレクトリには、LibDriver AGS02MAオフラインドキュメントが含まれています。

/ datasheetディレクトリには、AGS02MAデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_ags02ma_basic.h"

uint8_t res;
uint32_t i;
uint32_t ppb;

/* basic init */
res = ags02ma_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    ags02ma_interface_delay_ms(2000);

    /* read data */
    res = ags02ma_basic_read((uint32_t *)&ppb);
    if (res != 0)
    {
        (void)ags02ma_basic_deinit();

        return 1;
    }

    /* output */
    ags02ma_interface_debug_print("ags02ma: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    ags02ma_interface_debug_print("ags02ma: tvoc is %dppb.\n", ppb);
    
    ...
}

...
    
/* deinit */
(void)ags02ma_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ags02ma/index.html](https://www.libdriver.com/docs/ags02ma/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。