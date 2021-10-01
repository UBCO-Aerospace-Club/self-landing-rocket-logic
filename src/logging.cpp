#include "logging.h"

#include "globals.h"

void imuLog(float data[6][3]) {
  // A function to take data from the IMU and log it to an array

  sensors_event_t orientationData, angVelocityData, linearAccelData, magnetometerData,
      accelerometerData, gravityData;

  // get data
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);

  // save data
  logEvent(&orientationData, data[0]);
  logEvent(&angVelocityData, data[1]);
  logEvent(&linearAccelData, data[2]);
  logEvent(&magnetometerData, data[3]);
  logEvent(&accelerometerData, data[4]);
  logEvent(&gravityData, data[5]);
}

void logEvent(sensors_event_t* event, float localData[3]) {
  switch (event->type) {
    case SENSOR_TYPE_ACCELEROMETER:
      Serial.print("Accl:");
      localData[0] = event->acceleration.x;
      localData[1] = event->acceleration.y;
      localData[2] = event->acceleration.z;
      break;

    case SENSOR_TYPE_ORIENTATION:
      Serial.print("Orient:");
      localData[0] = event->orientation.x;
      localData[1] = event->orientation.y;
      localData[2] = event->orientation.z;
      break;

    case SENSOR_TYPE_MAGNETIC_FIELD:
      Serial.print("Mag:");
      localData[0] = event->magnetic.x;
      localData[1] = event->magnetic.y;
      localData[2] = event->magnetic.z;
      break;

    case SENSOR_TYPE_GYROSCOPE:
      Serial.print("Gyro:");
      localData[0] = event->gyro.x;
      localData[1] = event->gyro.y;
      localData[2] = event->gyro.z;
      break;

    case SENSOR_TYPE_ROTATION_VECTOR:
      Serial.print("Rot:");
      localData[0] = event->gyro.x;
      localData[1] = event->gyro.y;
      localData[2] = event->gyro.z;
      break;

    case SENSOR_TYPE_LINEAR_ACCELERATION:
      Serial.print("Linear:");
      localData[0] = event->acceleration.x;
      localData[1] = event->acceleration.y;
      localData[2] = event->acceleration.z;
      break;

    default:
      Serial.print("Unk:");
      break;
  }
}

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