# Description

The **Sigfox Device Motherboard** is a generic radio platform which can be used in various remote applications using **Sigfox long-range connectivity**. The design is an original mix between an evolutive development board and a finished product: multiple GPIOs can be used to extend the board capabilities, while the 80x50mm form factor and its embedded PCB antenna are suited for a final integration. The BOM can also be adjusted according to the targetted use-case. The board embeds the following features:

* **3 digital sensors**: temperature/humidity, light and accelerometer.
* **8 GPIOs** with programmable functions (digital input/output, analog front-end, ADC, USART, SPI, etc.).
* **I2C connector** to connect additionnal sensors.
* **HMI** including an RGB LED, a push button and a radio indicator (top or bottom mounted).
* Multiple **power configurations**: coin cells, secondary battery with solar charging or USB connector.
* **External power switch** to control an external module.
* **Low power transceiver** with **PCB antenna** or UFL connector.

# Hardware

The board was designed on **Circuit Maker V2.0**. Below is the list of hardware revisions:

| Hardware revision | Description | `cmake_hw_version` | Status |
|:---:|:---:|:---:|:---:|
| [SDM HW1.0](https://365.altium.com/files/42D89E56-8F99-44A0-8EC9-BADE76D3B536) | Initial version. | `HW1_0` | :white_check_mark: |

# Embedded software

## Environment

The embedded software is developed under **Eclipse IDE** version 2025-06 (4.36.0) and **GNU MCU** plugin. The `script` folder contains Eclipse run/debug configuration files and **JLink** scripts to flash the MCU.

## Target

The board is based on the **STM32L051K8U6** microcontroller of the STMicroelectronics L0 family. Each hardware revision has a corresponding **build configuration** in the Eclipse project, which sets up the code for the selected board version.

## Structure

The project is organized as follow:

* `drivers` :
    * `device` : MCU **startup** code and **linker** script.
    * `registers` : MCU **registers** address definition.
    * `registers` : MCU **registers** address definition.
    * `peripherals` : internal MCU **peripherals** drivers.
    * `components` : external **components** drivers.
    * `utils` : **utility** functions.
* `middleware` :
    * `analog` : High level **analog measurements** driver.
    * `cli` : **AT commands** implementation.
    * `power` : Board **power tree** manager.
    * `sigfox` : **Sigfox EP_LIB** and **ADDON_RFP** submodules and low level implementation.
* `application` : Main **application**.

## Build

The project can be compiled by command line with `cmake`.

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="script/cmake-arm-none-eabi/toolchain.cmake" \
      -DTOOLCHAIN_PATH="<arm_none_eabi_gcc_path>" \
      -DSDM_HW_VERSION="<cmake_hw_version>" \
      -DSDM_MODE_CLI=OFF \
      -G "Unix Makefiles" ..
make all
```
