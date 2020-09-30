#include <Arduboy2.h>
#include <EEPROM.h>
#include <ArduboyTones.h>

#define NDUR 100
#define SDUR 160//200
#define LDUR 400//500

#define NDUR1 80
#define SDUR1 120//200
#define LDUR1 300//500

#define NDUR2 60
#define SDUR2 80//200
#define LDUR2 200//500

#define NDUR3 40
#define SDUR3 40//200
#define LDUR3 100//500




const uint16_t Score0[] PROGMEM = {
  NOTE_C4H,LDUR, NOTE_REST,NDUR,
  NOTE_B3H,LDUR, NOTE_REST,NDUR,
  NOTE_A3H,LDUR, NOTE_REST,NDUR,
  NOTE_A3H,SDUR, NOTE_REST,NDUR,
  NOTE_B3H,SDUR, NOTE_REST,NDUR,
  NOTE_C4H,SDUR, NOTE_REST,NDUR,
  NOTE_E4H,SDUR, NOTE_REST,NDUR,
  NOTE_C4H,SDUR, NOTE_REST,NDUR,
  NOTE_B3H,SDUR, NOTE_REST,NDUR,
  NOTE_A3H,LDUR, NOTE_REST,NDUR,
  NOTE_B3H,SDUR, NOTE_REST,NDUR,
  NOTE_C4H,SDUR, NOTE_REST,NDUR,
  NOTE_E4H,SDUR, NOTE_REST,NDUR,
  NOTE_E4H,LDUR, NOTE_REST,NDUR,
  NOTE_F4H,SDUR, NOTE_REST,NDUR,
  NOTE_E4H,SDUR, NOTE_REST,NDUR,
  NOTE_D4H,SDUR, NOTE_REST,NDUR,
  NOTE_C4H,SDUR, NOTE_REST,NDUR,
  NOTE_D4H,SDUR, NOTE_REST,NDUR,
  NOTE_D4H,SDUR, NOTE_REST,NDUR,
  NOTE_D4H,LDUR, NOTE_REST,NDUR,
  NOTE_E4H,SDUR, NOTE_REST,NDUR,
  NOTE_D4H,SDUR, NOTE_REST,NDUR,
  NOTE_C4H,SDUR, NOTE_REST,NDUR,
  NOTE_B3H,SDUR, NOTE_REST,NDUR,
  
  
  
  
  TONES_REPEAT
};


const uint16_t Score1[] PROGMEM = {
  NOTE_C4H,LDUR1, NOTE_REST,NDUR1,
  NOTE_B3H,LDUR1, NOTE_REST,NDUR1,
  NOTE_A3H,LDUR1, NOTE_REST,NDUR1,
  NOTE_A3H,SDUR1, NOTE_REST,NDUR1,
  NOTE_B3H,SDUR1, NOTE_REST,NDUR1,
  NOTE_C4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_E4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_C4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_B3H,SDUR1, NOTE_REST,NDUR1,
  NOTE_A3H,LDUR1, NOTE_REST,NDUR1,
  NOTE_B3H,SDUR1, NOTE_REST,NDUR1,
  NOTE_C4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_E4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_E4H,LDUR1, NOTE_REST,NDUR1,
  NOTE_F4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_E4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_D4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_C4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_D4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_D4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_D4H,LDUR1, NOTE_REST,NDUR1,
  NOTE_E4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_D4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_C4H,SDUR1, NOTE_REST,NDUR1,
  NOTE_B3H,SDUR1, NOTE_REST,NDUR1,
  
  
  
  
  TONES_REPEAT
};

const uint16_t Score2[] PROGMEM = {
  NOTE_C4H,LDUR2, NOTE_REST,NDUR2,
  NOTE_B3H,LDUR2, NOTE_REST,NDUR2,
  NOTE_A3H,LDUR2, NOTE_REST,NDUR2,
  NOTE_A3H,SDUR2, NOTE_REST,NDUR2,
  NOTE_B3H,SDUR2, NOTE_REST,NDUR2,
  NOTE_C4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_E4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_C4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_B3H,SDUR2, NOTE_REST,NDUR2,
  NOTE_A3H,LDUR2, NOTE_REST,NDUR2,
  NOTE_B3H,SDUR2, NOTE_REST,NDUR2,
  NOTE_C4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_E4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_E4H,LDUR2, NOTE_REST,NDUR2,
  NOTE_F4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_E4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_D4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_C4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_D4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_D4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_D4H,LDUR2, NOTE_REST,NDUR2,
  NOTE_E4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_D4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_C4H,SDUR2, NOTE_REST,NDUR2,
  NOTE_B3H,SDUR2, NOTE_REST,NDUR2,
  
  
  
  
  TONES_REPEAT
};


