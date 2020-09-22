# SX1276 / Sigfox on Murata module example code

This example code is demonstrating how to implement a sigfox communication on a Murata CMWX1ZZABZ module (stm32 + sx1276). This example is based on [Disk91 IoT SDK repository](https://github.com/disk91/stm32-it-sdk) where the driver code is.

The hardware configuration has been set with CubeMX.

You can get details on this example in the [related blog post on disk91.com](https://www.disk91.com/2019/technology/sigfox/murata-abz-sigfox-connectivity/)

## Status
** Ready for use **

## Dependencies
* This example requires [Disk91 IoT SDK version >= 1.6](https://github.com/disk91/stm32-it-sdk/tree/Version-1.6)
* This example requires [ST CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) the ST-Microelectronic free IDE based on Eclipse + GCC

## Installation
1. If you never start CubeIDE, do it to get your project's workspace created. Then open a terminal and go to this directory.
2. Clone this repository
	```sh
	[Workspace_CubeMx]# git clone https://github.com/disk91/itsdk-example-sigfox-sx1276.git
	```
3. Enter this repository
	```sh
	[Workspace_CubeMx]# cd itsdk-example-sigfox-sx1276
	```
4. Clone the ItSDK repository
	```sh
	[itsdk-example-sigfox-sx1276]# git clone -b Version-1.6 https://github.com/disk91/stm32-it-sdk.git
	``` 
5. In CubeIDE go to File >> Import >> Existing Projects into Workspace. Select the _itsdk-example-sigfox-sx1276_ directory and import the project.
6. Build the project in Release mode
7. You get a _itsdk-example-sigfox-sx1276.bin_ in the _Release_ folder
8. Connect the LRWAN ST board with USB
9. Open a serial tty on the _STM32 STLink_ USB Serial port with 9600bps configuration 
10. Copy the _itsdk-example-sigfox-sx1276.bin_ file on the automatically mounted drive (named *DIS_L072Z*)
11. The board programming led is blinking, then the program is running.

On the console, at this step you should see:
```
[INFO] S 0x10001001
Startup
Booting
- 
```
On the board, you should see:
 - LD1 blinking (this is part of the program) 
 - LD2 should be on (but this is a side effect of the DIO4 pin mutualization)
 - LD3 should be on (but this is a side effect of the Serial 1 pin mutualization)

If you want to better understand [how the LRWAN board led are mapped, take a look to this post](https://www.disk91.com/2019/technology/hardware/getting-started-with-st-murata-lorawan-board/)

## Configuration
The board is not yet configured for Sigfox: you need to setup different infromations:
- The Radio Zone
- The Device PAC
- The Device Key
- The device ID
This order is important as device ID is a trigger for this exemple.
To [obtain Sigfox credentials, read this post explaining the process to follow](https://www.disk91.com/2019/technology/sigfox/murata-abz-sigfox-connectivity/).

1. Test the console, typing ? on the serial port. You should get:
	```
	?
	--- Common
	?          : print help
	!          : print copyright
	v          : print version
	o          : print OK
	--- ConfigMng
	c          : print config
	C          : print shadow config
	```
2. Enter in admin mode by typing in the console _changeme_
	```
	changme
	OK
	```
3. Verify you are now in admin mode by typing _?_
	```
	-- Common
	?          : print help
	!          : print copyright
	v          : print version
	o          : print OK
	X          : exit console
	R          : reset device
	R!         : clear the whole eeprom
	l / L      : switch LowPower ON / OFF
	s          : print device state
	t          : print current time in S
	T          : print current cpu temperature in oC
	b          : print battery level
	B          : print VCC level
	r          : print last Reset Cause
	--- ErrorMng
	e          : print errors log
	E          : Clear the error logs
	--- SecureStore
	ss:R       : restore all SS to factory default
	SS:0:xxxx  : change the secure store dyn Key (12B)
	...
	```
4. configure Sigfox assuming
	- Device ID like : 00D206AF
	- Device PAC : 0000000000000000
	- Device KEY : 42394514F99016C3A7334A12CFFD4A2C
	These credentials can be use for your tests but you won't be able to register them as the PAC is invalid.
	Now you can type in the console to setup your device (if you copy/paste, you need to add a delay between each char)
	* Configure radio for Europe: _SC:A:01_
	* Configure PAC: _SC:C:0000000000000000_
	* Configure KEY: _SS:2:42394514F99016C3A7334A12CFFD4A2C_
	* Configure DeviceId: _SC:D:00D206AF_
	For each of the command you should see *OK* printed
	Now you can watch the pending configuration by typing _C_ command (Upper Case)
	```
	- sdk.version : 16
	sdk.activeNetwork : 1
	sdk.activeRegion : 0000
	sdk.sigfox.rcz : 1
	sdk.sigfox.txPower : rcz default
	sdk.sigfox.speed : rcz default
	sdk.sigfox.sgfxKey : 0
	sdk.sigfox.initialPac : [0000000000000000]
	sdk.sigfox.deviceId : 00D206AF 
	sdk.sigfox.rssiCal : 0
	[WARN] S 0x40000070
	```
	The Key is not accessible once set, so you can't verify it.

	If corresponding you can apply this configuration by typing _S_ and get:
	```
	- [INFO] S 0x00000072
	OK
	/ Init Sigfox Stack success
	| Tx completed <3
	```
	A first Sigfox transmission has been fired and you will get one new on every 10 minutes.


## General Usage

* A console for debug is accessible on USART2 @ 9600
* A console for configuration is accessible on USART2 @ 9600 ; type "?" to access the command. "changeme" to access the private extension to modify the configuration.

## License

This code and ItSdk are under GPLv3. You can use it freely, you can modify, redistribute but *you must* to publish your source code. Other licenses can be obtained by contacting me on [disk91.com](https://www.disk91.com)
