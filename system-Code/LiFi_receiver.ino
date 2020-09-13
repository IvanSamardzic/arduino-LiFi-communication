/*
 * LI-Fi Communication Example - Receiver station code
 * Written by Ivan Samardžić
 */
#include"GPIO.h"

//Pin connection declarations
GPIO<BOARD::D7> inPin;
GPIO<BOARD::D8> sync;

//Write forward method declaration
char binstr2Char(char* binStr);
int bin2Dec(int* n);

//Global variables definitions
int count = 0;
int decimal = 0;
int arrayNum[8];

//Define global variables
char binaryNum[8];
char strArray[8];
int printFlag = 0;
int k = 0;
int lastSync = 0;
int currSync = 0;

void setup() {
  //In setup section sync pin is declared as input and sent to LOW state
  sync.input();
  sync.low(); 

  //Define serial communication and declare speed as 9600 bauds per second
  Serial.begin(9600);
  
  //define inPin as input pin
  inPin.input();
  
  while(!Serial){
    //wait for connection to be established
  }
  
  //if serial communication is established, print the string
  Serial.println("Receiver is connected!");
}

void loop() {
  //while syncInPin pin is at HIGH state, program will be executed
  //delay(5);
  //Serial.print(sync);
  
  if (sync == 0){
    lastSync = currSync;
    currSync = 0;}
  if (sync == 1){
   lastSync = currSync;
    currSync = 1;}
   //Serial.print(lastSync);
   //Serial.print(currSync);
   //Serial.println("");
  if (lastSync == 0 & currSync == 1){
    Serial.println(inPin);
    arrayNum[count++] = inPin;
  }

  //If receiver received eight bits, create the decimal representation from 8 bits and write it to the monitor
  if(count > 7){
    decimal = bin2Dec(arrayNum);
    Serial.print("Decimal value is: ");
    Serial.println(decimal);
    count = 0;
  }
}

char binstr2Char(char binStr[]){
  int multiplier = 0;
  int temp;
  int sum = 0;
  for(temp = 7; temp>=0; temp--){
    sum += (binStr[temp]*(1 << multiplier++));
  }
  return sum;
}


int bin2Dec(int n[]){
  //initialise index to act as array pointer, dec_value is initialised as 0,
  //num takes each array binary digit
  //multiple base with binary digit and each time increment index and multiple
  //base with const = 2
    int index = 0;
    int dec_value;
    int base = 128;
    dec_value = 0;
    while(index < 8){
    int num = n[index];
      dec_value += num * base;
      index++;
      base /= 2;
    }
    return dec_value;
}
