#include "logging.h"
#include "globals.h"

void sdLog(float data[6][3]) {
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
    Serial.println("error opening datalog.txt");
  }
}

void dataWriteToFile(float data[6][3], File dataFile) {
  //  A function to take accelleration data and write to a file in a csv format.

  for (int j = 0; j < 6; j++) {
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
    Serial.println("LED: off");
    flag = 1;
  } else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    if (flag == 0) {
      Serial.println("LED: on");
      flag = 1;
    }
  }
}