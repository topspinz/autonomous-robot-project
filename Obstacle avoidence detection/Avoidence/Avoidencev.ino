#include <DRV8835MotorShield.h>
#define trigPin 2
#define echoPin 3

#define FrontRightDownIR 30 //verified 
#define FrontLeftDownIR 31  //verified
#define FrontLeftIR 33  //verified
#define FrontRightIR 32 //verified

#define BackRightIR 34
#define BackLeftIR 35
#define BackIR 36

const int FrontRight = A0;  
const int Frontcenter = A1; // Verified center
const int FrontLeft = A2; // Verified When Reflective = 5V 1024 Not on tape

int ValueLeft = 0;        
int ValueRight = 0;        

DRV8835MotorShield motors;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

//Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(FrontLeftDownIR, INPUT);
  pinMode(FrontRightDownIR, INPUT);
  pinMode(FrontLeftIR, INPUT);
  pinMode(FrontRightIR, INPUT);
  
  pinMode(BackRightIR, INPUT);
  pinMode(BackLeftIR, INPUT);
  pinMode(BackIR, INPUT);

  
}

void loop() {
  int UltraFlag;
  int UltraFlagRight;
  int UltraFlagLeft;
  int FrontLeftIRFlag;
  int FrontRightIRFlag;
  long duration, distance;
  int FrontDownLeftIRFlag;
  int FrontDownRightIRFlag;



//*********************************************Inital Detection Algorithm
//***********************************************************************
UltraFlag = 0; //Reset ultrasonic check
UltraFlagRight = 0;
UltraFlagLeft = 0;
FrontLeftIRFlag = 1;
FrontRightIRFlag = 1;
FrontDownLeftIRFlag = 1;
FrontDownRightIRFlag = 1;

for (int i = 0; i < 4000; i++){    //turn to the left
  //Serial.println("first left"); 
    motors.setM1Speed(-100);    // Left
    motors.setM2Speed(100);    //Right

    
    //Ultra scan with limited checking
    if( i == 0 || i == 500 || i == 1000 || i == 1500 || i == 2000 || i == 2500 || i == 3000 || i == 3500){
        //Check Range of ultra sonic continuous scanning
         //long duration, distance;
          digitalWrite(trigPin, LOW);  // Added this line
          delayMicroseconds(2); // Added this line
          digitalWrite(trigPin, HIGH);
        
          delayMicroseconds(10); // Added this line
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance = (duration/2) / 29.1;
    }

    
    
    if (distance <= 13){
          UltraFlag = 1;
          UltraFlagLeft = 1;
       }
    if  (digitalRead(FrontRightIR) == 0)
          FrontRightIRFlag = 0;

    if  (digitalRead(FrontLeftIR) == 0)
          FrontLeftIRFlag = 0;
    
          
}

for (int i = 0; i < 8000; i++){  // Don't move as far back then go go to the right
    motors.setM1Speed(100);    // Left
    motors.setM2Speed(-100);    //Right


    //Ultra scan with limited checking
    if( i == 0 || i == 500 || i == 1000 || i == 1500 || i == 2000 || i == 2500 || i == 3000 || i == 3500){
        //Check Range of ultra sonic continuous scanning
         //long duration, distance;
          digitalWrite(trigPin, LOW);  // Added this line
          delayMicroseconds(2); // Added this line
          digitalWrite(trigPin, HIGH);
        
          delayMicroseconds(10); // Added this line
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance = (duration/2) / 29.1;
    }



  
    if (distance <= 13){
          UltraFlag = 1;
          
    }
    if  (digitalRead(FrontRightIR) == 0)
          FrontRightIRFlag = 0;

    if  (digitalRead(FrontLeftIR) == 0)
          FrontLeftIRFlag = 0;
    
}


for (int i = 0; i < 4000; i++){

    motors.setM1Speed(-100);    // Left
    motors.setM2Speed(100);    //Right


    //Ultra scan with limited checking
    if(i == 0 || i == 500 || i == 1000 || i == 1500 || i == 2000 || i == 2500 || i == 3000 || i == 3500){
        //Check Range of ultra sonic continuous scanning
         //long duration, distance;
          digitalWrite(trigPin, LOW);  // Added this line
          delayMicroseconds(2); // Added this line
          digitalWrite(trigPin, HIGH);
        
          delayMicroseconds(10); // Added this line
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance = (duration/2) / 29.1;
    }


    
    if (distance <= 13){
          UltraFlag = 1;
          UltraFlagRight = 1;
    }
    if  (digitalRead(FrontRightIR) == 0)
          FrontRightIRFlag = 0;

    if  (digitalRead(FrontLeftIR) == 0)
          FrontLeftIRFlag = 0;
    
          
}
//*********************************************End of Inital Detection Algorithm
//***********************************************************************



///Serial.println("UltraFlag");
//Serial.println(UltraFlag);
//Serial.println(FrontLeftIRFlag);
//Serial.println(FrontRightIRFlag);






// If the way is clear proceed straight 
if (UltraFlag == 0 && FrontLeftIRFlag == 1 && FrontRightIRFlag == 1 ){  // High means nothing infront



           //Edge of table detection during continous check 
           if (digitalRead(FrontLeftDownIR) == 1 && digitalRead(FrontRightDownIR) == 0){ // over the edge on the left side
                   
                      // Back up a bit
                      motors.setM1Speed(-150);    // Left
                      motors.setM2Speed(-150);    //Right
                      delay(500);
                      //Rotate right
                      motors.setM1Speed(150);    // Left
                      motors.setM2Speed(-150);    //Right
                      delay(1000);
                      motors.setM1Speed(0);    // Left
                      motors.setM2Speed(0);    //Right
                             //Serial.println("left");     


                    
              } 
              else if (digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 1) // over the edge on the right side
              {      
  
                      // Back up a bit
                      motors.setM1Speed(-150);    // Left
                      motors.setM2Speed(-150);    //Right
                      delay(500);
                      //Rotate left
                      motors.setM1Speed(-150);    // Left
                      motors.setM2Speed(150);    //Right
                      delay(1000);
                      motors.setM1Speed(0);    // Left
                      motors.setM2Speed(0);    //Right

                      //Serial.println("right");    
              }
              else if (digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 0) // both sensors not triggered
              {      
  

                     
                    motors.setM1Speed(150);    // Left
                    motors.setM2Speed(150);    //Right
                    delay(500);
                    //Serial.println("both not triggered");    
              }      
              else if (digitalRead(FrontLeftDownIR) == 1 && digitalRead(FrontRightDownIR) == 1) // both sensors Are TRIGGERED
              {      
                      // Back up a bit
                      motors.setM1Speed(-150);    // Left
                      motors.setM2Speed(-150);    //Right
                      delay(500);
                      //Rotate left
                      motors.setM1Speed(-150);    // Left
                      motors.setM2Speed(150);    //Right
                      delay(1000);
                      motors.setM1Speed(0);    // Left
                      motors.setM2Speed(0);    //Right
                     //Serial.println("both ARE TRIGGERED"); 
              

              
        } // End of nothing in front
  
    }
    //************ Object detected in the front right
    else if (UltraFlagRight == 1 || (FrontLeftIRFlag == 1 && FrontRightIRFlag == 0) )
    {
      Serial.println("Right Side in"); 
              //Edge of table detection during continous check 
             if (digitalRead(FrontLeftDownIR) == 1 && digitalRead(FrontRightDownIR) == 0){ // over the edge on the left side ideally back up a bit and rotatea bit
  
                  //for (int j = 0 ; j < 1000; j ++){ // Back up a bit
                    motors.setM1Speed(-150);    // Left
                    motors.setM2Speed(-150);    //Right
                    delay(1000);
                  //}
                 // for (int j = 0 ; j < 3000; j ++){ // rotate to the left
                    motors.setM1Speed(150);    // Left
                    motors.setM2Speed(-150);    //Right
                    delay(5000);
                  //}
  
  
                  
                } else if ((digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 1)) // over the edge on the right side
                {         
                  //rotate to the left
                motors.setM1Speed(-150);    // Left
                motors.setM2Speed(150);    //Right
                delay(1000);
                } else if ((digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 0)) // both sensors not triggered
                {      
  
                 //Move to the left
                motors.setM1Speed(-150);    // Left
                motors.setM2Speed(150);    //Right
                delay(5000);
                }      
  
  
       // }
    
    }
    //************ Object detected in the front left
    else if (UltraFlagLeft == 1 || ( FrontLeftIRFlag == 0 && FrontRightIRFlag == 1) )
    {
               Serial.println("Left Side in"); 
              //Edge of table detection during continous check 
             if (digitalRead(FrontLeftDownIR) == 1 && digitalRead(FrontRightDownIR) == 0){ // over the edge on the left side
                motors.setM1Speed(150);    // Left
                motors.setM2Speed(-150);    //Right
                delay(2000);
  
                } 
                else if ((digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 1)) // over the edge on the right side
                {         
                //motors.setM1Speed(-150);    // Left
                //motors.setM2Speed(150);    //Right
  
  
                  //for (int j = 0 ; j < 1000; j ++){ // Back up a bit
                    motors.setM1Speed(-150);    // Left
                    motors.setM2Speed(-150);    //Right
                    delay (1000);
                  //}
                  //for (int j = 0 ; j < 3000; j ++){ // rotate to the left enugh to clear the object
                    motors.setM1Speed(-150);    // Left
                    motors.setM2Speed(150);    //Right
                    delay(5000);
                 //}
  
  
                
                } 
                else if ((digitalRead(FrontLeftDownIR) == 0 && digitalRead(FrontRightDownIR) == 0)) // both sensors not triggered
                {         
                motors.setM1Speed(150);    // Left
                motors.setM2Speed(150);    //Right
                delay(1000);
                }      
  
  
  
    }

 //************ Object detected in the front left and front right
    else if (UltraFlagLeft == 1 &&  UltraFlagRight == 1)
    {
           
                motors.setM1Speed(-150);    // Left
                motors.setM2Speed(150);    //Right
                delay(8000);
                 
   }









    
}








 








  

