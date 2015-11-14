#define LeftMotorPWM 12
#define RightMotorPWM 13

#define LeftMotorDir 22
#define RightMotorDir 24


void setup()
{
  pinMode(LeftMotorDir,OUTPUT);  // Left side direction    M1
  pinMode(RightMotorDir,OUTPUT);  // Right side direction
  pinMode(LeftMotorPWM,OUTPUT);  // Left Speed Control     M1
  pinMode(RightMotorPWM,OUTPUT);  // Right Speed Control
  

}

void loop()
{
  
  
  // Forward
  digitalWrite(LeftMotorDir,LOW);  // LOW is forward
  digitalWrite(RightMotorDir,LOW);

 for (int j = 0 ; j < 5800; j++) //~ 9 Seconds
 
    for(int i = 0; i < 100; i++){
    if ( i < 100){
      digitalWrite(LeftMotorPWM,HIGH);
      digitalWrite(RightMotorPWM,HIGH);
    }else{
      digitalWrite(LeftMotorPWM,LOW);
      digitalWrite(RightMotorPWM,LOW); 
    }
  }


  
  // Reverse
  digitalWrite(LeftMotorDir,HIGH);  // Higg is reverse
  digitalWrite(RightMotorDir,HIGH);

 for (int j = 0 ; j < 3866; j++)
 
    for(int i = 0; i < 100; i++){
    if ( i < 75){
      digitalWrite(LeftMotorPWM,HIGH);
      digitalWrite(RightMotorPWM,HIGH);
    }else{
      digitalWrite(LeftMotorPWM,LOW);
      digitalWrite(RightMotorPWM,LOW); 
    }
  }


  // Reverse
  digitalWrite(LeftMotorDir,HIGH);  // Higg is reverse
  digitalWrite(RightMotorDir,HIGH);

 for (int j = 0 ; j < 5155; j++)
 
    for(int i = 0; i < 100; i++){
    if ( i < 50){
      digitalWrite(LeftMotorPWM,HIGH);
      digitalWrite(RightMotorPWM,HIGH);
    }else{
      digitalWrite(LeftMotorPWM,LOW);
      digitalWrite(RightMotorPWM,LOW); 
    }
  }


  // Reverse
  digitalWrite(LeftMotorDir,HIGH);  // Higg is reverse
  digitalWrite(RightMotorDir,HIGH);

 for (int j = 0 ; j < 5155; j++)
 
    for(int i = 0; i < 100; i++){
    if ( i < 25){
      digitalWrite(LeftMotorPWM,HIGH);
      digitalWrite(RightMotorPWM,HIGH);
    }else{
      digitalWrite(LeftMotorPWM,LOW);
      digitalWrite(RightMotorPWM,LOW); 
    }
  }

    digitalWrite(LeftMotorPWM,LOW);
    digitalWrite(RightMotorPWM,LOW);
 delay (10000);
}
