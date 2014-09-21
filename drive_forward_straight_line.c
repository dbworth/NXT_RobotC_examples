// drive_forward_straight_line.c
// RobotC for Mindstorms NXT
//
// Drive forward in a straight line
// [David Butterworth, 2012]
//
// This program will loop forever.
// Both motors are driven at the same speed,
// but if one motor is rotating faster than
// the other, the opposite motor will be
// driven faster to compensate.
//
// The result is that the robot drives
// forward with a slight wiggling motion,
// but the resulting motion is much straighter
// than without using the encoders.

#define MOTOR_PORT_LEFT  motorC
#define MOTOR_PORT_RIGHT motorA

// Declare variables
int encoder_right = 0;
int encoder_left  = 0;

// TaskDriveForward
// Makes the robot drive forward in a straight line
void TaskDriveForward()
{
    // Start by driving both motors at same speed
    // A static integer is initialised only the first
    // time this code is executed, then keeps its
    // value until changed.
    static int state = 0;

    switch (state)
    {
        case 0:  // going straight
            motor[MOTOR_PORT_LEFT]= 15;
            motor[MOTOR_PORT_RIGHT]= 15;
            nxtDisplayString(4, "FWD");
            break;

        case 1:   // drifting to the right
            motor[MOTOR_PORT_LEFT]= 15;
            motor[MOTOR_PORT_RIGHT]= 20;
            nxtDisplayString(4, "LEFT");
            break;

        case 2:     // drifting to the left
            motor[MOTOR_PORT_LEFT]= 20;
            motor[MOTOR_PORT_RIGHT]= 15;
            nxtDisplayString(4, "RIGHT");
            break;
    } // end switch

    // Read Motor Encoders and chose next movement
    if (nMotorEncoder[MOTOR_PORT_LEFT] == nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 0; }  // Go straight
    else if (nMotorEncoder[MOTOR_PORT_LEFT] > nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 1; } // Turn left
    else if (nMotorEncoder[MOTOR_PORT_LEFT] < nMotorEncoder[MOTOR_PORT_RIGHT])  { state = 2; } // Turn right
}


task main()
{
    // Reset Motor Encoders because they don't start at zero
    nMotorEncoder[MOTOR_PORT_LEFT] = 0;
    nMotorEncoder[MOTOR_PORT_RIGHT] = 0;

    // Loop forever
    while (true)
    {
        // Read wheel encoders
        // elapsed count since start of program
        // for integer type, will count 0 to 32,767 fwd, or 0 to -32765 in reverse
        //
        // This is not used by TaskDriveForward, but is used
        // to display a total rotation count for each motor.
        int encoder_left  = nMotorEncoder[MOTOR_PORT_LEFT];
        int encoder_right  = nMotorEncoder[MOTOR_PORT_RIGHT];

        // Execute this function once and return
        TaskDriveForward();

        // Update Display
        //
        // Total rotation count
        nxtDisplayString(1, "L rot cnt: %i", encoder_left);
        nxtDisplayString(2, "R rot cnt: %i", encoder_right);

        // The current driving motion FWD/LEFT/RIGHT is display on line 4

        wait1Msec(40);
        eraseDisplay();
    }
}
