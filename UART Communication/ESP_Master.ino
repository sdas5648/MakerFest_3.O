//master code start here
#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>
HardwareSerial uart(2); 
#define RXD2 16
#define TXD2 17
//#define slave_addr 0x08 
int p1=23;int p2=32;
int p3=33;int p4=18;
int p5=5;int p6=27;
int p7=14;int p8=4;
int p9=0;int p10=2;

typedef union {
  int value;
  byte bytes[sizeof(int)];
} IntBytes;

void setup() {
  //Wire.begin();
  Serial.begin(115200);
  uart.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("ESP32 Board 1 Ready");
  pinMode(p1, INPUT_PULLUP);pinMode(p2, INPUT_PULLUP);
  pinMode(p3, INPUT_PULLUP);pinMode(p4, INPUT_PULLUP);
  pinMode(p5, INPUT_PULLUP);pinMode(p6, INPUT_PULLUP);
  pinMode(p7, INPUT_PULLUP);pinMode(p8, INPUT_PULLUP);
  pinMode(p9, INPUT_PULLUP);pinMode(p10, INPUT_PULLUP);
}
void loop(){
  int button1=digitalRead(p1);int button2=digitalRead(p2);
  int button3=digitalRead(p3);int button4=digitalRead(p4);
  int button5=digitalRead(p5);int button6=digitalRead(p6);
  int button7=digitalRead(p7);int button8=digitalRead(p8);
  int button9=digitalRead(p9);int button10=digitalRead(p10);
  //Wire.beginTransmission(slave_addr);
  if (button1==0){
    //Wire.write(1);
    IntBytes data;data.value = 1;uart.write(data.bytes, sizeof(int));
  }
  else if (button2==0){
    //Wire.write(2);
    IntBytes data;data.value = 2;uart.write(data.bytes, sizeof(int));
  }
  else if (button3==0){
    //Wire.write(3);
    IntBytes data;data.value = 3;uart.write(data.bytes, sizeof(int));
  }
  else if (button4==0){
    //Wire.write(4);
    IntBytes data;data.value = 4;uart.write(data.bytes, sizeof(int));
  }
  else if (button5==0){
    //Wire.write(5);
    IntBytes data;data.value = 5;uart.write(data.bytes, sizeof(int));
  }
  else if (button6==0){
    //Wire.write(6);
    IntBytes data;data.value = 6;uart.write(data.bytes, sizeof(int));
  }
  else if (button7==0){
    //Wire.write(7);
    IntBytes data;data.value = 7;uart.write(data.bytes, sizeof(int));
  }
  else if (button8==0){
    //Wire.write(8);
    IntBytes data;data.value = 8;uart.write(data.bytes, sizeof(int));
  }
  else if (button9==0){
    //Wire.write(9);
    IntBytes data;data.value = 9;uart.write(data.bytes, sizeof(int));
  }
  else if (button10==0){
    //Wire.write(10);
    IntBytes data;data.value = 10;uart.write(data.bytes, sizeof(int));
  }
  //Wire.endTransmission();
  delay(50);
}