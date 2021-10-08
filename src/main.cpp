//------------------------------------------------------------------//
//                                                                  //
//                 Self Landing Model Rocket Logic                  //
//                     UBCO Aerospace Club                          //
//                                                                  //
//------------------------------------------------------------------//

// included libraries
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <ArduinoLogger.h>
#include <SD.h>
#include <SoftwareSerial.h>

#include "../configuration.h"
#include "globals.h"
#include "logging.h"
#include "sensors.h"

//////////// Global Var's & Constants ///////////////

/* Set the delay between fresh samples */
const uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

unsigned short chipSelect = ChipSelect;
unsigned short ledPin = LEDPin;
unsigned short state = 0;
unsigned short flag = 0;
float data[7][3] = {0};

/////////////////////////////////////////////////////

// setup
void imuSetup();
void sdSetup();
void bluetoothSetup();

void setup() {
  Serial.begin(9600);
  logger.add(Serial, LOG_LEVEL_VERBOSE);  // This will log everything on Serial
  inf << np << endl;  // Displays an end of line without the prefix (Because of "np")
  verb << "Begin Setup...\n";

  logSetup();
  sensorsSetup();
  imuSetup();
  sdSetup();
  // bluetoothSetup();
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  pollSensors();
#ifdef log
  sdLog(data);
// bluetoothLog();
#endif
}

///////////////////////////////// Setup Funcitons ///////////////////////////////////////

void imuSetup() {
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */

    err << "Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!\n";

    while (1) {
      errorCode(0);
    }
  }

  delay(1000);
}

void sdSetup() {
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    err << "Card failed, or not present\n";

    while (1) {
      errorCode(1);
    }
  }
}

void bluetoothSetup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  SoftwareSerial Bluetooth(0, 1);  // RX, TX
}