/*Images used */
const unsigned char PROGMEM Title[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1F, 0x81, 0x80, 0x00, 0x03, 0x81, 0xC0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 
0x00, 0x70, 0xE1, 0x80, 0x00, 0x01, 0xC3, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 
0x00, 0x60, 0x61, 0x80, 0x00, 0x01, 0xC3, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0xFC, 0x00, 0x01, 0xE7, 0x8E, 
0x38, 0xFD, 0xC7, 0xEE, 0x3C, 0x3C, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0xC6, 0x00, 0x01, 0xE7, 0x86, 
0x18, 0x77, 0x63, 0xBB, 0x18, 0x18, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0x86, 0x00, 0x01, 0xBD, 0x86, 
0x18, 0x66, 0x63, 0x33, 0x0C, 0x30, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0x86, 0x00, 0x01, 0xBD, 0x86, 
0x18, 0x66, 0x63, 0x33, 0x0C, 0x30, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0x86, 0x00, 0x01, 0x99, 0x86, 
0x18, 0x66, 0x63, 0x33, 0x06, 0x60, 0x0C, 0x00, 
0x00, 0xC0, 0x31, 0x86, 0x00, 0x01, 0x99, 0x86, 
0x18, 0x66, 0x63, 0x33, 0x06, 0x60, 0x00, 0x00, 
0x00, 0x60, 0x61, 0x86, 0x00, 0x01, 0x81, 0x86, 
0x18, 0x66, 0x63, 0x33, 0x03, 0xC0, 0x00, 0x00, 
0x00, 0x70, 0xE1, 0x86, 0x01, 0x81, 0x81, 0x86, 
0x38, 0x66, 0x63, 0x33, 0x03, 0xC0, 0x0C, 0x00, 
0x00, 0x1F, 0x83, 0xCF, 0x01, 0x83, 0xC3, 0xC3, 
0xFC, 0xF7, 0x77, 0xBB, 0x81, 0x80, 0x0C, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x1C, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xDE, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x36, 0x00, 0x00, 0x00, 0x2F, 0xE0, 0x00, 0x00, 
0x00, 0x03, 0xFC, 0x0E, 0x00, 0x00, 0x00, 0x00, 
0xFF, 0x80, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00, 
0x00, 0x00, 0x30, 0x1F, 0x00, 0x00, 0x00, 0x01, 
0x22, 0x40, 0x00, 0x00, 0x22, 0x18, 0x00, 0x00, 
0x00, 0x00, 0x30, 0x7F, 0xC0, 0x00, 0x00, 0x02, 
0x22, 0x20, 0x00, 0x00, 0x26, 0x38, 0x00, 0x00, 
0x00, 0x00, 0x30, 0xFF, 0xF0, 0x00, 0x00, 0x04, 
0x41, 0x10, 0x00, 0x00, 0x10, 0xF0, 0x00, 0x00, 
0x00, 0x00, 0x39, 0xFF, 0xFF, 0x40, 0x00, 0x08, 
0x41, 0x08, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 
0x00, 0x00, 0x3F, 0xFF, 0xF9, 0xC0, 0x00, 0x10, 
0x80, 0x84, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x20, 
0x80, 0x83, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 
0xFF, 0xFF, 0x80, 0x00, 0x0E, 0x70, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x80, 0x40, 0x00, 0x01, 0x01, 
0x00, 0x40, 0x40, 0x00, 0x06, 0xFC, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x02, 0x02, 
0x00, 0x40, 0x20, 0x00, 0x07, 0xE0, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x00, 0xC0, 0x00, 0x04, 0x02, 
0x00, 0x20, 0x10, 0x00, 0x03, 0xC0, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x08, 0x04, 
0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x00, 0xC0, 0x00, 0x10, 0x04, 
0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 
0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 
0x00, 0x08, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 
0x00, 0x04, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x18, 0x30, 0x0C, 0xC0, 0x1E, 0x00, 
0x01, 0xC3, 0x80, 0x00, 0x00, 0x78, 0x00, 0x00, 
0x00, 0x00, 0x3C, 0x78, 0x18, 0x60, 0x06, 0x00, 
0x00, 0xE7, 0x00, 0xFF, 0x80, 0xCC, 0x0C, 0xE0, 
0x06, 0x66, 0x24, 0x48, 0x10, 0x21, 0x9E, 0x00, 
0x00, 0x66, 0x03, 0xC3, 0xE1, 0x86, 0x06, 0xE0, 
0x0F, 0xFE, 0x3F, 0xF8, 0x10, 0x20, 0x7F, 0x80, 
0x00, 0x7E, 0x07, 0x60, 0x01, 0x86, 0x07, 0xE0, 
0x1B, 0xBA, 0x1F, 0xF0, 0x10, 0x20, 0x0E, 0x60, 
0x01, 0xFF, 0x86, 0x27, 0xC1, 0x86, 0x07, 0x60, 
0x00, 0x00, 0x0C, 0x60, 0x78, 0x60, 0x0E, 0x00, 
0x01, 0xFF, 0x87, 0x6E, 0xE7, 0xCF, 0x82, 0x60, 
0x00, 0x00, 0x1F, 0xF0, 0xCC, 0x60, 0x0E, 0x00, 
0x00, 0x7E, 0x03, 0xCC, 0x60, 0x00, 0x02, 0x7F, 
0x02, 0x04, 0x3F, 0xF8, 0x84, 0x40, 0x0E, 0x00, 
0x00, 0x66, 0x00, 0x0E, 0xE0, 0x00, 0x02, 0x31, 
0x07, 0xFE, 0x24, 0x48, 0x8C, 0xC0, 0x0E, 0x00, 
0x00, 0xE7, 0x07, 0x87, 0xC7, 0xFF, 0x80, 0x31, 
0x00, 0x00, 0x3C, 0x78, 0xC8, 0xC0, 0x1B, 0x00, 
0x01, 0xC3, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x3F, 
0x00, 0x00, 0x1C, 0x70, 0x79, 0x80, 0x31, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x61, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 
0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t PROGMEM Key[] =
{
    0x00, 0x00, 0x06, 0x79, 0x49, 0x06, 0x00, 0x00,
};
const uint8_t PROGMEM BulletImg[] =
{
    0x00, 0x00, 0xf8, 0xa4, 0xa4, 0xf8, 0x00, 0x00,
};
const uint8_t PROGMEM PointsImg[] =
{
    0x00, 0x00, 0x74, 0x6a, 0x42, 0x68, 0x00, 0x00,
};

const byte PROGMEM player_Right[] =
{
  8, 8,
    0x00, 0x00, 0x02, 0xff, 0xff, 0x92, 0x00, 0x00,
    0x00, 0x00, 0xe2, 0x3f, 0x7f, 0xd2, 0x00, 0x00,
};

const byte PROGMEM player_Left[] =
{
  8, 8,
    0x00, 0x00, 0x92, 0xff, 0xff, 0x02, 0x00, 0x00,
    0x00, 0x00, 0xd2, 0x7f, 0x3f, 0xe2, 0x00, 0x00,
};

const byte PROGMEM player_Up[] =
{
  8, 8,
    0x00, 0x00, 0xda, 0x3f, 0x3f, 0x6a, 0x00, 0x00,
    0x00, 0x00, 0x6a, 0x3f, 0x3f, 0xda, 0x00, 0x00,
};

const byte PROGMEM player_Down[] =
{
  8, 8,
    0x00, 0x00, 0x6a, 0x3d, 0x3d, 0xda, 0x00, 0x00,
    0x00, 0x00, 0xda, 0x3d, 0x3d, 0x6a, 0x00, 0x00,
};

const byte PROGMEM player_Dead[] =
{
  8, 8,
    0xc, 0xc, 0xc, 0xf3, 0xf3, 0xc, 0xc, 0xc,
    0xc, 0xc, 0xc, 0xf3, 0xf3, 0xc, 0xc, 0xc,
};

const byte PROGMEM mummy_Right[] =
{
  8, 8,
    0x00, 0x10, 0xde, 0x4a, 0x7e, 0xfa, 0x10, 0x20,
    0x00, 0x10, 0xde, 0x4a, 0x7e, 0x7a, 0x90, 0x20,
};

const byte PROGMEM mummy_Left[] =
{
  8, 8,
    0x20, 0x10, 0xfa, 0x7e, 0x4a, 0xde, 0x10, 0x00,
    0x20, 0x90, 0x7a, 0x7e, 0x4a, 0xde, 0x10, 0x00,
};

const byte PROGMEM mummy_Up[] =
{
  8, 8,
    0x00, 0x00, 0xda, 0x3f, 0x3f, 0x6a, 0x00, 0x00,
    0x00, 0x00, 0x6a, 0x3f, 0x3f, 0xda, 0x00, 0x00,
};

const byte PROGMEM mummy_Down[] =
{
  8, 8,
    0x00, 0x00, 0x6a, 0x3d, 0x3d, 0xda, 0x00, 0x00,
    0x00, 0x00, 0xda, 0x3d, 0x3d, 0x6a, 0x00, 0x00,
};

const byte PROGMEM mummy_Dead[] =
{
  8, 8,
    0xc, 0xc, 0xc, 0xf3, 0xf3, 0xc, 0xc, 0xc,
    0xc, 0xc, 0xc, 0xf3, 0xf3, 0xc, 0xc, 0xc,
};

enum State{Right,Left,Up,Down,Dead};
enum GameState{Load,Game,NextLevel,Win,Lose,Instructions};
GameState OhMummy;


Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;
byte frame = 0;
byte mumframe = 0;
int maxmummys = 8;
int stuntime = 60;
int JP = 0;
int Level = 5 ;
int StartUp = 0;

#define ANIM_SPEED 4
#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 8
#define X_MAX (WIDTH - PLAYER_WIDTH - 4)
#define Y_MAX (HEIGHT - PLAYER_HEIGHT - 4)
#define EEPROM_START_C1   EEPROM_STORAGE_SPACE_START+1
#define EEPROM_START_C2   EEPROM_START_C1+1
#define EEPROM_SCORE      EEPROM_START_C2+1

void initEEPROM()
{
unsigned char c1 = EEPROM.read(EEPROM_START_C1);
unsigned char c2 = EEPROM.read(EEPROM_START_C2);

if((c1 != 'M')||(c2 != 'V'))
  {
    EEPROM.update(EEPROM_START_C1, 'M');
    EEPROM.update(EEPROM_START_C2, 'V');  
    EEPROM.put(EEPROM_SCORE, (unsigned int)0);
  }  
}





struct Player {
  int x;
  int y;
  int Speed;
  State state;
  const byte *image;
};

struct Mummy {
  int x;
  int y;
  int Speed;
  State state;
  const byte *image;
  int Active;
  int mumframe;
  int stunned;
  int type;
  bool HasBeenStunned;
  int refSpeed;
};

struct Bullet {
  int x;
  int y;
  int Speed;
  State state;
  int Active;  
};

/*allowable vertical and horizontal movement paths (grid)*/
int Vpath[5] = {4,32,60,88,116};
int Hpath[3] = {4,28,52};
int KeyLoc = 0;
int ExitLoc = 0;
int BulletLoc = 0;
int PointsLoc = 0;
int BulletFound = 0;
int PointsFound = 0;
int ExitActive = 0;
int Lives=3;
int BulletQ = 5;
unsigned int Score =0;
unsigned int HiScore = 0;
int UpdateScore =0;
bool mute = false;

/*Background block locations (x,y, active, amount door is closed), where active controls if the player has unlocked the block*/
int block[8][4] = 	{
					{12,12,0,8},
					{40,12,0,8},
					{68,12,0,8},
					{96,12,0,8},
					{12,36,0,8},
					{40,36,0,8},
					{68,36,0,8},
					{96,36,0,8}
					};




const byte *player_images[] = {player_Right,player_Left,player_Up,player_Down,player_Dead};
const byte *mummy_images[] 	= {mummy_Right,mummy_Left,mummy_Up,mummy_Down,mummy_Dead};

Player player 	= {4,4,2,State::Right,player_Right};
Mummy mummy[8] 	= {	
					{116,52,1,State::Right,mummy_Right,1,0,0,0,false,1},
					{60,28,1,State::Left,mummy_Left,0,0,0,1,false,1},
					{32,52,1,State::Up,mummy_Up,0,0,0,1,false,1},
					{88,4,1,State::Down,mummy_Down,0,0,0,0,false,1},
					{88,52,2,State::Right,mummy_Right,0,0,0,0,false,2},
					{32,28,2,State::Right,mummy_Right,0,0,0,0,false,2},
					{116,4,3,State::Right,mummy_Right,0,0,0,0,false,3},
					{116,28,3,State::Right,mummy_Right,0,0,0,0,false,3},
					};

Bullet bullet 	= {0,0,4,State::Right,0};

/*Level number and no of mummys*/
int Levels[10][2]= 	{
					{1,1},
					{2,2},
					{3,2},
					{4,3},
					{5,4},
					{6,4},
					{7,4},
					{8,4},
					{9,5},
					{10,6},
					};



void drawBullet()
{
	if (bullet.Active==1)
	{
		arduboy.drawPixel(bullet.x,bullet.y);
	}
	/*Destroy bullet if it goes off screen*/
	if ((bullet.x<4)||(bullet.x>WIDTH -4)||(bullet.y<4)||(bullet.y>HEIGHT - 4))
	{
		bullet.Active = 0;
	}
}

void drawPlayer()
{
	player.image = player_images[player.state];
	Sprites::drawSelfMasked(player.x,player.y,player.image, frame);
}

void drawMummy(int mum)
{
	if (mummy[mum].Active)
	{
		mummy[mum].image = mummy_images[mummy[mum].state];
		int x = mummy[mum].x;
		int y = mummy[mum].y;
		const byte *img = mummy[mum].image;
		int mumf = mummy[mum].mumframe;
		Sprites::drawSelfMasked(x,y,img,mumf);
	}
}

void drawBorder()   /*Draws background and border*/
{
int borderx = 0;
int bordery = 0;
    
	for(borderx = 0; borderx < 128; borderx = borderx + 4 ) 
	{
		arduboy.drawRect( borderx, 0, 4, 4, WHITE );
		arduboy.drawRect( borderx, 60, 4, 4, WHITE );
    }
    for(bordery = 4; bordery < 60; bordery = bordery + 4 ) 
	{
		arduboy.drawRect( 0, bordery, 4, 4, WHITE );
		arduboy.drawRect( 124, bordery, 4, 4, WHITE );
    }
    if(ExitActive==1)
    {
		arduboy.fillRect( ExitLoc, 0, 8, 4, BLACK );
    }
    for(int r=0;r<8;r++)
    {
        arduboy.fillRect(block[r][0]    ,block[r][1]     ,20,8,WHITE);  
        arduboy.fillRect(block[r][0]    ,block[r][1]  +8 ,7 ,8,WHITE);  
        arduboy.fillRect(block[r][0] +13,block[r][1]  +8 ,7 ,8,WHITE);  
        if (block[r][2]==0)
        {
			arduboy.fillRect(block[r][0] +7 ,block[r][1] +8 ,6 ,7,WHITE);
			arduboy.drawRect(block[r][0] +7 ,block[r][1] +8 ,6 ,8,BLACK);
			arduboy.drawFastHLine(block[r][0] +9 ,block[r][1] +15 ,2,WHITE);

        }
        else
        {
			arduboy.fillRect(block[r][0] +7 ,block[r][1] +8 ,6 ,block[r][3],WHITE);
			arduboy.drawRect(block[r][0] +7 ,block[r][1] +8 ,6 ,8,BLACK);
			block[r][3]--;
			if(block[r][3]<=0)block[r][3] = 0;
        }
        arduboy.drawBitmap(block[KeyLoc][0] +6 ,block[KeyLoc][1] +9,Key ,8 ,8,WHITE);
        arduboy.drawBitmap(block[BulletLoc][0] +6 ,block[BulletLoc][1] +7,BulletImg ,8 ,8,WHITE);
        arduboy.drawBitmap(block[PointsLoc][0] +6 ,block[PointsLoc][1] +8,PointsImg ,8 ,8,WHITE);
    } 
}

int alignV(int objx) /*Check the nearest allowable Vertical path and returns the direction to it, unless the object 
						is too far away*/
{
int delta=1000;
int closestVpath=10;
int res = 0; 
int aLim = 5;

	for (int i=0;i<5;i++)
	{
		res=objx-Vpath[i];
		if (abs(res)<delta)
		{
			delta = abs(res);
			closestVpath = Vpath[i];
		}
	}
/*Return the direction to move in order to align to the nearest path*/  
	if ((objx>closestVpath)&&(objx<closestVpath+aLim))
	{
		return -1;  
	}
	if ((objx<closestVpath)&&(objx>closestVpath-aLim))
	{
		return 1;
	}
	if (objx == closestVpath)
	{
		return 0;  
	}
	return 2;
}

int alignH(int objy)	/*Check the nearest allowable Vertical path and returns the direction to it, unless the object 
						is too far away*/
{
int delta=1000;
int closestHpath=10;
int res = 0; 
int aLim = 5;

	for (int i=0;i<3;i++)
	{
		res=objy-Hpath[i];
		if (abs(res)<delta)
		{
			delta = abs(res);
			closestHpath = Hpath[i];
		}
	}

/*Return the direction to move in order to align to the nearest path*/  
	if ((objy>closestHpath)&&(objy<closestHpath+aLim))
	{
		return(-1);  
	}
	if ((objy<closestHpath)&&(objy>closestHpath-aLim))
	{
		return(1);
	}
	if (objy == closestHpath)
	{
		return(0);  
	}
	return(2);
}


  
void setup()
{
	arduboy.begin();
	Serial.begin(9600);
	arduboy.clear();
	arduboy.setFrameRate(30);
	StartUp = 1;
	OhMummy = GameState::Load;
  sound.tones(Score0);
	initEEPROM();
	EEPROM.get(EEPROM_SCORE,HiScore);
}


void loop() 
{
int distancex = 200;
int distancey = 200;
int alignVOffset = 0;
int alignHOffset = 0;
int DeltaX;
int DeltaY;
int randnum;
int ActivBlock;
int mumnum;
int count=0;

Rect playerRect;

	arduboy.clear();
	arduboy.pollButtons();

	if(OhMummy==GameState::NextLevel)
	{
	  /*Add up how many blocks were activated and add to score*/
	  sound.noTone();
		if (UpdateScore==1)
		{
			for (int r = 0;r<8;r++)
			{
				if (block[r][2] == 1)Score = Score+100;
			}
			UpdateScore = 0;
		}
		
		player.x = 4;
		player.y = 4; 
		  
		mummy[0].x = 116;
		mummy[0].y = 52;
		mummy[1].x = 60;
		mummy[1].y = 28;
		mummy[2].x = 32;
		mummy[2].y = 52;       
		mummy[3].x = 88;
		mummy[3].y = 4;    
		mummy[4].x = 88;
		mummy[4].y = 52;       
		mummy[5].x = 32;
		mummy[5].y = 28;     
		mummy[6].x = 116;
		mummy[6].y = 4;       
		mummy[7].x = 116;
		mummy[7].y = 28;       

		if(Level==11)
		{
			OhMummy=GameState::Win;
		}
		else
		{
			arduboy.setCursor(41,00);
			arduboy.print("Level ");
			arduboy.print(Level);

			arduboy.setCursor(40,15);
			arduboy.print("Lives ");
			arduboy.print(Lives);

			arduboy.setCursor(35,25);
			arduboy.print("Bullets ");
			arduboy.print(BulletQ);

			arduboy.setCursor(41,35);
			arduboy.print("Score ");
			arduboy.print(Score);
			arduboy.setCursor(35,45);
			arduboy.print("HiScore ");
			arduboy.print(HiScore);

			arduboy.setCursor(5,55);
			arduboy.print("Press A to Continue");

			StartUp = 1;

			if (arduboy.justPressed(A_BUTTON))
			{
				UpdateScore = 1;
				OhMummy = GameState::Game;
			}
		}
	}

else if(OhMummy==GameState::Instructions)
	{
		arduboy.setCursor(25,00);
		arduboy.print("Move Around");
		
		arduboy.setCursor(10,15);
		arduboy.print("Open Doors with A");
		
		arduboy.setCursor(25,25);
		arduboy.print("Shoot with B");

    arduboy.setCursor(30,35);
    
    if (mute)
    {
      arduboy.print("Sound: OFF");
    }
    else
    {
      arduboy.print("Sound: ON");
    }
		
		arduboy.setCursor(25,45);
		arduboy.print("HiScore ");
		arduboy.print(HiScore);

		arduboy.setCursor(5,55);
    arduboy.print("Press A to Continue");
		if (arduboy.justPressed(A_BUTTON))
		{
			OhMummy = GameState::Load;
		}
    if (arduboy.justPressed(B_BUTTON))
    {
      if(mute)
      {
       mute = false; 
       sound.tones(Score0); 
      }
      else 
      {
       mute = true;
       sound.noTone();
      }
    }
		
	}

	else if(OhMummy==GameState::Load)
	{
		/*Load screen here*/
		arduboy.drawSlowXYBitmap(0,0,Title,128,64,WHITE);
		 if(!mute)
    {
      if (!sound.playing())
      {
       sound.tones(Score0);
      }
    }
		if (arduboy.justPressed(A_BUTTON))
		{
			Lives = 3;
			Level=1;
			BulletQ =5;
			Score = 0;
			for (int i=1;i<maxmummys;i++)
			{
				mummy[i].Active = 0;
			}
			OhMummy = GameState::NextLevel;
		}
		if (arduboy.justPressed(B_BUTTON))
		{
			OhMummy = GameState::Instructions;
		}
		
	}

	else if(OhMummy==GameState::Win)
	{

     if(!mute)
    {
      if (!sound.playing())
      {
       sound.tones(Score0);
      }
    }
  
		arduboy.setCursor(35,00);
		arduboy.print("You Win");
		arduboy.setCursor(47,10);
		arduboy.print("Yay ");
		arduboy.setCursor(35,25);
		arduboy.print("Score ");
		arduboy.print(Score);

		if (Score>=HiScore)
		{
			HiScore = Score;
			EEPROM.update(EEPROM_START_C1, 'M');
			EEPROM.update(EEPROM_START_C2, 'V');
			EEPROM.put(EEPROM_SCORE,HiScore);
			arduboy.setCursor(20,35);
			arduboy.print("New HiScore ");
			arduboy.print(HiScore);
		}
		else
		{
			arduboy.setCursor(30,35);
			arduboy.print("HiScore ");
			arduboy.print(HiScore);
		}
		arduboy.setCursor(5,55);
		arduboy.print("Press A to Continue");

		if (arduboy.justPressed(A_BUTTON))
		{
			OhMummy = GameState::Load;
		}
	}

	else if(OhMummy==GameState::Lose)
	{
    if(!mute)
    {
      if (!sound.playing())
      {
        sound.tones(Score0);
      }
    }
    	  
		arduboy.setCursor(37,00);
		arduboy.print("You Lose");

		arduboy.setCursor(35,15);
		arduboy.print("Score ");
		arduboy.print(Score);

		if (Score>=HiScore)
		{
			HiScore = Score;
			EEPROM.update(EEPROM_START_C1, 'M');
			EEPROM.update(EEPROM_START_C2, 'V');
			EEPROM.put(EEPROM_SCORE,HiScore);
			arduboy.setCursor(20,25);
			arduboy.print("New HiScore ");
			arduboy.print(HiScore);
		}
		else
		{
			arduboy.setCursor(30,25);
			arduboy.print("HiScore ");
			arduboy.print(HiScore);
		}
			arduboy.setCursor(5,55);
			arduboy.print("Press A to Continue");
		if (arduboy.justPressed(A_BUTTON))
		{
			OhMummy = GameState::Load;
		}
	}

	  
		else if(OhMummy==GameState::Game)
		{
		/*Reset all the level control type stuff*/
    if(!mute)
    {
      if (!sound.playing())
      {
        if(Level<=3)sound.tones(Score0);
        else if(Level<=5)sound.tones(Score1);
        else if(Level<=10)sound.tones(Score2);
      }
    }
		if (StartUp==1)
		{
			BulletFound = 0;
			PointsFound = 0;
			arduboy.initRandomSeed();
			KeyLoc =random(0,7);
			
			do
			{
				BulletLoc = random(0,7);
			}while (BulletLoc == KeyLoc);
			
			do
			{
				PointsLoc = random(0,7);
			}while ((PointsLoc == KeyLoc)||(PointsLoc==BulletLoc));
			
			ExitLoc =random(4,116);
			ExitActive = 0;
			EEPROM.get(EEPROM_SCORE,HiScore);
			
			for (int r = 0;r<8;r++)
			{
				block[r][2] = 0;
				block[r][3] = 8;
			}
			mumnum = Levels[Level-1][1];
			
			for(int m=0;m<mumnum;m++)
			{
				mummy[m].Active = 1;
			}
			StartUp = 0;
		}

		if (!(arduboy.nextFrame())) return;
		arduboy.clear();
		  
		/*Handle player movement inputs, only update the player frame if the player has moved*/
			if ((arduboy.pressed(LEFT_BUTTON))||(arduboy.pressed(RIGHT_BUTTON)))
			{
				Score++;
				alignHOffset = alignH(player.y);
				/*if the player is close to an allowable path gravitate to the path, if not then dont allow horizontal movement*/
				if(alignHOffset<2)
				{
					player.y = player.y +(alignHOffset);

					if (arduboy.pressed(RIGHT_BUTTON))
					{
						player.state = State::Right;
			
						if(player.x < X_MAX)
						{
							player.x = player.x+player.Speed;
							
							if (arduboy.everyXFrames(ANIM_SPEED)) 
							{
								frame++;
							}
						}
					}
					else if (arduboy.pressed(LEFT_BUTTON))
					{
						player.state = State::Left;
			
						if(player.x > 4)
						{
							player.x = player.x-player.Speed;
							
							if (arduboy.everyXFrames(ANIM_SPEED)) 
							{
								frame++;
							}
						}
					}
				}
			}
			else if ((arduboy.pressed(UP_BUTTON))||(arduboy.pressed(DOWN_BUTTON)))
			{
				Score++;
				if(ExitActive==1)
				{
					if (arduboy.pressed(UP_BUTTON)&&(player.y==4)&&(player.x<=ExitLoc+2)&&(player.x>=ExitLoc-2))
					{
						player.state = State::Up;
						Level++;
						Score=Score +500;
						OhMummy = GameState::NextLevel;
					}
				}
			  
				alignVOffset = alignV(player.x);
				/*if the player is close to an allowable path gravitate to the path, if not then dont allow vertical movement*/
				if(alignVOffset<2)
				{
					player.x = player.x +(alignVOffset);
				
					if (arduboy.pressed(UP_BUTTON))
					{
						player.state = State::Up;

						if (player.y > 4)
						{
							player.y = player.y-player.Speed;
							
							if (arduboy.everyXFrames(ANIM_SPEED))
							{
								frame++;
							}    
						}
					}
					else if (arduboy.pressed(DOWN_BUTTON))
					{
						player.state = State::Down;
						
						if (player.y < Y_MAX)
						{
							player.y = player.y+player.Speed;

							if (arduboy.everyXFrames(ANIM_SPEED))
							{
								frame++;
							}
						}
					}
				}
			}

			/*Deal with the mummys*/
			/*Check if the mummy is close to a path*/
			for (int i = 0;i<maxmummys;i++)
			{
				if(mummy[i].Active)
				{
					alignVOffset = alignV(mummy[i].x);
					alignHOffset = alignH(mummy[i].y);
					/*if the mummy is at a crossroads allow a direction change or if type 1 take a random turn*/
					if ((alignHOffset==0)&&(alignVOffset==0))
					{
						if(mummy[i].type==1)
						{
							arduboy.initRandomSeed();
							randnum =random(1,12);
						   if(randnum==1)mummy[i].state = State::Right;
						   if(randnum==2)mummy[i].state = State::Left;
						   if(randnum==3)mummy[i].state = State::Up;
						   if(randnum==4)mummy[i].state = State::Down;
						   if(randnum==5)mummy[i].type = 0;
						}
						else
						{
							arduboy.initRandomSeed();
							randnum =random(1,12);

							if(randnum==1)mummy[i].type = 1;

							/*decide which is the shorter route to the player_Left*/
							DeltaX = (mummy[i].x - player.x);
							DeltaX = abs(DeltaX);
							DeltaY = (mummy[i].y - player.y);
							DeltaY = abs(DeltaY);
					  
							if (DeltaX>DeltaY)
							{
								if(mummy[i].x < player.x)
								{
									mummy[i].state = State::Right;
								}
								else if(mummy[i].x > player.x)
								{
									mummy[i].state = State::Left;
								}
							}
							else
							{
								if(mummy[i].y < player.y)
								{
									mummy[i].state = State::Down;
								}
								else if(mummy[i].y > player.y)
								{
									mummy[i].state = State::Up;
								}
							} 
						}
					}
					/*once direction is decided move in that direction*/
					if(mummy[i].state == State::Right)
					{
						mummy[i].x = mummy[i].x+mummy[i].Speed;
					}
					if(mummy[i].state == State::Left)
					{
						mummy[i].x = mummy[i].x-mummy[i].Speed;
					}
					if(mummy[i].state == State::Down)
					{
						mummy[i].y = mummy[i].y+mummy[i].Speed;
					}
					if(mummy[i].state == State::Up)
					{
						mummy[i].y = mummy[i].y-mummy[i].Speed;
					}
					/*limit the movement within the bounds of the screen*/
					if(mummy[i].x<4) 		mummy[i].x=4;
					if(mummy[i].x>X_MAX) 	mummy[i].x=X_MAX;
					if(mummy[i].y<4)		mummy[i].y=4;
					if(mummy[i].y>Y_MAX) 	mummy[i].y=Y_MAX;
				}
			}	

			/*does the player shoot?*/
			if (arduboy.pressed(B_BUTTON)&&(bullet.Active==0)&&(BulletQ>0))
			{
				BulletQ--;
				if (BulletQ<0)BulletQ = 0;
				bullet.Active = 1;
				bullet.x = player.x+4;
				bullet.y = player.y+4;
				/*set bullet direction to same as player*/
				bullet.state = player.state;
			}
			
			if (bullet.Active)
			{
				if (bullet.state == State::Right)
				{
					bullet.x = bullet.x+bullet.Speed;
				}
				if (bullet.state == State::Left)
				{
					bullet.x = bullet.x-bullet.Speed;
				}
				if (bullet.state == State::Down)
				{
					bullet.y = bullet.y+bullet.Speed;
				}
				if (bullet.state == State::Up)   
				{
					bullet.y = bullet.y-bullet.Speed;
				}
				drawBullet();  
			}

			/*Check to see if treasure is activated*/
			/*control the mummys for testing*/
			if (arduboy.pressed(A_BUTTON))
			{
				playerRect = {player.x,player.y,8,8};
				for (int i =0;i<8;i++)
				{
					Rect BlockRect = {block[i][0]+7,block[i][1]+20,4,8};

					if (arduboy.collide(playerRect,BlockRect))
					{
						block[i][2] = 1;

						if (i==KeyLoc) ExitActive = 1;
						if (i==BulletLoc)
						{
							if(BulletFound==0)
							{
								BulletQ++;
								BulletFound=1;
							}
						}
						if (i==PointsLoc)
						{
							if(PointsFound==0)
							{
								Score=Score+1000;
								PointsFound = 1;
							}
						}
					}
				}
			}

		/*Collision detection*/
			for (int i = 0;i<maxmummys;i++)
			{
				if(mummy[i].Active)
				{
					Rect playerRect = {player.x,player.y,4,8};
					Rect mummyRect  = {mummy[i].x,mummy[i].y,6,8};
					Rect bulletRect = {bullet.x,bullet.y,2,2};

					if ((bullet.Active)&&(arduboy.collide(bulletRect, mummyRect)))
					{
						bullet.Active = 0;
						mummy[i].Speed = 0;
						mummy[i].stunned = stuntime;
            mummy[i].HasBeenStunned = true;
					}

					if (mummy[i].stunned>0)
					{
						mummy[i].stunned--;  
					}
					else 
					{
						mummy[i].stunned = 0;
           if(mummy[i].HasBeenStunned)
           {
						mummy[i].Speed = 1;
           }
           else
           {
            mummy[i].Speed = mummy[i].refSpeed;
           }
					}
					
					if (arduboy.collide(playerRect, mummyRect))
					{
						Lives--;
						if(Lives<=0)
						{
              Lives = 0;
							OhMummy = GameState::Lose;
              sound.noTone();
						}
						else
						{
							OhMummy = GameState::NextLevel;
						}
					}

					if (mummy[i].Speed>0)
					{
						if (arduboy.everyXFrames(ANIM_SPEED))
						{
							mummy[i].mumframe++;
						}
					}
					if (mummy[i].mumframe>1)
					{
						mummy[i].mumframe = 0;
					}
				}
			}

			if (frame>1)
			{
				frame = 0;
			}

			for (int i = 0;i<maxmummys;i++)
			{
				if(mummy[i].Active)
				{
					drawMummy(i);
				}
			}

			drawPlayer();
			drawBorder();
		}
	arduboy.display();
}
