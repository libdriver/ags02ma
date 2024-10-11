### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AGS02MA

#### 3.1 Command Instruction

1. Show ags02ma chip and driver information.

   ```shell
   ags02ma (-i | --information)
   ```

2. Show ags02ma help.

   ```shell
   ags02ma (-h | --help)
   ```

3. Show ags02ma pin connections of the current board.

   ```shell
   ags02ma (-p | --port)
   ```

4. Run ags02ma read test, num means test times. 

   ```shell
   ags02ma (-t read | --test=read) [--times=<num>]
   ```

5. Run ags02ma read function, num means test times.

   ```shell
   ags02ma (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
ags02ma -i

ags02ma: chip is ASAIR AGS02MA.
ags02ma: manufacturer is ASAIR.
ags02ma: interface is IIC.
ags02ma: driver version is 1.0.
ags02ma: min supply voltage is 3.3V.
ags02ma: max supply voltage is 5.5V.
ags02ma: max current is 33.00mA.
ags02ma: max temperature is 50.0C.
ags02ma: min temperature is 0.0C.
```

```shell
ags02ma -p

ags02ma: SCL connected to GPIOB PIN8.
ags02ma: SDA connected to GPIOB PIN9.
```

```shell
ags02ma -t read --times=3

ags02ma: chip is ASAIR AGS02MA.
ags02ma: manufacturer is ASAIR.
ags02ma: interface is IIC.
ags02ma: driver version is 1.0.
ags02ma: min supply voltage is 3.3V.
ags02ma: max supply voltage is 5.5V.
ags02ma: max current is 33.00mA.
ags02ma: max temperature is 50.0C.
ags02ma: min temperature is 0.0C.
ags02ma: start read test.
ags02ma: version is 0x76.
ags02ma: tvoc is 1879ppb.
ags02ma: tvoc is 1882ppb.
ags02ma: tvoc is 1886ppb.
ags02ma: resistance is 1909500.00ohm.
ags02ma: modify slave address 0x1A.
ags02ma: finish read test.
```

```shell
ags02ma -e read --times=3

ags02ma: 1/3.
ags02ma: tvoc is 1831ppb.
ags02ma: 2/3.
ags02ma: tvoc is 1836ppb.
ags02ma: 3/3.
ags02ma: tvoc is 1842ppb.
```

```shell
ags02ma -h

Usage:
  ags02ma (-i | --information)
  ags02ma (-h | --help)
  ags02ma (-p | --port)
  ags02ma (-t read | --test=read) [--times=<num>]
  ags02ma (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <read>, --test=<read>       Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

