
#include <Servo.h>

//Constants
int const GIVE_BACK_TIME = 125;

//Constants for inputs
int const I_RED_BUTTON_PIN = 4;
int const I_GREEN_BUTTON_PIN = 2;
int const I_LDR1_PIN = A3;  //top left
int const I_LDR2_PIN = A2;  //top right
int const I_LDR3_PIN = A1;  //bottom left
int const I_LDR4_PIN = A0;  //bottom right
int const I_TEMPERATURE_PIN = A4;  //temperature

//Constants for outputs
int const O_RED_LED_PIN = 9;
int const O_GREEN_LED_PIN = 11;
int const O_BLUE_LED_PIN = 10;
int const O_TWIST_SERVO_PIN = 5;
int const O_TILT_SERVO_PIN = 6;

//Global variables
bool gRunning = false;
bool gVerboseDiagMode = false;

Servo gServoTwist;
int gServoTwistPositionCommand; //commanded position
bool gServoTwistMoveIP; //move in progress

Servo gServoTilt;
bool gServoTiltMoveIP; //move in progress
int gServoTiltPositionCommand; //commanded position

int gLDR1;
int gLDR2;
int gLDR3;
int gLDR4;
int gTemperature;

int gVectorStep;
bool gVectorSeq1Enabled;
bool gVectorSeq2Enabled;
bool gTrackToLightEnabled;

bool gStartupOneShot = false;


//Runs once
void setup() 
{
  //Open a serial port
  Serial.begin(9600);

  //Setup digital inputs
  pinMode(I_RED_BUTTON_PIN, INPUT);
  pinMode(I_GREEN_BUTTON_PIN, INPUT);
  
  //Setup digital outputs
  pinMode(O_RED_LED_PIN, OUTPUT);
  pinMode(O_GREEN_LED_PIN, OUTPUT);
  pinMode(O_BLUE_LED_PIN, OUTPUT);

  //Power-up to the stopped (red LED energized) state
  disableTracking();

  //Post product information to serial port
  reportProductInfo();
}


//Runs continuously
void loop()
{
  //Serial port message receipt processing
  if (Serial.available() > 0)
  {
    int iControlCode;
    iControlCode = Serial.parseInt();
    processSerialMessage(iControlCode);
  }

  //Read green button
  int iGreenButton;
  iGreenButton = digitalRead(I_GREEN_BUTTON_PIN);
  if (iGreenButton == HIGH && gRunning == false)
  {
    enableTracking();
  }

  //Read red button
  int iRedButton;
  iRedButton = digitalRead(I_RED_BUTTON_PIN);
  if (iRedButton == HIGH && gRunning == true)
  {
    disableTracking();
  }

  //Read all instrumentation into global variables
  readPhotoResistors();
  averageTopTwoSensors();
  averageBottomTwoSensors();
  readTemperatureProbe();

  //Adjust servo positions according to light on photoresistors
  if (gRunning == true)
  {
    if (gTrackToLightEnabled == true)
    {
      //Make small moves of servos based on photo-resitor light levels
      trackToLightSensors();
    }
    else
    {
      //Make small moves based on user commands at serial port. Avoids high velocity moves on mechanism
      smoothMoveTwist();
      smoothMoveTilt();
    }

    //Exercise a series of move steps to see mechanism
    if (gVectorSeq1Enabled == true)
    {
      vectorMoveMatrixSeq1();
    }

    //Exercise a different series of move steps to see mechanism
    if (gVectorSeq2Enabled == true)
    {
      vectorMoveMatrixSeq2();
    }
  }

  //Run the startup sequence only once
  if (gStartupOneShot == false)
  {
    gStartupOneShot = true;
    startup();
  }

  //Give a little time back
  delay(GIVE_BACK_TIME);
}


//Turn on servo tracking
void enableTracking()
{
  //Set global variables so other parts of program knows motors are ready to run
  gRunning = true;

  //Attach to the servo motors
  gServoTwist.attach(O_TWIST_SERVO_PIN);
  gServoTilt.attach(O_TILT_SERVO_PIN);

  //Turn on green LED and turn off red LED
  digitalWrite(O_GREEN_LED_PIN, HIGH);
  digitalWrite(O_RED_LED_PIN, LOW);

  //Post results
  Serial.println("system enabled");
}


