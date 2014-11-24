#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          heartbeat,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          leftHook,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightHook,     tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     liftRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeftMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     wheelB,        tmotorTetrix, PIDControl, driveLeft)
#pragma config(Motor,  mtr_S1_C2_2,     wheelA,        tmotorTetrix, PIDControl, driveRight)
#pragma config(Motor,  mtr_S1_C3_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     wheelC,        tmotorTetrix, PIDControl, driveRight)
#pragma config(Motor,  mtr_S2_C2_2,     wheelD,        tmotorTetrix, PIDControl, driveLeft)
#pragma config(Servo,  srvo_S2_C1_1,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    doorServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma once
//@ Archmere-Robotics/libHolonomics repo on github
#include "JoystickDriver.c"
#include "libHolonomics.c"
#ifndef _TELEOP2014_H
#define _TELEOP2014_H
const int joyTol=10;//tolerance for joystick(s): if the |joystick value|<tolerance, then ignore joystick. This is to prevent noise.
int m1v, m2v, m3v, m4v;
int lightVal = 0;
/**
 * Initializes the robot. Should only be called once
 */
void init();
/**
 * Reads the joystick values, and recalculates the motor values.
 */
void drive();
/**
 * Updates the servo values and resets their positions. Should be called once per main loop cycle.
 */
void udServos();
/**
 * Updates the heartbeat light. Should be called once per main loop cycle.
 */
void udLight();
/**
 * Main loop. Should not be called ever.
 */
task main();

#endif
