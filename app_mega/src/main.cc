#include <Arduino.h>
#include "libmath.h"
#include <SPI.h>
#include "RH_RF69.h"


#define RF69_FREQ 915.0
#define CS 4
#define INT_PIN 3
#define RST_PIN 2
#define LED_IND 13

RH_RF69 rh_rf69(CS, INT_PIN);

int16_t packetNum = 0;


void setup(void)
{
    Serial.begin(115200);
        while (!Serial);

    pinMode(LED_IND, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    digitalWrite(RST_PIN, LOW);

    digitalWrite(RST_PIN, 1);
    delay(10);
    digitalWrite(RST_PIN, 0);
    delay(10);

    if(!rh_rf69.init())
    {
        digitalWrite(LED_IND, 1);
        delay(3000);
        digitalWrite(LED_IND, 0);
        delay(700);
        digitalWrite(LED_IND, 1);
        delay(2000);
        digitalWrite(LED_IND, 0);
        delay(800);
        digitalWrite(LED_IND, 1);
        delay(1000);
        digitalWrite(LED_IND, 0);
        while(1);
    }

    digitalWrite(LED_IND, 0);
    delay(500);
    digitalWrite(LED_IND, 1);
    delay(3000);
    digitalWrite(LED_IND, 0);

    if (!rh_rf69.setFrequency(RF69_FREQ))
        {
            digitalWrite(LED_IND, 1);
            delay(7000);
            digitalWrite(LED_IND, 0);
        }
    rh_rf69.setTxPower(20, true);

    uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    
    rh_rf69.setEncryptionKey(key);

}

void loop()
{
      if (rh_rf69.available())
        { 
          uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
          uint8_t len = sizeof(buf);
          if (rh_rf69.recv(buf, &len))
          {
            if (!len) return;
              buf[len] = 0;
              Serial.print("Received [");
              Serial.print(len);
              Serial.print("]: ");
              Serial.println((char*)buf);
              Serial.print("RSSI: ");
              Serial.println(rh_rf69.lastRssi(), DEC);
            if (strstr((char *)buf, "Hello World"))
            {
              uint8_t data[] = "And hello back to you";
              rf69.send(data, sizeof(data));
              rf69.waitPacketSent();
              Serial.println("Sent a reply");
            }else
              {
                Serial.println("recv failed");
              }
          }
        }
}

