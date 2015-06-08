#include "RotEnc.h"
#include "Arduino.h"


//**********************************************
//  Initialize encoder pins and values
// **********************************************

encoder::encoder(int pinA, int pinB, int pinSwitch){
  _pinA = pinA;
  _pinB = pinB;
  _pinSwitch = pinSwitch;
  value = 0;
  pushButton = false;
  _Sold = 0;
  _A = 0;
  _B = 0;
  _S = 0;
  pinMode(pinA, INPUT_PULLUP);    		// Encoder pin mode
  pinMode(pinB, INPUT_PULLUP);			// 
  pinMode(pinSwitch, INPUT_PULLUP);     // Knob pushbutton pin mode
  _lastEncoderTime = millis();
}


//************************************************
//  Update encoder values, return if values changed
// ***********************************************

int encoder::check()
{
  if (millis()-_lastEncoderTime < DebounceDelay) return false;  // Wait for DebounceDelay
  _lastEncoderTime = millis();          // Reset _lastEncoderTime for next debounced read

  // ---- Check the encoder --- //
  bool rtrn = false;					// Return variable
  if (isLow(_pinA)) {_A++;}             // If pin A is pulled low, increment A 
  else {_A = 0;}                        // ... else reset A
  if (isLow(_pinB)) {_B++;}             // If pin B is pulled low, increment B 
  else {_B = 0;}                        // ... else reset B

  if (_A && _B){                        // A and B low, time to record encoder step
    if (_A>_B) {value += 1; rtrn=1;}    // ... A was first, increase encoder value, set return value
    if (_A<_B) {value -= 1; rtrn=1;}    // ... B was first, decrease encoder value, set return value
    _A = 0;                             // ... reset A and B 
    _B = 0;                             // ...
  }

  // ---- Check the pushbutton switch ---- //
  if (isLow(_pinSwitch)) {_S++;}        	// If switch-pin is pulled low, increment S 
  else {_S = 0; _Sold = 0; pushButton = 0;} // ... else reset
  
  if (_S && !_Sold) {				    	// Switch was pulled low (2 reads to debounce)
    pushButton = true; 						// ... update switch value
    _Sold = 1;								// ... deactivate switch until released
    rtrn = 1;								// ... set return value
  }
  return rtrn;								// Return return value
}

