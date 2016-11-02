Modded Arduino Library for SparkFun ISL29125 Breakout
==========================================

[![ISL29125 Breakout](https://cdn.sparkfun.com//assets/parts/9/6/7/7/12829-01.jpg)   
*RGB Light Sensor Breakout-ISL29125 (SEN-12829)*](https://www.sparkfun.com/products/12829)

Modified code for the ISL29125 RGB Light Sensor. Based on [ISL29125_Breakout](https://github.com/sparkfun/ISL29125_Breakout).

I needed to use multiple ISL29125 sensors at once. They use the same address, which is hardwired and cannot be changed. I decided to use the same approach that Fire7 used for the [Adafruit TCS34725 Color Sensor](https://github.com/Fire7/Adafruit_TCS34725_SoftI2C).

Using this library, you initialize ISL29125 giving it two pins that are used for software SDA and SCL:

```javascript
// Declare sensor object
static int SDA = 2;
static int SCL = 3;
ISL29125_SOFT RGB_sensor;
RGB_sensor.init(SDA,SCL);
```

So, if you want to use multiple sensors, you can just use different pins:

// Declare sensor objects
```javascript
RGB_sensor_1.init(2,3);
RGB_sensor_2.init(4,5);
RGB_sensor_3.init(6,7);
RGB_sensor_4.init(8,9);

```

And then read them as usual:

```javascript
RGB_sensor_1.readRed();
RGB_sensor_2.readRed();
...etc.
```


Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE.
* **/src** - Source files for the library (.cpp, .h).
* **library.properties** - General library properties for the Arduino package manager.

Documentation
--------------

* **[Hookup Guide](https://learn.sparkfun.com/tutorials/isl29125-rgb-light-sensor-hookup-guide)** - Basic hookup guide for the SparkFun ISL29125 Breakout.
* **[Modded Repository](https://github.com/christosku/ISL29125_SoftWire)** - Main repository for the modified ISL29125 library.
* **[Base Repository](https://github.com/sparkfun/ISL29125_Breakout)** - Main repository (including hardware files) for the SparkFun ISL29125 Breakout.
* **[SoftwareWire Repository](https://github.com/Fire7/SoftwareWire)** - SoftwareWire repository

License Information
-------------------
This product is _**open source**_!

The **code** is beerware; if you see me at the local, and you've found this code helpful, please buy me a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to Christos Koutsouradis and SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.
