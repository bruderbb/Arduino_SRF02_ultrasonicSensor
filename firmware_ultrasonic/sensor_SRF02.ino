// ultra sonic distance sensor
// by rouan van der ende
// https://github.com/fluentart/Arduino_SRF02_ultrasonicSensor
// http://www.robot-electronics.co.uk/htm/srf02techI2C.htm

#define SRF02 112  //240

double height = 0.0;

double getheight() {
  if (SRF02_ready() == 0) {
    //still busy with a reading.
    //return last reading
    //could perhaps do prediction based on velocity and time
    return height;
  } else {
    //new reading available
    unsigned int readrange = SRF02_range();

    double echotime = (double) readrange;
    //ultrasonic sensor is set to microseconds for echo to come back. 
    //so using speed of sound we calculate distance. more accurate than 1cm increment setting
    //we divide by 2 because the echo time to to the distance and back again.
    double newheight = echotime/1000000*340.29/2*100; //times 100 to go from meter to cm.

    height = (height * 0.9) + (newheight * 0.1); //smoothes out noise a bit.
    SRF02_ping(); // initiate a new ping so that it is ready next time we read.
    return height;
  }
}

/* ############################################################################ */

void SRF02_ping() {
  Wire.beginTransmission(SRF02); // transmit to device #112 (0x70)
                                 // the address specified in the datasheet is 224 (0xE0)
                                 // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0x00));        // sets register pointer to the command register (0x00)  
  Wire.write(byte(0x52));        // command sensor to measure in "inches" (0x50) 
                                 // use 0x51 for centimeters
                                 // use 0x52 for ping microseconds
  Wire.endTransmission();        // stop transmitting  
}

int SRF02_ready() {
  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(SRF02);
  Wire.write(byte(0x00));     
  Wire.endTransmission();     
  Wire.requestFrom(int(SRF02), 1);    // request 2 bytes from slave device #112
  if(1 <= Wire.available())    // if two bytes were received
  {
    int reading = Wire.read();  // receive high byte (overwrites previous reading)
    return reading;   // print the reading
  } else {
    return 0;
  }
}

unsigned int SRF02_range() {
  unsigned int reading = 0;
  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(SRF02); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(SRF02, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    return reading;
  } else {
    return 0;
  }
}
