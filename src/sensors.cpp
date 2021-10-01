#include "globals.h"
#include "logging.h"

void pollSensors(float (&data)[7][3]) {
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

  // save data by passing array from matrix
  updateValues(&orientationData, data[0]);
  updateValues(&angVelocityData, data[1]);
  updateValues(&linearAccelData, data[2]);
  updateValues(&magnetometerData, data[3]);
  updateValues(&accelerometerData, data[4]);
  updateValues(&gravityData, data[5]);
}

// Take data row and append values based on which event type it is
void updateValues(sensors_event_t* event, float localData[3]) {
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