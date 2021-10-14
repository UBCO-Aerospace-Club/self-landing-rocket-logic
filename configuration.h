#define LogSensorSerial  // Enable if you want to log sensor data to serial (uses more clock cycles)
#define ErrorCodes       // Enable for led error codes
#define LEDPin 13        // The pin you want to use for the signal LED
#define ChipSelect 10    // The pin for the SD card chip select option
#define LOGSD            // Log to SD card Disabling saves a lot of memory about 6Kb!
                         //#define LOGBT          // Enable to log data to bluetooth