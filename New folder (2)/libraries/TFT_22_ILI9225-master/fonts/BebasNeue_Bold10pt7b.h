const uint8_t BebasNeue_Bold10pt7bBitmaps[] PROGMEM = {
  0xF0, 0x07, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x30, 0x30, 0x60,
  0x60, 0x60, 0xC0, 0x7B, 0xFC, 0xF3, 0xCF, 0x3C, 0xF3, 0xCF, 0x3C, 0xF3,
  0xFD, 0xE0, 0x33, 0xFF, 0x33, 0x33, 0x33, 0x33, 0x33, 0x7B, 0xFC, 0xF3,
  0xCC, 0x31, 0xCE, 0x71, 0x8C, 0x30, 0xFF, 0xF0, 0x7B, 0xFC, 0xF3, 0x0C,
  0x33, 0x8F, 0x0C, 0x3C, 0xF3, 0xFD, 0xE0, 0x0E, 0x0E, 0x1E, 0x1E, 0x36,
  0x36, 0x66, 0x66, 0x66, 0xFF, 0xFF, 0x06, 0x06, 0x06, 0xFF, 0xFC, 0x30,
  0xFB, 0xFC, 0xF3, 0x0F, 0x3C, 0xF3, 0xFD, 0xE0, 0x7B, 0xFC, 0xF3, 0xC3,
  0xEF, 0xF3, 0xCF, 0x3C, 0xF3, 0xFD, 0xE0, 0xFF, 0xF0, 0xC3, 0x1C, 0x61,
  0x86, 0x30, 0xC3, 0x1C, 0x61, 0x80, 0x7B, 0xFC, 0xF3, 0xCF, 0x3F, 0xFF,
  0xCF, 0x3C, 0xF3, 0xFD, 0xE0, 0x7B, 0xFC, 0xF3, 0xCF, 0x3C, 0xFF, 0xFC,
  0x3C, 0xF3, 0xFD, 0xE0 };

const GFXglyph BebasNeue_Bold10pt7bGlyphs[] PROGMEM = {
  {     0,   2,   2,   4,    1,   -1 },   // 0x2E '.'
  {     1,   8,  14,   8,    0,  -13 },   // 0x2F '/'
  {    15,   6,  14,   8,    1,  -13 },   // 0x30 '0'
  {    26,   4,  14,   8,    2,  -13 },   // 0x31 '1'
  {    33,   6,  14,   8,    1,  -13 },   // 0x32 '2'
  {    44,   6,  14,   8,    1,  -13 },   // 0x33 '3'
  {    55,   8,  14,   8,    0,  -13 },   // 0x34 '4'
  {    69,   6,  14,   8,    1,  -13 },   // 0x35 '5'
  {    80,   6,  14,   8,    1,  -13 },   // 0x36 '6'
  {    91,   6,  14,   8,    1,  -13 },   // 0x37 '7'
  {   102,   6,  14,   8,    1,  -13 },   // 0x38 '8'
  {   113,   6,  14,   8,    1,  -13 } }; // 0x39 '9'

const GFXfont BebasNeue_Bold10pt7b PROGMEM = {
  (uint8_t  *)BebasNeue_Bold10pt7bBitmaps,
  (GFXglyph *)BebasNeue_Bold10pt7bGlyphs,
  0x2E, 0x39, 20 };

// Approx. 215 bytes