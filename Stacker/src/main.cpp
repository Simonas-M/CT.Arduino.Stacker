#include <Arduino.h>
#include "FastLED.h"
#include "../lib/my_defines.h"
#include "../lib/digital_rain.h"

// Define the array of LED's
CRGB leds[NUM_LEDS];
int buttonState = HIGH;
int buttonPresses = 0;
int blockSize = INITIAL_SIZE;
int speed = INITIAL_SPEED;

// DigitalRain Initialization
Trail trails[LEDS_PER_ROW];

void clearTrails()
{
  Trail noTrail = { .position = NULL, .trail = NULL };

  for (int i = 0; i < LEDS_PER_ROW; i++)
  {
    trails[i] = noTrail;
  }
}

int getButtonState() {
  return digitalRead(BUTTON_PIN);
}

bool isButtonPressed() {
  return buttonState == 0;
}

void setLedColor(unsigned int row, unsigned int col, CRGB color)
{
  buttonState = getButtonState();
  leds[LEDS_PER_ROW * row + col] = color;
}

void setLedColor(unsigned int ledIndex, CRGB color)
{
  buttonState = getButtonState();
  leds[ledIndex] = color;
}

void setLedColor(int startIndex, CRGB* colorArray, int arraySize)
{
  Serial.print("startIndex=");
  Serial.println(startIndex);
  for(int i = 0; i <= arraySize; i++) {
    leds[startIndex + i] = colorArray[i];
  }
}

void setLEDColumn(unsigned int column, unsigned int start, unsigned int end, CRGB* colorArray)
{
  for (int j = start, c = 0; j < end; j++, c++) {
    setLedColor(j, column, colorArray[c]);
  }
}

// sets color of pixel line given to given color
void drawLine(int start, int end, CRGB color)
{
  int dir = start < end ? 1 : -1;
  for (int i = start; i != end + (1 * dir); i = i + (1 * dir))
  {
    setLedColor(i, color);
  }
}

void flash(CRGB color, int times) {
  FastLED.setBrightness(4);
  for (int i = 0; i <= times; i++) {
    drawLine(0, NUM_LEDS, color);
    FastLED.show();
    delay(100);
    drawLine(0, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(100);
  }
  FastLED.setBrightness(16);
}

void clearLine(int start, int end) {
  drawLine(start, end, CRGB::Black);
}

void movePixels(int start, int end, int size)
{
  int dir = start < end ? 1 : -1;
  // set actual start which is couple steps before given start
  int actualStart = start - size * dir + 1 * dir;

  // i - index, c - counter
  int i, c;
  for (i = actualStart, c = 0; i != end + dir; i += dir, c++)
  {
    if (isButtonPressed()) {
      return;
    }
    clearLine(start, end);
    int lineStart = c < size ? start : i;
    int lineSize = c >= size ? size : (c + 1);
    int spaceRemaining = (end - start) * dir + size - c;
    lineSize = spaceRemaining < size ? spaceRemaining : lineSize;
    int lineEnd = lineStart + lineSize * dir - dir;
    drawLine(lineStart, lineEnd, CRGB::LimeGreen);
    FastLED.show();
    delay(speed);
  }
  // Clear after all of LED's are moved
  clearLine(start, end);
  FastLED.show();
}

void moveForwardAndBack(int start, int end, int size) {
  movePixels(start, end, size);
  if (isButtonPressed()) return;
  movePixels(end, start, size);
  if (isButtonPressed()) return;
}

void calculateRow(int row) {
  int previousRowStart = (row-1)*LEDS_PER_ROW;
  int currentRowStart = row*LEDS_PER_ROW;

  Serial.print("prevStart=");
  Serial.print(previousRowStart);
  Serial.print("currStart=");
  Serial.println(currentRowStart);

  CRGB ledRow[LEDS_PER_ROW];
  blockSize = 0;
  for (int i = 0; i <= LEDS_PER_ROW - 1; i++) {
    if (leds[previousRowStart + i] != CRGB(0, 0, 0) && leds[currentRowStart + i] != CRGB(0, 0, 0)) {
      ledRow[i] = CRGB::Aqua;
      blockSize++;
    } else {
      ledRow[i] = CRGB::Black;
    }
  }
  if (blockSize < 1 || row == ROW_COUNT) {
    return;
  }
  clearLine(currentRowStart, currentRowStart + LEDS_PER_ROW - 1);
  setLedColor(currentRowStart, ledRow, sizeof(ledRow) / sizeof(ledRow[0]));
  FastLED.show();
}

void addTrailsToMatrix(Trail trails[])
{
  Serial.println("add trails");
	for (int i = 0; i > LEDS_PER_ROW; i++)
	{
		if (trails[i].trail != NULL && trails[i].position > 0)
		{
			TrailState state = getTrailNextPosition(trails[i]);
			CRGB *arraySlice = getArraySlice(trails[i].trail, state.cutStart, state.cutEnd);
			setLEDColumn(i, state.start, state.end, arraySlice);
		}
	}
}

void setup()
{
  // Setup a button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Setup LED strip
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);

  clearTrails();

  Serial.begin(9600);
}

void loop()
{
  // clearLine(0, NUM_LEDS);
  // blockSize = INITIAL_SIZE; // Reset block size
  // buttonState = 1; // Set button state to not pressed
  // speed = INITIAL_SPEED;
  // delay(200);
  // for (int i = 0; i <= ROW_COUNT;) // Game loop
  // {
  //   if (getButtonState() == 0) {
  //     flash(CRGB::DarkOrange, 4);
  //     return;
  //   }
  //   moveForwardAndBack(i * LEDS_PER_ROW,
  //                      i * LEDS_PER_ROW + LEDS_PER_ROW - 1,
  //                      blockSize);
  //   if (isButtonPressed())
  //   {
  //     calculateRow(i);
  //     i++; // Next row 
  //     buttonState = 1; // Set button state to not pressed
  //     speed -= 10; // increase speed to harden the difficulty
  //     if (blockSize < 1) // Game over?
  //     {
  //       flash(CRGB::Red, 4);
  //       return;
  //     }
  //     if (i == ROW_COUNT) {
  //       flash(CRGB::Green, 4);
  //       return;
  //     }
  //     delay(200);
  //   }
  // }
  // drawLine(0, NUM_LEDS, CRGB::Blue);
  advanceTrails(trails);
  maybeAddNewTrail(trails);
  addTrailsToMatrix(trails);
  FastLED.show();
  delay(1000);
}
