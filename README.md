# blipsblops
Ardunio controller for RGB LED strips to simulate old timey sci fi computers. Use in movie props or just about anywhere.

Works with APA102 and WS2812 RGB LED strips.

# Video
![video](./readme/example.gif)

# Workflow

You can assign any LED on your strip a rhythm, a color, and various other settings.
You do not have to declare every single LED, its possible to just define what you need to blip and to blop.

The rhythm is defined for each LED in an array of structs.
Each LED has a `trigger` defined, e.g. `3`. This LED triggers every *n*th loop which is a multiple of `3`.
`3` means that this LED triggers every *third* loop to be either *on* or *off*. A `loop()` is about as fast as your `speed` variable.

So if you want a simple single flashing LED that triggers every second either on or off:
- Set `speed` to `1000` (milliseconds)
- Set the `trigger` of your LED to `1`

If you want to fade out this led, you 
- Set `speed` to `15` (milliseconds)
- Set the `trigger` of your LED to `67` (1000/15=66.6)
- Set `fadeOut` of your LED to `50`

As the fade out logic needs the `speed` variable to fade out the LEDs, set it to `15`, which is the sweet spot for dimming. Calculate how many loops it takes for the trigger to reach *1000* (it takes ~67 loops @ 15ms to reach 1 second).

Note: A "fade in" mode is not implemented.

### All the options per LED

```C++
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
```

## Random color
For a random color each loop assign color CRGB::Black.
Each loop where the trigger of this LED is firing, a random color will be chosen from your `colorSpace[]` array.
```C++
  {0, 75,   0, CRGB::Black,  0, 1.0, 100.0, 0}
```


## Var. ledSchemas examples

Walking lights:
```C++
int numLightUpLeds = 20;
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
};
```

Various random LEDs:
```C++
int numLightUpLeds = 14;
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
};
```

Random Flickering blips and blobs:
```C++
int numLightUpLeds = 20;
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
};
```

Massive:
```C++
int numLightUpLeds = 53;
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
  {20, 33,   0, CRGB::Orange,  0, 1.0, 100.0, 90},
  {21, 66,   25, CRGB::White,  0, 2.0, 100.0, 90},
  {22, 125,   50, CRGB::White,  0, 4.0, 100.0, 90},
  {23, 50,   0, CRGB::White,  0, 1.0, 100.0, 90},
  {24, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0},
  {25, 6,   0, CRGB::Red,  0, 1.0, 100.0, 0}, 
  {26, 18,   0, CRGB::Green,  0, 1.0, 100.0, 0}, 
  {27, 12,   0, CRGB::Green,  0, 1.0, 88.0, 0},
  {28, 6,   25, CRGB::Orange,  0, 2.0, 55.0, 50},
  {29, 3,   50, CRGB::White,  0, 4.0, 33.0, 90},
  {30, 3,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {31, 9,   75, CRGB::White,  0, 1.0, 77.0, 90},
  {32, 9,   75, CRGB::White,  0, 1.0, 88.0, 90},
  {33, 333,   75, CRGB::White,  0, 1.0, 88.0, 90},  // slowpoke

  // 18 stk LEDs: 34-52 "Motherboard"
  {34, 100,   75, CRGB::Green,  0, 1.0, 100.0, 99},  // slowly blinking, fade out
  {35, 3,   75, CRGB::Orange,  0, 1.0, 22.0, 0},
  {36, 4,   75, CRGB::Black,  0, 1.0, 77.0, 0},
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
  {52, 150,   75, CRGB::Green,  0, 1.0, 50.0, 60},  // sync
  {54, 2,   50, CRGB::Black,  0, 4.0, 33.0, 50},
  {55, 3,   75, CRGB::Orange,  0, 1.0, 22.0, 0},
  {56, 4,   75, CRGB::Black,  0, 1.0, 77.0, 0}
};
```

Fading out:
```C++
int numLightUpLeds = 12;
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
};
```


# Beware: Flickering on camera when using fadeOut options

If you set the `brightness` to anything other than *255* ("max") or set `fadeout` to anything other than *0* ("immediately black out"), be prepared to see flickering on camera, because this uses PMW for dimming/fading out.
