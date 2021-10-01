#pragma once
#include <Adafruit_BNO055.h>
#include <SD.h>

void dataWriteToFile(float[7][3], File dataFile);
void updateValues(sensors_event_t* event, float localData[3]);
void sdLog(float (&data)[7][3]);
void bluetoothLog();
void errorCode(int error);