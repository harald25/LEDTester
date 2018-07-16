#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#include <SLIPEncodedSerial.h>
#include <OSCMessage.h>

#define NUM_LEDS_PER_STRIP 177
#define NUM_STRIPS 2

uint8_t active_LED;
String readString;
boolean update_pattern;
SLIPEncodedSerial SLIPSerial(Serial1);

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
    Serial.begin(9600);
    SLIPSerial.begin(115200);   //Teensy <=> ESP
    Serial.println("Started");


    LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
    LEDS.setBrightness(5);
    for (int i = 0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; i++) {
        leds[i] = CRGB::Black;
      }
    FastLED.show();
}

void SetActiveLED() {
  while (Serial.available())
  {
    Serial.println("Reading serial");
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0)
  {
    Serial.println(readString);  //so you can see the captured string
    int n = readString.toInt();  //convert readString into a number
    Serial.print("Lyser opp LED nr: ");
    Serial.println(n);

    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
    {
      if (i == n) {
        leds[i] = CRGB::White;
      }
      else {
        leds[i] = CRGB::Black;
      }
    }
    FastLED.show();
  }

  readString=""; //empty for next input
}

void SetPixel(int pixel)
{
  if (update_pattern)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
    {
      if (i == pixel) {
        leds[i] = CRGB::White;
      }
      else {
        leds[i] = CRGB::Black;
      }
    }
    FastLED.show();
  }
}

void loop() {
  SetActiveLED();
  //OSCMsgReceive();

}

void OSCMsgReceive()
{

  OSCMessage msgIN;
  int size;

  static unsigned long microsTime = 0;
  while (!SLIPSerial.endofPacket())
  {
    if ((size = SLIPSerial.available()) > 0)
    {
      microsTime = micros();
      while (size--)  //this needs a byte limit
      {
        msgIN.fill(SLIPSerial.read());
      }
    }
    if ((micros() - microsTime) > 10000) break; //Timeout for no eoP()
  }


  if(!msgIN.hasError())
  {
    msgIN.route("/Fader",funcValue);
  }

}
void funcValue(OSCMessage &msg, int addrOffset ) {

  // Origin
  if (msg.fullMatch("/Fader/pixel"))
  {
    float pixel = msg.getFloat(0);
    SetPixel(pixel);
  }
}
