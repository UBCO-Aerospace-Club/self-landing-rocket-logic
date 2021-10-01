#pragma once
#include <Adafruit_BNO055.h>

void pollSensors(float data[6][3]);
void updateValues(sensors_event_t* event, float localData[3]);