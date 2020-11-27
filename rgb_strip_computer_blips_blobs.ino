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


// define of led array structure
typedef struct ledPersonality {
  int ledNum;             // which led from 0 to NUM_LEDS
  int trigger;            // toggle on/off every x step (1 step = 1 loop). 1 = every step; 2 every second step and so on
  int offset;             // trigger with offset steps
  CRGB color;             // duh; color like CRGB::Red etc
  int lastStepTriggered;  // last time on-blink is triggered. always start at 0.
  float symmetricRatio;   // times off-time is skipped so longer off times than on times. 1=symmetric on/off; >1 longer off than on.
  float accuracy;         // hit trigger time. 100=non random; 50=50% chance of triggering when supposed; 1 very random; 0 never.
  int fadeOut;            // fadeout of led 0-99. 0 immediately black out; 99 very slowly; 100 never.
};

// VAR. EXAMPLES ------------------------------------------------------------------
// various random shit
/* int numLightUpLeds = 14;
ledPersonality ledSchemas[14] = {  
  {0, 30,   0, CRGB::Red,     0, 1.0,, 0 100.0},
  {1, 60,   0, CRGB::Green,   0, 2.0, 100.0, 0},  // black out is twice as long
  {2, 60,   0, CRGB::Orange,   0, 12.0, 100.0, 0},  // black out is twelve times as long
  {3, 30,   0, CRGB::White,   0, 1.0, 33.0, 0},
  {7, 5,   0, CRGB::Yellow,  0, 1.0, 100.0, 0},  // fast
  {8, 5,   0, CRGB::Yellow,  0, 1.0, 15.0, 0},  // fast, radom
  {9, 5,   0, CRGB::Yellow,  0, 1.0, 5.0, 0},  // fast, very random
  {12, 100, 0, CRGB::Magenta, 0, 1.0, 100.0, 0},
  {13, 45, 0, CRGB::Blue, 0, 1.0, 100.0, 0},
  {14, 175, 0, CRGB::Green, 0, 1.0, 100.0, 0},
  {17, 80, 0, CRGB::Cyan, 0, 1.0, 100.0, 0},
  {18, 80, 0, CRGB::Cyan, 0, 1.0, 100.0, 0},
  {19, 80, 0, CRGB::Cyan, 0, 1.0, 100.0, 0},
  {20, 80, 0, CRGB::Cyan, 0, 1.0, 95.0, 0}  // slightly off timing
}; */

// Walking lights
/* int numLightUpLeds = 20;
ledPersonality ledSchemas[20] = {  
  {0, 100,   0, CRGB::Red,  0, 1.0, 100.0, 0},
  {1, 100,   25, CRGB::Red,  0, 1.0, 100.0, 10},
  {2, 100,   50, CRGB::Red,  0, 1.0, 100.0, 20},
  {3, 100,   75, CRGB::Red,  0, 1.0, 100.0, 30},
  {4, 100,   100, CRGB::Red,  0, 1.0, 100.0, 40},
  {5, 100,   125, CRGB::Red,  0, 1.0, 100.0, 50},
  {6, 100,   150, CRGB::Red,  0, 1.0, 100.0, 60},
  {7, 100,   175, CRGB::Red,  0, 1.0, 100.0, 70},
  {8, 100,   200, CRGB::Red,  0, 1.0, 100.0, 80},
  {9, 100,   225, CRGB::Red,  0, 1.0, 100.0, 90},
  {10, 100,   250, CRGB::Red,  0, 1.0, 100.0, 100},
  {11, 100,   275, CRGB::Red,  0, 1.0, 100.0, 100},
  {12, 100,   300, CRGB::Red,  0, 1.0, 100.0, 100},
  {13, 100,   325, CRGB::Red,  0, 1.0, 100.0, 100},
  {14, 100,   350, CRGB::Red,  0, 1.0, 100.0, 100},
  {15, 100,   375, CRGB::Red,  0, 1.0, 100.0, 100},
  {16, 100,   400, CRGB::Red,  0, 1.0, 100.0, 100},
  {17, 100,   425, CRGB::Red,  0, 1.0, 100.0, 100},
  {18, 100,   450, CRGB::Red,  0, 1.0, 100.0, 100},
  {19, 100,   475, CRGB::Red,  0, 1.0, 100.0, 100}
}; */

