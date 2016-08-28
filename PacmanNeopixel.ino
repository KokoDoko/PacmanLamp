#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LAMPS 30

// adafruit init for this particular strip (see adafruit.com)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LAMPS, PIN, NEO_GRB + NEO_KHZ800);

// we are lighting 15 leds at the same time, setting the max brightness lower
// allows us to light all the leds from an arduino board without separate power source
// (15 leds * 33mA = 495 mA)
void setup() {
  strip.begin();
  strip.setBrightness(80);    // overall brightness can be 0 to 255
  strip.show();               // Initialize all pixels to 'off'
}

void loop() {
  // white food pixels
  setFood();
  delay(1500);
  
  // pacman eats the food
  eatFood();
  delay(1800);

  // pacman is chased by ghosts
  chasedByGhosts();
  delay(1800);
}

// the max brightness here can also be reduced to avoid using too much amps
void setFood() {
  // fade in
  for(int br=0; br<200; br++) {
    uint32_t white = strip.Color(br, br, br);
    for(int i=0; i<strip.numPixels(); i+=2) {
        strip.setPixelColor(i, white); 
    }
    strip.show();
    delay(5);
  }
}

void eatFood(){
  uint32_t yellow = strip.Color(255, 255, 0);
  uint32_t off = strip.Color(0, 0, 0);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, yellow);

      if(i>0){
        strip.setPixelColor(i-1, off);
      }
      
      strip.show();
      delay(100);
  }
  strip.setPixelColor(strip.numPixels()-1, off);
  strip.show();
  delay(100);
}

void chasedByGhosts() {
  uint32_t yellow = strip.Color(255, 255, 0);
  uint32_t clyde = strip.Color(249, 154, 0);
  uint32_t blinky = strip.Color(244, 7, 8);
  uint32_t pinky = strip.Color(249, 161, 166);
  uint32_t inky = strip.Color(48, 218, 219);

  // run back
  for(int i=strip.numPixels(); i>-14; i--) {
      // pacman - i is position, 0 is ruimte tussen pacman en kleur (elke ghost iets verder)
      checkLed(yellow, i, 0);

      checkLed(yellow, i, 0);
      checkLed(clyde, i, 6);
      checkLed(blinky, i, 8);
      checkLed(pinky, i, 10);
      checkLed(inky, i, 12);

      strip.show();
      delay(100);
  }
}

// check if this position is within the led strip, if yes then show the color
void checkLed(uint32_t color, int i, int offset) {
  int pos = i + offset;

  if(pos < strip.numPixels() && pos > -1){
     strip.setPixelColor(pos, color); 
  }
  // opvolgende uitzetten
  if(pos+1 < strip.numPixels() && pos+1 > -1){
     strip.setPixelColor(pos+1, strip.Color(0, 0, 0));
  } 
}
