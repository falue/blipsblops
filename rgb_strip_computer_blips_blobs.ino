#include "FastLED.h"

// LED TYPE APA102
#define LED_TYPE  APA102
#define DATA_PIN  0
#define CLK_PIN  1

// LED TYPE WS2812
//#define LED_TYPE  WS2812
//#define LED_PIN 6

// General
#define COLOR_ORDER  BGR  // if colors are wrong, use GRB
#define NUM_LEDS  14
CRGB leds[NUM_LEDS];
long step = 0;
int speed = 15;
int brightness = 255;

// ORIGINAL WEB COLORS (SUCK FOR LED, ALL WASHED OUT)
// CRGB colorSpace[] = {CRGB::AliceBlue, CRGB::Amethyst, CRGB::AntiqueWhite, CRGB::Aqua, CRGB::Aquamarine, CRGB::Azure, CRGB::Beige, CRGB::Bisque, CRGB::BlanchedAlmond, CRGB::Blue, CRGB::BlueViolet, CRGB::Brown, CRGB::BurlyWood, CRGB::CadetBlue, CRGB::Chartreuse, CRGB::Chocolate, CRGB::Coral, CRGB::CornflowerBlue, CRGB::Cornsilk, CRGB::Crimson, CRGB::Cyan, CRGB::DarkBlue, CRGB::DarkCyan, CRGB::DarkGoldenrod, CRGB::DarkGray, CRGB::DarkGrey, CRGB::DarkGreen, CRGB::DarkKhaki, CRGB::DarkMagenta, CRGB::DarkOliveGreen, CRGB::DarkOrange, CRGB::DarkOrchid, CRGB::DarkRed, CRGB::DarkSalmon, CRGB::DarkSeaGreen, CRGB::DarkSlateBlue, CRGB::DarkSlateGray, CRGB::DarkSlateGrey, CRGB::DarkTurquoise, CRGB::DarkViolet, CRGB::DeepPink, CRGB::DeepSkyBlue, CRGB::DimGray, CRGB::DimGrey, CRGB::DodgerBlue, CRGB::FireBrick, CRGB::FloralWhite, CRGB::ForestGreen, CRGB::Fuchsia, CRGB::Gainsboro, CRGB::GhostWhite, CRGB::Gold, CRGB::Goldenrod, CRGB::Gray, CRGB::Grey, CRGB::Green, CRGB::GreenYellow, CRGB::Honeydew, CRGB::HotPink, CRGB::IndianRed, CRGB::Indigo, CRGB::Ivory, CRGB::Khaki, CRGB::Lavender, CRGB::LavenderBlush, CRGB::LawnGreen, CRGB::LemonChiffon, CRGB::LightBlue, CRGB::LightCoral, CRGB::LightCyan, CRGB::LightGoldenrodYellow, CRGB::LightGreen, CRGB::LightGrey, CRGB::LightPink, CRGB::LightSalmon, CRGB::LightSeaGreen, CRGB::LightSkyBlue, CRGB::LightSlateGray, CRGB::LightSlateGrey, CRGB::LightSteelBlue, CRGB::LightYellow, CRGB::Lime, CRGB::LimeGreen, CRGB::Linen, CRGB::Magenta, CRGB::Maroon, CRGB::MediumAquamarine, CRGB::MediumBlue, CRGB::MediumOrchid, CRGB::MediumPurple, CRGB::MediumSeaGreen, CRGB::MediumSlateBlue, CRGB::MediumSpringGreen, CRGB::MediumTurquoise, CRGB::MediumVioletRed, CRGB::MidnightBlue, CRGB::MintCream, CRGB::MistyRose, CRGB::Moccasin, CRGB::NavajoWhite, CRGB::Navy, CRGB::OldLace, CRGB::Olive, CRGB::OliveDrab, CRGB::Orange, CRGB::OrangeRed, CRGB::Orchid, CRGB::PaleGoldenrod, CRGB::PaleGreen, CRGB::PaleTurquoise, CRGB::PaleVioletRed, CRGB::PapayaWhip, CRGB::PeachPuff, CRGB::Peru, CRGB::Pink, CRGB::Plaid, CRGB::Plum, CRGB::PowderBlue, CRGB::Purple, CRGB::Red, CRGB::RosyBrown, CRGB::RoyalBlue, CRGB::SaddleBrown, CRGB::Salmon, CRGB::SandyBrown, CRGB::SeaGreen, CRGB::Seashell, CRGB::Sienna, CRGB::Silver, CRGB::SkyBlue, CRGB::SlateBlue, CRGB::SlateGray, CRGB::SlateGrey, CRGB::Snow, CRGB::SpringGreen, CRGB::SteelBlue, CRGB::Tan, CRGB::Teal, CRGB::Thistle, CRGB::Tomato, CRGB::Turquoise, CRGB::Violet, CRGB::Wheat, CRGB::White, CRGB::WhiteSmoke, CRGB::Yellow, CRGB::YellowGreen, CRGB::FairyLight, CRGB::FairyLightNCC };

