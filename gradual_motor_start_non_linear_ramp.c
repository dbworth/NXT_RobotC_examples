// gradual_motor_start_non_linear_ramp.c
// RobotC for Mindstorms NXT
//
// Gradual start of motors using non-linear speed ramp
// [David Butterworth, 2012]
//
// This program demonstrates how to gradually start a
// pair of NXT motors, drive at a steady speed,
// then gradually slow down again.
//
// This is useful for vehicles or robots, where
// suddenly applying maximum speed can cause the
// robot to "jerk", which may affect wheel encoder
// readings.
//
// The motor output speed is calculated using a
// non-linear (bell shaped) speed profile.
//
//    outputSpeed = finalSpeed*( 0.5 - 0.5*cos( (1/stepsForRamp)*PI*step ) );
//
// finalSpeed = The desired output speed (amplitude).
// stepsForRamp = How fast to increase the motor speed.
//                You should experiment with this value, because it
//                depends on the loop execution time of your program.
// step = The ramp iterator.
//
// The outputSpeed will increase from 0 to finalSpeed, in stepsForRamp
// number of steps.
// However we can't calculate (1/stepsForRamp)*PI on the fly in RobotC,
// the equation output is zero, so we calculate a rampConstant during
// program compilation using a pre-processor definition.

// stepsForRamp
#define STEPS_FOR_RAMP 70 // 70 steps is good for demo.
                          // 25 is quite fast.
                          // 1 is minimum value, so you can see how much
                          //   jerk the robot has.

#define MOTOR_PORT_LEFT  motorC
#define MOTOR_PORT_RIGHT motorA

//----------------------------------------------------------------------------//

// Calculate the rampConstant during program compilation
#define RAMP_CONSTANT (PI/STEPS_FOR_RAMP)
// e.g.  (1/200)*PI = 0.015708

// Declare vars
int finalSpeed = 0;
float outputSpeed = 0;
int step = 0;

// Main
task main()
{
    // Set maximum final speed for motors
    finalSpeed = 70;

    // Loop forever
    while (true)
    {
        // Initial state is state1
        static int state = 1;

        switch (state)
        {
            case 1: // State 1
                // Ramp-up Motor Speed
                nxtDisplayString(3, "Faster...");

                // Increase motor speed over STEPS_FOR_RAMP
                // number of steps.
                // This case statement will get executed
                // STEPS_FOR_RAMP number of times.
                if (step < STEPS_FOR_RAMP)
                {
                    outputSpeed = finalSpeed*( 0.5 - 0.5*cos( RAMP_CONSTANT*step ) );
                    motor[MOTOR_PORT_LEFT]= outputSpeed;
                    motor[MOTOR_PORT_RIGHT]= outputSpeed;
                    nxtDisplayString(1, "Ramp step: %i", step);
                    step++;
                }
                // After STEPS_FOR_RAMP number of loops
                // change to State 2.
                else
                {
                    state++;
                    // clear step counter
                    step=0;
                }
                // Jump to end of switch structure
                break;

            case 2: // State 2
                // Maintain speed
                nxtDisplayString(3, "Steady.");

                // Steady speed for 30 cycles
                if (step < 30)
                {
                    outputSpeed = finalSpeed;
                    motor[MOTOR_PORT_LEFT]= outputSpeed;
                    motor[MOTOR_PORT_RIGHT]= outputSpeed;
                    step++;
                }
                else
                {
                    state++;
                    // Set step counter so we can use the
                    // right-hand half of the bell-shaped
                    // speed curve (for decreasing).
                    step=STEPS_FOR_RAMP;
                }
                break;

            case 3: // State 3
                // Ramp-down Motor Speed
                nxtDisplayString(3, "Slower...");

                // For decreasing speed, we iterate from
                // STEPS_FOR_RAMP to 2*STEPS_FOR_RAMP steps.
                if (step < 2*STEPS_FOR_RAMP)
                {
                    outputSpeed = finalSpeed*( 0.5 - 0.5*cos( RAMP_CONSTANT*step ) );
                    motor[MOTOR_PORT_LEFT]= outputSpeed;
                    motor[MOTOR_PORT_RIGHT]= outputSpeed;
                    nxtDisplayString(1, "Ramp step: %i", step);
                    step++;
                }
                else
                {
                    state++;
                    // Clear step counter
                    step=0;
                    // Clear outputSpeed, due to floating point
                    // arithmetic this doesn't always go to zero.
                    outputSpeed = 0;
                    // Turn off motors by setting speed to integer 0.
                    // If we set speed to a floating point number
                    // near zero, the motors may still turn.
                    motor[MOTOR_PORT_LEFT]= 0;
                    motor[MOTOR_PORT_RIGHT]= 0;
                }
                break;


            case 4: // State 4
                // Stopped
                nxtDisplayString(3, "Stopped.");

                // No state change, so this empty
                // case will keep getting executed.
                break;

        } // end switch

        // Display current motor speed
        nxtDisplayString(3, "Motor speed: %.1f", outputSpeed);

        // Note that this wait delay will effect how fast
        // the motor speed ramps, and may not be required
        // for bigger program loops.
        wait1Msec(40);
        eraseDisplay();
    }
}
