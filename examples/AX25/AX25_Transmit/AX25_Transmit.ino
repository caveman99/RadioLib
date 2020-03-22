/*
   RadioLib AX.25 Transmit Example

   This example sends AX.25 messages using
   SX1278's FSK modem.

   Other modules that can be used for AX.25:
    - SX127x/RFM9x
    - RF69
    - SX1231
    - CC1101
    - SX126x
    - nRF24
*/

// include the library
#include <RadioLib.h>

// SX1278 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
SX1278 fsk = new Module(10, 2, 9, 3);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1278 fsk = RadioShield.ModuleA;

// create AX.25 client instance using the FSK module
AX25Client ax25(&fsk);

void setup() {
  Serial.begin(9600);

  // initialize SX1278
  Serial.print(F("[SX1278] Initializing ... "));
  // carrier frequency:           434.0 MHz
  // bit rate:                    1.2 kbps (1200 baud AFSK AX.25)
  // frequency deviation:         0.5 kHz  (1200 baud AFSK AX.25)
  int state = fsk.beginFSK(434.0, 1.2, 0.5);

  // when using one of the non-LoRa modules for AX.25
  // (RF69, CC1101, etc.), use the basic begin() method
  // int state = fsk.begin();

  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  // initialize AX.25 client
  Serial.print(F("[AX.25] Initializing ... "));
  // source station callsign:     "N7LEM"
  // source station SSID:         0
  // preamble length:             8 bytes
  state = ax25.begin("N7LEM");
  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

void loop() {
  // send AX.25 unnumbered information frame
  Serial.print(F("[AX.25] Sending UI frame ... "));
  // destination station callsign:     "NJ7P"
  // destination station SSID:         0
  int state = ax25.transmit("Hello World!", "NJ7P");
  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else {
    // some error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  delay(1000);
}
