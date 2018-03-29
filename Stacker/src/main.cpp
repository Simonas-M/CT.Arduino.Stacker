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

void lightFromToAsc(int from, int to, int size)
{
  for (int i = from; i <= (to - size) + 1; i++)
  {
    if (i != from)
      setLedColor(i - 1, CRGB::Black);
    setLedColor(i, CRGB::Blue);
    FastLED.show();
    delay(20);
    if (i == (to - size) + 1)
    {
      setLedColor(i, CRGB::Black);
      FastLED.show();
    }
  }
}

void lightFromToDesc(int from, int to, int size)
{
  from = from - size + 1;
  for (int i = from; i >= to; i--)
  {
    if (i != from)
      setLedColor(i + 1, CRGB::Black);
    setLedColor(i, CRGB::Blue);
    FastLED.show();
    delay(20);
    if (i == to)
    {
      setLedColor(i, CRGB::Black);
      FastLED.show();
    }
  }
}

// sets color of pixel line given to given color
void drawLine(int start, int end, CRGB color)
{
  Serial.print("Start=");
  Serial.print(start);
  Serial.print("end=");
  Serial.println(end);
  int dir = start < end ? 1 : -1;
  for (int i = start; i != end + (1 * dir); i = i + (1 * dir))
  {
    setLedColor(i, color);
  }
}

void clearLine(int start, int end) {
  drawLine(start, end, CRGB::Black);
}

void movePixels(int start, int end, int size) {
  int dir = start < end ? 1 : -1;

  int interpolatedStart = start - size*dir + 1*dir;
  int interpolatedEnd = end + size*dir - 1*dir;

  int i, c;// c - counter
  for (i = interpolatedStart, c = 0; i != end + dir; i += dir, c++) {
    clearLine(start, end);
    int lineStart = i < start ? start : i;
    int lineSize = c >= size ? size : (c + 1);
    if (lineStart + lineSize - 1 > end) {
      lineSize = interpolatedEnd - lineStart - 1;
    }
    drawLine(lineStart, lineStart + lineSize -1, CRGB::Purple);
    FastLED.show();
    delay(200);
  }
  clearLine(start, end);
  FastLED.show();
}

// void move(int from, int to, int size)
// {
//   int direction = from < to ? 1 : -1;
//   for (int i = from * direction; i <= to + size; i++)
//   {
//     clear(from, to);
//     int start = i - size; //-9
//     int currentSize = size;
//     if (start*direction < 0)
//     {
//       start = 0;
//       currentSize = i;
//     }
//     if (start < i) {
//       start = i; //-6
//       currentSize = from + i + 1;
//     }
//     drawLine(start * direction, to + start*direction+currentSize-1, currentSize);
//     delay(1000);
//   }
//   clear(from, to);
//   FastLED.show();
// }

void lightRowFromTo(int row, int from, int to, int size)
{
  if (from < to)
  {
    lightFromToAsc(LEDS_PER_ROW * row + from, LEDS_PER_ROW * row + to, size);
  }
  else
  {
    lightFromToDesc(LEDS_PER_ROW * row + from, LEDS_PER_ROW * row + to, size);
  }
}

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
}

void loop()
{
  movePixels(5, 11, 3);
  movePixels(11, 5, 3);
  // for (int i = 0; i < ROW_COUNT; i++) {
  //   lightRowFromTo(ROW_COUNT - i - 1, 6, 0, 1);
  // }
  delay(1000);
}
