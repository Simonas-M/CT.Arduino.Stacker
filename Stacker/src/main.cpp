#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 60 // LED's in strip
#define DATA_PIN 5  // LED strip data pin

#define LEDS_PER_ROW 7 // how many LED's per row

// Define the array of LED's
const int ROW_COUNT = NUM_LEDS / LEDS_PER_ROW;
CRGB leds[NUM_LEDS];

void setLedColor(unsigned int row, unsigned int col, CRGB color)
{
  // Serial.print(row);
  // Serial.println(col);
  leds[LEDS_PER_ROW * row + col] = color;
}

void setLedColor(unsigned int ledIndex, CRGB color)
{
  // Serial.println(ledIndex);
  leds[ledIndex] = color;
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

void clearLine(int start, int end) {
  drawLine(start, end, CRGB::Black);
}

void movePixels(int start, int end, int size)
{
  // Set direction
  int dir = start < end ? 1 : -1;
  // set actual start which is couple steps before given start
  int actualStart = start - size * dir + 1 * dir;

  // i - index, c - counter
  int i, c;
  for (i = actualStart, c = 0; i != end + dir; i += dir, c++)
  {
    clearLine(start, end);
    int lineStart = c < size ? start : i;
    int lineSize = c >= size ? size : (c + 1);
    int spaceRemaining = (end - start) * dir + size - c;
    lineSize = spaceRemaining < size ? spaceRemaining : lineSize;
    int lineEnd = lineStart + lineSize * dir - dir;
    drawLine(lineStart, lineEnd, CRGB::Purple);
    FastLED.show();
    delay(200);
  }
  // Clear after all of LED's are moved
  clearLine(start, end);
  FastLED.show();
}

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
}

void loop()
{
  movePixels(5, 11, 5);
  movePixels(11, 5, 5);
  // for (int i = 0; i < ROW_COUNT; i++) {
  //   lightRowFromTo(ROW_COUNT - i - 1, 6, 0, 1);
  // }
  delay(1000);
}
