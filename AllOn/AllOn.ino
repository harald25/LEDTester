// ----- Bare FastLED -----

#include <FastLED.h>
#define NUM_LEDS 610
#define DATA_PIN 6
#define GLOBAL_BRIGHTNESS 150

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setCorrection( TypicalSMD5050  );
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
  FastLED.setTemperature(UncorrectedTemperature);

  for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
  }
  FastLED.show();

  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::White;
    }

  FastLED.show();
}

void loop() {
  FastLED.delay(10);
}


// ----- FastLED med OCTOWS -----
/*
#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>

#define NUM_LEDS_PER_STRIP 250
#define NUM_STRIPS 8

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(150);
  for (int i = 0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; i++) {
        leds[i] = CRGB::White;
      }
  FastLED.show();
}

void loop() {

  static uint8_t hue = 255;
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::White;
    }
  }

  LEDS.show();
  LEDS.delay(1000);

}
*/
