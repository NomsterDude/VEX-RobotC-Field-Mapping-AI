#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl11, armEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  armIME,         sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           frontRightMotor, tmotorVex393_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port2,           backRightMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeftMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backLeftMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void drive (float inches, int speed = 127, int offset = 0, float wheel_diam = 3.66142) {
	//28.65 * inches = encoder ticks
	int lEncoder = SensorValue[leftEncoder];
	int rEncoder = -SensorValue[rightEncoder];
	int lCurrentDrive = lEncoder;
	int rCurrentDrive = rEncoder;
	float eGoal = (360/(wheel_diam * PI)) * inches;
	while (lEncoder < lCurrentDrive + eGoal - offset && rEncoder < rCurrentDrive + eGoal - offset) {
		if (lEncoder < lCurrentDrive + eGoal - offset) {
			motor[backLeftMotor] = speed;
			motor[frontLeftMotor] = speed;
		}
		if (rEncoder < rCurrentDrive + eGoal - offset) {
			motor[backRightMotor] = speed;
			motor[frontRightMotor] = speed;

		}
		lEncoder = SensorValue[leftEncoder];
		rEncoder = -SensorValue[rightEncoder];
	}
	motor[backLeftMotor] = 0;
	motor[backRightMotor] = 0;
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
}

void turnLeft(float degrees = 90.00, int speed = 127, int offset = 0, float gearRatio = 1, float wheel_diam = 93) {
	float lEncoder = -SensorValue[leftEncoder];
	float rEncoder = -SensorValue[rightEncoder];
	int currentLeft = lEncoder;
	int currentRight = rEncoder;
	//float rotOffset = 4.475;
	float rotOffset = (2 * 152.75 * PI) /
    (wheel_diam * 2) * gearRatio * degrees;
	float leftPosToGet = currentLeft + (rotOffset);
	float rightPosToGet = currentRight + (rotOffset);
	while (lEncoder < leftPosToGet - offset && rEncoder <  rightPosToGet - offset) {
		if (lEncoder < leftPosToGet - offset) {
			motor[frontLeftMotor] = -speed;
			motor[backLeftMotor] = -speed;
		}
		if (rEncoder < rightPosToGet - offset) {
			motor[frontRightMotor] = speed;
			motor[backRightMotor] = speed;
		}
		lEncoder = -SensorValue[leftEncoder];
		rEncoder = -SensorValue[rightEncoder];
	}
	motor[backLeftMotor] = 0;
	motor[backRightMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[frontLeftMotor] = 0;
}

void turnRight(float degrees = 90.00, int speed = 127, int offset = 0, float gearRatio = 1, float wheel_diam = 93) {
	float lEncoder = SensorValue[leftEncoder];
	float rEncoder = SensorValue[rightEncoder];
	int currentLeft = lEncoder;
	int currentRight = rEncoder;
	//float rotOffset = 4.475;
	float rotOffset = (2 * 140 * PI) /
    (wheel_diam * 2) * gearRatio * degrees;
	float leftPosToGet = currentLeft + (rotOffset);
	float rightPosToGet = currentRight + (rotOffset);
	while (lEncoder < leftPosToGet - offset && rEncoder <  rightPosToGet - offset) {
		if (lEncoder < leftPosToGet - offset) {
			motor[frontLeftMotor] = speed;
			motor[backLeftMotor] = speed;
		}
		if (rEncoder < rightPosToGet - offset) {
			motor[frontRightMotor] = -speed;
			motor[backRightMotor] = -speed;
		}
		lEncoder = SensorValue[leftEncoder];
		rEncoder = SensorValue[rightEncoder];
	}
	motor[backLeftMotor] = 0;
	motor[backRightMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[frontLeftMotor] = 0;
}

void straighten(int speed = 63) {
	int lEncoder = SensorValue[leftEncoder];
	int rEncoder = -SensorValue[rightEncoder];
	if (lEncoder < rEncoder) {
		while (lEncoder < rEncoder) {  //turned left too much - run left motors
			motor[backLeftMotor] = speed;
			motor[frontLeftMotor] = speed;
			motor[backRightMotor] = -speed;
			motor[frontRightMotor] = -speed;
			lEncoder = SensorValue[leftEncoder];
			rEncoder = -SensorValue[rightEncoder];
		}
	} else if (lEncoder > rEncoder) {
		while (lEncoder > rEncoder) {  //run right motors
			motor[backRightMotor] = speed;
			motor[frontRightMotor] = speed;
			motor[backLeftMotor] = -speed;
			motor[frontLeftMotor] = -speed;
			lEncoder = SensorValue[leftEncoder];
			rEncoder = -SensorValue[rightEncoder];
		}
	}
}

/*void interpret_array(int *arr, int index) {  //works?  unsure
	switch(arr[index]) {
		case 0:
		drive(24);
		break;

		case 1:
		turnLeft();
		break;

		case 2:
		turnRight();
		break;

		default:
		//nothing
		break;
	}
}*/

task main() {
	/*drive(24);
	turnRight();
	wait1Msec(500);
	straighten();
	straighten();
	straighten();*/

	int instructions[25] = {0, 0, 0, 1, 12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345};

	int commandNum = 0;

	while (instructions[commandNum] == 0 || instructions[commandNum] == 1 || instructions[commandNum] == 2) {
		//do stuff
		switch(instructions[commandNum]) {
			case 0:
				drive(24);
				break;
			case 1:
				turnLeft();
				break;
			case 2:
				turnRight();
				break;
			default:
				//nothing
		}
		commandNum++;
	}
}