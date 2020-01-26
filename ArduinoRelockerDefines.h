//////////////////////////////////////////
////////////////// PINS \\\\\\\\\\\\\\\\\\
//////////////////////////////////////////

// Pushbuttons setup
#define BUTTON1_PIN 7 // SW1
#define BUTTON2_PIN 4 // SW2

// TFT LCD Screen setup
#define CS   10
#define DC   9
#define RST  8  




//////////////////////////////////////////
////////////// PARAMETERS \\\\\\\\\\\\\\\\
//////////////////////////////////////////

#define STEP_SIZE      80
#define SCAN_LENGTH   125
#define SENSITIVITY     0.9
#define ANALOG_BITS     12
#define ANALOG_HALF_SCALE   32767
#define ANALOG_FULL_SCALE   65534
#define STATE_MACHINE_MAX 1
#define BIT_TO_uA      .2 //rough calibration, good to within 10%
#define CAVITY_TRANS_THRESHOLD   -28000
#define REFRESH_INTERVAL 200
#define RAMP_STEP 15 // .153 mV per unit (cavity linewidth ~16mV)
