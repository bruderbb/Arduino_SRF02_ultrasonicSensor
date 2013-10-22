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

