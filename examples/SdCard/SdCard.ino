


#ifdef __AVR__
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
#else

#include <FastLED.h>
#include "Arduino.h"

#endif


/// 



#include <FastLED.h>

#include "fx/2d/noisepalette.hpp"
#include "fx/2d/animartrix.hpp"
#include "fx/fx_engine.h"
#include "fx/storage/sd.h"
#include "file_system.h"
#include "ui.h"

#include "file_system.h"

#define LED_PIN 2
#define BRIGHTNESS 96
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

#define MATRIX_WIDTH 22
#define MATRIX_HEIGHT 22

#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)

#ifdef __EMSCRIPTEN__
#define IS_SERPINTINE false
#else
#define IS_SERPINTINE true
#endif


Slider SCALE("SCALE", 20, 20, 100);
Slider SPEED("SPEED", 30, 20, 100);

CRGB leds[NUM_LEDS];
XYMap xyMap(MATRIX_WIDTH, MATRIX_HEIGHT, IS_SERPINTINE);  // No serpentine
NoisePalette noisePalette(xyMap);
Animartrix animartrix(xyMap, POLAR_WAVES);
FxEngine fxEngine(NUM_LEDS);
Checkbox switchFx("Switch Fx", true);

/*

const int CHIP_SELECT_PIN = 5;

FileSystem fs(CHIP_SELECT_PIN);


void setup() {
    Serial.begin(115200);
    if (!fs.begin()) {
        Serial.println("Failed to initialize file system.");
    }
    delay(2000);  // If something ever goes wrong this delay will allow upload.
}

*/

void setup() {
    Serial.begin(115200);
    delay(1000); // sanity delay

    if (!fs.begin()) {
        Serial.println("Failed to initialize file system.");
    }

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip)
        .setScreenMap(MATRIX_WIDTH, MATRIX_HEIGHT);
    FastLED.setBrightness(96);
    noisePalette.lazyInit();
    noisePalette.setPalettePreset(2);
    fxEngine.addFx(noisePalette);
    fxEngine.addFx(animartrix);
}

void loop() {
    noisePalette.setSpeed(SPEED);
    noisePalette.setScale(SCALE);
    EVERY_N_SECONDS(1) {
        if (switchFx) {
            fxEngine.nextFx(500);
        }
    }
    fxEngine.draw(millis(), leds);
    FastLED.show();

    FileHandleRef fh = fs.openRead("data/video.dat");
    if (!fh) {
      Serial.println("Failed to open SD card because sd is null");
    } else {
      fs.close(fh);
    }
}



