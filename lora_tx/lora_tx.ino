// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX

#include <SPI.h>
#include <RH_RF95.h>
#include "__lib/lib.h"

#define USE_MEGA 1
#ifdef USE_MEGA
  // Mega
  #define RFM95_CS  4
  #define RFM95_RST 2
  #define RFM95_INT 3
#else
  /* for feather32u4 */
  #define RFM95_CS  10   // "B"
  #define RFM95_RST 11   // "A"
  #define RFM95_INT 2    // "SDA" (only SDA/SCL/RX/TX have IRQ!)
#endif

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

const int TempSensorPin = 0;
const int LedPin = 13;

const float VMax = 5.0;

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup()
{
    Serial.begin(9600);
    pinMode(RFM95_RST, OUTPUT);
    pinMode(LedPin, OUTPUT);

    digitalWrite(RFM95_RST, HIGH);
    delay(100);
    // manual reset
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    if (!rf95.init()) {
        Serial.println("LoRa radio init failed");
        while (1);
    } else {
        Serial.println("LoRa radio init OK!");
    }

    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ)) {
        Serial.println("setFrequency failed");
        while (1);
    } else {
        Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    }

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
    // you can set transmitter powers from 5 to 23 dBm:
    rf95.setTxPower(23, false);
    rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096); // slow, long     SNR 6-7
    //rf95.setModemConfig(RH_RF95::Bw31_25Cr48Sf512); // slow, long      SNR 9-10     it sometimes doesn't work
    //rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128);  // fast, short
}

//float num = 0;

typedef int8_t temp_t;

void loop()
{
    temp_t temp = (temp_t)getTemperatureInC(TempSensorPin, VMax);
    Serial.print("Measured temperature (C): "); Serial.println(temp);

    Serial.println("Sending to rf95_server");
    // Send a message to rf95_server

    Serial.println("Sending..."); delay(10);
    rf95.send((uint8_t *)(&temp), sizeof(temp_t));

    Serial.println("Waiting for packet to complete..."); delay(10);
    rf95.waitPacketSent();
  
    blink(LedPin, 1);
    delay(3000);
}
