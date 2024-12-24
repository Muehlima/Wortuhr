#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

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

// Struct for LED Patterns
typedef struct {
    size_t size;         // Anzahl der Elemente
    const uint8_t* word; // Pointer auf ein statisches Array
} Word;

// LED Patterns for the different Words
const uint8_t ESISCH_ARRAY[] = {90, 109, 70, 69, 50, 49};
const uint8_t FUEF_ARRAY[] = {29, 10, 9};
const uint8_t ZAEAE_ARRAY[] = {28, 11, 8};
const uint8_t VIURTU_ARRAY[] = {108, 91, 88, 71, 68, 51};
const uint8_t ZWAENZG_ARRAY[] = {107, 92, 87, 72, 67, 52};
const uint8_t AB_ARRAY[] = {106, 93};
const uint8_t VOR_ARRAY[] = {27, 12, 7};
const uint8_t HAUBI_ARRAY[] = {73, 66, 53, 46, 33};
const uint8_t EIS_ARRAY[] = {105, 94, 85};
const uint8_t ZWOEI_ARRAY[] = {74, 65, 54, 45};
const uint8_t DRUE_ARRAY[] = {25, 14, 5};
const uint8_t VIERI_ARRAY[] = {104, 95, 84, 75, 64};
const uint8_t FUEFI_ARRAY[] = {55, 44, 35, 24};
const uint8_t SAECHSI_ARRAY[] = {103, 96, 83, 76, 63, 56};
const uint8_t SIEBNI_ARRAY[] = {43, 36, 23, 16, 3};
const uint8_t ACHTI_ARRAY[] = {102, 97, 82, 77, 62};
const uint8_t NUENI_ARRAY[] = {57, 42, 37, 22};
const uint8_t ZAENI_ARRAY[] = {101, 98, 81, 78};
const uint8_t EUFI_ARRAY[] = {38, 21, 18, 1};
const uint8_t ZWOEUFI_ARRAY[] = {58, 41, 38, 21, 18, 1};

const Word ESISCH = {sizeof(ESISCH_ARRAY) / sizeof(ESISCH_ARRAY[0]), ESISCH_ARRAY};
const Word FUEF = {sizeof(FUEF_ARRAY) / sizeof(FUEF_ARRAY[0]), FUEF_ARRAY};
const Word ZAEAE = {sizeof(ZAEAE_ARRAY) / sizeof(ZAEAE_ARRAY[0]), ZAEAE_ARRAY};
const Word VIURTU = {sizeof(VIURTU_ARRAY) / sizeof(VIURTU_ARRAY[0]), VIURTU_ARRAY};
const Word ZWAENZG = {sizeof(ZWAENZG_ARRAY) / sizeof(ZWAENZG_ARRAY[0]), ZWAENZG_ARRAY};
const Word AB = {sizeof(AB_ARRAY) / sizeof(AB_ARRAY[0]), AB_ARRAY};
const Word VOR = {sizeof(VOR_ARRAY) / sizeof(VOR_ARRAY[0]), VOR_ARRAY};
const Word HAUBI = {sizeof(HAUBI_ARRAY) / sizeof(HAUBI_ARRAY[0]), HAUBI_ARRAY};
const Word EIS = {sizeof(EIS_ARRAY) / sizeof(EIS_ARRAY[0]), EIS_ARRAY};
const Word ZWOEI = {sizeof(ZWOEI_ARRAY) / sizeof(ZWOEI_ARRAY[0]), ZWOEI_ARRAY};
const Word DRUE = {sizeof(DRUE_ARRAY) / sizeof(DRUE_ARRAY[0]), DRUE_ARRAY};
const Word VIERI = {sizeof(VIERI_ARRAY) / sizeof(VIERI_ARRAY[0]), VIERI_ARRAY};
const Word FUEFI = {sizeof(FUEFI_ARRAY) / sizeof(FUEFI_ARRAY[0]), FUEFI_ARRAY};
const Word SAECHSI = {sizeof(SAECHSI_ARRAY) / sizeof(SAECHSI_ARRAY[0]), SAECHSI_ARRAY};
const Word SIEBNI = {sizeof(SIEBNI_ARRAY) / sizeof(SIEBNI_ARRAY[0]), SIEBNI_ARRAY};
const Word ACHTI = {sizeof(ACHTI_ARRAY) / sizeof(ACHTI_ARRAY[0]), ACHTI_ARRAY};
const Word NUENI = {sizeof(NUENI_ARRAY) / sizeof(NUENI_ARRAY[0]), NUENI_ARRAY};
const Word ZAENI = {sizeof(ZAENI_ARRAY) / sizeof(ZAENI_ARRAY[0]), ZAENI_ARRAY};
const Word EUFI = {sizeof(EUFI_ARRAY) / sizeof(EUFI_ARRAY[0]), EUFI_ARRAY};
const Word ZWOEUFI = {sizeof(ZWOEUFI_ARRAY) / sizeof(ZWOEUFI_ARRAY[0]), ZWOEUFI_ARRAY};

// LED Patterns for Minutes in Corners
const uint8_t MIN_ONE_ARRAY[] = {111};
const uint8_t MIN_TWO_ARRAY[] = {111, 110};
const uint8_t MIN_THREE_ARRAY[] = {111, 110, 112};
const uint8_t MIN_FOUR_ARRAY[] = {111, 110, 112, 113};

const Word MIN_ONE = {sizeof(MIN_ONE_ARRAY) / sizeof(MIN_ONE_ARRAY[0]), MIN_ONE_ARRAY};
const Word MIN_TWO = {sizeof(MIN_TWO_ARRAY) / sizeof(MIN_TWO_ARRAY[0]), MIN_TWO_ARRAY};
const Word MIN_THREE = {sizeof(MIN_THREE_ARRAY) / sizeof(MIN_THREE_ARRAY[0]), MIN_THREE_ARRAY};
const Word MIN_FOUR = {sizeof(MIN_FOUR_ARRAY) / sizeof(MIN_FOUR_ARRAY[0]), MIN_FOUR_ARRAY};


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
