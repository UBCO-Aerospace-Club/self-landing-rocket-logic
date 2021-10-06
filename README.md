# self-landing-rocket-logic
Code for the self landing rocket in the UBCO Aerospace Club.

## Tech Stack
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

It is possible to visualize data from the Sensors by using a program such as [Serial Studio](https://github.com/Serial-Studio/Serial-Studio)

