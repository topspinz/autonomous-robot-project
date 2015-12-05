/*
 
  This example code is in the public domain.
 
  ---------------------------------------------------------------------
 
  This program demonstrates button detection, LCD text/number printing,
  and LCD backlight control on the Freetronics LCD & Keypad Shield, connected to an Arduino board.
 
 
  Pins used by LCD & Keypad Shield:
 
    A0: Buttons, analog input from voltage ladder
    D4: LCD bit 4
    D5: LCD bit 5
    D6: LCD bit 6
    D7: LCD bit 7
    D8: LCD RS
    D9: LCD E
    D10: LCD Backlight (high = on, also has pullup high so default is on)
 
  ADC voltages for the 5 buttons on analog input pin A0:
 
    RIGHT:  0.00V :   0 @ 8bit ;   0 @ 10 bit
    UP:     0.71V :  36 @ 8bit ; 145 @ 10 bit
    DOWN:   1.61V :  82 @ 8bit ; 329 @ 10 bit
    LEFT:   2.47V : 126 @ 8bit ; 505 @ 10 bit
    SELECT: 3.62V : 185 @ 8bit ; 741 @ 10 bit
*/
/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <LiquidCrystal.h>   // include LCD library
#include <DRV8835MotorShield.h>
/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
// Pins in use
#define BUTTON_ADC_PIN           A0  // A0 is the button ADC input
#define LCD_BACKLIGHT_PIN         10  // D10 controls LCD backlight
// ADC readings expected for the 5 buttons on the ADC input
#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            145  // up
#define DOWN_10BIT_ADC          329  // down
#define LEFT_10BIT_ADC          505  // left
#define SELECT_10BIT_ADC        741  // right
#define BUTTONHYSTERESIS         10  // hysteresis for valid button sensing window
//return values for ReadButtons()
#define BUTTON_NONE               0  // 
#define BUTTON_RIGHT              1  // 
#define BUTTON_UP                 2  // 
#define BUTTON_DOWN               3  // 
#define BUTTON_LEFT               4  // 
#define BUTTON_SELECT             5  // 
//some example macros with friendly labels for LCD backlight/pin control, tested and can be swapped into the example code as you like
#define LCD_BACKLIGHT_OFF()     digitalWrite( LCD_BACKLIGHT_PIN, LOW )
#define LCD_BACKLIGHT_ON()      digitalWrite( LCD_BACKLIGHT_PIN, HIGH )
#define LCD_BACKLIGHT(state)    { if( state ){digitalWrite( LCD_BACKLIGHT_PIN, HIGH );}else{digitalWrite( LCD_BACKLIGHT_PIN, LOW );} }
/*--------------------------------------------------------------------------------------
  Variables
--------------------------------------------------------------------------------------*/
byte buttonJustPressed  = false;         //this will be true after a ReadButtons() call if triggered
byte buttonJustReleased = false;         //this will be true after a ReadButtons() call if triggered
byte buttonWas          = BUTTON_NONE;   //used by ReadButtons() for detection of button events
/*--------------------------------------------------------------------------------------
  Init the LCD library with the LCD pins to be used
--------------------------------------------------------------------------------------*/
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );   //Pins for the freetronics 16x2 LCD shield. LCD: ( RS, E, LCD-D4, LCD-D5, LCD-D6, LCD-D7 )
/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
--------------------------------------------------------------------------------------*/

//************************* Sensors **********************
int battraw = A1;    // select the input pin for the potentiometer
int right = A3;
int center = A4;
int left = A2; 
int LightSensorRaw = A5;    // Light Sensor
//************************* END Sensors **********************