// WEB COLORS WHICH ARE NOT **VERY** TERRIBLE
// CRGB colorSpace[] = {CRGB::Aqua, CRGB::Azure, CRGB::Blue, CRGB::Brown, CRGB::Chartreuse, CRGB::Coral, CRGB::CornflowerBlue, CRGB::Crimson, CRGB::Cyan, CRGB::DarkBlue, CRGB::DarkCyan, CRGB::DarkGoldenrod, CRGB::DarkGreen, CRGB::DarkMagenta, CRGB::DarkOrange, CRGB::DarkOrchid, CRGB::DarkRed, CRGB::DarkTurquoise, CRGB::DarkViolet, CRGB::DeepPink, CRGB::DeepSkyBlue, CRGB::DodgerBlue, CRGB::FireBrick, CRGB::ForestGreen, CRGB::Fuchsia, CRGB::Gold, CRGB::Green, CRGB::HotPink, CRGB::Indigo, CRGB::LawnGreen, CRGB::LightSeaGreen, CRGB::Lime, CRGB::Magenta, CRGB::Maroon, CRGB::MediumBlue, CRGB::MediumSpringGreen, CRGB::MediumTurquoise, CRGB::MediumVioletRed, CRGB::MidnightBlue, CRGB::Navy, CRGB::Olive, CRGB::Orange, CRGB::OrangeRed, CRGB::Purple, CRGB::Red, CRGB::RoyalBlue, CRGB::SpringGreen, CRGB::SteelBlue, CRGB::Teal, CRGB::Tomato, CRGB::White, CRGB::Yellow, CRGB::FairyLight};

// Less colors
//CRGB colorSpace[] = {CRGB::Blue, CRGB::Brown, CRGB::Chartreuse, CRGB::CornflowerBlue, CRGB::Cyan, CRGB::DarkBlue, CRGB::DarkCyan, CRGB::DarkGoldenrod, CRGB::DarkGreen, CRGB::DarkMagenta, CRGB::DarkOrange, CRGB::DarkOrchid, CRGB::DarkRed, CRGB::DarkTurquoise, CRGB::DarkViolet, CRGB::DeepPink, CRGB::DeepSkyBlue, CRGB::FireBrick, CRGB::ForestGreen, CRGB::Gold, CRGB::Green, CRGB::HotPink, CRGB::Indigo, CRGB::LightSeaGreen, CRGB::Lime, CRGB::Magenta, CRGB::MediumBlue, CRGB::MediumSpringGreen, CRGB::MediumTurquoise, CRGB::MediumVioletRed, CRGB::MidnightBlue, CRGB::Navy, CRGB::Olive, CRGB::Orange, CRGB::OrangeRed, CRGB::Purple, CRGB::Red, CRGB::RoyalBlue, CRGB::SteelBlue, CRGB::Tomato, CRGB::White, CRGB::Yellow, CRGB::FairyLight};

// Even lesser colors
// CRGB colorSpace[] = {CRGB::Blue, CRGB::Red, CRGB::Orange, CRGB::White, CRGB::Cyan, CRGB::Green, CRGB::DarkCyan, CRGB::DarkGoldenrod, CRGB::DarkGreen, CRGB::Tomato, CRGB::White, CRGB::Yellow, CRGB::FairyLight};

