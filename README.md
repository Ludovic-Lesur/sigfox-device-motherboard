# Description

The **Sigfox Device Motherboard** is a generic radio platform which can be used in various remote applications using **Sigfox long-range connectivity**.

The design is an original mix between an evolutive **development board** and a **finished product**: multiple GPIOs can be used to extend the board capabilities, while the 80x50mm form factor and its embedded PCB antenna are suited for a final integration. The BOM can also be adjusted according to the targetted use-case.

The board embeds the following features:

* **3 digital sensors**: temperature/humidity, light and accelerometer.
* **8 GPIOs** with programmable functions (digital input/output, analog front-end, ADC, USART, SPI, etc.).
* **I2C interface** to connect additionnal sensors.
* **HMI** including an RGB LED, a push button and a radio indicator (top or bottom mounted).
* Multiple **power configurations**: coin cells, secondary battery with solar charging or USB connector.
* **External power switch** to control an external circuit.
* **Low power transceiver** with **PCB antenna** or UFL connector.

# Hardware

## Revisions

The board was designed on **Circuit Maker V2.0**. Below is the list of hardware revisions:

| Hardware revision | Description | `cmake_hw_version` | Status |
|:---:|:---:|:---:|:---:|
| [SDM HW1.0](https://365.altium.com/files/42D89E56-8F99-44A0-8EC9-BADE76D3B536) | Initial version. | `HW1_0` | :hammer: |

## Architecture

<p align="center">
<img src="https://github.com/Ludovic-Lesur/sigfox-device-motherboard/wiki/images/sdm-hw-architecture.drawio.png" width="600"/>
</p>

# Embedded software

## Environment

The firmware is developed under **Eclipse IDE** and **GNU MCU** plugin. The `script` folder contains Eclipse run/debug configuration files and **JLink** scripts to flash the MCU.

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

## Flash

### Preparation

* **Build** the desired version (with IDE or `cmake`) or **download** a specific [firmware release](https://github.com/Ludovic-Lesur/sigfox-device-motherboard/releases) (expand the `Assets` menu, download the corresponding artifact and extract the binary files from the `zip`).
* Connect the flashing tool to the **P5 connector** located in the edge of the PCB (standard SWD pinout).

### ST-Link on Nucleo board

* Make sure that the ST-LINK/NUCLEO jumpers (generally designated by **CN2**) are not fitted, in order to **select the external programming connector** instead of the internal MCU.
* An **MSC disk** named `NODE_XXXXXX` should be mounted by the system after USB plugging. If not, download the [ST Cube Programmer](https://www.st.com/en/development-tools/stm32cubeprog.html) software which will install the required drivers. If the MSC disk is still not mounted, follow the ST-Link probe procedure thereafter.
* **Copy/paste** or **click/drop** the `bin` file into the disk.

### ST-Link probe

* Download the [ST Cube Programmer](https://www.st.com/en/development-tools/stm32cubeprog.html) software.
* Launch the software (it might be necessary to run it as **root** or to install specific **USB rules** for the probe to be recognized).
* In the right panel, select `ST-LINK` and click `Connect`.
* Click on the `Open file` tab and select the `hex` file to flash.
* Click on the `Download` button.
* Perform a **memory check** with the `Verify` button located under the `Download` button menu.
* If the operation completed successfully, click on `Disconnect` in the right panel.

### Segger J-Link probe

* Download the [Segger J-Link](https://www.segger.com/downloads/jlink/) software.
* Launch the `JFlashLite` tool.
* Set target device to **STM32L051K8**, target interface to **SWD**, speed to **4000kHz** and click `OK`.
* Open the `hex` file to flash.
* Click on the `Program Device` button.

### Final steps

* Check on the platform if the device has properly rebooted with the **expected firmware version**.