//Turn off servo tracking
void disableTracking()
{
  gRunning = false;

  //Detach from servo motors
  gServoTwist.detach();
  gServoTilt.detach();

  //Clean up move command and move in-process (IP) variables
  gServoTwistPositionCommand = gServoTwist.read();
  gServoTwistMoveIP = false;

  //Clean up move command and move in-process (IP) variables
  gServoTiltPositionCommand = gServoTilt.read();
  gServoTiltMoveIP = false;

  //Turn on red LED, turn off green LED
  digitalWrite(O_RED_LED_PIN, HIGH);
  digitalWrite(O_GREEN_LED_PIN, LOW);

  //Post results
  Serial.println("system disabled");
}


//track to light based on photosensor values
void trackToLightSensors()
{
  float fTop;
  float fBottom;
  float fLeft;
  float fRight;

  int iTwistMoveCommand;
  int iTiltMoveCommand;

  int iMoveAmount;

  //Initialize
  //The variable below determines how many degrees of potential motion for both servos
  //per scan of the program. This number in combination with the global constant
  //named 'GIVE_BACK_TIME' determine how aggressive the moves will be.
  iMoveAmount = 5;

  //Get current servo positions
  iTwistMoveCommand = gServoTwist.read();
  iTiltMoveCommand = gServoTilt.read();

  //Get averages
  fTop = averageTopTwoSensors();
  fBottom = averageBottomTwoSensors();
  fLeft = averageLeftTwoSensors();
  fRight = averageRightTwoSensors();

  //Calculate twist move
  if (fLeft > fRight)
  {
    //Move positive
    iTwistMoveCommand += iMoveAmount;

  }
  else if (fRight > fLeft)
  {
    //Move negative
    iTwistMoveCommand -= iMoveAmount;

  }
  else
  {
    //same. don't move
    
  }

  //Calculate tilt move
  if (fTop > fBottom)
  {
    //Move positive
    iTiltMoveCommand += iMoveAmount;

  }
  else if (fBottom > fTop)
  {
    //Move negative
    iTiltMoveCommand -= iMoveAmount;

  }
  else
  {
    //same. don't move
    
  }

  //Bounds check twist servo move command
  if (iTwistMoveCommand < 0)
  {
    iTwistMoveCommand = 0;
  }

  if (iTwistMoveCommand > 179)
  {
    iTwistMoveCommand = 179;
  }

  //Bounds check tilt servo move command
  if (iTiltMoveCommand < 45)
  {
    iTiltMoveCommand = 45;
  }

  if (iTiltMoveCommand > 135)
  {
    iTiltMoveCommand = 135;
  }
  
  //Perform moves
  gServoTwist.write(iTwistMoveCommand);
  gServoTilt.write(iTiltMoveCommand);

  //Post results
  if (gVerboseDiagMode == true)
  {
    Serial.println("tl, tr, bl, br, top avg, bottom avg, left avg, right avg, twist move, tilt move: ");
    Serial.print(gLDR1);
    Serial.print(", ");
    Serial.print(gLDR2);
    Serial.print(", ");
    Serial.print(gLDR3);
    Serial.print(", ");
    Serial.print(gLDR4);
    Serial.print(", ");
    Serial.print(fTop);
    Serial.print(", ");
    Serial.print(fBottom);
    Serial.print(", ");
    Serial.print(fLeft);
    Serial.print(", ");
    Serial.print(fRight);
    Serial.print(", ");
    Serial.print(iTwistMoveCommand);
    Serial.print(", ");
    Serial.println(iTiltMoveCommand);
    Serial.println("-----");
  }
  
}


//read photoresistor values into global variables
void readPhotoResistors()
{
  //Values come in scaled 0-1024
  gLDR1 = analogRead(I_LDR1_PIN);
  gLDR2 = analogRead(I_LDR2_PIN);
  gLDR3 = analogRead(I_LDR3_PIN);
  gLDR4 = analogRead(I_LDR4_PIN);
}


//Read and scale value from temperature probe
void readTemperatureProbe()
{
  int iSensorVal;
  float fVoltage;

  //read
  iSensorVal = analogRead(I_TEMPERATURE_PIN);
  fVoltage = (iSensorVal/1024.0) * 5.0;
  
  //Convert voltage to temperature in deg C
  gTemperature = (fVoltage - 0.5) * 100;
}


