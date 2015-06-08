# Arduino-Rotary-Knob-Gray-code-
Small Arduino library for asynchronous read-out of a rotary knob with keyswitch. Library returns status change, encoder value, switch value.

Arduino class for asynchronous reading of a EC11 rotary encoder with keyswitch
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

Usage:
(1) Create instance (encoder ENCODER(encoderPinA,encoderPinB,switchPin);)
(2) Set pinMode for all pins to INPUT_PULLUP
(3) Call ENCODER.check() continuously in main loop. The return value is true if 
	the encoder position changed or if the Keyswitch is pressed. 
	--> perform desired actions.
The routine requires quite fast calling of rthe check routine to ensure a responsive behavior. 
If the delays in the main loop are too large (>5 ms), consider using interrupt-driven read-out.
