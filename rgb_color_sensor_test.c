#pragma config(Sensor, S1, colorPort, sensorCOLORFULL)
// ^^the above line configures the NXT 2.0 RGB color sensor
// on Port 1, in full color mode.

// rgb_color_sensor_test.c
// RobotC for Mindstorms NXT
//
// RGB Color Sensor Test
// [David Butterworth, 2012]
//
// This program uses the NXT 2.0 RGB (Red Green Blue)
// color sensor.
//
// The detected color is displayed on the LCD screen
// e.g. white, black, blue, etc.
// using an inbuilt NXT funtion.
//
// Also the individual Red/Green/Blue values are
// displayed, as returned by the "AtoD" and "Raw"
// inbuilt functions.

// Display the color name
void displayColorIndex()
{
    string sColor;

    // Get the the current color name from the
    // NXT Brick, which returns a string name value.
    switch (SensorValue[colorPort])
    {
        case BLACKCOLOR: sColor = "Black"; break;
        case BLUECOLOR: sColor = "Blue"; break;
        case GREENCOLOR: sColor = "Green"; break;
        case YELLOWCOLOR: sColor = "Yellow"; break;
        case REDCOLOR: sColor = "Red"; break;
        case WHITECOLOR: sColor = "White"; break;
        default: sColor = "???"; break;
    }
    nxtDisplayCenteredTextLine(2, sColor);
}

// Main
task main()
{
    // Declare variables
    short nAtoDValues[4];
    short nRawValues[4];
    short nColorValues[4];
    string sTemp;

    // Loop foever
    while (true)
    {
        // Get the current Red/Green/Blue light values from the
        // RGB sensor, using various NXT 2.0 functions.
        getColorSensorData(colorPort, colorAtoD,   &nAtoDValues);
        getColorSensorData(colorPort, colorRaw,    &nRawValues);
        getColorSensorData(colorPort, colorValue,  &nColorValues);

        // Call this function
        displayColorIndex();

        // Display formatted output on LCD screen
        nxtDisplayTextLine(3, "   AtoD  Raw   %%");
        StringFormat(sTemp, "R  %4i%5i", nAtoDValues[0], nRawValues[0]);      nxtDisplayTextLine(4, "%s%4i", sTemp, nColorValues[0]);
        StringFormat(sTemp, "G  %4i%5i", nAtoDValues[1], nRawValues[1]);      nxtDisplayTextLine(5, "%s%4i", sTemp, nColorValues[1]);
        StringFormat(sTemp, "B  %4i%5i", nAtoDValues[2], nRawValues[2]);      nxtDisplayTextLine(6, "%s%4i", sTemp, nColorValues[2]);
        StringFormat(sTemp, "Amb%4i%5i", nAtoDValues[3], nRawValues[3]);      nxtDisplayTextLine(7, "%s%4i", sTemp, nColorValues[3]);

        wait1Msec(200);
        eraseDisplay();
    }
}
