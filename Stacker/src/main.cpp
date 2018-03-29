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

void clear(int from, int to)
{
   int direction = from < to ? 1 : -1;
  for (int i = from * direction; i <= to; i++)
  {
    setLedColor(i * direction, CRGB::Black);
  }
}

void drawStuff(int start, int end, int size)
{
  Serial.print("Start=");
  Serial.print(start);
  Serial.print("end=");
  Serial.print(end);
  Serial.print("size=");
  Serial.println(size);
  for (int k = start; k <= end && k < size + start; k++)
  {
    setLedColor(k, CRGB::Blue);
  }
  FastLED.show();
}

void move(int from, int to, int size)
{
  int direction = from < to ? 1 : -1;
  for (int i = from * direction; i <= to + size; i++)
  {
    clear(from, to);
    int start = i - size; //-9
    int currentSize = size;
    if (start*direction < 0)
    {
      start = 0;
      currentSize = i;
    }
    if (start < i) {
      start = i; //-6
      currentSize = from + i + 1;
    }
    drawStuff(start * direction, to + start*direction+currentSize-1, currentSize);
    delay(1000);
  }
  clear(from, to);
  FastLED.show();
}

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
  move(6, 0, 3);
  // for (int i = 0; i < ROW_COUNT; i++) {
  //   lightRowFromTo(ROW_COUNT - i - 1, 6, 0, 1);
  // }
  delay(1000);
}
