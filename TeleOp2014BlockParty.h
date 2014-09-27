#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Drivetrain,     sensorI2CMuxController)
#pragma config(Sensor, S4,     Auxillary,      sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     wheelA,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     wheelB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C2_1,     wheelC,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     wheelD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_1,     winch,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     hookLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     conveyorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     flagLift,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_1,    basket,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    conveyorLift,         tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo12,              tServoNone)
//@ Archmere-Robotics/libHolonomics repo on github
#include "libHolonimics.c"
//#include "graphLib.c"
const int hookOff=255;
const int hookOn=60;
const int joyTol=10;//tolerance for joystick(s): if the |joystick value|<tolerance, then ignore joystick. This is to prevent noise.
int m1v, m2v, m3v, m4v, j1x1, j1x2, j1y1, j1y2, j2x1, j2y1, j2x2, j2y2=0;
int lightVal=0;//light value
int dl=1;//light change (how much the light changes every cycle
// const bool graphing=true;
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
