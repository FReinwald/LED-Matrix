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

int lastMenu = MENUOPTIONS;
bool lastR = R_PIN_Input;
bool lastG = G_PIN_Input;
bool lastB = B_PIN_Input;
bool lastUtil = Util_PIN_Input;
//*******************************************************************
Adafruit_NeoPixel pixels(NUMPIXELS,C_PIN,NEO_GRB+NEO_KHZ800);
//*******************************************************************
void AllLED()
{
  int red = 0;
  int green = 0;
  int blue = 0;
  int Util_PIN_Input = !digitalRead(UTIL_PIN);
  pixels.begin();

  while(Util_PIN_Input)
    Util_PIN_Input = !digitalRead(UTIL_PIN);

  while(!Util_PIN_Input)
  {
    R_PIN_Input = !digitalRead(R_PIN);
    G_PIN_Input = !digitalRead(G_PIN);
    B_PIN_Input = !digitalRead(B_PIN);
    Util_PIN_Input = !digitalRead(UTIL_PIN);
    lastUtil = Util_PIN_Input;

    if(R_PIN_Input)
    {
      if(red<255)
        red++;

      for(int i=0;i<NUMPIXELS;i++)
      {
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
      }
      pixels.show();
    }

    if(G_PIN_Input)
    {
      if(green<255)
        green++;
   
      for(int i=0; i<NUMPIXELS;i++)
      {
        pixels.setPixelColor(i,pixels.Color(red,green,blue));
      }
      pixels.show();
    }

    if(B_PIN_Input)
    {
      if(blue<255)
        blue++;
     
      for(int i=0; i<NUMPIXELS;i++)
      {
        pixels.setPixelColor(i,pixels.Color(red,green,blue));
      }
      pixels.show();
    }

    lastUtil = Util_PIN_Input;
    delay(20);
  }
  MainMenu();         //sends back to main menu on util key press
}

void SingleLED()
{
  int red = 0;
  int green = 0;
  int blue = 0;
  int Util_PIN_Input = !digitalRead(UTIL_PIN);
  pixels.begin();
  int i = 0;

  while(Util_PIN_Input)
    Util_PIN_Input = !digitalRead(UTIL_PIN);

  while(!Util_PIN_Input)
  {
    R_PIN_Input = !digitalRead(R_PIN);
    G_PIN_Input = !digitalRead(G_PIN);
    B_PIN_Input = !digitalRead(B_PIN);
    Util_PIN_Input = !digitalRead(UTIL_PIN);
    lastUtil = Util_PIN_Input;

    if(R_PIN_Input)
    {
      if(red<255)
        red++;

      pixels.setPixelColor(i,pixels.Color(red,green,blue));

      pixels.show();
    }

    if(G_PIN_Input)
    {
      if(green<255)
        green++;

        pixels.setPixelColor(i,pixels.Color(red,green,blue));

      pixels.show();
    }

    if(B_PIN_Input)
    {
      if(blue<255)
        blue++;

        pixels.setPixelColor(i,pixels.Color(red,green,blue));
 
      pixels.show();
    }

    if(G_PIN_Input && B_PIN_Input)        //next pixel by pressing G and B pin
    {
      i++;
      if(i>NUMPIXELS)
        i = 0;

      delay(200);
      red = 0;
      green = 0;
      blue = 0;
    }

    if(R_PIN_Input && G_PIN_Input)        //reset Pin color
    {
      delay(200);
      red = 0;
      green = 0;
      blue = 0;
    }

    lastUtil = Util_PIN_Input;
    delay(20);
  }
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
  //MainMenu Interface
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(0,0,50));
  }
  pixels.setPixelColor(1,pixels.Color(80,0,0));
  pixels.show();

  //Menu Loop to read Buttoninput
  while(true)
  {
    int R_PIN_Input = !digitalRead(R_PIN);
    int G_PIN_Input = !digitalRead(G_PIN);
    int B_PIN_Input = !digitalRead(B_PIN);
    int Util_PIN_Input = !digitalRead(UTIL_PIN);

    //Moves cursor forward
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

    //Moves cursor backwards
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

    //Confirms Menuselection
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
  pixels.show();
}