// Custom colors
CRGB colorSpace[] = {CRGB::Red, CRGB::Red, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Green};


// Define of led array structure
typedef struct ledPersonality {
  int ledNum;             // which led from 0 to NUM_LEDS
  int trigger;            // toggle on/off every x step (1 step = 1 loop). 1 = every step; 2 every second step and so on
  int offset;             // trigger with offset steps
  CRGB color;             // duh; color like CRGB::Red etc
  int lastStepTriggered;  // last time on-blink is triggered. always start at 0. Do not change this.
  float symmetricRatio;   // times off-time is skipped so longer off times than on times. 1=symmetric on/off; >1 longer off than on.
  float accuracy;         // hit trigger time. 100=non random; 50=50% chance of triggering when supposed; 1 very random; 0 never.
  int fadeOut;            // fadeout of led 0-99. 0 immediately black out; 99 very slowly; 100 never.
};

// Setup up your LED strip
int numLightUpLeds = 14;
ledPersonality ledSchemas[14] = {
  {0, 33,   0, CRGB::Orange,  0, 1.0, 100.0, 90},
  {1, 66,   25, CRGB::White,  0, 2.0, 100.0, 90},
  {2, 125,   50, CRGB::White,  0, 4.0, 100.0, 90},
  {3, 50,   0, CRGB::White,  0, 1.0, 100.0, 90},
  {4, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},
  {5, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0}, 
  {6, 18,   0, CRGB::Green,  0, 1.0, 100.0, 0}, 
  {7, 12,   0, CRGB::Green,  0, 1.0, 88.0, 0},
  {8, 6,   25, CRGB::Orange,  0, 2.0, 55.0, 50},
  {9, 3,   50, CRGB::White,  0, 4.0, 33.0, 90},
  {10, 3,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {11, 9,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {12, 9,   75, CRGB::White,  0, 1.0, 88.0, 90},
  {13, 333,   75, CRGB::White,  0, 1.0, 88.0, 90}  // slowpoke
};

void setup() {
  Serial.begin(9600);
  delay(333); // Delay for recovery

  // LED TYPE APA102
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // LED TYPE WS2812
  // FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  FastLED.setBrightness(brightness);
  Serial.println("*********************************");
  Serial.println("Startup complete.");
  Serial.println("*********************************");

  // Black out all leds
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}

void loop() {
  for(int i = 0; i < numLightUpLeds; i++) {
    ledPersonality led = ledSchemas[i];
    int ledNum = led.ledNum;
    
    // If its more than 0% on, turn it off
    if(leds[ledNum] && (step - led.offset) % led.trigger == 0 && led.fadeOut == 0) {
        // Blackout led if it is lit
        if(led.accuracy == 100.0 || random(0, 100) < led.accuracy) {
          leds[ledNum] = CRGB::Black;
        }

      // Fadeout LED more if it is fading out
      } else if (leds[ledNum] && step > led.lastStepTriggered + led.trigger  && led.fadeOut > 0) {
        fadeTowardColor(leds[ledNum], CRGB::Black, 255 - map(led.fadeOut, 0, 100, 0, 255));

      // Turn LED on
      } else if (
        !leds[ledNum] &&
        (step - led.offset) % led.trigger == 0 &&
        (step - led.offset) - led.lastStepTriggered > led.trigger * led.symmetricRatio
      ) {
        if(led.accuracy == 100.0 || random(0, 100) < led.accuracy) {
          if(led.color == CRGB(CRGB::Black)) {
            leds[ledNum] = pickRandomColor();
          } else {
            leds[ledNum] = led.color;
          }
          ledSchemas[i].lastStepTriggered = step;
        }
    }
  }

  FastLED.show();
  step++;
  delay(speed);
}

CRGB pickRandomColor() {
  int length = sizeof(colorSpace) / sizeof(colorSpace[0]);
  return colorSpace[random(0, length-1)];  // Chosen by fair dice roll
}

// Blend one CRGB color toward another CRGB color by a given amount.
// Blending is linear, and done in the RGB color space.
// This function modifies 'cur' in place.
CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red,   target.red,   amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue,  target.blue,  amount);
  return cur;
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if( cur == target) return;
 
  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}
