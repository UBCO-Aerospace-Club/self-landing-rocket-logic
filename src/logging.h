#pragma once
#include <Adafruit_BNO055.h>
#include <SD.h>

void imuLog(float data[6][3]);
void dataWriteToFile(float data[6][3], File dataFile);
void logEvent(sensors_event_t* event, float localData[3]);