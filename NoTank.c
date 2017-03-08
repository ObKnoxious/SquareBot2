// Pragma goes here
// Pragma goes here
task main(){

// Left Stick controls both motor's vertical power
	while(1 == 1){
		motor[leftMotor] = vexRT[Ch3];
		motor[rightMotor] = vexRT[Ch3];
	}
	
// Right Stick controls both motor's power at a slower rate
	while(1 == 1){
		motor[leftMotor] = vexRT[Ch2] / 3;
		motor[rightMotor] = vexRT[Ch2] / 3;
}