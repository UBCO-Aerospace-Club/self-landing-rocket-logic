//------------------------------------------------------------------//
//                                                                  //
//                 Self Landing Model Rocket Logic                  //
//                     UBCO Aerospace Club                          //
//                                                                  //
//------------------------------------------------------------------//

// included libraries
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <utility/imumaths.h>

#include "globals.h"
#include "logging.h"
#include "sensors.h"

//////////// Global Var's & Constants ///////////////

/* Set the delay between fresh samples */
const uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

int chipSelect = 10;
int ledPin = 13;
int state = 0;
int flag = 0;

/////////////////////////////////////////////////////

// setup
void imuSetup();
void sdSetup();
void bluetoothSetup();

void setup() {
  Serial.begin(9600);

  imuSetup();
  sdSetup();
  // bluetoothSetup();
  delay(100);
}

void loop() {
  // Required variables
  float data[6][3] = {0};

  /* Get new sensor events with the readings */
  pollSensors(data);
  sdLog(data);
  // bluetoothLog();
}

///////////////////////////////// Setup Funcitons ///////////////////////////////////////

void imuSetup() {
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  delay(1000);
}

void sdSetup() {
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }
}

void bluetoothSetup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  SoftwareSerial Bluetooth(0, 1);  // RX, TX
}
