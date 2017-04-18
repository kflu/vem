// Arduino9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Arduino9x_TX

#include <SPI.h>
#include <RH_RF95.h>
#include "__lib/lib.h"

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

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Blinky on receipt
#define LED 13

void setup() 
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);     
    pinMode(RFM95_RST, OUTPUT);

    // manual reset
    digitalWrite(RFM95_RST, HIGH); delay(100);
    digitalWrite(RFM95_RST, LOW); delay(10);
    digitalWrite(RFM95_RST, HIGH); delay(10);

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

    rf95.setModeRx();
}

//int temp_to_comfort(float tempC) {
//    if (tempC < 0) return 6;
//    if (0 <= tempC && tempC < 25) return 1;
//    if (25 <= tempC && tempC < 30) return 2;
//    if (30 <= tempC && tempC < 35) return 3;
//    if (35 <= tempC && tempC < 40) return 4;
//    if (tempC >= 40) return 5;
//    return 10;
//}

int temp_to_comfort(float tempC) {
    if (               tempC < 0)  return 7;
    if ( 0 <= tempC && tempC < 20) return 1;
    if (20 <= tempC && tempC < 25) return 2;
    if (25 <= tempC && tempC < 30) return 3;
    if (30 <= tempC && tempC < 35) return 4;
    if (35 <= tempC && tempC < 40) return 5;
    if (40 <= tempC)               return 6;
}

typedef int8_t temp_t;
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);

void loop()
{
    /*
    Serial.print("Time: "); Serial.print(millis() / 1000, DEC);
    Serial.print(" Waiting for data...");
    Serial.println("");
    */
    
    //if (rf95.waitAvailableTimeout(5 * 1000)) {
    if (rf95.available()) {
        if (rf95.recv(buf, &len)) {
            RH_RF95::printBuffer("Received: ", buf, len);
            temp_t* temp = (temp_t*)buf;

            Serial.print("Time: "); Serial.print(millis() / 1000, DEC);
            Serial.print(" | Temp (C): "); Serial.print(*temp);
            Serial.print(" | SNR: "); Serial.print(rf95.lastSNR(), DEC);
            Serial.print(" | RSSI: "); Serial.print(rf95.lastRssi(), DEC);
            Serial.println("");

            blink(LED, temp_to_comfort(*temp), 200);
        } else {
            blink(LED, 1, 2000);
            //Serial.println("Receive failed");
        }
    } else {
        blink(LED, 1, 2000);
        //Serial.println("data not available");
    }

    delay(5000);
}
