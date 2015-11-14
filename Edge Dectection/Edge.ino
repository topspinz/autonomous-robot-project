#include <DRV8835MotorShield.h>

const int FrontLeft = A0;  
const int FrontRight = A1;

int ValueLeft = 0;        
int ValueRight = 0;        

DRV8835MotorShield motors;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {


//Note High number 1024 means over 

if (analogRead(FrontLeft) > 250 && analogRead(FrontRight) > 250) // Dead ahead edge back up 
{
  motors.setM1Speed(-150); //Left Motor
  motors.setM2Speed(-250); //Right Motor
  delay(1000);
}
else if ( analogRead(FrontLeft) > 250 ) // Over the Edge on the left
{
  // Stop
  motors.setM1Speed(0); //Left Motor
  motors.setM2Speed(0); //Right Motor
  delay(1000);
  
  // Back up with right turn
  motors.setM1Speed(-150); //Left Motor
  motors.setM2Speed(-250); //Right Motor
  delay(1000);

  //Stop
  motors.setM1Speed(0); //Left Motor
  motors.setM2Speed(0); //Right Motor
  delay(1000);
}
else if (analogRead(FrontRight) > 250 ) // Over the Edge on the Right
 {
  // Stop
  motors.setM1Speed(0); //Left Motor
  motors.setM2Speed(0); //Right Motor
  delay(1000);
  
  // Back up with right turn
  motors.setM1Speed(-250); //Left Motor
  motors.setM2Speed(-150); //Right Motor
  delay(1000);

  //Stop
  motors.setM1Speed(0); //Left Motor
  motors.setM2Speed(0); //Right Motor
  delay(1000);
 }

//Move forward
  motors.setM1Speed(200); //Left Motor
  motors.setM2Speed(200); //Right Motor










  
}
