/**
  Specs for the LED Matrix and the connected Arduino UNO
  Author: Fabian Reinwald
  Date: 20.02.2021
  Version: 1.0
*/

//PIN controlling the LEDs
#define C_PIN 6
//Number of LEDs
#define NUMPIXELS 256
//Delay between loops
#define DELAYVAL 1000
//Input Next/Blue
#define B_PIN 2
//Input Green
#define G_PIN 4
//Input Previous/Red
#define R_PIN 7
//Input PIN On/Off/Select
#define UTIL_PIN 13
//Number of Menu Options
#define MENUOPTIONS 3

int R_PIN_Input = !digitalRead(R_PIN);
int G_PIN_Input = !digitalRead(G_PIN);
int B_PIN_Input = !digitalRead(B_PIN);
int Util_PIN_Input = !digitalRead(UTIL_PIN);

void AllLED();
void SingleLED();
void ColorControl(int PIN);
void Program(int MenuState);
void MainMenu();