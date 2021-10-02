
// use this file for global variables shared across multiple cpp files
#pragma once
#include <Adafruit_BNO055.h>

#include "sensors.h"

extern Adafruit_BNO055 bno;
extern int chipSelect;
extern int ledPin;
extern int state;
extern int flag;
extern float data[7][3];