/******************************************************************************
ISL29125_basics.ino
Simple example for using the ISL29125 RGB sensor library.
Originally by Jordan McConnell @ SparkFun Electronics, modified by Christos Koutsouradis
28 Oct 2016
https://github.com/christosku/ISL29125_SoftWire

This example declares an SFE_ISL29125 object called RGB_sensor. The 
object/sensor is initialized with a basic configuration so that it continuously
samples the light intensity of red, green and blue spectrums. These values are
read from the sensor every 2 seconds and printed to the Serial monitor.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.6.12

Requires:
ISL29125_SoftWire Library (https://github.com/christosku/ISL29125_SoftWire)
SoftwareWire Library (https://github.com/Fire7/SoftwareWire)


This code is beerware.
Distributed as-is; no warranty is given. 
******************************************************************************/

#include <SoftwareWire.h>
#include "ISL29125_SoftWire.h"

// Declare sensor object
ISL29125_SOFT RGB_sensor;

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the ISL29125 with simple configuration so it starts sampling (Pin 2 is SDA, pin 3 is SCL)
  if (RGB_sensor.init(2,3)) 
  {
    Serial.println("Sensor Initialization Successful\n\r");
  }
}

// Read sensor values for each color and print them to serial monitor
void loop()
{
  // Read sensor values (16 bit integers)
  unsigned int red = RGB_sensor.readRed();
  unsigned int green = RGB_sensor.readGreen();
  unsigned int blue = RGB_sensor.readBlue();
  
  // Print out readings, change HEX to DEC if you prefer decimal output
  Serial.print("Red: "); Serial.println(red,HEX);
  Serial.print("Green: "); Serial.println(green,HEX);
  Serial.print("Blue: "); Serial.println(blue,HEX);
  Serial.println();
  delay(2000);
}
