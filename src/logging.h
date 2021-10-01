#pragma once
#include <Adafruit_BNO055.h>
#include <SD.h>

void dataWriteToFile(float data[6][3], File dataFile);
void updateValues(sensors_event_t* event, float localData[3]);
void sdLog(float[6][3]);
void bluetoothLog();