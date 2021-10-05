#include "logging.h"

#include <ArduinoLogger.h>

#include "globals.h"

void logSetup() {}

void logJson() {
  Serial.print("/*");
  Serial.print(data[0][0]);
  Serial.print(",");
  Serial.print(data[0][1]);
  Serial.print(",");
  Serial.print(data[0][2]);
  Serial.print(",");
  Serial.print(data[4][0]);
  Serial.print(",");
  Serial.print(data[4][1]);
  Serial.print(",");
  Serial.print(data[4][2]);
  Serial.print("*/\n");
}

void sdLog(float (&data)[7][3]) {
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
}

void dataWriteToFile(float data[7][3], File dataFile) {
  //  A function to take accelleration data and write to a file in a csv format.
  for (int j = 0; j < 7; j++) {
    for (int k = 0; k < 3; k++) {
      String dataChar = (String)data[j][k];
      dataFile.print(dataChar + ",");
    }
  }
  dataFile.print("\n");
}

void bluetoothLog() {
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
}

// Display error code (0 IMU error, 1 SD Connection Error, 2 Bluetooth Conection Error)
void errorCode(int error) {
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
}