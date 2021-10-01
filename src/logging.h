#pragma once
#include <SD.h>
#include <Adafruit_BNO055.h>

void imuLog(float data[6][3]);
void dataWriteToFile(float data[6][3], File dataFile);
void logEvent(sensors_event_t* event, float localData[3]);