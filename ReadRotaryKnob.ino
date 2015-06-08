// For documentation, see RotEnc.h

#include "RotEnc.h"                   // Statistics library to calculate average, std, min, max

#define encoderPinA 2                 // Choose the encoder pins
#define encoderPinB 3                 // (... pull to ground via encoder)
#define switchPin 4                   // Pushbutton pin

encoder Encoder(encoderPinA,encoderPinB,switchPin);  // Initialize encoder instance

void setup()
{
  Serial.begin(115200);               // Serial for feedback to user
}

void loop()
{
  if (Encoder.check()){              // True if encoder or pushbutton value changed
    Serial.print("Encoder: ");
    Serial.print(Encoder.value);
    Serial.print(", PushButton: ");
    Serial.println(Encoder.pushButton);
  }
}

