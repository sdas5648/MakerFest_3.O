//slave code start
#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>
HardwareSerial uart(2); 
#define RXD2 16
#define TXD2 17
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//#define slave_addr 0x08
#define width 128
#define height 64
#define oled_reset -1
#define screen_address 0x3C
Adafruit_SSD1306 oled(width,height, &Wire, oled_reset);

typedef union {
  int value;
  byte bytes[sizeof(int)];
} IntBytes;

int receivedValue = 0; bool newDataReceived = false;

void setup() {
  Serial.begin(115200);
  uart.begin(115200, SERIAL_8N1, RXD2, TXD2);
  //Wire.begin(slave_addr);
  //Wire.onReceive(data);
  if (!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println(F("ssd1306 oled initiation failed"));
    for (;;);
  }
  oled.clearDisplay();
}

void loop(){
  if (uart.available() >= sizeof(int)) {
    IntBytes receivedData;
    int bytesRead = uart.readBytes(receivedData.bytes, sizeof(int)); 
    if (bytesRead == sizeof(int)) {
      receivedValue = receivedData.value; 
      newDataReceived=true;
    }
  }
  if (newDataReceived){ 
    oled.setTextSize(1);oled.setTextColor(WHITE,BLACK);oled.setCursor(0,32);
    oled.println(receivedValue);
    oled.display();
    for (int i=5;i>0;i--){
      oled.setCursor(0,54);
      oled.printf("Clearing in %d...",i);
      oled.display();
      delay(1000);
    }
    oled.clearDisplay();
    newDataReceived=false;
  }
}