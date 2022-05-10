// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution
// to the top shield
Adafruit_StepperMotor *myStepperY = AFMStop.getStepper(200, 2);
Adafruit_StepperMotor *myStepperX = AFMStop.getStepper(200, 1);

// wrappers for the first motor
void forwardstepY() {  
  myStepperY->onestep(FORWARD, SINGLE);
}
void backwardstepY() {  
  myStepperY->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor
void forwardstepX() {  
  myStepperX->onestep(FORWARD, DOUBLE);
}
void backwardstepX() {  
  myStepperX->onestep(BACKWARD, DOUBLE);
}

// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepperY(forwardstepY, backwardstepY);
AccelStepper stepperX(forwardstepX, backwardstepX);

unsigned long ymin = 700;
unsigned long xmin = 200;
unsigned long ymax = 1700; // Max 1750
unsigned long xmax = 2000; //absolute Max 2100
unsigned long yinc = 50;
unsigned long xinc = 50;

void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
   
  stepperY.setMaxSpeed(200.0);
  stepperY.setAcceleration(100.0);
  //stepperY.moveTo(500);
    
  stepperX.setMaxSpeed(200.0);
  stepperX.setAcceleration(100.0);
  //stepperX.moveTo(500);

  stepperY.move(-5000);
  while (digitalRead(6) == 0 && digitalRead(7) == 0){ // Full speed up to 300
    stepperY.run();
   }
  stepperY.stop(); // Stop as fast as possible: sets new target
  
  stepperX.move(-5000);
  while (digitalRead(10) == 0){ // Full speed up to 300
    stepperX.run();
  }
  stepperX.stop();
  
  stepperY.setCurrentPosition(0);
  stepperX.setCurrentPosition(0);
  
  stepperY.runToNewPosition(ymin);
  stepperX.runToNewPosition(xmin);

  Serial.begin(9600);
}

void loop()
{
  //unsigned long currentMillis = millis();
  
  while( stepperX.currentPosition() < xmax ) {
    
    while( stepperY.currentPosition() < ymax ) {
      // send x,y
      Serial.print(stepperX.currentPosition());
      Serial.print(" ,");
      Serial.print(stepperY.currentPosition());
      Serial.print(" ,");
      // delay ms for reading
      delay(500);
      float sensorValue = analogRead(A1);
      float ArduinoVoltage = ((sensorValue +5.56) / 1027.33);// this was obtained by hooking up a voltmeter to the op-amp and arduino system and 
      //this scaling is a result of both
      float FrontFaceVoltage =((ArduinoVoltage + .01)/.92);//Put this in to make the front face voltage reading the same as what the ardunio out puts
      //float MeterVoltage= ArduinoVoltage * (1023.0 / 5.0);
      //Serial.println(ArduinoVoltage*1000.);
      Serial.print(FrontFaceVoltage*1000.); // multiply by 1000 since the output on the voltmeter is x/1000
      Serial.print(" ,");
      float sensorValue2 = analogRead(A2);
      //Serial.print(sensorValue2);
      //Serial.print(" ,");
      float DiffAmp =((sensorValue2 -511.02)/411.76)*1000;
      Serial.println(DiffAmp);
      
      
      stepperY.runToNewPosition(stepperY.currentPosition() + yinc);
    }
    
    stepperY.runToNewPosition(ymax);
    stepperX.runToNewPosition(stepperX.currentPosition() + xinc);
   
    while( stepperY.currentPosition() > ymin ) {
      // send x,y
      Serial.print(stepperX.currentPosition());
      Serial.print(" ,");
      Serial.print(stepperY.currentPosition());
      Serial.print(" ,");
      // delay ms for reading
      delay(500);
      float sensorValue = analogRead(A1);
      float ArduinoVoltage = ((sensorValue +5.56) / 1027.33);
      float FrontFaceVoltage =((ArduinoVoltage + .01)/.92);//Put this in to make the front face voltage reading the same as what the ardunio out puts
      //float MeterVoltage= ArduinoVoltage * (1023.0 / 5.0);
      //Serial.println(ArduinoVoltage*1000.);
      Serial.print(FrontFaceVoltage*1000.);
      Serial.print(" ,");
      float sensorValue2 = analogRead(A2);
      //Serial.print(sensorValue2);
      //Serial.print(" ,");
      float DiffAmp =((sensorValue2 - 511.02)/411.76)*1000;
      Serial.println(DiffAmp);
      
      stepperY.runToNewPosition(stepperY.currentPosition() - yinc);
    }
    
    stepperY.runToNewPosition(ymin);
    stepperX.runToNewPosition(stepperX.currentPosition() + xinc);
  }
  
  stepperY.runToNewPosition(ymin);
  stepperX.runToNewPosition(xmin);
 
  Serial.println("Finished");
}
