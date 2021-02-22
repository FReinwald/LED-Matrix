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
  pixels.begin();
  pixels.setPixelColor(1,pixels.Color(100,100,50));
  pixels.show();
}

void SingleLED()
{
  pixels.begin();
  pixels.setPixelColor(2,pixels.Color(100,0,50));
  pixels.show();
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
  int lastMenu = MENUOPTIONS;
  bool lastR = R_PIN_Input;
  bool lastG = G_PIN_Input;
  bool lastB = B_PIN_Input;
  bool lastUtil = Util_PIN_Input;
  //MainMenu Interface
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(0,0,50));
  }
  pixels.setPixelColor(1,pixels.Color(80,0,0));
  pixels.show();


  while(true)
  {
    int R_PIN_Input = !digitalRead(R_PIN);
    int G_PIN_Input = !digitalRead(G_PIN);
    int B_PIN_Input = !digitalRead(B_PIN);
    int Util_PIN_Input = !digitalRead(UTIL_PIN);
    if(R_PIN_Input && !lastR)
    {
      if(MenuState==1)
        MenuState=MENUOPTIONS;
      else
        MenuState--;

      //Move Cursor
      pixels.begin();
      pixels.setPixelColor(MenuState,pixels.Color(80,0,0));
      pixels.setPixelColor(lastMenu,pixels.Color(0,0,50));
      pixels.show();
    }
    if(B_PIN_Input && !lastB)
    {
      if(MenuState==MENUOPTIONS)
        MenuState=1;
      else
        MenuState++;

      //Move Cursor
      pixels.setPixelColor(MenuState,pixels.Color(80,0,0));
      pixels.setPixelColor(lastMenu,pixels.Color(0,0,50));
      pixels.show();
    }
/*    if(G_PIN_Input && !lastG)
    {
      pixels.setPixelColor(5,pixels.Color(80,80,0));
      pixels.show();
    }*/
    if(Util_PIN_Input && !lastUtil)
    {
      pixels.setPixelColor(7,pixels.Color(80,0,0));
      pixels.show();
      Program(MenuState);
    }
    lastR = R_PIN_Input;
    lastG = G_PIN_Input;
    lastB = B_PIN_Input;
    lastUtil = Util_PIN_Input;
    lastMenu = MenuState;
  }
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