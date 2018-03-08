
#include <Arduino.h>
#include <SPI.h>
#include <RH_RF69.h>



  #define RFM69_INT     3  // 
  #define RFM69_CS      10  //
  #define RFM69_RST     2  // "A"
  #define ledpin        7

RH_RF69 rf69(RFM69_CS, RFM69_INT);
int16_t packetnum = 0;

void setup() 
{
  Serial.begin(9600); 
  while (!Serial);
  
  pinMode(ledpin, OUTPUT);
  Serial.println("Initializing");
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
  if (!rf69.init())
  {
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    delay(1000);
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    Serial.println("init failed");

  }
    
  
  if (!rf69.setFrequency(915.0))
  {
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    delay(1000);
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    delay(1000);
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    delay(1000);
    digitalWrite(ledpin, LOW);
    Serial.println("setFrequency failed");
  }
    
digitalWrite(ledpin, LOW);
delay(1000);
digitalWrite(ledpin, HIGH);
delay(3000);
  
  rf69.setTxPower(20, true);
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
}


void loop() {
  delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!

  char radiopacket[20] = "Hello World #";
  itoa(packetnum++, radiopacket+13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);
  
  // Send a message!
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();

  // Now wait for a reply
  uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf69.waitAvailableTimeout(500))  { 
    // Should be a reply message for us now   
    if (rf69.recv(buf, &len)) {
      Serial.print("Got a reply: ");
      Serial.println((char*)buf);
      Blink(ledpin, 50, 3); //blink LED 3 times, 50ms between blinks
    } else {
      Serial.println("Receive failed");
    }
  } else {
    Serial.println("No reply, is another RFM69 listening?");
  }
}

void Blink(byte PIN, byte DELAY_MS, byte loops) {
  for (byte i=0; i<loops; i++)  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}
