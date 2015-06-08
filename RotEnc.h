/************************************************************************
Class for asynchronous reading of a EC11 rotary encoder with keyswitch
(Purchased from Aliexpress, " 12mm Rotary Encoder Switch W. Keyswitch")

The manual encoder puts our Gray code via 3 pins (A, COM, B):

         Positive turn (1 step)    Negative Turn (1 step)
   open  ____         ___________  ________         _______
A            |        |                    |        |      
   COM       |________|                    |________|      

   open  ________         _______  ____         ___________         
B                |        |            |        |  
   COM           |________|            |________|     

Pressing the knob opens a switch between 2 additional pins (C,D)

I assume that A, B, C are pulled up and COM and D are grounded. 
--> Pressing the button pulls C low. 
--> Turning the knob 1 step positive first pulls A low, then B, then releases A, B.
--> Turning the knob 1 step negative first pulls B low, then A, then releases B, A.

Use:
(1) Create instance (encoder ENCODER(encoderPinA,encoderPinB,switchPin);)
(2) Set pinMode for all pins to INPUT_PULLUP
(3) Call ENCODER.check() continuously in main loop. The return value is true if 
	the encoder position changed or if the Keyswitch is pressed. 
	--> perform desired actions.
The routine requires quite fast calling of rthe check routine to ensure a responsive behavior. 
If the delays in the main loop are too large (>5 ms), consider using interrupt-driven read-out.

Thomas Schultz, June 2015
Use according to the MIT license (http://opensource.org/licenses/MIT)
***********************************************************************/

#ifndef RotEnc_h
#define RotEnc_h

#define DebounceDelay 1          // Debounce delay in milliseconds

//-----------------
// Defines for fast port read 
//(see: http://masteringarduino.blogspot.kr/2013/10/fastest-and-smallest-digitalread-and.html)
//-----------------
#define pinOfPin(P)    (((P)>=0&&(P)<8)?&PIND:(((P)>7&&(P)<14)?&PINB:&PINC))
#define pinIndex(P)    ((uint8_t)(P>13?P-14:P&7))
#define pinMask(P)     ((uint8_t)(1<<pinIndex(P)))
#define isHigh(P)      ((*(pinOfPin(P))& pinMask(P))>0)
#define isLow(P)       ((*(pinOfPin(P))& pinMask(P))==0)

class encoder
{
  public:
	encoder(int, int, int); 		// Initialize encoder pins and values
    int check();					// Update encoder/button value, returns True if value changed
    
    long int value;					// Encoder value
    bool pushButton;				// True if switch is pressed

 private:   
	int _pinA, _pinB, _pinSwitch;	// Digital pins for reading encoder and switch
	int _A,_B,_S,_Sold;				// Counters for tracking state of pins A, B, Switch 
	long int _lastEncoderTime;		// Time variable for debouncing
};

#endif
