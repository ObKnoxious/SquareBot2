#pragma config(Sensor, dgtl1,  FRLSwerveEnc,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  RRLSwerveEnc,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  RRRSwerveEnc,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  FRRSwerveEnc,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, Sonar,          sensorSONAR_cm)
#pragma config(Motor,  port2,           FRLSwerve,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3,           FRRSwerve,     tmotorVex269, openLoop)
#pragma config(Motor,  port4,           RRLSwerve,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port5,           RRRSwerve,     tmotorVex269, openLoop)
#pragma config(Motor,  port6,           FRLDrive,      tmotorVex269, openLoop)
#pragma config(Motor,  port7,           FRRDrive,      tmotorVex269, openLoop)
#pragma config(Motor,  port8,           RRLDrive,      tmotorVex269, openLoop)
#pragma config(Motor,  port9,           RRRDrive,      tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task swerveWheelControl();

void drive();

float turnMultiplier = 6.0;

void setDrive(float power)
{
	motor[FRLDrive] = power;
	motor[FRRDrive] = power;
	motor[RRLDrive] = power;
	motor[RRRDrive] = power;
}

void resetSwerveEncoders()
{
	SensorValue[FRLSwerveEnc] = 0;
	SensorValue[FRRSwerveEnc] = 0;
	SensorValue[RRLSwerveEnc] = 0;
	SensorValue[RRRSwerveEnc] = 0;
}

int deadZone = 10;

float getJoystickAngle()
{
	int x = vexRT[Ch1];
	int y = vexRT[Ch2];

	if (abs(x) < deadZone || abs(y) < deadZone) {
		return 0;
	}

	if (y < 0) {
		// angle reversed, flip direction
		x = -x;
		y = -y;
	}

	int turn = radiansToDegrees(atan2(y, x));

	if (x < 0) {
		// turning left
		return 90 - turn + 180;
	} else {
		return 90 - turn;
	}
}

float getJoystickMagnitude()
{
	int x = vexRT[Ch1];
	int y = vexRT[Ch2];

	int direction = y < 0 ? -1 : 1;

	//return direction * sqrt((x * x) + (y * y));
	return vexRT[Ch3];
}

void wheelTurnToAngle(tMotor corner, tSensors sensor, float angle)
{
	motor[corner] = 0;
	float degreesRemaining = angle - SensorValue[sensor];
	int power = degreesRemaining / turnMultiplier;

	motor[corner] = power;
}

void wheelsTurnToAngle()
{
	float angle = getJoystickAngle() * turnMultiplier;

	wheelTurnToAngle(FRLSwerve, FRLSwerveEnc, angle);
	wheelTurnToAngle(FRRSwerve, FRRSwerveEnc, angle);
	wheelTurnToAngle(RRLSwerve, RRLSwerveEnc, angle);
	wheelTurnToAngle(RRRSwerve, RRRSwerveEnc, angle);
}

task main()
{
	resetSwerveEncoders();

	StartTask(swerveWheelControl);

	//StartTask(drive);

	while (true) {
		drive();
	}
}

task swerveWheelControl()
{
	while(true)
	{
		wheelsTurnToAngle();
	}
}

void drive()
{
	while(true)
	{
		setDrive(getJoystickMagnitude());
	}
}
