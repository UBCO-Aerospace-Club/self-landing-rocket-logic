#pragma once
#include <Adafruit_BNO055.h>
#include <SD.h>

void dataWriteToFile(float[7][3], File dataFile);
void sdLog(float (&data)[7][3]);
void bluetoothLog();
void errorCode(int error);