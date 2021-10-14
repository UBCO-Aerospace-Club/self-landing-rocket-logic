# self-landing-rocket-logic
Code for the self landing rocket in the UBCO Aerospace Club.

[Andre's repo](https://github.com/AndreCox/self-landing-rocket-logic) is usually more up to date

## Hardware
**Processor** - Atmel 328P @ 16MHz

**IMU** - BNO055

**Barometer** - BMP280

## Compiling

Open project in [platformIO](https://platformio.org/)

Select the ATmega328P enviroment

Connect hardware via serial

Press upload button 

## Logging

You can set the log level in the code, options are 

* LOG_LEVEL_SILENT  
* LOG_LEVEL_ERROR   
* LOG_LEVEL_WARNING 
* LOG_LEVEL_INFO    
* LOG_LEVEL_TRACE   
* LOG_LEVEL_VERBOSE 

It's possible to visualize data from the Sensors by using a program such as [Serial Studio](https://github.com/Serial-Studio/Serial-Studio)

## Library's Used

*	adafruit/Adafruit BNO055@^1.5.1
*	Wire
*	adafruit/SD@0.0.0-alpha+sha.041f788250
*	farossco/ArduinoLogger@^1.2.4
*	fabyte/Tiny BME280@^1.0.2
