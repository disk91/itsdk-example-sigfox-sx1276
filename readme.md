# SX1276 / Sigfox on Murata module example code

This example code is demonstrating how to implement a sigfox communication on a Murata CMWX1ZZABZ module (stm32 + sx1276). This example is based on [Disk91 IoT SDK repository](https://github.com/disk91/stm32-it-sdk) where the driver code is.

The hardware configuration has been set with CubeMX.

You can get details on this example in the [related blog post on disk91.com](https://www.disk91.com/2019/technology/sigfox/murata-abz-sigfox-connectivity/)

## Status
** Ready **

## Dependencies
* This example requires [Disk91 IoT SDK version >= 1.5](https://github.com/disk91/stm32-it-sdk/releases/tag/v1.5.0)

## Installation

Watch the setup video for getting started (select HD display). This video is about the LoRaWan example but the principles are the same.

[![Alt text](https://img.youtube.com/vi/VEWrr4t8ujo/0.jpg)](https://www.youtube.com/watch?v=VEWrr4t8ujo)

1. Clone this repository and open it with AC6 environment [See here on how to install it](https://www.disk91.com/2018/technology/hardware/getting-started-with-nucleo32-stm32l031/)

2. Clone the [Disk91 STM32 IoT SDK repository](https://github.com/disk91/stm32-it-sdk) in the Project root directory to add the needed sdk dependencies. This project has been tested & refied with SDK [Version 1.5](https://github.com/disk91/stm32-it-sdk/releases/tag/v1.5.0) 

## Usage

* A console for debug is accessible on USART2 @ 115000 ; the sigfox stack trace are activated
* A console for configuration is accessible on USART1 @ 9600 ; type "?" to access the command. "changeme" to access the private extension to modify the configuration.

## License

This code and ItSdk are under GPLv3. You can use it freely, you can modify, redistribute but *you must* to publish your source code. Other licenses can be obtained by contacting me on [disk91.com](https://www.disk91.com)