//When the servos are commanded to a position they move at a fast speed.
//Too fast will potentially affect the mechanical structure that holds and moves
//the solar panel and light sensor platform. This routine takes a "move command"
//and makes small incremental moves until the servo is at that desired position.
//This routine is for the base mounted twisting servo motor
void smoothMoveTwist()
{
  int iCurrentPos;
  int iMoveAmountPerScan;
  int iNewMoveCommand;

  //Set move amount per scan in degrees.
  //Combination of this variable and global const 'GIVE_BACK_TIME' determine overall move speed
  iMoveAmountPerScan = 1;

  //Determine current position
  iCurrentPos = gServoTwist.read();

  //Are we at position?
  if (iCurrentPos == gServoTwistPositionCommand)
  {
    gServoTwistMoveIP = false;
    return;
  }
  else
  {
    gServoTwistMoveIP = true;
  }

  //Start off where we are currently at
  iNewMoveCommand = iCurrentPos;
  
  //Determine move amount
  if (iCurrentPos < gServoTwistPositionCommand)
  {
    //Add
    iNewMoveCommand = iNewMoveCommand + iMoveAmountPerScan;
  }
  else
  {
    //Subtract
    iNewMoveCommand = iNewMoveCommand - iMoveAmountPerScan;
  }

  //Clamp if needed
  if (iNewMoveCommand < 0)
  {
    iNewMoveCommand = 0;
  }

  if (iNewMoveCommand > 179)
  {
    iNewMoveCommand = 179;
  }

  //Move
  gServoTwist.write(iNewMoveCommand);

  //Post results
  if (gVerboseDiagMode == true)
  {
    //todo:
    Serial.print("Twist servo move (this move, total):");
    Serial.print(iNewMoveCommand);
    Serial.print(", ");
    Serial.println(gServoTwistPositionCommand);
  }
}


//When the servos are commanded to a position they move at a fast speed.
//Too fast will potentially affect the mechanical structure that holds and moves
//the solar panel and light sensor platform. This routine takes a "move command"
//and makes small incremental moves until the servo is at that desired position.
//This routine is for the bracket mounted tilting servo motor
void smoothMoveTilt()
{
  int iCurrentPos;
  int iMoveAmountPerScan;
  int iNewMoveCommand;

  //Set move amount per scan in degrees.
  //Combination of this variable and global const 'GIVE_BACK_TIME' determine overall move speed
  iMoveAmountPerScan = 1;

  //Determine current position
  iCurrentPos = gServoTilt.read();

  //Are we at position?
  if (iCurrentPos == gServoTiltPositionCommand)
  {
    gServoTiltMoveIP = false;
    return;
  }
  else
  {
    gServoTiltMoveIP = true;
  }

  //Start off where we are currently at
  iNewMoveCommand = iCurrentPos;
  
  //Determine move amount
  if (iCurrentPos < gServoTiltPositionCommand)
  {
    //Add
    iNewMoveCommand = iNewMoveCommand + iMoveAmountPerScan;
  }
  else
  {
    //Subtract
    iNewMoveCommand = iNewMoveCommand - iMoveAmountPerScan;
  }

  //Clamp if needed
  if (iNewMoveCommand < 0)
  {
    iNewMoveCommand = 0;
  }

  if (iNewMoveCommand > 179)
  {
    iNewMoveCommand = 179;
  }

  //Move
  gServoTilt.write(iNewMoveCommand);

  //Post results
  if (gVerboseDiagMode == true)
  {
    //todo:
    Serial.print("Tilt servo move (this move, total):");
    Serial.print(iNewMoveCommand);
    Serial.print(", ");
    Serial.println(gServoTiltPositionCommand);
  }
}


//Take the mathematical average of the two LDR at top of panel
float averageTopTwoSensors()
{
  float fAvg;

  //Math
  fAvg = (gLDR1 + gLDR2) / 2.0;

  return fAvg;
}


//Take the mathematical average of the two LDR at bottom of panel
float averageBottomTwoSensors()
{
  float fAvg;

  //Math
  fAvg = (gLDR3 + gLDR4) / 2.0;

  return fAvg;
}


//Take the mathematical average of the two LDR on left of panel
float averageLeftTwoSensors()
{
  float fAvg;

  //Math
  fAvg = (gLDR1 + gLDR3) / 2.0;

  return fAvg;
}


//Take the mathematical average of the two LDR on right of panel
float averageRightTwoSensors()
{
  float fAvg;

  //Math
  fAvg = (gLDR2 + gLDR4) / 2.0;

  return fAvg;
}


