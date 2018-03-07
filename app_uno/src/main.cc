#include <SPI.h>
#include <RH_RF69.h>

RH_RF69 rf69(10, 3); 
void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ;
  if (!rf69.init())
    Serial.println("init failed");
  
  if (!rf69.setFrequency(433.0))
    Serial.println("setFrequency failed");

  
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
}


void loop()
{
  Serial.println("Sending to rf69_server");
  
  uint8_t data[] = "Hello World!";
  rf69.send(data, sizeof(data));
  
  rf69.waitPacketSent();
  
  uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf69.waitAvailableTimeout(500))
  { 
    
    if (rf69.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf69_server running?");
  }
  delay(400);
}
