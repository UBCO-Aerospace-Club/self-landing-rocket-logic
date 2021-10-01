//------------------------------------------------------------------//
//                                                                  //
//                 Self Landing Model Rocket Logic                  //
//                     UBCO Aerospace Club                          //
//                                                                  //
//------------------------------------------------------------------//

//included libraries
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

//Global Constants
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
int chipSelect = 10;
int ledPin = 13;
int state = 0;
int flag = 0;

//setup
void imuSetup();
void sdSetup();
void bluetoothSetup();

//loop functions
void imuLog(float [6][3]);
void logEvent(sensors_event_t* event, float [3]);
void dataFormat(float [10][6][3], File);
void dataWriteToFile(float data[6][3], File dataFile);
void sdLog(float [6][3]);
void bluetoothLog();

void setup() {
  Serial.begin(9600);

  imuSetup();
  sdSetup();
  //bluetoothSetup();
  
  delay(100);

}

void loop() {
  // Required variables
  float data[6][3] = {0};
  
  /* Get new sensor events with the readings */
  imuLog(data);
  sdLog(data);
  //bluetoothLog();

}

void imuSetup(){

  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);

}

void sdSetup(){

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }

}

void bluetoothSetup(){

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  SoftwareSerial Bluetooth(0, 1); // RX, TX

}

void imuLog(float data[6][3]){
  // A function to take data from the IMU and log it to an array

  sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
      
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
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  switch(event->type){
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


void sdLog( float data[6][3] ){
  
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

void dataWriteToFile(float data[6][3], File dataFile){
  //  A function to take accelleration data and write to a file in a csv format.

    for(int j=0;j<6;j++){
      for(int k=0;k<3;k++){
        String dataChar = (String)data[j][k];
        dataFile.print( dataChar +",");
      }
    }
    dataFile.print("\n");  

}

void bluetoothLog(){
  if (Serial.available()>0){
    state = Serial.read();
    flag = 0;
  }

  if (state == '0'){
    digitalWrite(ledPin, LOW);
  }
  if(flag == 0){
    Serial.println("LED: off");
    flag = 1;
  } else if(state == '1' ) {
    digitalWrite(ledPin, HIGH);
    if(flag == 0){
      Serial.println("LED: on");
      flag = 1;
    }
  }
}