//Process received messages from the serial port interface
//Input parameter iControlCode is the value received from the serial port to be processed
//First two digits are the control command, remaining three are the value to process
void processSerialMessage(int iControlCode)
{
  int iControlCommand;
  int iControlValue;
  
  //Calculate command and value
  iControlCommand = iControlCode / 1000;
  iControlValue = iControlCode % 1000;

  //Report command and value
  Serial.print("control code: ");
  Serial.println(iControlCode);
  
  Serial.print("control command: ");
  Serial.println(iControlCommand);
  
  Serial.print("control value: ");
  Serial.println(iControlValue);

  //Misc command category
  if (iControlCommand == 10)
  {
    if (iControlValue == 0)
    {
      gVerboseDiagMode = true;
      digitalWrite(O_BLUE_LED_PIN, HIGH);
      Serial.println("diagnostics mode started");
    }
    else if (iControlValue == 1)
    {
      gVerboseDiagMode = false;
      digitalWrite(O_BLUE_LED_PIN, LOW);
      Serial.println("diagnostics mode stopped");
    }
    else if (iControlValue == 2)
    {
      reportProductInfo();
    }
    else if (iControlValue == 3)
    {
      //Red LED on
      digitalWrite(O_RED_LED_PIN, HIGH);
      Serial.println("red led on");
    }
    else if (iControlValue == 4)
    {
      //Red LED off
      digitalWrite(O_RED_LED_PIN, LOW);
      Serial.println("red led off");
    }
    else if (iControlValue == 5)
    {
      //Green LED on
      digitalWrite(O_GREEN_LED_PIN, HIGH);
      Serial.println("green led on");
    }
    else if (iControlValue == 6)
    {
      //Green LED off
      digitalWrite(O_GREEN_LED_PIN, LOW);
      Serial.println("green led of");
    }
    else if (iControlValue == 7)
    {
      //Blue LED on
      digitalWrite(O_BLUE_LED_PIN, HIGH);
      Serial.println("blue led on");
    }
    else if (iControlValue == 8)
    {
      //Blue LED off
      digitalWrite(O_BLUE_LED_PIN, LOW);
      Serial.println("blue led off");
    }
    else if (iControlValue == 9)
    {
      //Display LDR1 value
      Serial.print("LDR1 value: ");
      Serial.println(gLDR1);
    }
    else if (iControlValue == 10)
    {
      //Display LDR2 value
      Serial.print("LDR2 value: ");
      Serial.println(gLDR2);
    }
    else if (iControlValue == 11)
    {
      //Display LDR3 value
      Serial.print("LDR3 value: ");
      Serial.println(gLDR3);
    }
    else if (iControlValue == 12)
    {
      //Display LDR4 value
      Serial.print("LDR4 value: ");
      Serial.println(gLDR4);
    }
    else if (iControlValue == 13)
    {
      //Turn on tracking mode
      enableTracking();
    }
    else if (iControlValue == 14)
    {
      //Turn off tracking mode
      disableTracking();
    }
    else if (iControlValue == 15)
    {
      gVectorStep = -1;
      gVectorSeq1Enabled = true;
      gVectorSeq2Enabled = false;
      Serial.println("Vector Seq1 enabled");
    }
    else if (iControlValue == 16)
    {
      gVectorSeq1Enabled = false;
      Serial.println("Vector Seq1 disabled");
    }
    else if (iControlValue == 17)
    {
      gVectorStep = -1;
      gVectorSeq1Enabled = false;
      gVectorSeq2Enabled = true;
      Serial.println("Vector Seq2 enabled");
    }
    else if (iControlValue == 18)
    {
      gVectorSeq2Enabled = false;
      Serial.println("Vector Seq2 disabled");
    }
    else if (iControlValue == 19)
    {
      if (gRunning == true && gServoTwistMoveIP == false && gServoTiltMoveIP == false)
      {
        gServoTwistPositionCommand = 90;
        gServoTiltPositionCommand = 90;
        Serial.println("twist and tilt servos commanded to 90 degrees");
      }
    }
    else if (iControlValue == 20)
    {
      Serial.print("Temperature probe (degc): ");
      Serial.println(gTemperature);
    }
    else if (iControlValue == 21)
    {
      if (gRunning == true)
      {
      gVectorSeq1Enabled = false;
      gVectorSeq2Enabled = false;
      gTrackToLightEnabled = true;
      Serial.println("Track to light source enabled");
      }
    }
    else if (iControlValue == 22)
    {
      gTrackToLightEnabled = false;
      Serial.println("Track to light source disabled");
    }
    else
    {
      Serial.print("invalid control value: ");
      Serial.println(iControlValue);
    }
  }

  //Servo1 (twist) command category
  if (iControlCommand == 11)
  {
    if (iControlValue >=0 && iControlValue <= 179)
    {
      //Move servo1 to position
      if (gRunning == true && gServoTwistMoveIP == false)
      {
        gServoTwistPositionCommand = iControlValue;
        gServoTwistMoveIP = true;

        Serial.print("Move twist servo command: ");
        Serial.println(gServoTwistPositionCommand);
      }
    }
    else
    {
      Serial.print("invalid control value: ");
      Serial.println(iControlValue);
    }
  }

    //Servo2 (tilt) command category
  if (iControlCommand == 12)
  {
    if (iControlValue >=0 && iControlValue <= 179)
    {
      //Move servo2 to position
      //Move servo1 to position
      if (gRunning == true && gServoTiltMoveIP == false)
      {
        gServoTiltPositionCommand = iControlValue;
        gServoTiltMoveIP = true;
        
        Serial.print("Move tilt servo command: ");
        Serial.println(gServoTiltPositionCommand);
      }
    }
    else
    {
      Serial.print("invalid control value: ");
      Serial.println(iControlValue);
    }
  }

  //End of request string
  Serial.println("-----");
}


