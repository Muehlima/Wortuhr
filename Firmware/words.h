#ifndef WORDS_H
#define WORDS_H

// Struct for LED Patterns
typedef struct {
    size_t size;         // Number of elements
    const uint8_t* word; // Pointer to a static array
} Word;

// External declarations for the arrays and words
extern const uint8_t ESISCH_ARRAY[];
extern const Word ESISCH;

extern const uint8_t FUEF_ARRAY[];
extern const Word FUEF;

extern const uint8_t ZAEAE_ARRAY[];
extern const Word ZAEAE;

extern const uint8_t VIURTU_ARRAY[];
extern const Word VIURTU;

extern const uint8_t ZWAENZG_ARRAY[];
extern const Word ZWAENZG;

extern const uint8_t AB_ARRAY[];
extern const Word AB;

extern const uint8_t VOR_ARRAY[];
extern const Word VOR;

extern const uint8_t HAUBI_ARRAY[];
extern const Word HAUBI;

extern const uint8_t EIS_ARRAY[];
extern const Word EIS;

extern const uint8_t ZWOEI_ARRAY[];
extern const Word ZWOEI;

extern const uint8_t DRUE_ARRAY[];
extern const Word DRUE;

extern const uint8_t VIERI_ARRAY[];
extern const Word VIERI;

extern const uint8_t FUEFI_ARRAY[];
extern const Word FUEFI;

extern const uint8_t SAECHSI_ARRAY[];
extern const Word SAECHSI;

extern const uint8_t SIEBNI_ARRAY[];
extern const Word SIEBNI;

extern const uint8_t ACHTI_ARRAY[];
extern const Word ACHTI;

extern const uint8_t NUENI_ARRAY[];
extern const Word NUENI;

extern const uint8_t ZAENI_ARRAY[];
extern const Word ZAENI;

extern const uint8_t EUFI_ARRAY[];
extern const Word EUFI;

extern const uint8_t ZWOEUFI_ARRAY[];
extern const Word ZWOEUFI;

// External declarations for the minute patterns
extern const uint8_t MIN_ONE_ARRAY[];
extern const Word MIN_ONE;

extern const uint8_t MIN_TWO_ARRAY[];
extern const Word MIN_TWO;

extern const uint8_t MIN_THREE_ARRAY[];
extern const Word MIN_THREE;

extern const uint8_t MIN_FOUR_ARRAY[];
extern const Word MIN_FOUR;

#endif // WORDS_H
