#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     IRLeft,         sensorI2CCustom)
#pragma config(Motor,  motorA,          heartbeat,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          leftHook,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightHook,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     wheelB,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     wheelA,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     liftMotor,     tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S2_C2_1,     wheelC,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     wheelD,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    doorServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    IRServo,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//KING OF PREPROCESSING!!!!
//include stuff only once
#pragma once
#include "TeleOp2015BlockParty.h"
#ifndef _TELEOP2015
#define _TELEOP2015

void init(){
	Stop();//stop all of the robot's motors
	setDoorPos(false);
	moveConveyor(false);
	setDump(0);//flatten the PVC thing
	activateServos();
	updateServos();//magic
	//reset motor encoders
	nMotorEncoder[liftMotor]=0;
	nMotorEncoder[wheelA]=0;
	nMotorEncoder[wheelB]=0;
	nMotorEncoder[wheelC]=0;
	nMotorEncoder[wheelD]=0;
	return;
}
void drive(){
	getJoystickSettings(joystick);//poll joystick
	if(abs(joystick.joy1_x1) >= joyTol || abs(joystick.joy1_y1) >= joyTol){//determines if the drive joystick is moved. If so, move the robot.{
		//change the joystick values from -128|127 to -100|100.
		float j1x1=joystick.joy1_x1*25.0/32.0;
		float j1y1=joystick.joy1_y1*25.0/32.0;
		// better motor code. mXv is the motor value.
		float m1v=j1x1+j1y1;
		float m2v=j1y1-j1x1;
		float m3v=-j1y1-j1x1;
		float m4v=j1x1-j1y1;
		//sends the values to the motor control library.
		addVal(-m1v, -m2v, -m3v, -m4v);
	}
	//determine whether the rotation joystick has been moved.
	if(abs(joystick.joy1_x2) >=joyTol)
		addVal(-joystick.joy1_x2, -joystick.joy1_x2, -joystick.joy1_x2, -joystick.joy1_x2);
		
	//rotate robot with buttons on the back of the controller
	if(joy1Btn(8))
		addVal(-50,-50,-50,-50);
	if(joy1Btn(7))
		addVal(50,50,50,50);
	//no idea why 18, but it works
	if(joy1Btn(6))
		addVal(-18,-18,-18,-18);
	if(joy1Btn(5))
		addVal(18,18,18,18);
	//move the robot in a straight line with the tophat
	switch(joystick.joy1_TopHat){
		case 0://up
			addVal(-25,-25,25,25);
			break;
		case 2://right
			addVal(-25,25,25,-25);
			break;
		case 4://down
			addVal(25,25,-25,-25);
			break;
		case 6://left
			addVal(25,-25,-25,25);
			break;
		//TODO: add functionality for non-cardinal direction tophat states
	}
	//tells the motor control library to actually move the robot.
	loadVal();
}
//update the servos & non-drivetrain motors
void udServos(){
	//control the hooks on the sides of the robot
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
		setLiftPos(-1,false);//down
	else if(joy2Btn(6))
		setLiftPos(1,true);//up
	else
		setLiftPos(0,true);//stop if no button is pressed
	
	//control conveyor
	if(joy2Btn(7))
		moveConveyor(CONVEYOR_UP);//intake
	else if(joy2Btn(8))
		moveConveyor(CONVEYOR_DOWN);//outtake
	else
		moveConveyor(CONVEYOR_STOP);
	
	//move the door infront of the conveyor belt
	if(joystick.joy2_TopHat==0){
		setDoorPos(true);
	}else if(joystick.joy2_TopHat==4)
		setDoorPos(false);
	
	//tilt the PVC carrier thing
	if(abs(joystick.joy2_x1)>joyTol)
		setDump(joystick.joy2_x1/-6);
	else
		setDump(-10);
	
	//move the conveyor also with the joystick
	if(abs(joystick.joy2_y2)>joyTol)
		moveConveyor(joystick.joy2_y2);
	
	//do magical things with the MC library
	updateServos();
}
//update the heartbeat sensor value (motor A)
void updateLight(){
	//loops from -100 to 100
	motor[heartbeat]=(lightVal=((++lightVal)%200))-100;
}
task main() {
	init();
	waitForStart();
	doorActive=true;
	while(true){
		udServos();
		drive();
		updateLight();
	}
}
#endif
