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
#include "TeleOp2015BlockParty.h"
//#include "graphLib.c"
#ifndef _TELEOP2015
#define _TELEOP2015

void init(){
	Stop();//stops the robot.
	setDoorPos(false);
	dooractive=false;
	moveConveyor(false);
	dumpservo_pos=DUMPSERVO_FLAT;
	activateServos();
	return;
}
void drive(){
	getJoystickSettings(joystick);//poll joystick
	if(abs(joystick.joy1_x1) >= joyTol || abs(joystick.joy1_y1) >= joyTol){//determines if the drive joystick is moved. If so, move the robot.{
		//change the joystick values from -128|127 to -100|100.
		int j1x1=joystick.joy1_x1*25/32;
		int j1y1=joystick.joy1_y1*25/32;
		// better motor code. mXv where 0<X<5 is the motor value.
		m1v=j1x1+j1y1;
		m2v=j1y1-j1x1;
		m4v=j1x1-j1y1;
		m3v=-j1y1-j1x1;
		//sends the values to the motor control library.
		addVal(-m1v, -m2v, -m3v, -m4v);
	}
	if(abs(joystick.joy1_x2) >=joyTol){//determines if the rotation joystick is moved.
		addVal(-joystick.joy1_x2, -joystick.joy1_x2, -joystick.joy1_x2, -joystick.joy1_x2);
	}
	//rotates robot with buttons on the back of the controller & sends them to the motor control library.
	if(joy1Btn(8)){addVal(-50,-50,-50,-50);}
	if(joy1Btn(7)){addVal(50,50,50,50);}
	if(joy1Btn(6)){addVal(-18,-18,-18,-18);}
	if(joy1Btn(5)){addVal(18,18,18,18);}

	if(joystick.joy1_TopHat == 0)
		addVal(-25,-25,25,25);

	if(joystick.joy1_TopHat == 2)
		addVal(-25,25,25,-25);

	if(joystick.joy1_TopHat == 4)
		addVal(25,25,-25,-25);

	if(joystick.joy1_TopHat == 6)
		addVal(25,-25,-25,25);
	//tells the motor control library to actually move the robot.
	loadVal();
}
void udServos(){//updates the servos (and conveyor & flag motors).
	//activates/deactivates servos
	if(joy2Btn(1))
		motor[leftHook]=30;
	else if(joy2Btn(2))
		motor[leftHook]=-30;
	else
		motor[leftHook]=0;

	if(joy2Btn(4))
		motor[rightHook]=30;
	else if(joy2Btn(3))
		motor[rightHook]=-30;
	else
		motor[rightHook]=0;

	//move lift
	if(joy2Btn(5))
		setLiftPos(-1,false);
	else if(joy2Btn(6))
		setLiftPos(1,true);
	else
		setLiftPos(0,true);
	//activate conveyor <=
	if(joy2Btn(7)){
		moveConveyor(CONVEYOR_UP);
		}else if(joy2Btn(8)){
		moveConveyor(CONVEYOR_DOWN);
		}else{
		moveConveyor(CONVEYOR_STOP);
	}
	if(joystick.joy2_TopHat==0){
		setDoorPos(true);
	}else if(joystick.joy2_TopHat==4)
		setDoorPos(false);
	if(abs(joystick.joy2_x1)>joyTol) {
		setDump(joystick.joy2_x1/-6);
		}else{
		setDump(-10);
	}
	if(abs(joystick.joy2_y2)>joyTol){
		moveConveyor(joystick.joy2_y2);
	}

	updateServos();
}
void udLight(){
	lightVal+=1;
	lightVal%=100;
	motor[heartbeat]=lightVal;
}
task main() {
	init();
	waitForStart();
	dooractive=true;
	while(true){
		udServos();
		drive();
		udLight();
	}
}
#endif
