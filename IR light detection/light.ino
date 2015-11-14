#include <DRV8835MotorShield.h>

const int FrontRight = A0;  
const int Frontcenter = A1; // Verified center
const int FrontLeft = A2; // Verified When Reflective = 5V 1024 Not on tape

int ValueLeft = 0;        
int ValueRight = 0;        

DRV8835MotorShield motors;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {


//Note High number 1024 means over 
// note sensor < 250 means triggered on


//Only Center on tape Other two are white
if (analogRead(Frontcenter) < 250 && analogRead(FrontRight) > 250 && analogRead(FrontLeft) > 250)
{
//Move forward
  motors.setM1Speed(-100); //Right Motor - forward
  motors.setM2Speed(-100); //LeftMotor
  //delay(1000);
}
// (L shape right) Center and right on tape means do a hard right turn  less then < is on tape ie  (analog < 255) triggered on tape 
else if ( analogRead(Frontcenter) < 250 && analogRead(FrontRight) < 250  && analogRead(FrontLeft) > 250 ) // Over the Edge on the left
{
  // Stop
  motors.setM1Speed(0);  //Right Motor
  motors.setM2Speed(0);  //Left Motor
  delay(1000);

  //reverse
   //motors.setM1Speed(100); //Right Motor
  //motors.setM2Speed(100); //Left Motor
  //delay(1000);
  
  // Back up with right turn
  motors.setM1Speed(0); //right Motor
  motors.setM2Speed(-150); //Left Motor
  delay(500);


}
// (L shape left) Center and right on tape means do a hard right turn
else if (analogRead(Frontcenter) < 250 && analogRead(FrontRight) > 250  && analogRead(FrontLeft) < 250 ) // Over the Edge on the Right
 {
  // Stop
  motors.setM1Speed(0); //Right Motor
  motors.setM2Speed(0); //Left Motor
  delay(1000);

 //reverse
 // motors.setM1Speed(100); //Right Motor
  //motors.setM2Speed(100); //Left Motor
 // delay(1000);

  
  // Back up with right turn
  motors.setM1Speed(-150); //right Motor
  motors.setM2Speed(0); //left Motor
  delay(500);


 }
 // Right is triggered only
 else if (analogRead(Frontcenter) > 250 && analogRead(FrontRight) < 250  && analogRead(FrontLeft) > 250 ) // Right is triggered only
 {
  // Stop
  motors.setM1Speed(0); //Right Motor
  motors.setM2Speed(0); //Left Motor
  delay(1000);

 //reverse
 // motors.setM1Speed(100); //Right Motor
  //motors.setM2Speed(100); //Left Motor
 // delay(1000);

  while (analogRead(Frontcenter) > 250)
  {
  // Back up with right turn
  motors.setM1Speed(0); //right Motor
  motors.setM2Speed(-150); //left Motor
  delay(500);
  }

 }


 // Left is triggered only
 else if (analogRead(Frontcenter) > 250 && analogRead(FrontRight) > 250  && analogRead(FrontLeft) < 250 ) // Right is triggered only
 {
  // Stop
  motors.setM1Speed(0); //Right Motor
  motors.setM2Speed(0); //Left Motor
  //delay(1000);

 //reverse
 // motors.setM1Speed(100); //Right Motor
  //motors.setM2Speed(100); //Left Motor
 // delay(1000);

  while (analogRead(Frontcenter) > 250)
  {
  // Back up with right turn
  motors.setM1Speed(-150); //right Motor
  motors.setM2Speed(0); //left Motor
  delay(500);
  }

 }

 // Nothing Is triggered
 else if (analogRead(Frontcenter) > 250 && analogRead(FrontRight) > 250  && analogRead(FrontLeft) > 250 ) // Right is triggered only
 {
  // Stop
  motors.setM1Speed(0); //Right Motor
  motors.setM2Speed(0); //Left Motor
  delay(1000);

 //reverse
 // motors.setM1Speed(100); //Right Motor
  //motors.setM2Speed(100); //Left Motor
 // delay(1000);
int counterright = 0;

  while (analogRead(FrontRight) > 250 && analogRead(FrontLeft) > 250)
  {
  // Back up with right turn

      motors.setM1Speed(-150); //right Motor
      motors.setM2Speed(150); //left Motor


      
  }



 }








  
}
