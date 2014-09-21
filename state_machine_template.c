// state_machine_template.c
// RobotC for Mindstorms NXT
//
// Basic State Machine
// [David Butterworth, 2012]
//
// Used to perform tasks in a serial order,
// or repeat certain tasks multiple times.
// e.g. follow line, detect color, find object,
//          find line, follow line.
//  or drive straight, turn, check sonar,
//         drive straight, turn, ....
//
// This program will loop forever.
// On first iteration of while loop,
// case0 statement is executed and the
// state variable is incremented.
// On 2nd iteration case1 is executed,
// and the state variable incremented again.
// Case2 is repeatedly executed until
// program execution is halted.
//
// Generally you would make the robot change
// state based on some input, such as when a
// counter has reach a certain value, after
// a specific number of encoders ticks, or if
// a sensor returns a defined value.
// e.g.
// if (sensorValue == 50) { state = 7; }

task main()
{
    // Loop forever
    while(true)
    {
        // Initial State is 1
        // A static integer is initialised only the first
        // time this code is executed, then keeps its
        // value until changed.
        static int state = 1;

        switch (state)
        {
            case 1: // State 1
                // Do this first
                nxtDisplayString(3, "State 1");
                wait1Msec(1000);
                // change state
                state++;
                // jump to end of switch structure
                break;

            case 2: // State 2
                // Do this second
                nxtDisplayString(3, "State 2");
                wait1Msec(1000);
                // change state
                state++;
                // jump to end of switch structure
                break;

            case 3: // State 3
                // Do this third
                nxtDisplayString(3, "State 3");
                wait1Msec(10);

                // Because we don't change the state,
                // this case statment will get executed
                // until the program is terminated.

                // jump to end of switch structure
                break;
        } // end switch
    }
}
