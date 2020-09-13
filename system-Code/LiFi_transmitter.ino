/*
 * LiFi Communication Example - Transmitter Station Code
 * Written by Ivan Samardžić
 */
#include"GPIO.h"
//#define syncPinOut 8

//Pin declarations
GPIO<BOARD::D13> led;
GPIO<BOARD::D8> sync;

//Global variables declarations
String inString = "";    
unsigned char binary[10] = "22222222";

void setup() {
  //Declare sync pin as output pin and set it to LOW state
  sync.output();
  sync.low();
  led.output();
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Send an intro:
  Serial.println("Transmitter is connected");
  Serial.println("Write a number: ");
  Serial.println();
}

void loop() {
  //Sync pin is set at HIGH state
  //Read serial input:
  while (Serial.available() > 0) {
    //digitalWrite(syncPinOut,HIGH);
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    
    //If you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      int brojka=inString.toInt();
      hex2binstr(binary,brojka);
      inString = "";
      led.low();
      delayMicroseconds(10000);
      for (int i=0;i<8;i++){
      Serial.print(char(binary[i]));
      if (char(binary[i] == '0')){        
      led.low();
      delay(2);
      sync.high();
      delayMicroseconds(10000);
      }
      if (char(binary[i] == '1')){      
      led.high();
      delay(2);
      sync.high();
      delayMicroseconds(10000);      
      }
      led.low();
      delay(2);
      sync.low();
      Serial.println("");
      }
    }
  }
  //Little delay to enable progra execution
  delay(random(1,10));
  
  //the task ends
  //digitalWrite(syncPinOut, LOW);
}


unsigned char *hex2binstr(unsigned char *str, unsigned char dat) {
  unsigned char mask = 0x80;
  do {
    if (dat & mask) *str='1'; //the bit is 1
    else *str='0'; //otherwise it is 0
    str+=1; //increment the pointer
    mask = mask >> 1; //shift mask
  } while (mask);
  return str;
}
