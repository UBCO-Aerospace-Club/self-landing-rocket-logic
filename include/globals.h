
// use this file for global variables shared across multiple cpp files
#pragma once
#include <Adafruit_BNO055.h>

#include "sensors.h"

extern Adafruit_BNO055 bno;
extern unsigned short chipSelect;
extern unsigned short ledPin;
extern unsigned short state;
extern unsigned short flag;
extern float data[7][3];