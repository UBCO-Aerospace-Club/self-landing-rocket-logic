//------------------------------------------------------------------//
//                                                                  //
//                 Self Landing Model Rocket Logic                  //
//                     UBCO Aerospace Club                          //
//                                                                  //
//------------------------------------------------------------------//

//included libraries
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//Global Constants
Adafruit_MPU6050 mpu;
const int chipSelect = 4;

//setup
void imuSetup();
void sdSetup();

//loop functions
void imuLog(float [10][6]);
void dataFormat(float [10][6], File);
void sdLog(float [10][6]);

void setup() {
  Serial.begin(9600);

  imuSetup();
  sdSetup();
  
  delay(100);

}

void loop() {
  // Required variables
  float data[10][6]={0};
  
  /* Get new sensor events with the readings */
  imuLog(data);
  sdLog(data);

}

void imuSetup(){

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }

  //Some paramaters to set the capabilities of the IMU
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

}

void sdSetup(){

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }

}

void imuLog(float data[10][6]){
  // A function to take data from the IMU and log it to an array

    for(int timer=0;timer<10;timer++){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      data[timer][0]=a.acceleration.x;
      data[timer][1]=a.acceleration.y;
      data[timer][2]=a.acceleration.z;
      data[timer][3]=g.gyro.x;
      data[timer][4]=g.gyro.y;
      data[timer][5]=g.gyro.z;
      
  }

}

void sdLog( float data[10][6] ){
  
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

void dataWriteToFile(float data[10][6], File dataFile){
  //  A function to take accelleration data and write to a file in a csv format.

  for(int i=0;i<10;i++){
    for(int j=0;j<6;j++){
      String dataChar = (String)data[i][j];
      dataFile.print( dataChar +",");
    }
    dataFile.print("\n");  
  }

}
