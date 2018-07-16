#include <FastLED.h>
#define NUM_LEDS 150
#define DATA_PIN 6
#define GLOBAL_BRIGHTNESS 150

const uint16_t update_delay = 10;
int last_update = 0;
uint8_t index = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setCorrection( TypicalSMD5050  );
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
  FastLED.setTemperature(UncorrectedTemperature);
}

void loop() {
  //Check if enough time has elapsed since last update
  if (millis() - last_update > update_delay)
  {
    lightLEDS();
  }
}

//Function for lighting up the LEDs
void lightLEDS {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    //All LEDs with an index equal to or higher than the variable 'index' will be set to white
    if (i <= index) {
      leds[i] = CRGB::White;
    }
    //All other LEDs will be set to black
    else {
      leds[i] = CRGB::Black;
    }
  }
  //Increment index and output data to LEDs
  increment();
  FastLED.show();
}

//This function increments 'index' by one, but sets it back to zero if index is higher than the number of LEDs
void increment {
  index++;
  if (index > NUM_LEDS) {
    index = 0;
  }
}
