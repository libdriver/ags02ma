### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ags02ma REQUIRED)
```

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
./ags02ma -i

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
./ags02ma -p

ags02ma: SCL connected to GPIO3(BCM).
ags02ma: SDA connected to GPIO2(BCM).
```

```shell
./ags02ma -t read --times=3

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
./ags02ma -e read --times=3

ags02ma: 1/3.
ags02ma: tvoc is 1831ppb.
ags02ma: 2/3.
ags02ma: tvoc is 1836ppb.
ags02ma: 3/3.
ags02ma: tvoc is 1842ppb.
```

```shell
./ags02ma -h

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

#### 3.3 Command Problem

1. There is some unknown problem in the iic interface of ags02ma on the raspberry board, one command may try many times to run successfully or run failed.
