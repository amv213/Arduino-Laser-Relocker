#include <elapsedMillis.h>

#include <analogShield.h> // Digilent ADC/DAC shield library
#include <TFT.h>  // MODDED (see onenote: Arduino Relocking for SR1 cavity PDH)
#include <SPI.h> // Arduino SPI library

#include "ArduinoRelockerDefines.h"
#include "ArduinoRelockerFunctions.h"

//////////////////////////////////////////
/////////////// VARIABLES \\\\\\\\\\\\\\\\
//////////////////////////////////////////

// Auto Relocking
int unlockCount = 0;

int DAC1 = 3; // DAC/ADC shield .write(3) is board "DAC1"
int DAC2 = 2;
int DAC3 = 1;
int DAC4 = 0;

int ADC1 = 3; // DAC/ADC shield .read(3) is board "ADC1"
int ADC2 = 2;
int ADC3 = 1;
int ADC4 = 0;

int lock;
int button1State = 0;
int button2State = 0;

int photod = 0;
int setpoint = 0;

int mode = 0;
int tab = 0;

elapsedMillis timeElapsed;
unsigned int interval = REFRESH_INTERVAL;

unsigned int ramp = ANALOG_HALF_SCALE;
int rstep = RAMP_STEP;

TFT TFTscreen = TFT(CS, DC, RST);

//////////////////////////////////////////
////////////// INITIALISE \\\\\\\\\\\\\\\\
//////////////////////////////////////////

void setup() {
    
  TFTscreen.begin(); // MODDED

  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  
  Serial.begin(9600);

  displayLCD(TFTscreen, 0);
  
}

void loop() {

  switch (mode) {

  case 0:
  analog.write(DAC1, ANALOG_FULL_SCALE); // set DAC1 SMA output to 5V when IDLE
    
  // Check if button pressed
  button1State = digitalRead(BUTTON1_PIN);
  if (button1State == LOW) {
      mode = mode + 1;
      tab = 1;
      displayLCD(TFTscreen, tab);

    }
    
    break;

  case 1:
    
    photod = analog.read(ADC4) + ANALOG_HALF_SCALE; // 5 V = 0 & 0 V = - 32767 --> 5 V = 32767 & 0 V = 0
    setpoint = analog.read(ADC3)+ ANALOG_HALF_SCALE;
       
    lock = checkCavityTransmission(photod, setpoint);
      
    if (lock)
      { //set "Lock/Tune" digital out to 5V and set unlockCount = 0
        
        analog.write(DAC1, ANALOG_FULL_SCALE); // set DAC1 SMA output to 5V
        unlockCount = 0;

        //if (tab != 2) {
        //  tab = 2;
        //  displayLCD(TFTscreen, tab);
        //}
        
      }
      
    else if (unlockCount < 30)
      { // unlockCount += 1 and wait 10 ms
        
        analog.write(DAC1, ANALOG_FULL_SCALE); // Keep lock ON (also to avoid LCD/wirte/read bug)
        unlockCount += 1;

        //if (tab != 3) {
        //  tab = 3;
        //  displayLCD(TFTscreen, tab);
        //}
        
        delay(1);
       
      }
      
    else
      { //Set "Lock/Tune" digital out to 0V

        //if (tab != 4) {
        //  tab = 4;
        //  displayLCD(TFTscreen, tab);
        //}
        
        analog.write(DAC1, ANALOG_HALF_SCALE); // set DAC1 SMA output to 0V
        
        // Ramp piezo to find lock
        while (!lock) {

            ramp = ramp + rstep;  

            if ((ramp + rstep > ANALOG_FULL_SCALE) || (ramp + rstep < ANALOG_HALF_SCALE)) {
              rstep = -rstep;
             }

            analog.write(DAC2, ramp);

            int k = 0; // to change ramp speed change upper number of checks (while loop exit condition)
            while (k < 5 && lock != 1) {
              photod = analog.read(ADC4) + ANALOG_HALF_SCALE;
              setpoint = analog.read(ADC3)+ ANALOG_HALF_SCALE;
              lock = checkCavityTransmission(photod, setpoint);  
              k++;
            } 

          }

          break;

      }
              
     // Check if button pressed
     button1State = digitalRead(BUTTON1_PIN);
     if (button1State == LOW) {
       mode = 0;
       tab = 0;
       displayLCD(TFTscreen, tab);
     }

      break;
  
    } 
 
}
