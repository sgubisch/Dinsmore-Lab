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

unsigned long ymin = 1100;
unsigned long xmin = 100;
unsigned long ymax = 1700;
unsigned long xmax = 2000; //absolute Max 2100
unsigned long yinc = 50;
unsigned long xinc = 50;

void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
   
  stepperY.setMaxSpeed(200.0);
  stepperY.setAcceleration(100.0);

    
  stepperX.setMaxSpeed(200.0);
  stepperX.setAcceleration(100.0);
  

  Serial.begin(9600);
}

void loop()
{
 stepperY.moveTo(2000);
 stepperY.run();
 stepperX.moveTo(1000);
 stepperX.run();
 Serial.println("Finished");
}
