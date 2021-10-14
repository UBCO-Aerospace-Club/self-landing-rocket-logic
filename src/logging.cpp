#include "logging.h"

#include <ArduinoLogger.h>
//#include <SPI.h>
#include <SD.h>

#include "../configuration.h"
//#include "SdFat.h"
#include "globals.h"
//#include "sdios.h"

#ifdef LOGSD
// SdFat sd;
// SdFile file;
#endif

void logSetup() {}

// this code is horrific but we can fix it later
void logToSerial() {
#ifdef LogSensorSerial
  Serial.print("/*");  // orentation
  Serial.print(data[0][0]);
  Serial.print(",");
  Serial.print(data[0][1]);
  Serial.print(",");
  Serial.print(data[0][2]);
  //////////////////////
  Serial.print(",");  // ang Velocity
  Serial.print(data[1][0]);
  Serial.print(",");
  Serial.print(data[1][1]);
  Serial.print(",");
  Serial.print(data[1][2]);
  //////////////////////
  Serial.print(",");  // Linear acceleration
  Serial.print(data[2][0]);
  Serial.print(",");
  Serial.print(data[2][1]);
  Serial.print(",");
  Serial.print(data[2][2]);
  //////////////////////
  Serial.print(",");  // magnetometer
  Serial.print(data[3][0]);
  Serial.print(",");
  Serial.print(data[3][1]);
  Serial.print(",");
  Serial.print(data[3][2]);
  //////////////////////
  Serial.print(",");  // accelerometer
  Serial.print(data[4][0]);
  Serial.print(",");
  Serial.print(data[4][1]);
  Serial.print(",");
  Serial.print(data[4][2]);
  //////////////////////
  Serial.print(",");  // gravity
  Serial.print(data[5][0]);
  Serial.print(",");
  Serial.print(data[5][1]);
  Serial.print(",");
  Serial.print(data[5][2]);
  //////////////////////
  Serial.print(",");  // time
  Serial.print(data[6][0]);
  Serial.print("*/\n");
#endif
}

void sdLog(float (&data)[7][3]) {
#ifdef LOGSD
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataWriteToFile(data, dataFile);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    err << "error opening datalog.txt";
  }
#endif
}

void dataWriteToFile(float data[7][3], File dataFile) {
#ifdef LOGSD
  //  A function to take accelleration data and write to a file in a csv format.
  for (int j = 0; j < 7; j++) {
    for (int k = 0; k < 3; k++) {
      String dataChar = (String)data[j][k];
      dataFile.print(dataChar + ",");
    }
  }
  dataFile.print("\n");
#endif
}

void bluetoothLog() {
#ifdef LOGBT
  if (Serial.available() > 0) {
    state = Serial.read();
    flag = 0;
  }
  if (state == '0') {
    digitalWrite(ledPin, LOW);
  }
  if (flag == 0) {
    inf << "LED: off";
    flag = 1;
  } else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    if (flag == 0) {
      inf << "LED: on";
      flag = 1;
    }
  }
#endif
}

// Display error code (0 IMU error, 1 SD Connection Error, 2 Bluetooth Conection Error)
void errorCode(int error) {
#ifdef ErrorCodes
  switch (error) {
    case 0:  // IMU conection error (slow led blink)
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      break;
    case 1:  // SD connection error (fast led blink)
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      break;
    case 3:  // Bluetooth connection error (2 short blinks one long blink)
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);
      delay(1000);
    default:
      break;
  }
#endif
}