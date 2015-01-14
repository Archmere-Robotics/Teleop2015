#pragma once
//@ Archmere-Robotics/libHolonomics repo on github
#include "JoystickDriver.c"
//include guard
#ifndef _TELEOP2014_H
#define _TELEOP2014_H

//say what functions to use
#define USING_moveConveyor
#define USING_setLiftPos
#define USING_activateServos
#define USING_setDoorPos
#define USING_setDump
#define USING_setRightHook
#define DEBUG_MOTOR_VALUES
#include "libHolonomics.c"

//Fine Control Constant (speed to move motors from tophat)
#define FCC 25


const int joyTol=10;//tolerance for joystick(s): if the |joystick value|<tolerance, then ignore joystick. This is to prevent noise.
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
void updateLight();
/**
 * Main loop. Should not be called ever.
 */
task main();

#endif
