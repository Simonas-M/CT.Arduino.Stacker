#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 60

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 5

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  lightUp();
  lightDown();
}

void lightUp() {
  for (int i = 0; i<= NUM_LEDS - 7; i++) {
    leds[i-1] = CRGB::Black;
    leds[i] = CRGB::Cyan;
    leds[i+1] = CRGB::Blue;
    leds[i+2] = CRGB::Teal;
    leds[i+3] = CRGB::Green;
    leds[i+4] = CRGB::Yellow;
    leds[i+5] = CRGB::Orange;
    leds[i+6] = CRGB::Pink;
    leds[i+7] = CRGB::Magenta;
    FastLED.show();
    delay(20);
  }
}

void lightDown() {
  for (int i = NUM_LEDS; i != 0; i--) {
    leds[i+1] = CRGB::Black;
    leds[i] = CRGB::Red;
    leds[i-1] = CRGB::Blue;
    leds[i-2] = CRGB::Green;
    FastLED.show();
    delay(20);
  }
}

