#include <Arduino.h>
#include <analogShield.h>
#include <SPI.h>  //required for ChipKIT but does not affect Arduino
#include <TFT.h> // Hardware-specific library

#include "ArduinoRelockerDefines.h"


//////////////////////////////////////////
/////////////// FUNCTIONS \\\\\\\\\\\\\\\\
//////////////////////////////////////////

void setupLCD0(TFT TFTscreen) {
  // write the welcome screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // Write text to screen ...
  TFTscreen.text("PDH Relock", 20, 20);

  TFTscreen.stroke(255, 0, 0);
  TFTscreen.text("IDLE", 50, 40);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Start", 47, 70);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("Press LB", 30, 90);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}

void setupLCD1(TFT TFTscreen) {
  // write the ON screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // Write text to screen ...
  TFTscreen.text("PDH Relock", 20, 20);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("ACTIVE", 45, 40);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}

void setupLCD2(TFT TFTscreen) {
  // write the lock screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // Write text to screen ...
  TFTscreen.text("PDH Relock", 20, 20);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("ON", 65, 40);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Status:", 40, 70);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("Locked", 40, 90);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}


void setupLCD3(TFT TFTscreen) {
  // write the Low signal screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // Write text to screen ...
  TFTscreen.text("PDH Relock", 20, 20);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("ON", 60, 40);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Status:", 40, 70);

  TFTscreen.stroke(255,165,0);
  TFTscreen.text("Low Signal", 20, 90);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}

void setupLCD4(TFT TFTscreen) {
  // write the Scanning screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // Write text to screen ...
  TFTscreen.text("PDH Relock", 20, 20);

  TFTscreen.stroke(0, 255, 0);
  TFTscreen.text("ON", 60, 40);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text("Status:", 40, 70);

  TFTscreen.stroke(255,69,0);
  TFTscreen.text("Scanning", 30, 90);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}

void setupLCD5(TFT TFTscreen) {
  // write the static text to the screen
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  // set the font size
  TFTscreen.setTextSize(2);
  
  // write the text to the top left corner of the screen
  TFTscreen.text("Cavity Tx:\n ", 0, 10);

  // Write other fixed text ...
  TFTscreen.text("Setpoint:\n ", 0, 50);
  
  // Write other fixed text ...
  TFTscreen.text("Unlock count:\n ", 0, 90);

 SPI.setClockDivider(4);
 SPI.setDataMode(SPI_MODE1);
  
}

void writeLCD(TFT TFTscreen, int photovoltage, int setpoint, int unlockcount, int start, bool erase){
    
  float temp; 
  String numString;
  char printout[7];
  char printout3[7];
  char printout2[3]; 
 
  TFTscreen.setTextSize(2);
  
  temp = photovoltage; 
  numString = String(temp);
  numString.toCharArray(printout, 7);
  
  TFTscreen.text(printout, 0, start+20);

  temp = setpoint; 
  numString = String(temp);
  numString.toCharArray(printout3, 7);
  
  TFTscreen.text(printout3, 0, start+60);
  
  temp = unlockcount; 
  numString = String(temp);
  numString.toCharArray(printout2, 3);
  
  TFTscreen.text(printout2,0,start+100);

  if(erase){
    //delay(10);
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(printout, 0, start+20);
    TFTscreen.text(printout3, 0, start+60);
    TFTscreen.text(printout2, 0, start+100);
  }

  SPI.setClockDivider(4);
  SPI.setDataMode(SPI_MODE1);

}

void displayLCD(TFT TFTscreen, int tab) {
    
    switch (tab) {
    
    case 0: // OFF
      setupLCD0(TFTscreen);
      break;
    
    case 1: // ON
      setupLCD1(TFTscreen);
      break;
    
    case 2: // LOCKED
      setupLCD2(TFTscreen);
      break;

    case 3: // LOW SIGNAL
      setupLCD3(TFTscreen);
      break;

    case 4: // SCANNING
      setupLCD4(TFTscreen);
      break;
  }

}



int checkCavityTransmission(int photod, int setpoint){
  
  //delay(5);
  if (photod > 0.9*setpoint){

    return 1; 
  }
  
  else{
    return 0;
  }
}