//Exercise move limits of both servos in parallel
void vectorMoveMatrixSeq1()
{
  //Advance step when moves complete
  if (gServoTwistMoveIP == false && gServoTiltMoveIP == false)
  {
    //Advance step and execute move commands
    gVectorStep++;

    if (gVectorStep > 3)
    {
      gVectorStep = 0;
    }
  }
  else
  {
    //Wait for moves to complete
    return;
  }

  if (gVectorStep == 0)
  { //90, 90
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 1)
  { //45, 45
    gServoTwistPositionCommand = 45;
    gServoTiltPositionCommand = 45;
  }
  else if(gVectorStep == 2)
  { //90, 90
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 3)
  {
    //135, 135
    gServoTwistPositionCommand = 135;
    gServoTiltPositionCommand = 135;
  }
}


//Exercise move limits of both servos in parallel
void vectorMoveMatrixSeq2()
{
  //Advance step when moves complete
  if (gServoTwistMoveIP == false && gServoTiltMoveIP == false)
  {
    //Advance step and execute move commands
    gVectorStep++;

    if (gVectorStep > 7)
    {
      gVectorStep = 0;
    }
  }
  else
  {
    //Wait for moves to complete
    return;
  }

  if (gVectorStep == 0)
  {
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 1)
  {
    gServoTwistPositionCommand = 45;
    gServoTiltPositionCommand = 45;
  }
  else if(gVectorStep == 2)
  {
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 3)
  {
    gServoTwistPositionCommand = 0;
    gServoTiltPositionCommand = 30;
  }
  else if(gVectorStep == 4)
  {
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 5)
  {
    gServoTwistPositionCommand = 135;
    gServoTiltPositionCommand = 135;
  }
  else if(gVectorStep == 6)
  {
    gServoTwistPositionCommand = 90;
    gServoTiltPositionCommand = 90;
  }
  else if(gVectorStep == 7)
  {
    gServoTwistPositionCommand = 179;
    gServoTiltPositionCommand = 30;
  }

  //Post results
  if (gVerboseDiagMode == true)
  {
    Serial.print("vector seq 2 step, twist cmd, tilt cmd (");
    Serial.print(gVectorStep);
    Serial.print(", ");
    Serial.print(gServoTwistPositionCommand);
    Serial.print(", ");
    Serial.print(gServoTiltPositionCommand);
    Serial.println(")");
  }
}


//Run a sequence of steps to self-test functions, enable servos and enter light tracking mode
void startup()
{
  int iDelay;

  //Initialize
  iDelay = 500;

  //Display app info
  reportProductInfo();
  delay(iDelay);

  //Turn on red LED
  processSerialMessage(10003);
  delay(iDelay);

  //Turn off red LED, turn on green LED
  processSerialMessage(10004);
  processSerialMessage(10005);
  delay(iDelay);

  //Turn off green LED, turn on blue LED
  processSerialMessage(10006);
  processSerialMessage(10007);
  delay(iDelay);

  //Turn off blue LED, display photo-resistor values (all four)
  processSerialMessage(10008);
  processSerialMessage(10009);
  processSerialMessage(10010);
  processSerialMessage(10011);
  processSerialMessage(10012);
  delay(iDelay);

  //Enable servos
  enableTracking();
  delay(iDelay);

  //Move servos to home position
  processSerialMessage(10019);
  delay(iDelay);

  //Enable tracking to light levels
  gTrackToLightEnabled = true;

  //Say good-bye
  Serial.println("startup sequence completed");

}


//Send product information to the serial port
void reportProductInfo()
{
  //Report product and other information to serial port
  Serial.println("q1 version 1.0");
  Serial.println("tucson, arizona usa");
  Serial.println("april 2017");
  Serial.print("checksum ");
  Serial.println("5218-C8E7-1F60-3F0F-6F10-6732-3368-3EB2");
}