// Random Flickering blips and blobs
/* int numLightUpLeds = 20;
ledPersonality ledSchemas[20] = {  
  {0, 33,   0, CRGB::Black,  0, 1.0, 88.0, 50},
  {1, 5,   25, CRGB::Black,  0, 2.0, 55.0, 0},
  {2, 125,   50, CRGB::Black,  0, 4.0, 33.0, 75},
  {3, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {4, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {5, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {6, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {7, 33,   0, CRGB::Black,  0, 1.0, 88.0, 0},
  {8, 5,   25, CRGB::Black,  0, 2.0, 55.0, 50},
  {9, 125,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {10, 250,   75, CRGB::Black,  0, 1.0, 77.0, 0},
  {11, 22,   75, CRGB::Black,  0, 1.0, 77.0, 0},
  {12, 25,   75, CRGB::Black,  0, 1.0, 88.0, 50},
  {13, 80,   75, CRGB::Blue,  0, 1.0, 100.0, 99},  // slowly blinking, fade out
  {14, 2,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {15, 3,   75, CRGB::Black,  0, 1.0, 22.0, 0},
  {16, 4,   75, CRGB::Black,  0, 1.0, 77.0, 0},
  {17, 5,   75, CRGB::Black,  0, 1.0, 88.0, 50},
  {18, 10,   75, CRGB::Black,  0, 1.0, 75.0, 0},
  {19, 10,   75, CRGB::Black,  0, 1.0, 75.0, 90}
}; */

int numLightUpLeds = 14;  // CHANGE IT DEPENDING ON struct of leds!
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

// FROZEN WAR
/* int numLightUpLeds = 53;  // CHANGE IT DEPENDING ON struct of leds!
ledPersonality ledSchemas[53] = {
  // 20 LEDS:  0-19 "Lüfter"
  {0, 33,   0, CRGB::Black,  0, 1.0, 88.0, 50},
  {1, 5,   25, CRGB::Black,  0, 2.0, 55.0, 0},
  {2, 125,   50, CRGB::Black,  0, 4.0, 33.0, 75},
  {3, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {4, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {5, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {6, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  // synchron 
  {7, 33,   0, CRGB::Black,  0, 1.0, 88.0, 0},
  {8, 5,   25, CRGB::Black,  0, 2.0, 55.0, 50},
  {9, 125,   50, CRGB::Orange,  0, 4.0, 33.0, 50},
  {10, 250,   75, CRGB::Black,  0, 1.0, 77.0, 0},
  {11, 22,   75, CRGB::Black,  0, 1.0, 77.0, 0},
  {12, 25,   75, CRGB::Black,  0, 1.0, 88.0, 50},
  {13, 80,   75, CRGB::Red,  0, 1.0, 100.0, 99},  // slowly blinking, fade out
  {14, 2,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {15, 3,   75, CRGB::Black,  0, 1.0, 22.0, 0},
  {16, 4,   75, CRGB::Orange,  0, 1.0, 77.0, 0},
  {17, 5,   75, CRGB::Black,  0, 1.0, 88.0, 50},
  {18, 10,   75, CRGB::Black,  0, 1.0, 75.0, 0},
  {19, 10,   75, CRGB::Black,  0, 1.0, 75.0, 90},

  // 14 LEDs: 20-33 "Racks"
  {20, 33,   0, CRGB::Orange,  0, 1.0, 100.0, 90},  // schublade 1
  {21, 66,   25, CRGB::White,  0, 2.0, 100.0, 90},  // schublade 2
  {22, 125,   50, CRGB::White,  0, 4.0, 100.0, 90},  // schublade 3
  {23, 50,   0, CRGB::White,  0, 1.0, 100.0, 90},  // schublade 4
    // "Kontrollzentrum": Erste reihe
  {24, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},
  {25, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0}, 
  {26, 18,   0, CRGB::Green,  0, 1.0, 100.0, 0}, 
  {27, 12,   0, CRGB::Green,  0, 1.0, 88.0, 0},
  {28, 6,   25, CRGB::Orange,  0, 2.0, 55.0, 50},
    // "Kontrollzentrum": Zweite reihe
  {29, 3,   50, CRGB::White,  0, 4.0, 33.0, 90},
  {30, 3,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {31, 9,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {32, 9,   75, CRGB::White,  0, 1.0, 88.0, 90},
  {33, 333,   75, CRGB::White,  0, 1.0, 88.0, 90},  // slowpoke

  // 18 stk LEDs: 34-52 "Motherboard"
  {34, 100,   75, CRGB::Green,  0, 1.0, 100.0, 99},  // slowly blinking, fade out
  {35, 3,   75, CRGB::Orange,  0, 1.0, 22.0, 0},
  {36, 4,   75, CRGB::Black,  0, 1.0, 77.0, 0},  // MIT PHYSISCHEM DIFFUSOR
  {38, 10,   75, CRGB::Orange,  0, 1.0, 75.0, 90},
  {39, 80,   0, CRGB::Orange,  0, 1.0, 100.0, 0},
  {40, 33,   0, CRGB::Orange,  0, 1.0, 88.0, 50},
  {41, 5,   25, CRGB::Black,  0, 2.0, 55.0, 0},  
  {42, 125,   50, CRGB::Black,  0, 4.0, 33.0, 75},
  {43, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},  
  {44, 12,   0, CRGB::Black,  0, 1.0, 100.0, 0}, 
  {45, 6,   0, CRGB::Orange,  0, 1.0, 100.0, 0}, 
  {46, 80,   0, CRGB::Orange,  0, 1.0, 100.0, 0}, 
  {47, 33,   0, CRGB::Black,  0, 1.0, 88.0, 0},
  {48, 5,   25, CRGB::Black,  0, 2.0, 55.0, 50},
  {49, 125,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {50, 150,   75, CRGB::Green,  0, 1.0, 50.0, 60},  // sync
  {51, 150,   75, CRGB::Green,  0, 1.0, 50.0, 60},  // sync
  {52, 150,   75, CRGB::Green,  0, 1.0, 50.0, 60},  // sync + MIT PHYSISCHEM DIFFUSOR
  /*   {53, 150,   75, CRGB::Green,  0, 1.0, 50.0, 60},  // sync
  {54, 2,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {55, 3,   75, CRGB::Orange,  0, 1.0, 22.0, 0},
  {56, 4,   75, CRGB::Black,  0, 1.0, 77.0, 0} */
