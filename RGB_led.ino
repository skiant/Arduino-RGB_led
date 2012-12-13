/*
 * RGB Led control via Arduino PWM pins
 * Applied from http://www.instructables.com/id/RGB-LED-Tutorial-using-an-Arduino-RGBL/
 */

// defining the analog pins we're going to use
 int ledAnalog[] = {3, 5, 6};

// pre-defined colors
const byte RED[] = {255, 0, 0};
const byte ORANGE[] = {83, 4, 0};
const byte YELLOW[] = {255, 255, 0};
const byte GREEN[] = {0, 255, 0};
const byte BLUE[] = {0, 0, 255};
const byte INDIGO[] = {4, 0, 19};
const byte VIOLET[] = {23, 0, 22};
const byte CYAN[] = {0, 255, 255};
const byte MAGENTA[] = {255, 0, 255};
const byte WHITE[] = {255, 255, 255};
const byte BLACK[] = {0, 0, 0};
const byte PINK[] = {158, 4, 79};


void setup(){
  for(int i = 0; i < 3; i++)
  {
    pinMode(ledAnalog[i], OUTPUT);
  }
  setColor(ledAnalog, BLACK);
  fadeToColor(ledAnalog, BLACK, WHITE, 10);
}

void loop() {
  fadeToColor(ledAnalog, WHITE, RED, 10);
  fadeToColor(ledAnalog, RED, YELLOW, 10);
  fadeToColor(ledAnalog, YELLOW, GREEN, 10);
  fadeToColor(ledAnalog, GREEN, BLUE, 10);
  fadeToColor(ledAnalog, BLUE, MAGENTA, 10);
  fadeToColor(ledAnalog, MAGENTA, WHITE, 10);
}

void setColor(int* led, byte* color)
{
  for(int i = 0; i < 3; i++)
  {
    //iterate through each of the three pins (red green blue)
    analogWrite(led[i], 255 - color[i]);
    //set the analog output value of each pin to the input value (ie led[0] (red pin) to 255- color[0] (red input color)
    //we use 255 - the value because our RGB LED is common anode, this means a color is full on when we output analogWrite(pin, 0)
    //and off when we output analogWrite(pin, 255).
  }
}

/* A version of setColor that takes a predefined color (neccesary to allow const int pre-defined colors */
void setColor(int* led, const byte* color)
{
  byte tempByte[] = {color[0], color[1], color[2]};
  setColor(led, tempByte);
}


void fadeToColor(int* led, byte* startColor, byte* endColor, int fadeSpeed)
{
  // calculate color difference
  int changeRed = endColor[0] - startColor[0];
  int changeGreen = endColor[1] - startColor[1];
  int changeBlue = endColor[2] - startColor[2];

  // calculate steps
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue)));

  //iterate for the channel with the maximum change
  for(int i = 0 ; i < steps; i++)
  {
    // calculate new RGB values & assign it
    byte newRed = startColor[0] + (i * changeRed / steps);
    byte newGreen = startColor[1] + (i * changeGreen / steps);
    byte newBlue = startColor[2] + (i * changeBlue / steps);
    byte newColor[] = {newRed, newGreen, newBlue};
    setColor(led, newColor);
    // fadeSpeed as delay, not quite right
    delay(fadeSpeed);
  }
  //The LED should be at the endColor but set to endColor to avoid rounding errors
  setColor(led, endColor);
}

/* A version of fadeToColor that takes predefined colors (neccesary to allow const int pre-defined colors */
void fadeToColor(int* led, const byte* startColor, const byte* endColor, int fadeSpeed)
{
  byte tempByte1[] = {startColor[0], startColor[1], startColor[2]};
  byte tempByte2[] = {endColor[0], endColor[1], endColor[2]};
  fadeToColor(led, tempByte1, tempByte2, fadeSpeed);
}
