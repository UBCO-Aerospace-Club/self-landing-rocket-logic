#pragma once
#include <Adafruit_BNO055.h>

void pollSensors();
void sensorsSetup();
void updateValues(sensors_event_t* event, float (&data)[3]);