void setup()
{
   //********************** LCD SETUP *******************************************
   //button adc input
   pinMode( BUTTON_ADC_PIN, INPUT );         //ensure A0 is an input
   digitalWrite( BUTTON_ADC_PIN, LOW );      //ensure pullup is off on A0
   //lcd backlight control
   digitalWrite( LCD_BACKLIGHT_PIN, HIGH );  //backlight control pin D3 is high (on)
   pinMode( LCD_BACKLIGHT_PIN, OUTPUT );     //D3 is an output
   //set up the LCD number of columns and rows: 
   lcd.begin( 16, 2 );
   /*
   //Print some initial text to the LCD.
   lcd.setCursor( 0, 0 );   //top left
   //          1234567890123456
   lcd.print( "LinkSprite  16x2" );
   //
   lcd.setCursor( 0, 1 );   //bottom left
   //          1234567890123456
   lcd.print( "Btn:" );
   */
   //********************** END of LCD SETUP *******************************************

   //********************** Motor Serial SETUP *******************************************
   // set the digital pin as output:
   //pinMode(13, OUTPUT);  
  
   // set the data rate for the SoftwareSerial port
   //Serial.begin(9600, SERIAL_8N1);
  //********************** END Motor Serial SETUP *******************************************

   // LCD Menu Items

  


}


   int state =0;
   byte button;
   byte timestamp;
   float batt; 
   float LightSensor; 
   byte motorspeed = 50;
   

  void loop()
  {

   //get the latest button pressed, also the buttonJustPressed, buttonJustReleased flags
   

   
   button = ReadButtons();
   
    switch( button )
   {
      case BUTTON_UP:
      {
        if (state <= 8){
          state = state + 1; 
           //lcd.setCursor( 4, 1 );
           //lcd.print( "UP" );
       
           delay(250); 
           //Clear Screen
           lcd.setCursor( 0, 0 );
           lcd.print( "                " );
           lcd.setCursor( 0, 1 );
           lcd.print( "                " ); 
       }
         break;
      }
      case BUTTON_DOWN:
      {
         if (state >= 1){
           state = state - 1;
           //lcd.setCursor( 4, 1 );
           //lcd.print( "DOWN" );
           
           delay(250);  
           //Clear Screen
           lcd.setCursor( 0, 0 );
           lcd.print( "                " );
           lcd.setCursor( 0, 1 );
           lcd.print( "                " );   
         }
         break;
      }
   
      case BUTTON_LEFT:
      {
        if (motorspeed > 0){
        motorspeed = motorspeed - 1;
        lcd.setCursor( 0, 1);
        lcd.print("   ");
        }
        delay(50); 
        break;
      }
      
      case BUTTON_RIGHT:
      {
        if (motorspeed <= 99){
        lcd.setCursor( 0, 1);
        lcd.print("   ");
         motorspeed = motorspeed + 1;
        }
         delay(50);
         
         break;
      }
   
   
   
   }
   
   
   
   // print the number of seconds since reset (two digits only)
   timestamp = ( (millis() / 1000) % 100 );   //"% 100" is the remainder of a divide-by-100, which keeps the value as 0-99 even as the result goes over 100
   lcd.setCursor( 14, 1 );
   if( timestamp <= 9 )
      lcd.print( " " );   //quick trick to right-justify this 2 digit value when it's a single digit
   lcd.print( timestamp, DEC );
   
   
   //Battery State
   if (state == 0){
       
     lcd.setCursor( 0, 0 );
     lcd.print( "Batt:" );
     lcd.setCursor( 5, 0 );
     batt = analogRead(battraw)/100.0 -0.04;
     lcd.print(batt,3);
     
   } 
   
    //Test State
   if (state == 1){

   
     lcd.setCursor( 0, 0 );
     lcd.print( "L:" );
     lcd.setCursor( 2, 0 );
     lcd.print (analogRead(left)/1000);
     //LightSensor = analogRead(right);
     //lcd.print (analogRead((float) right)/1000.0,0);
     
     lcd.setCursor( 5, 0 );
     lcd.print( "C:" );
     lcd.setCursor( 7, 0 );
     lcd.print (analogRead(center)/1000);
     
     lcd.setCursor( 11, 0 );
     lcd.print( "R:" );
     lcd.setCursor( 13, 0 );
     lcd.print (analogRead(right)/1000);
     
     if ((analogRead(left)/1000 == 1)&& (analogRead(right)/1000 == 0)){ 
         delay(50);
         rightmotorreverse(120);
         leftmotorforward(120);
         delay(50);
         }
         else if ((analogRead(right)/1000 == 1) && (analogRead(left)/1000 == 0)){
         delay(50);
         rightmotorforward(120);
         leftmotorreverse(120);
         delay(50);
         }
         else if ((analogRead(center)/1000 == 0) && (analogRead(right)/1000 == 1) && (analogRead(left)/1000 == 1)){
           //delay(100);
          // rightmotorforward(100);
          // leftmotorforward(100);
           
      //Motor forward
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
      
       
       Serial.write(3);
       //count = count + 1;
       Serial.write(100);
           
        Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(0);
       //count = count + 1;
       Serial.write(100);
           
           
           
           
           
         }
         else {
           delay(50);
           rightmotorforward(120);
           leftmotorreverse(120);
           
         }
     
     
     
     
   } 
    if (state == 2){
    delay(50);
   
     lcd.setCursor( 0, 0 );
     lcd.print( "Stop" );
       rightmotorforward(0);
           leftmotorreverse(0);
   /*
     lcd.setCursor( 0, 1 );
     //LightSensor = analogRead(LightSensorRaw);
     lcd.print(motorspeed);
     rightmotorforward(motorspeed);
     */
   } 
     if (state == 3){

   
     lcd.setCursor( 0, 0 );
     lcd.print( "Right Motor Reverse" );
     lcd.setCursor( 0, 1 );
     //LightSensor = analogRead(LightSensorRaw);
     lcd.print(motorspeed);
     rightmotorreverse(motorspeed);
   } 
     if (state == 4){

   
     lcd.setCursor( 0, 0 );
     lcd.print( "Left Motor Forward" );
     lcd.setCursor( 0, 1 );
     //LightSensor = analogRead(LightSensorRaw);
     lcd.print(motorspeed);
     leftmotorforward(motorspeed);
   } 
     if (state == 5){

   
     lcd.setCursor( 0, 0 );
     lcd.print( "Left Motor Reverse" );
     lcd.setCursor( 0, 1 );
     //LightSensor = analogRead(LightSensorRaw);
     lcd.print(motorspeed);
     leftmotorreverse(motorspeed);
   } 
   
     //lcd.setCursor( 0, 1 );
     //LightSensor = analogRead(LightSensorRaw);
     //lcd.print(LightSensor,4);
     
     
     //Current State
     //lcd.setCursor( 0, 1);
     //lcd.print("   ");
     
   
   
   
   /*
   
   
         // Initilize MotorController 
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(1);
       //count = count + 1;
       Serial.write(50);
   
   
   
   
   */
   
   
   
  }
  
  /*--------------------------------------------------------------------------------------
  ReadButtons()
  Detect the button pressed and return the value
  Uses global values buttonWas, buttonJustPressed, buttonJustReleased.
--------------------------------------------------------------------------------------*/
byte ReadButtons()
{
   unsigned int buttonVoltage;
   byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn
 
   //read the button ADC pin voltage
   buttonVoltage = analogRead( BUTTON_ADC_PIN );
   //sense if the voltage falls within valid voltage windows
   if( buttonVoltage < ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_RIGHT;
   }
   else if(   buttonVoltage >= ( UP_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( UP_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_UP;
   }
   else if(   buttonVoltage >= ( DOWN_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_DOWN;
   }
   else if(   buttonVoltage >= ( LEFT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_LEFT;
   }
   else if(   buttonVoltage >= ( SELECT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_SELECT;
   }
   //handle button flags for just pressed and just released events
   if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
   {
      //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
      //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
      buttonJustPressed  = true;
      buttonJustReleased = false;
   }
   if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
   {
      buttonJustPressed  = false;
      buttonJustReleased = true;
   }
 
   //save the latest button value, for change event detection next time round
   buttonWas = button;
 
   return( button );
}


void leftmotorforward(int speed)
{
        // Initilize MotorController 
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(0);
       //count = count + 1;
       Serial.write(speed);
       
}

void leftmotorreverse(int speed)
{
        // Initilize MotorController 
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(1);
       //count = count + 1;
       Serial.write(speed);
       
}
void rightmotorforward(int speed)
{
        // Initilize MotorController 
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(3);
       //count = count + 1;
       Serial.write(speed);
       
}
void rightmotorreverse(int speed)
{
        // Initilize MotorController 
       Serial.write(128);
       
       // Device Configuration which allows for motor and speed
       Serial.write(0);
       
       // Motor Selection
       // 0 is left Reverse  (00)
       // 1 is left Forward  (01)
       // 2 is right reverse (10)
       // 3 is right Forward (11)
       // 1 is both 
       
       
       Serial.write(2);
       //count = count + 1;
       Serial.write(speed);
       
}
