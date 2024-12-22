#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  110

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:W
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// LED Patterns for the different Words
const int ESISCH[]  = {90, 109, 70, 69, 50, 49};
const int FUEF[]    = {29, 10, 9};
const int ZAEAE[]   = {28, 11, 8};
const int VIURTU[]  = {108, 91, 88, 71, 68, 51};
const int ZWAENZG[] = {107, 92, 87, 72, 67, 52};
const int VOR[]     = {27, 12, 7};
const int AB[]      = {73, 66, 53, 46, 33};
const int HAUBI[]   = {86, 73, 66, 53, 46, 33};
const int EIS[]     = {105, 94, 85};
const int ZWOEI[]   = {74, 65, 54, 45};
const int DRUE[]    = {25, 14, 5};
const int VIERI[]   = {104, 95, 84, 74, 64};
const int FUEFI[]   = {55, 44, 35, 24};
const int SAECHSI[] = {103, 96, 83, 76, 63, 56};
const int SIEBNI[]  = {43, 36, 23, 16, 3};
const int ACHTI[]   = {102, 97, 82, 77, 62};
const int NUENI[]   = {57, 42, 37, 22};
const int ZAEHNI[]  = {101, 98, 81, 78};
const int EUFI[]    = {38, 21, 18, 1};
const int ZWOEUFI[] = {100, 99, 80, 79, 60, 59};

// LED Patterns for Minutes in Corners
const int MIN_ONE[]   = {111};
const int MIN_TWO[]   = {111, 110};
const int MIN_THREE[] = {111, 110, 112};
const int MIN_FOUR[]  = {111, 110, 112, 113};

const int *Test[] = {ES, ISCH, FUEF, AB, ZAEHNI};
const int Test2[] = {ES, ISCH, FUEF, AB, ZAEHNI};

void setup() {
  // Setup LEDs
  Serial.begin(115200);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.println("Setup Complete");

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < sizeof(Test) / sizeof(Test[0]); i++) {
    showTime(strip.Color(255, 0, 0, 0), Test[i], sizeof(Test[i]) / sizeof(Test[i][0])); // Red
    delay(1000);
  }
  //showTime(strip.Color(  0,   0,   0, 255), EIS, sizeof(EIS) / sizeof(EIS[0])); // True white (not RGB white)



}

*int[], *int[], *int[] build_time_array(int hour, int minute) {
  *int intro[] = {ES, ISCH};
  *int minutes[];
  *int hours[];

  // Get "Minutes" Text
  switch (minute/5)
  {
  case 1:
    minutes = {FUEF, AB};
    break;
  case 2:
    minutes = {ZAEAE, AB};
    break;
  case 3:
    minutes = {VIURTU, AB};
    break;
  case 4: 
    minutes = {ZWAENZG, AB};
    break;  
  case 5:
    minutes = {FUEF, VOR, HAUBI};
    break;
  case 6:
    minutes = {HAUBI};
    break;
  case 7:
    minutes = {FUEF, AB, HAUBI};
    break; 
  case 8: 
    minutes = {ZWAENZG, VOR};
    break;
  case 9:
    minutes = {VIURTU, VOR}; 
    break;
  case 10:  
    minutes = {ZAEAE, VOR};
    break;  
  case 11:  
    minutes = {FUEF, VOR};
    break;
  default:
    break;
  }

  // Get "Hours" Text
  // Add 1 to hour if minute is greater than 25 ("5 vor Haubi XX")
  if minute >= 25 {
    hour++;
  }

  switch (hour%12)
  {
  case 1:
    hours = {EIS};
    break;
  case 2:
    hours = {ZWOEI};
    break;
  case 3:
    hours = {DRUE};
    break;  
  case 4:
    hours = {VIERI};
    break;
  case 5:
    hours = {FUEFI};
    break;
  case 6:
    hours = {SAECHSI};
    break;  
  case 7:
    hours = {SIEBNI};
    break;
  case 8:
    hours = {ACHTI};
    break;
  case 9: 
    hours = {NUENI};
    break;
  case 10:
    hours = {ZAEHNI};
    break;
  case 11:
    hours = {EUFI};
    break;
  case 12:
    hours = {ZWOEUFI};
    break;
  }

  return {intro, minutes, hours};
}

void showTime(uint32_t color, const int pixels[], int size) {
  for (int i = 0; i < size; i++) {
    strip.setPixelColor(pixels[i], color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  } 

}
