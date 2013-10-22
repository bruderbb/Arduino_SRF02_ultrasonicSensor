How to use
==========

Copy `sensor_SRF02.ino` into your project folder.

Merge this into your main program.

```
#include <Wire.h>

void setup()
{
  Wire.begin();                // join i2c bus (address optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
}

void loop()
{
	double distance = getheight();	//gets the reading from the sensor.
  	Serial.println(distance, 5); 	//prints centimetres to Serial with 5 decimal points. 
}
```



The important things are `#include <Wire.h>` and `Wire.begin();` so we can use I2C communication. 

Then  `getheight();` returns a double floating point value in centimetres. 

The factor can be changed by modifying `double newheight = echotime/1000000*340.29/2*100; //times 100 to go from meter to cm.` in `sensor_SRF02.ino`
