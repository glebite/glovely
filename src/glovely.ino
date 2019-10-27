/*
	glovely.ino

	A flex-sensor driven glove to allow for bluetooth controls over a
	presentation system and built-in laser pointer and extra fun!

	Flex sensor on index finger - when extended activates laser pointer
	Flex sensor on the thumb - activates the happy face
	Button on the index finger is forward page
	Button on the index finger is backward page
	
	The circuit:
	-
	-
	-

	Copied 2019-10-04
	https://www.instructables.com/id/Arduino-Flex-Sensor-Glove/
	Modified 2019-10-04
	Me.

	https://github.com/glebite/glovely
*/


#define FLEXINDEX A2 
#define FLEXTHUMB A3
#define FLEXSENSORPIN0 0
#define BUTTON_FORWARD D0
#define BUTTON_BACKWARD D1

float singleReading(int);

//defined variables for each sensor according to finger
float indexReading;
float thumbReading;

int ledAnalogOne[] = {5,6};

void setup(void) {
  Serial.begin(9600);
  for(int thisPin = 0; thisPin < 2; thisPin++){
   pinMode(ledAnalogOne[thisPin], OUTPUT);   //Set the three LED pins as outputs
  }
}
 
void loop(void) {
  indexReading = singleReading(FLEXINDEX);
  thumbReading = singleReading(FLEXTHUMB);
  
  Serial.print("Single reading Index "); 
  Serial.println(indexReading);

  Serial.print("Single reading Thumb "); 
  Serial.println(thumbReading);

  delay(1000);
}

/**
 * gets a reading from an analog pin
 * @param pin the pin to read from
 * @return the reading
 */
float singleReading(int pin)
{
  float reading;
  reading = analogRead(pin);
  return reading;
}

/**
 * maps an analog reading to a value between 0-254, 254 used for demonstration purposes to show that values were 
 * being read and manipulated at all times. bottom and top values used are the average values when the sensor is bent (bottom)
 * and when it is held straight (top)
 * @param analogReading reading to be mapped
 * @param bottom the value used as the minimum value for the sensor
 * @param top the value used as the maximum value for the sensor
 * @return mapped value to be used for the RGB light
 */
float mapReading(float analogReading, float bottom, float top)
{
  float calibratedValue;
  if(analogReading > top)
  {
    calibratedValue = 254;
  }
  else if(analogReading < bottom)
  {
    calibratedValue = 0;
  }
  else
  {
    calibratedValue = map(analogReading, bottom,top,0,254); 
  }
  return calibratedValue;
}

/**
 * gets and print the average values taken from the sensor as per the NUMSAMPLES variable
 */
void average()
{
  int NUMSAMPLES = 100;
  uint8_t i;
  float average;
  int samples[NUMSAMPLES];
  
    // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
    //Change the pin according to which sensor you are calibrating
   samples[i] = analogRead(FLEXSENSORPIN0);
   delay(10);
  }

  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  Serial.print("Average reading "); 
  Serial.println(average);
}
