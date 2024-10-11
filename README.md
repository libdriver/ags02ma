[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AGS02MA

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ags02ma/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AGS02MA is a high-performance TVOC sensor which is equipped with a dedicated ASIC chip, adopting special digital module acquisition technology and gas sensing technology, to ensure good performance of high reliability, long-term stability, low power consumption, high sensitivity. Output signal of AGS02MA is standard I²C. Each sensor is fully calibrated and tested before delivery to meet the large-scale applications of customers.

LibDriver AGS02MA is the full function driver of AGS02MA launched by LibDriver.It provides the function of reading TVOC, etc. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AGS02MA source files.

/interface includes LibDriver AGS02MA IIC platform independent template.

/test includes LibDriver AGS02MA driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AGS02MA sample code.

/doc includes LibDriver AGS02MA offline document.

/datasheet includes AGS02MA datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/ags02ma/index.html](https://www.libdriver.com/docs/ags02ma/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.