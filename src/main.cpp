#include <Arduino.h>
#include <lora.h>

#define RFM_CS 10//chipselect pin 
#define RFM_RST 9 //reset pin
#define RFM_INT 2//interrupt pin

#define DEBUG 1

#define BUFFER_LEN 20
#define APP_DATA_LEN 20

lora lorafiit(RFM_CS, RFM_INT , RFM_RST);

void setup() {
  Serial.flush();
  while(!Serial);
  Serial.begin(9600);//Sets Baud rate
  Serial.flush();
  delay(100);


  uint8_t buffer[BUFFER_LEN];
  uint8_t sizeOfBuffer = BUFFER_LEN;

  lorafiit.On();

  while (!lorafiit.Register(buffer, sizeOfBuffer)) {
    Serial.println("Registration not successfull.");
  }

  Serial.println("Registration successful, configuration data from server recieved");
}

void loop() {

  uint8_t appData[APP_DATA_LEN] = "App data from node";//user application data
  uint8_t sizeOfAppData = APP_DATA_LEN; //size in B

  delay(10000);

  if (lorafiit.Send(TYPE_DATA_UP, ACK_NO, appData, sizeOfAppData)) {
    Serial.println("Message with No ACK has been sent");
  }
}
