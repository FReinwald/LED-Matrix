/**
  Code for the Operation of a RGBW-LED Matrix
  Author: Fabian Reinwald
  Date: 06.02.2021
  Version: 1.0
*/
//*******************************************************************
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "specs.h"
/*#ifdef __AVR__
  #include <avr/power.h>
#endif*/
int R =0;
//*******************************************************************
Adafruit_NeoPixel pixels(NUMPIXELS,C_PIN,NEO_GRB+NEO_KHZ800);
//*******************************************************************
void AllLED()
{
  delay(29);
}

void SingleLED()
{
  delay(29);
}

void ColorControl(int PIN)
{
  delay(29);
}

void Program(int MenuState)
{
  switch (MenuState)
  {
  case 1:
    AllLED();
    break;
  case 2:
    SingleLED();
    break;
  default:
   // MainMenu();
    break;
  }
}

void MainMenu()
{
  pixels.begin();
  int MenuState=1;
  bool lastR = R_PIN_Input;
  bool lastB = B_PIN_Input;
  //MainMenu Interface
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(0,0,50));
  }
  pixels.show();


  do
  {
    if(R_PIN_Input)
    {
      if(MenuState==1)
      {
        MenuState=MENUOPTIONS;
      }
      else
      {
        MenuState--;
      }
      //Move Cursor
      pixels.begin();
      pixels.setPixelColor(MenuState,pixels.Color(10,0,10));
      pixels.show();
    }
    if(!B_PIN_Input && !lastB)
    {
      if(MenuState==MENUOPTIONS)
      {
        MenuState=1;
      }
      else
      {
        MenuState++;
      }
      //Move Cursor
      pixels.setPixelColor(MenuState,pixels.Color(0,0,10));
      pixels.show();
    }
    if(!Util_PIN_Input)
    {
      Program(MenuState);
    }
    lastR = R_PIN_Input;
    lastB = B_PIN_Input;
  } while (Util_PIN_Input);
}
//*******************************************************************
void setup() {
// put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  //Initialize NeoPixel strip object
  pixels.begin();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(40,0,50));
  }
  pixels.show();  
  //pixels.clear();

  //Initialize Joystick Pins
  pinMode(R_PIN, INPUT_PULLUP);
  pinMode(G_PIN, INPUT_PULLUP);
  pinMode(B_PIN, INPUT_PULLUP);
  pinMode(C_PIN, INPUT_PULLUP);


  //Start Main-Menu
 
  MainMenu(); 
}


void loop() {
pixels.begin();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(40,100,50));
  }
  pixels.show(); 
}