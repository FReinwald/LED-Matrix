/**
  Code for the Operation of a RGBW-LED Matrix
  Author: Fabian Reinwald
  Date: 06.02.2021
  Version: 1.0
*/
//*******************************************************************
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
/*#ifdef __AVR__
  #include <avr/power.h>
#endif*/
//*******************************************************************
//PIN am Arduino, an dem die LEDs angeschlossen sind
#define PIN 6
//Anzahl der LEDs
#define NUMPIXELS 12
//Pause zwischen Durchlauf
#define DELAYVAL 1000
//Input PIN X-Achse
#define X_PIN 2
//Input PIN Y-Achse
#define Y_PIN 4
//Input Push PIN
#define Z_PIN 7



Adafruit_NeoPixel pixels(NUMPIXELS,PIN,NEO_GRB+NEO_KHZ800);
//*******************************************************************



void setup() {
// put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();   //Initialize NeoPixel strip object
  pixels.clear();

  //Initialize Joystick Pins
  pinMode(X_PIN, INPUT_PULLUP);
  pinMode(Y_PIN, INPUT_PULLUP);
  pinMode(Z_PIN, INPUT_PULLUP);

    pixels.clear();

  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(0,1,0));
  }
  pixels.show();  
}


void loop() {
  // put your main code here, to run repeatedly:



  int X_PIN_Input = !digitalRead(X_PIN);
  int Y_PIN_Input = !digitalRead(Y_PIN);
  int Z_PIN_Input = !digitalRead(Z_PIN);
  int static index = 0;

if(X_PIN_Input)
 {
   pixels.setPixelColor(index,pixels.Color(10,10,10));
   pixels.show();
   index++;
 }

 if(Y_PIN_Input)
 {
   for(int i=0;i<NUMPIXELS;i++)
   {
    pixels.setPixelColor(i,pixels.Color(0,0,1));
  }
   pixels.show();
   index++;
 }

  if(Z_PIN_Input == true)
  {
    pixels.setPixelColor(index,pixels.Color(100,50,150));
    pixels.show();
    index++;
  }
 


  delay(50);

  if(index>=NUMPIXELS)
  {
    index=0;
  }
}