#pragma config(Motor,  port1,           leftMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
motor[leftMotor] = 31;
motor[rightMotor] = 31;
wait1Msec(3000)
}
