#pragma config(Sensor, S1, colorPort, sensorCOLORRED)
// ^^the above line configures the NXT 2.0 RGB color sensor
// on Port 1, using red illumination.

// rgb_color_sensor_as_a_light_sensor.c
// RobotC for Mindstorms NXT
//
// RGB Color Sensor as a Light Sensor
// (A simple line-following robot)
// [David Butterworth, 2012]
//
//
// This is a simple line-following program.
// First calibrate the sensor to find the light reading
// for black and white colors.
// Re-compile program and place the robot to the left
// side of the line and run the program again.
//
//
// This program uses the NXT 2.0 RGB (Red Green Blue)
// color sensor, however it is configured to use only
// the red color illumination.
//
// The result is that the RGB color sensor can be used
// in a similar fashion to the light sensor from the
// NXT 1.0 kit.
// This actually makes the sensor easier to program for
// tasks where only 2 or 3 colors need to be detected,
// such as for line-following.
// If dual functionality is required, to use the sensor
// both in 2-color and full-color detection modes, the
// sensor should be configured in sensorCOLORFULL mode
// and the program written to alternate between reading
// the single Red input value, or all three
// Red/Green/Blue input values.
//
//
// This program also illustrates the use of a Compiler
// "define" and "if-else" statements.
//
// The define statements are used to define values
// that are set before the program is compiled, and don't
// change while its being run.
// e.g. sensor calibration values, or equation constants.
//
// An if-else statement is used to quickly switch between
// 2 large blocks of code.
// This allows you to execute a program in calibration mode
// to take note of sample sensor readings, then quickly
// re-compile the program by making only small changes.
//
// If it's not possible to re-compile a program after
// calibration, such as during a robotics competition,
// the user will need to investigate writing an online
// calibration function.
// Such a function could be programmed to execute by
// pressing one of the grey buttons on the NXT, and
// a process designed such that the sensors are given
// input and the values are recorded into variables.

// If 1, the calibration code will be compiled.
// If 0, the main block of code will be compiled.
#define CALIBRATE_SENSOR 1
// Define which port is left/right motor
#define MOTOR_PORT_LEFT  motorC
#define MOTOR_PORT_RIGHT motorA
// The raw light values from the sensor
// for black and white colors.
// These values are obtained from the calibration mode.
#define RAW_COLOR_VALUE_BLACK 300
#define RAW_COLOR_VALUE_WHITE 600
// The light sensor reading will be averaged across
// multiple samples to smooth the input.
#define NUM_LIGHT_SAMPLES 3

//----------------------------------------------------------------------------//

// CALIBRATION MODE
//
// This block of code will only be compiled
// if we have specified:
// CALIBRATE_SENSOR 1
//
// This mode can be used to determine the raw Light Sensor
// readings for black (on the line), and white (off the line).
//
#if CALIBRATE_SENSOR

task main() {
    // Loop forever
    while (true) {

        // Display the current reading from the Light Sensor
        // on the LCD screen
        nxtDisplayString(2, "Raw light reading:");
        nxtDisplayString(4, "             %i", SensorRaw(colorPort) );

        // Wait a small delay before updating the display,
        // otherwise it will be too hard to read
        wait1Msec(150);
        eraseDisplay();
    }
}

#else
//----------------------------------------------------------------------------//

// MAIN OPERATION MODE
//
// This block of code will only be compiled
// if we have specified:
// CALIBRATE_SENSOR 0

// Normalise the raw input value from the light sensor
// to value in the range 0-100
int normalise(int value) {

    // Constrain values outside range
    if (value <= RAW_COLOR_VALUE_BLACK)   return 0;
    else if (value >= RAW_COLOR_VALUE_WHITE)   return 100;

    // otherwise scale the value
    else   return ((value - RAW_COLOR_VALUE_BLACK) * 100) / (RAW_COLOR_VALUE_WHITE - RAW_COLOR_VALUE_BLACK);
}

// Main
task main() {

    // Declare variables
    int normalisedInput = 0;
    int lightReading = 0;
    int temp = 0;
    int i;

    // Loop forever
    while (true) {

        // Take multiple samples from Light Sensor and
        // calculate the mean, in effect applying a smoothing
        // filter to the input
        for(i=0; i < NUM_LIGHT_SAMPLES; i++) {
            // Get normalised value of current light reading
            normalisedInput = normalise(SensorRaw(colorPort));

            // Calculate mean
            temp = temp + normalisedInput;
            lightReading = temp / NUM_LIGHT_SAMPLES;

            // Display normalized light reading on LCD screen
            nxtDisplayString(2, "Light reading:");
            nxtDisplayString(4, "             %i", lightReading );
        }

        wait1Msec(40);
        eraseDisplay();
        temp = 0;

        // If normalized light reading is near 100,
        // we are on the black line, so turn right.
        if ((lightReading < 100) && (lightReading > 75)) {
                motor[MOTOR_PORT_RIGHT]= 10;
                motor[MOTOR_PORT_LEFT]= 80;

        // or if reading is near 0, we're on white (off the line),
        // so turn left.
        // There is a gap inbetween these ranges, so the robot
        // operates more smoothly.
        } else if ((lightReading > 0) && (lightReading < 25)) {
            motor[MOTOR_PORT_RIGHT]= 80;
            motor[MOTOR_PORT_LEFT]= 10;

        }
    }
}

#endif
