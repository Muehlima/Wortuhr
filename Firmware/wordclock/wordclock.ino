#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "words.h"


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  110  // Max Value 255 (uint8_t)

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


void setup() {
  // Setup LEDs
  Serial.begin(115200);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.println("Setup Complete");
}

void loop() {
  // NEW APPROACH
  const Word* timeWords[10]; // Platz für 10 Wörter
  size_t wordCount;


  // Build Time Words for current time
  uint8_t minute = 0;  // Test values
  uint8_t hour = 0;    // Test values

  for (minute = 0; minute < 60; minute+=5) {
    build_time_words(hour, minute, timeWords, &wordCount);
    show_time(timeWords, wordCount);
    delay(5000);
  }
  minute = 0;
  for (hour = 0; hour < 12; hour++) {
    build_time_words(hour, minute, timeWords, &wordCount);
    show_time(timeWords, wordCount);
    delay(5000);
  }
  // build_time_words(hour, minute, timeWords, &wordCount);
  // show_time(timeWords, wordCount);
 
}

void build_time_words(int hour, int minute, const Word *result[], size_t *wordCount)
{
  *wordCount = 0; // Zähler zurücksetzen

  // Beispiel für Zeitkombinationen
  result[(*wordCount)++] = &ESISCH; // "Es isch"

  // Minuten abhängig von der Zeit hinzufügen
  switch (minute / 5)
  {
  case 1:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &AB;   // "ab"
    break;
  case 2:
    result[(*wordCount)++] = &ZAEAE; // "Zäae"
    result[(*wordCount)++] = &AB;    // "ab"
    break;
  case 3:
    result[(*wordCount)++] = &VIURTU; // "Viertu"
    result[(*wordCount)++] = &AB;     // "ab"
    break;
  case 4:
    result[(*wordCount)++] = &ZWAENZG; // "Zwänzg"
    result[(*wordCount)++] = &AB;      // "ab"
    break;
  case 5:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &VOR;  // "vor"
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 6:
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 7:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &AB;   // "ab"
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 8:
    result[(*wordCount)++] = &ZWAENZG; // "Zwänzg"
    result[(*wordCount)++] = &VOR;     // "vor"
    break;
  case 9:
    result[(*wordCount)++] = &VIURTU; // "Viertu"
    result[(*wordCount)++] = &VOR;    // "vor"
    break;
  case 10:
    result[(*wordCount)++] = &ZAEAE; // "Zäae"
    result[(*wordCount)++] = &VOR;   // "vor"
    break;
  case 11:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &VOR;  // "vor"
    break;
  default:
    break;
  }

  // Stunden hinzufügen
  if (minute >= 25) // Ab 25 Minuten wird die nächste Stunde angezeigt
  {
    hour++;
  }

  switch (hour % 12)
  {
  case 0:
    result[(*wordCount)++] = &ZWOEUFI;
    break; // "Zwoeufi"  
  case 1:
    result[(*wordCount)++] = &EIS;
    break; // "Eis"
  case 2:
    result[(*wordCount)++] = &ZWOEI;
    break; // "Zwoei"
  case 3:
    result[(*wordCount)++] = &DRUE;
    break; // "Drü"
  case 4:
    result[(*wordCount)++] = &VIERI;
    break; // "Vieri"
  case 5:
    result[(*wordCount)++] = &FUEFI;
    break; // "Füfi"
  case 6:
    result[(*wordCount)++] = &SAECHSI;
    break; // "Sächsi"
  case 7:
    result[(*wordCount)++] = &SIEBNI;
    break; // "Siebni"
  case 8:
    result[(*wordCount)++] = &ACHTI;
    break; // "Achti"
  case 9:
    result[(*wordCount)++] = &NUENI;
    break; // "Nueni"
  case 10:
    result[(*wordCount)++] = &ZAENI;
    break; // "Zaeni"
  case 11:
    result[(*wordCount)++] = &EUFI;
    break; // "Eufi"
  }
}

void show_time(const Word *words[], size_t wordCount) {
  // Initialize all LEDs to off
  strip.clear();
  strip.show();

  // Set LEDs for each word
  for (size_t i = 0; i < wordCount; i++) {
      const Word* word = words[i];
      for (size_t j = 0; j < word->size; j++) {
          strip.setPixelColor(word->word[j], strip.Color(0, 0, 0, 255)); // True white (not RGB white)
      } 
  }
  strip.show();
}
