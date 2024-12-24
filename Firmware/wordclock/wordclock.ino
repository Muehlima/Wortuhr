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
  size_t size;
  uint8_t word[];
} Word;

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
