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
const uint8_t HAUBI_ARRAY[] = {86, 73, 66, 53, 46, 33};
const uint8_t EIS_ARRAY[] = {105, 94, 85};
const uint8_t ZWOEI_ARRAY[] = {74, 65, 54, 45};
const uint8_t DRUE_ARRAY[] = {25, 14, 5};
const uint8_t VIERI_ARRAY[] = {104, 95, 84, 74, 64};
const uint8_t FUEFI_ARRAY[] = {55, 44, 35, 24};
const uint8_t SAECHSI_ARRAY[] = {103, 96, 83, 76, 63, 56};
const uint8_t SIEBNI_ARRAY[] = {43, 36, 23, 16, 3};
const uint8_t ACHTI_ARRAY[] = {102, 97, 82, 77, 62};
const uint8_t NUENI_ARRAY[] = {57, 42, 37, 22};
const uint8_t ZAENI_ARRAY[] = {101, 98, 81, 78};
const uint8_t EUFI_ARRAY[] = {38, 21, 18, 1};
const uint8_t ZWOEUFI_ARRAY[] = {100, 99, 80, 79, 60, 59};

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



// LED Patterns for the different Words
const Word ESISCH = {6, {90, 109, 70, 69, 50, 49}};
const Word FUEF = {3, {29, 10, 9}};
const Word ZAEAE = {3, {28, 11, 8}};
const Word VIURTU = {6, {108, 91, 88, 71, 68, 51}};
const Word ZWAENZG = {6, {107, 92, 87, 72, 67, 52}};
const Word AB = {2, {106, 93}};
const Word VOR = {3, {27, 12, 7}};
const Word HAUBI = {6, {86, 73, 66, 53, 46, 33}};
const Word EIS = {3, {105, 94, 85}};
const Word ZWOEI = {4, {74, 65, 54, 45}};
const Word DRUE = {3, {25, 14, 5}};
const Word VIERI = {5, {104, 95, 84, 74, 64}};
const Word FUEFI = {4, {55, 44, 35, 24}};
const Word SAECHSI = {6, {103, 96, 83, 76, 63, 56}};
const Word SIEBNI = {5, {43, 36, 23, 16, 3}};
const Word ACHTI = {5, {102, 97, 82, 77, 62}};
const Word NUENI = {4, {57, 42, 37, 22}};
const Word ZAENI = {4, {101, 98, 81, 78}};
const Word EUFI = {4, {38, 21, 18, 1}};
const Word ZWOEUFI = {6, {100, 99, 80, 79, 60, 59}};

// LED Patterns for Minutes in Corners
const Word MIN_ONE = {1, {111}};
const Word MIN_TWO = {2, {111, 110}};
const Word MIN_THREE = {3, {111, 110, 112}};
const Word MIN_FOUR = {4, {111, 110, 112, 113}};


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

  // for (int i = 0; i < sizeof(Test) / sizeof(Test[0]); i++) {
  //   showTime(strip.Color(255, 0, 0, 0), Test[i], sizeof(Test[i]) / sizeof(Test[i][0])); // Red
  //   delay(1000);
  // }
  //showTime(strip.Color(  0,   0,   0, 255), EIS, sizeof(EIS) / sizeof(EIS[0])); // True white (not RGB white)

  //Serial.println(Test);
  //Serial.println(Test2);

  int currentHour = 10; // Beispielwerte
  int currentMinute = 23;

  Word timeArray = build_time_struct(currentHour, currentMinute);

  // Zeige die Zeit an
  showTime(strip.Color(0, 0, 0, 255), timeArray.word, timeArray.size); // True white (not RGB white)

  delay(10000); // Wartezeit (1 Sekunde)
}

Word build_time_struct(int hour, int minute)
{
  Word* wordArray = (Word*)malloc(10 * sizeof(Word)); // Platz für bis zu 10 Wörter (anpassbar)
  int wordCount = 0;         // Anzahl der Wörter
  wordArray[wordCount++] = ESISCH;

  // Get "Minutes" Text
  switch (minute / 5)
  {
  case 1:
    wordArray[wordCount++] = FUEF;
    wordArray[wordCount++] = AB;
    break;
  case 2:
    wordArray[wordCount++] = ZAEAE;
    wordArray[wordCount++] = AB;
    break;
  case 3:
    wordArray[wordCount++] = VIURTU;
    wordArray[wordCount++] = AB;
    break;
  case 4:
    wordArray[wordCount++] = ZWAENZG;
    wordArray[wordCount++] = AB;
    break;
  case 5:
    wordArray[wordCount++] = FUEF;
    wordArray[wordCount++] = VOR;
    wordArray[wordCount++] = HAUBI;
    break;
  case 6:
    wordArray[wordCount++] = HAUBI;
    break;
  case 7:
    wordArray[wordCount++] = FUEF;
    wordArray[wordCount++] = AB;
    wordArray[wordCount++] = HAUBI;
    break;
  case 8:
    wordArray[wordCount++] = ZWAENZG;
    wordArray[wordCount++] = VOR;
    break;
  case 9:
    wordArray[wordCount++] = VIURTU;
    wordArray[wordCount++] = VOR;
    break;
  case 10:
    wordArray[wordCount++] = ZAEAE;
    wordArray[wordCount++] = VOR;
    break;
  case 11:
    wordArray[wordCount++] = FUEF;
    wordArray[wordCount++] = VOR;
    break;
  default:
    break;
  }

  // Get "Hours" Text
  // Add 1 to hour if minute is greater than 25 ("5 vor Haubi XX")
  if (minute >= 25) {
    hour++;
  }

  switch (hour % 12)
  {
  case 1:
    wordArray[wordCount++] = EIS;
    break;
  case 2:
    wordArray[wordCount++] = ZWOEI;
    break;
  case 3:
    wordArray[wordCount++] = DRUE;
    break;
  case 4:
    wordArray[wordCount++] = VIERI;
    break;
  case 5:
    wordArray[wordCount++] = FUEFI;
    break;
  case 6:
    wordArray[wordCount++] = SAECHSI;
    break;
  case 7:
    wordArray[wordCount++] = SIEBNI;
    break;
  case 8:
    wordArray[wordCount++] = ACHTI;
    break;
  case 9:
    wordArray[wordCount++] = NUENI;
    break;
  case 10:
    wordArray[wordCount++] = ZAENI;
    break;
  case 11:
    wordArray[wordCount++] = EUFI;
    break;
  case 12:
    wordArray[wordCount++] = ZWOEUFI;
    break;
  }

  // Inhalte der Wörter in das finale Array kopieren
  // Get Size of the final Array
  size_t totalSize = 0;
  for (int i = 0; i < wordCount; i++)
  {
    totalSize += wordArray[i].size;
  }

  Word time_struct;
  time_struct.size = totalSize;



  int bufferSize = 0;
  for (int i = 0; i < wordCount; i++)
  {
    for (int j = 0; j < wordArray[i].size; j++)
    {
      time_struct.word[bufferSize++] = wordArray[i].word[j];
    }
  }

  free(wordArray); // Free allocated memory
  return time_struct;
  
  
}

void showTime(uint32_t color, uint8_t pixels[], int size) {
  for (int i = 0; i < size; i++) {
    strip.setPixelColor(pixels[i], color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  } 

}