/*};
*/

// For random color assign ::Black
/* int numLightUpLeds = 1;  // CHANGE IT DEPENDING ON struct of leds!
ledPersonality ledSchemas[1] = {  
  {0, 75,   0, CRGB::Black,  0, 1.0, 100.0, 0}
}; */

// Fading out
/* int numLightUpLeds = 12;  // CHANGE IT DEPENDING ON struct of leds!
ledPersonality ledSchemas[12] = {  
  {0, 75,   0, CRGB::Black,  0, 1.0, 100.0, 0},
  {1, 75,   0, CRGB::Black,  0, 1.0, 100.0, 10},
  {2, 75,   0, CRGB::Black,  0, 1.0, 100.0, 30},
  {3, 75,   0, CRGB::Black,  0, 1.0, 100.0, 50},
  {4, 75,   0, CRGB::Black,  0, 1.0, 100.0, 60},
  {5, 75,   0, CRGB::Black,  0, 1.0, 100.0, 75},
  {6, 75,   0, CRGB::Black,  0, 1.0, 100.0, 82},
  {7, 75,   0, CRGB::Black,  0, 1.0, 100.0, 86},
  {8, 75,   0, CRGB::Black,  0, 1.0, 100.0, 91},
  {9, 75,   0, CRGB::Black,  0, 1.0, 100.0, 95},
  {10, 75,   0, CRGB::Black,  0, 1.0, 100.0, 98},
  {11, 75,   0, CRGB::Black,  0, 1.0, 100.0, 99}
}; */

void setup() {
  Serial.begin(9600);
  delay(333); // 3 second delay for recovery

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
    
    // if its more than 0% on, turn it off
    if(leds[ledNum] && (step - led.offset) % led.trigger == 0 && led.fadeOut == 0) {
        if(led.accuracy == 100.0 || random(0, 100) < led.accuracy) {
          leds[ledNum] = CRGB::Black;  // blackout
        }

      } else if (leds[ledNum] && step > led.lastStepTriggered + led.trigger  && led.fadeOut > 0) {
        fadeTowardColor(leds[ledNum], CRGB::Black, 255 - map(led.fadeOut, 0, 100, 0, 255));

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
