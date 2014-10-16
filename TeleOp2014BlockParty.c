//overwrite other motor config setups.
#define _MOTORPRAGMAS
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
#pragma once
#include "TeleOp2014BlockParty.h"
//#include "C:\Documents and Settings\student\Desktop\RobotC2014\graphLib.c"
#ifndef _TELEOP2015
#define _TELEOP2015

const int hookOff=255;
const int hookOn=60;
const int joyTol=10;//tolerance for joystick(s): if the |joystick value|<tolerance, then ignore joystick. This is to prevent noise.
int m1v, m2v, m3v, m4v, j1x1, j1x2, j1y1, j1y2, j2x1, j2y1, j2x2, j2y2=0;
int lightVal=0;//light value
int dl=1;//light change (how much the light changes every cycle
const bool graphing=true;
void init(){
	servoChangeRate[basket]=0;//stops the basket from moving.
	Stop();//stops the robot.
	activateServos();
	moveConveyor(false);
	setHookPos(hookOff);
	return;
}
void drive(){
	getJoystickSettings(joystick);//poll joystick.
	//update joystick values. these aren't nececary, but they allow shorthand while for the rest of the code.
	j1x1=joystick.joy1_x1; j1x2=joystick.joy1_x2; j1y1=joystick.joy1_y1; j1y2=joystick.joy1_y2;//for driver gamepad.
	j2x1=joystick.joy2_x1; j2x2=joystick.joy2_x2; j2y1=joystick.joy2_y1; j2y2=joystick.joy2_y2;//for auxillary gamepad.
	if(j1x1 >= joyTol || j1y1 >= joyTol || j1x1 <= -joyTol || j1y1 <= -joyTol)//determines if the drive joystick is moved. If so, move the robot.
	{
		//change the joystick values from -128|127 to -100|100.
		j1x1=j1x1*25/32;
		j1y1=j1y1*25/32;
		// better motor code. mXv where 0<X<5 is the motor value.
		m1v=j1x1+j1y1;
		m2v=j1y1-j1x1;
		m4v=j1x1-j1y1;
		m3v=-j1y1-j1x1;
		//sends the values to the motor control library.
		addVal(-m1v, -m2v, -m3v, -m4v);
	}
	if(j1x2 >=joyTol || j1x2 <= -joyTol){//determines if the rotation joystick is moved.
		//send rotation values to the motor control library.
		addVal(j1x2, j1x2, j1x2, j1x2);
	}
	//rotates robot with buttons on the back of the controller & sends them to the motor control library.
	if(joy1Btn(8)){addVal(50,50,50,50);}
	if(joy1Btn(7)){addVal(-50,-50,-50,-50);}
	if(joy1Btn(6)){addVal(18,18,18,18);}
	if(joy1Btn(5)){addVal(-18,-18,-18,-18);}
	//tells the motor control library to actually move the robot.
	loadVal();

	if(joystick.joy1_TopHat == 0){
		addVal(-25,-25,25,25);
	}
	if(joystick.joy1_TopHat == 2){
		addVal(-25,25,25,-25);
	}
	if(joystick.joy1_TopHat == 4){
		addVal(25,25,-25,-25);
	}
	if(joystick.joy1_TopHat == 6){
		addVal(25,-25,-25,25);
	}

}
void udServos(){//updates the servos (and conveyor & flag motors).
	//activates/deactivates servos
	if(joy2Btn(1)){
	moveWinch(-100);
	}
	if(joy2Btn(2)){
	moveWinch(100);
	}
	//TODO: lift hook
	if(joy2Btn(3)){
		setBasketPos(60);
	}else{
	}

	//control flag motor
	if(joy2Btn(4)){
		moveFlag(100);
	}else{
		moveFlag(0);
	}
	//move basket down
	if(joy2Btn(5)){setBasketPos(false);}
	//move basket up
	if(joy2Btn(6)){setBasketPos(true);}
	//activate conveyor <=
	if(joy2Btn(7)){
		motor[conveyorMotor]=-50;
		motor[motorA]=100;
		motor[motorB]=100;
	}
	//activate conveyor =>
	if(joy2Btn(8)){
		motor[conveyorMotor]=50;
		motor[motorA]=-100;
		motor[motorB]=-100;
	}
	//deactivate conveyor
	if((!joy2Btn(7))&&(!joy2Btn(8))){
		motor[conveyorMotor]=0;
		motor[motorA]=0;
		motor[motorB]=0;
	}
	//lower conveyor
	if(joy2Btn(9)){moveConveyor(true);}
	//raise conveyor
	if(joy2Btn(10)){moveConveyor(false);}
	//if(joy2Btn(10)){conveyorActive=false;}
	//
	if(abs(j2y2)>joyTol) {

	}
	if(abs(j2y1)>joyTol) {
		moveConveyor(j2y1);
	}
	//move the hook up or down wih d-pad
	if(joystick.joy2_TopHat == 0){
		liftHook(25);
		}else if(joystick.joy2_TopHat == 4){
		liftHook(-25);
		}else{
		liftHook(0);
	}

	//tighten or loosen the winch
	if(joystick.joy2_TopHat == 2){
		moveWinch(100);
		}else if(joystick.joy2_TopHat == 6){
		moveWinch(-100);
		}else{
		moveWinch(0);
	}//check to see if works
	if(joystick.joy2_TopHat==1){
		setHookPos(hookOn);
	}
	if(joystick.joy2_TopHat==5){
	setHookPos(hookOff);
}

	updateServos();
}
void udLight() {
	lightVal+=dl;
	if(abs(lightVal)>100){
		dl*=-1;
	}
	motor[motorC]=lightVal;
}
task main() {
	init();
	waitForStart();
	while(true){
		udServos();
		drive();
		udLight();
	}
}
#endif
