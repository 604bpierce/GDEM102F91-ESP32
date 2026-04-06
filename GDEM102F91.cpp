#include "GDEM102F91.h"

// ─── 6x8 Font (ASCII 32–126) ─────────────────────────────────────────────────
// Each character is 6 bytes wide x 8 pixels tall (1 bit per pixel, MSB first)
static const uint8_t FONT6x8[][6] PROGMEM = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, //  (32)
  { 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, // ! (33)
  { 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, // " (34)
  { 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, // # (35)
  { 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, // $ (36)
  { 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, // % (37)
  { 0x36, 0x49, 0x55, 0x22, 0x50, 0x00 }, // & (38)
  { 0x00, 0x05, 0x03, 0x00, 0x00, 0x00 }, // ' (39)
  { 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, // ( (40)
  { 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, // ) (41)
  { 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00 }, // * (42)
  { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, // + (43)
  { 0x00, 0x50, 0x30, 0x00, 0x00, 0x00 }, // , (44)
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, // - (45)
  { 0x00, 0x60, 0x60, 0x00, 0x00, 0x00 }, // . (46)
  { 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, // / (47)
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0 (48)
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1 (49)
  { 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2 (50)
  { 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3 (51)
  { 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, // 4 (52)
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5 (53)
  { 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6 (54)
  { 0x01, 0x71, 0x09, 0x05, 0x03, 0x00 }, // 7 (55)
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8 (56)
  { 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9 (57)
  { 0x00, 0x36, 0x36, 0x00, 0x00, 0x00 }, // : (58)
  { 0x00, 0x56, 0x36, 0x00, 0x00, 0x00 }, // ; (59)
  { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, // < (60)
  { 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, // = (61)
  { 0x41, 0x22, 0x14, 0x08, 0x00, 0x00 }, // > (62)
  { 0x02, 0x01, 0x51, 0x09, 0x06, 0x00 }, // ? (63)
  { 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00 }, // @ (64)
  { 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00 }, // A (65)
  { 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // B (66)
  { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, // C (67)
  { 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00 }, // D (68)
  { 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // E (69)
  { 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // F (70)
  { 0x3E, 0x41, 0x49, 0x49, 0x7A, 0x00 }, // G (71)
  { 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, // H (72)
  { 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, // I (73)
  { 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, // J (74)
  { 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // K (75)
  { 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // L (76)
  { 0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00 }, // M (77)
  { 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // N (78)
  { 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // O (79)
  { 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // P (80)
  { 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, // Q (81)
  { 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // R (82)
  { 0x46, 0x49, 0x49, 0x49, 0x31, 0x00 }, // S (83)
  { 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00 }, // T (84)
  { 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // U (85)
  { 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // V (86)
  { 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // W (87)
  { 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // X (88)
  { 0x07, 0x08, 0x70, 0x08, 0x07, 0x00 }, // Y (89)
  { 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // Z (90)
  { 0x00, 0x7F, 0x41, 0x41, 0x00, 0x00 }, // [ (91)
  { 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, // \ (92)
  { 0x00, 0x41, 0x41, 0x7F, 0x00, 0x00 }, // ] (93)
  { 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, // ^ (94)
  { 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, // _ (95)
  { 0x00, 0x01, 0x02, 0x04, 0x00, 0x00 }, // ` (96)
  { 0x20, 0x54, 0x54, 0x54, 0x78, 0x00 }, // a (97)
  { 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00 }, // b (98)
  { 0x38, 0x44, 0x44, 0x44, 0x20, 0x00 }, // c (99)
  { 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00 }, // d (100)
  { 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, // e (101)
  { 0x08, 0x7E, 0x09, 0x01, 0x02, 0x00 }, // f (102)
  { 0x08, 0x54, 0x54, 0x54, 0x3C, 0x00 }, // g (103)
  { 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, // h (104)
  { 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00 }, // i (105)
  { 0x20, 0x40, 0x44, 0x3D, 0x00, 0x00 }, // j (106)
  { 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, // k (107)
  { 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, // l (108)
  { 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00 }, // m (109)
  { 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, // n (110)
  { 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, // o (111)
  { 0x7C, 0x14, 0x14, 0x14, 0x08, 0x00 }, // p (112)
  { 0x08, 0x14, 0x14, 0x18, 0x7C, 0x00 }, // q (113)
  { 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, // r (114)
  { 0x48, 0x54, 0x54, 0x54, 0x20, 0x00 }, // s (115)
  { 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00 }, // t (116)
  { 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, // u (117)
  { 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, // v (118)
  { 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, // w (119)
  { 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, // x (120)
  { 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00 }, // y (121)
  { 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, // z (122)
  { 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, // { (123)
  { 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00 }, // | (124)
  { 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, // } (125)
  { 0x08, 0x08, 0x2A, 0x1C, 0x08, 0x00 }, // → (126)
};

// ─── Constructor ─────────────────────────────────────────────────────────────
GDEM102F91::GDEM102F91(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t busy,
                       uint8_t sck, uint8_t miso, uint8_t mosi)
    : _cs(cs), _dc(dc), _rst(rst), _busy(busy),
      _sck(sck), _miso(miso), _mosi(mosi), _tileY(0), _tileH(0) {
    _spi = new SPIClass(HSPI);
}

// ─── begin ────────────────────────────────────────────────────────────────────
void GDEM102F91::begin() {
    pinMode(_cs,   OUTPUT); digitalWrite(_cs,  HIGH);
    pinMode(_dc,   OUTPUT); digitalWrite(_dc,  HIGH);
    pinMode(_rst,  OUTPUT); digitalWrite(_rst, HIGH);
    pinMode(_busy, INPUT);

    _spi->begin(_sck, _miso, _mosi, _cs);
    _spi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    _init();
}

// ─── render ──────────────────────────────────────────────────────────────────
// Divides the display into tiles of EPD_TILE_ROWS rows each.
// For every tile: clears the tile buffer, calls your scene callback
// (which draws into the tile via setPixel/fillRect/etc.), then flushes
// the tile buffer to the display over SPI.
// Your scene callback is called once per tile — make sure all draw calls
// are stateless with respect to tile position (they clip automatically).
void GDEM102F91::render(SceneCallback scene, uint8_t bgColor) {
    _init();
    _sendCommand(0x10); // begin data transmission

    for (int16_t y = 0; y < EPD_HEIGHT; y += EPD_TILE_ROWS) {
        _tileY = y;
        _tileH = min((int16_t)EPD_TILE_ROWS, (int16_t)(EPD_HEIGHT - y));

        // Fill tile with background color
        memset(_buf, bgColor, _tileH * EPD_ROW_BYTES);

        // Call user scene — drawing calls clip to this tile automatically
        scene(this);

        // Flush tile rows to display
        _flushTile();
    }

    _sendCommand(0x12); // DRF display refresh
    delay(100);
    _waitBusy();
}

// ─── _flushTile ──────────────────────────────────────────────────────────────
void GDEM102F91::_flushTile() {
    digitalWrite(_dc, HIGH);
    for (int16_t row = 0; row < _tileH; row++) {
        for (int16_t col = 0; col < EPD_ROW_BYTES; col++) {
            digitalWrite(_cs, LOW);
            _spi->transfer(_buf[row * EPD_ROW_BYTES + col]);
            digitalWrite(_cs, HIGH);
        }
    }
}

// ─── sleep ────────────────────────────────────────────────────────────────────
void GDEM102F91::sleep() {
    _sendCommand(0x02); // POF power off
    _waitBusy();
    _sendCommand(0x07); // DSLP deep sleep
    _sendData(0xA5);
}

// ─── wake ─────────────────────────────────────────────────────────────────────
void GDEM102F91::wake() {
    _init();
}

// ─── setPixel ────────────────────────────────────────────────────────────────
// y is in display coordinates; we translate to tile-relative before writing.
void GDEM102F91::setPixel(int16_t x, int16_t y, uint8_t color) {
    if (x < 0 || x >= EPD_WIDTH) return;
    int16_t localY = y - _tileY;
    if (localY < 0 || localY >= _tileH) return;  // outside current tile

    uint32_t idx   = (uint32_t)localY * EPD_ROW_BYTES + (x / 4);
    uint8_t  shift = (3 - (x % 4)) * 2;
    uint8_t  mask  = 0x03 << shift;
    _buf[idx] = (_buf[idx] & ~mask) | ((color & 0x03) << shift);
}

// ─── getPixel ────────────────────────────────────────────────────────────────
uint8_t GDEM102F91::getPixel(int16_t x, int16_t y) {
    if (x < 0 || x >= EPD_WIDTH) return 0;
    int16_t localY = y - _tileY;
    if (localY < 0 || localY >= _tileH) return 0;
    uint32_t idx   = (uint32_t)localY * EPD_ROW_BYTES + (x / 4);
    uint8_t  shift = (3 - (x % 4)) * 2;
    return (_buf[idx] >> shift) & 0x03;
}

// ─── drawHLine ───────────────────────────────────────────────────────────────
void GDEM102F91::drawHLine(int16_t x, int16_t y, int16_t w, uint8_t color) {
    for (int16_t i = x; i < x + w; i++) setPixel(i, y, color);
}

// ─── drawVLine ───────────────────────────────────────────────────────────────
void GDEM102F91::drawVLine(int16_t x, int16_t y, int16_t h, uint8_t color) {
    for (int16_t i = y; i < y + h; i++) setPixel(x, i, color);
}

// ─── drawLine (Bresenham) ────────────────────────────────────────────────────
void GDEM102F91::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = (dx > dy ? dx : -dy) / 2, e2;
    while (true) {
        setPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}

// ─── drawRect ────────────────────────────────────────────────────────────────
void GDEM102F91::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    drawHLine(x,         y,         w, color);
    drawHLine(x,         y + h - 1, w, color);
    drawVLine(x,         y,         h, color);
    drawVLine(x + w - 1, y,         h, color);
}

// ─── fillRect ────────────────────────────────────────────────────────────────
void GDEM102F91::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color) {
    // Clamp to display bounds
    if (x < 0) { w += x; x = 0; }
    if (x + w > EPD_WIDTH) w = EPD_WIDTH - x;
    if (w <= 0) return;

    // Clamp to tile bounds
    int16_t y0 = max(y, _tileY);
    int16_t y1 = min(y + h, _tileY + _tileH);
    if (y0 >= y1) return;

    uint8_t packedColor = (color & 0x03);
    packedColor = packedColor | (packedColor << 2) | (packedColor << 4) | (packedColor << 6);

    for (int16_t row = y0; row < y1; row++) {
        int16_t localY = row - _tileY;
        int16_t col = x;
        while (col < x + w && (col % 4) != 0) { setPixel(col, row, color); col++; }
        while (col + 4 <= x + w) {
            uint32_t idx = (uint32_t)localY * EPD_ROW_BYTES + (col / 4);
            _buf[idx] = packedColor;
            col += 4;
        }
        while (col < x + w) { setPixel(col, row, color); col++; }
    }
}

// ─── Circle helpers ──────────────────────────────────────────────────────────
void GDEM102F91::_drawCircleHelper(int16_t cx, int16_t cy, int16_t r,
                                    uint8_t corners, uint8_t color) {
    int16_t f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
    while (x < y) {
        if (f >= 0) { y--; ddF_y += 2; f += ddF_y; }
        x++; ddF_x += 2; f += ddF_x;
        if (corners & 0x4) { setPixel(cx + x, cy + y, color); setPixel(cx + y, cy + x, color); }
        if (corners & 0x2) { setPixel(cx + x, cy - y, color); setPixel(cx + y, cy - x, color); }
        if (corners & 0x8) { setPixel(cx - y, cy + x, color); setPixel(cx - x, cy + y, color); }
        if (corners & 0x1) { setPixel(cx - y, cy - x, color); setPixel(cx - x, cy - y, color); }
    }
}

void GDEM102F91::_fillCircleHelper(int16_t cx, int16_t cy, int16_t r,
                                    uint8_t corners, int16_t delta, uint8_t color) {
    int16_t f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
    while (x < y) {
        if (f >= 0) { y--; ddF_y += 2; f += ddF_y; }
        x++; ddF_x += 2; f += ddF_x;
        if (corners & 0x1) {
            drawVLine(cx + x, cy - y, 2 * y + 1 + delta, color);
            drawVLine(cx + y, cy - x, 2 * x + 1 + delta, color);
        }
        if (corners & 0x2) {
            drawVLine(cx - x, cy - y, 2 * y + 1 + delta, color);
            drawVLine(cx - y, cy - x, 2 * x + 1 + delta, color);
        }
    }
}

// ─── drawCircle ──────────────────────────────────────────────────────────────
void GDEM102F91::drawCircle(int16_t cx, int16_t cy, int16_t r, uint8_t color) {
    int16_t f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
    setPixel(cx, cy + r, color); setPixel(cx, cy - r, color);
    setPixel(cx + r, cy, color); setPixel(cx - r, cy, color);
    while (x < y) {
        if (f >= 0) { y--; ddF_y += 2; f += ddF_y; }
        x++; ddF_x += 2; f += ddF_x;
        setPixel(cx + x, cy + y, color); setPixel(cx - x, cy + y, color);
        setPixel(cx + x, cy - y, color); setPixel(cx - x, cy - y, color);
        setPixel(cx + y, cy + x, color); setPixel(cx - y, cy + x, color);
        setPixel(cx + y, cy - x, color); setPixel(cx - y, cy - x, color);
    }
}

// ─── fillCircle ──────────────────────────────────────────────────────────────
void GDEM102F91::fillCircle(int16_t cx, int16_t cy, int16_t r, uint8_t color) {
    drawVLine(cx, cy - r, 2 * r + 1, color);
    _fillCircleHelper(cx, cy, r, 3, 0, color);
}

// ─── drawRoundRect ───────────────────────────────────────────────────────────
void GDEM102F91::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                int16_t r, uint8_t color) {
    drawHLine(x + r,     y,         w - 2 * r, color);
    drawHLine(x + r,     y + h - 1, w - 2 * r, color);
    drawVLine(x,         y + r,     h - 2 * r, color);
    drawVLine(x + w - 1, y + r,     h - 2 * r, color);
    _drawCircleHelper(x + r,         y + r,         r, 0x1, color);
    _drawCircleHelper(x + w - r - 1, y + r,         r, 0x2, color);
    _drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 0x4, color);
    _drawCircleHelper(x + r,         y + h - r - 1, r, 0x8, color);
}

// ─── fillRoundRect ───────────────────────────────────────────────────────────
void GDEM102F91::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                int16_t r, uint8_t color) {
    fillRect(x + r, y, w - 2 * r, h, color);
    _fillCircleHelper(x + r,         y + r,         r, 0x2, h - 2 * r - 1, color);
    _fillCircleHelper(x + w - r - 1, y + r,         r, 0x1, h - 2 * r - 1, color);
}

// ─── drawTriangle ────────────────────────────────────────────────────────────
void GDEM102F91::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                               int16_t x2, int16_t y2, uint8_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}

// ─── fillTriangle (scanline) ─────────────────────────────────────────────────
void GDEM102F91::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                               int16_t x2, int16_t y2, uint8_t color) {
    int16_t a, b, y, last;
    if (y0 > y1) { _swap(y0, y1); _swap(x0, x1); }
    if (y1 > y2) { _swap(y2, y1); _swap(x2, x1); }
    if (y0 > y1) { _swap(y0, y1); _swap(x0, x1); }
    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) a = x1; else if (x1 > b) b = x1;
        if (x2 < a) a = x2; else if (x2 > b) b = x2;
        drawHLine(a, y0, b - a + 1, color);
        return;
    }
    int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0;
    int16_t dx12 = x2 - x1, dy12 = y2 - y1;
    int32_t sa = 0, sb = 0;
    last = (y1 == y2) ? y1 : y1 - 1;
    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01; b = x0 + sb / dy02;
        sa += dx01; sb += dx02;
        if (a > b) _swap(a, b);
        drawHLine(a, y, b - a + 1, color);
    }
    sa = (int32_t)dx12 * (y - y1); sb = (int32_t)dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12; b = x0 + sb / dy02;
        sa += dx12; sb += dx02;
        if (a > b) _swap(a, b);
        drawHLine(a, y, b - a + 1, color);
    }
}

// ─── Text ─────────────────────────────────────────────────────────────────────
void GDEM102F91::drawChar(int16_t x, int16_t y, char c, uint8_t color, uint8_t size) {
    if (c < 32 || c > 126) c = '?';
    uint8_t idx = c - 32;
    for (uint8_t col = 0; col < 5; col++) {
        uint8_t line = pgm_read_byte(&FONT6x8[idx][col]);
        for (uint8_t row = 0; row < 8; row++) {
            if (line & (1 << row)) {
                if (size == 1) {
                    setPixel(x + col, y + row, color);
                } else {
                    fillRect(x + col * size, y + row * size, size, size, color);
                }
            }
        }
    }
}

void GDEM102F91::drawString(int16_t x, int16_t y, const char* str,
                             uint8_t color, uint8_t size) {
    int16_t cx = x;
    while (*str) {
        drawChar(cx, y, *str, color, size);
        cx += 6 * size;
        str++;
    }
}

void GDEM102F91::drawStringCentered(int16_t x, int16_t y, int16_t w,
                                     const char* str, uint8_t color, uint8_t size) {
    int16_t sw = getStringWidth(str, size);
    drawString(x + (w - sw) / 2, y, str, color, size);
}

void GDEM102F91::drawInt(int16_t x, int16_t y, int32_t value,
                          uint8_t color, uint8_t size) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%ld", (long)value);
    drawString(x, y, buf, color, size);
}

void GDEM102F91::drawFloat(int16_t x, int16_t y, float value, uint8_t decimals,
                            uint8_t color, uint8_t size) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%.*f", decimals, value);
    drawString(x, y, buf, color, size);
}

int16_t GDEM102F91::getStringWidth(const char* str, uint8_t size) {
    return strlen(str) * 6 * size;
}

int16_t GDEM102F91::getCharHeight(uint8_t size) {
    return 8 * size;
}

// ─── drawBitmap2bpp ──────────────────────────────────────────────────────────
// w must be a multiple of 4 (one byte covers 4 pixels).
// Bitmap rows are EPD_ROW_BYTES-style: 2 bits per pixel, MSB first.
void GDEM102F91::drawBitmap2bpp(int16_t x, int16_t y, int16_t w, int16_t h,
                                  const uint8_t* bitmap) {
    if (w <= 0 || h <= 0) return;

    // Clip to display bounds horizontally
    int16_t x0 = x, x1 = x + w;
    if (x0 >= EPD_WIDTH || x1 <= 0) return;
    if (x0 < 0) x0 = 0;
    if (x1 > EPD_WIDTH) x1 = EPD_WIDTH;

    int16_t rowBytes = (w + 3) / 4;  // bytes per bitmap row

    for (int16_t row = 0; row < h; row++) {
        int16_t displayY = y + row;
        int16_t localY   = displayY - _tileY;
        if (localY < 0 || localY >= _tileH) continue;  // outside current tile

        const uint8_t* srcRow = bitmap + (uint32_t)row * rowBytes;

        // Fast path: bitmap is 4-pixel aligned at both src and dst
        if ((x % 4) == 0 && (w % 4) == 0) {
            int16_t dstByte  = x / 4;
            int16_t srcByte0 = (x0 - x) / 4;
            int16_t srcByte1 = (x1 - x + 3) / 4;
            uint32_t dstIdx  = (uint32_t)localY * EPD_ROW_BYTES + dstByte + srcByte0;
            for (int16_t b = srcByte0; b < srcByte1; b++) {
                _buf[dstIdx++] = pgm_read_byte(srcRow + b);
            }
        } else {
            // Pixel-by-pixel fallback for unaligned bitmaps
            for (int16_t col = x0; col < x1; col++) {
                int16_t srcCol = col - x;
                uint8_t srcByte = pgm_read_byte(srcRow + (srcCol / 4));
                uint8_t shift   = (3 - (srcCol % 4)) * 2;
                uint8_t pixel   = (srcByte >> shift) & 0x03;
                setPixel(col, displayY, pixel);
            }
        }
    }
}

// ─── drawBitmap1bpp ──────────────────────────────────────────────────────────
// Each row is ceil(w/8) bytes, MSB = leftmost pixel.
// bgColor == 0xFF means transparent (clear bits are skipped).
void GDEM102F91::drawBitmap1bpp(int16_t x, int16_t y, int16_t w, int16_t h,
                                  const uint8_t* bitmap, uint8_t fgColor,
                                  uint8_t bgColor) {
    if (w <= 0 || h <= 0) return;

    int16_t rowBytes = (w + 7) / 8;
    bool transparent = (bgColor == 0xFF);

    for (int16_t row = 0; row < h; row++) {
        int16_t displayY = y + row;
        int16_t localY   = displayY - _tileY;
        if (localY < 0 || localY >= _tileH) continue;

        const uint8_t* srcRow = bitmap + (uint32_t)row * rowBytes;

        for (int16_t col = 0; col < w; col++) {
            int16_t displayX = x + col;
            if (displayX < 0 || displayX >= EPD_WIDTH) continue;

            uint8_t srcByte = pgm_read_byte(srcRow + (col / 8));
            bool    set     = (srcByte >> (7 - (col % 8))) & 0x01;

            if (set) {
                setPixel(displayX, displayY, fgColor);
            } else if (!transparent) {
                setPixel(displayX, displayY, bgColor);
            }
        }
    }
}

// ─── drawIcon ─────────────────────────────────────────────────────────────────
void GDEM102F91::drawIcon(int16_t x, int16_t y, uint8_t icon,
                           uint8_t size, uint8_t color) {
    int16_t s = size * 8;
    switch (icon) {
        case ICON_CHECK:
            drawLine(x, y + s/2, x + s/3, y + s - 2, color);
            drawLine(x + s/3, y + s - 2, x + s - 2, y + 2, color);
            break;
        case ICON_CROSS:
            drawLine(x + 2, y + 2, x + s - 2, y + s - 2, color);
            drawLine(x + s - 2, y + 2, x + 2, y + s - 2, color);
            break;
        case ICON_WARNING:
            fillTriangle(x + s/2, y + 2, x + 2, y + s - 2, x + s - 2, y + s - 2, color);
            fillRect(x + s/2 - 1, y + s/3, 2, s/3, PIXEL_WHITE);
            fillRect(x + s/2 - 1, y + s*2/3 + 2, 2, 2, PIXEL_WHITE);
            break;
        case ICON_INFO:
            drawCircle(x + s/2, y + s/2, s/2 - 2, color);
            fillRect(x + s/2 - 1, y + s/3, 2, s/3 + 2, color);
            fillRect(x + s/2 - 1, y + s/5, 2, 2, color);
            break;
        case ICON_ARROW_UP:
            fillTriangle(x + s/2, y + 2, x + 2, y + s/2, x + s - 2, y + s/2, color);
            fillRect(x + s/2 - 2, y + s/2, 4, s/2 - 2, color);
            break;
        case ICON_ARROW_DOWN:
            fillTriangle(x + s/2, y + s - 2, x + 2, y + s/2, x + s - 2, y + s/2, color);
            fillRect(x + s/2 - 2, y + 2, 4, s/2 - 2, color);
            break;
        case ICON_CLOUD:
            fillCircle(x + s/3,     y + s/2, s/4, color);
            fillCircle(x + s*2/3,   y + s/2, s/3, color);
            fillCircle(x + s/2,     y + s/3, s/4, color);
            fillRect(x + s/4, y + s/2, s/2, s/3, color);
            break;
        case ICON_SERVER:
            fillRoundRect(x + 2, y + 2,      s - 4, s/3 - 2, 2, color);
            fillRoundRect(x + 2, y + s/3 + 1, s - 4, s/3 - 2, 2, color);
            fillRoundRect(x + 2, y + s*2/3,  s - 4, s/3 - 2, 2, color);
            break;
        case ICON_CHART:
            drawLine(x + 2, y + s - 2, x + 2, y + 2, color);
            drawLine(x + 2, y + s - 2, x + s - 2, y + s - 2, color);
            drawLine(x + 4, y + s*2/3, x + s/3, y + s/2, color);
            drawLine(x + s/3, y + s/2, x + s*2/3, y + s/3, color);
            drawLine(x + s*2/3, y + s/3, x + s - 4, y + s/4, color);
            break;
        case ICON_LOCK:
            drawRoundRect(x + s/4, y + s/2, s/2, s/2, 2, color);
            drawLine(x + s/3, y + s/2, x + s/3, y + s/3, color);
            drawLine(x + s*2/3, y + s/2, x + s*2/3, y + s/3, color);
            drawCircle(x + s/2, y + s/3, s/6, color);
            break;
    }
}

// ─── drawProgressBar ─────────────────────────────────────────────────────────
void GDEM102F91::drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h,
                                  float percent, uint8_t fg, uint8_t bg,
                                  uint8_t border) {
    percent = constrain(percent, 0.0f, 100.0f);
    fillRoundRect(x, y, w, h, h / 2, bg);
    drawRoundRect(x, y, w, h, h / 2, border);
    int16_t filled = (int16_t)((percent / 100.0f) * (w - 4));
    if (filled > 0) {
        fillRoundRect(x + 2, y + 2, filled, h - 4, (h - 4) / 2, fg);
    }
}

// ─── drawSparkline ───────────────────────────────────────────────────────────
void GDEM102F91::drawSparkline(int16_t x, int16_t y, int16_t w, int16_t h,
                                float* values, uint8_t count, uint8_t color) {
    if (count < 2) return;
    float minVal = values[0], maxVal = values[0];
    for (uint8_t i = 1; i < count; i++) {
        if (values[i] < minVal) minVal = values[i];
        if (values[i] > maxVal) maxVal = values[i];
    }
    float range = maxVal - minVal;
    if (range == 0) range = 1;

    for (uint8_t i = 1; i < count; i++) {
        int16_t x0 = x + (int16_t)((i - 1) * w / (count - 1));
        int16_t y0 = y + h - 1 - (int16_t)((values[i - 1] - minVal) / range * (h - 1));
        int16_t x1 = x + (int16_t)(i * w / (count - 1));
        int16_t y1 = y + h - 1 - (int16_t)((values[i] - minVal) / range * (h - 1));
        drawLine(x0, y0, x1, y1, color);
    }
}

// ─── drawMetricCard ──────────────────────────────────────────────────────────
void GDEM102F91::drawMetricCard(int16_t x, int16_t y, int16_t w, int16_t h,
                                 const char* label, const char* value,
                                 const char* unit, uint8_t bg, uint8_t fg,
                                 uint8_t accent) {
    // Background
    fillRoundRect(x, y, w, h, 6, bg);
    drawRoundRect(x, y, w, h, 6, fg);

    // Accent bar at top
    fillRoundRect(x, y, w, 6, 3, accent);
    fillRect(x, y + 3, w, 3, accent);

    // Label (small, top)
    int16_t labelY = y + 12;
    drawStringCentered(x, labelY, w, label, fg, 1);

    // Large value (center)
    uint8_t valSize = (strlen(value) <= 4) ? 4 : (strlen(value) <= 6) ? 3 : 2;
    int16_t valW = getStringWidth(value, valSize);
    int16_t valX = x + (w - valW) / 2;
    int16_t valY = y + h / 2 - getCharHeight(valSize) / 2;
    drawString(valX, valY, value, fg, valSize);

    // Unit (small, below value)
    if (unit && strlen(unit) > 0) {
        int16_t unitY = valY + getCharHeight(valSize) + 4;
        drawStringCentered(x, unitY, w, unit, fg, 1);
    }
}

// ─── drawBadge ───────────────────────────────────────────────────────────────
void GDEM102F91::drawBadge(int16_t x, int16_t y, const char* text,
                            uint8_t bg, uint8_t fg) {
    int16_t tw = getStringWidth(text, 1);
    int16_t pw = tw + 10;
    int16_t ph = 14;
    fillRoundRect(x, y, pw, ph, ph / 2, bg);
    drawString(x + 5, y + 3, text, fg, 1);
}

// ─── drawDivider ─────────────────────────────────────────────────────────────
void GDEM102F91::drawDivider(int16_t x, int16_t y, int16_t w, uint8_t color,
                              const char* label, uint8_t labelColor) {
    if (label && strlen(label) > 0) {
        int16_t lw = getStringWidth(label, 1);
        int16_t lx = x + (w - lw) / 2;
        drawHLine(x,      y + 4, (w - lw) / 2 - 4, color);
        drawHLine(lx + lw + 4, y + 4, (w - lw) / 2 - 4, color);
        drawString(lx, y, label, labelColor, 1);
    } else {
        drawHLine(x, y, w, color);
    }
}

// ─── drawTrend ───────────────────────────────────────────────────────────────
void GDEM102F91::drawTrend(int16_t x, int16_t y, float percent,
                            bool up, uint8_t color) {
    // Arrow
    if (up) {
        fillTriangle(x + 6, y, x, y + 8, x + 12, y + 8, color);
    } else {
        fillTriangle(x + 6, y + 8, x, y, x + 12, y, color);
    }
    // Percentage text
    char buf[10];
    snprintf(buf, sizeof(buf), "%.1f%%", percent);
    drawString(x + 16, y + 1, buf, color, 1);
}

// ─── Low-level SPI ───────────────────────────────────────────────────────────
void GDEM102F91::_sendCommand(uint8_t cmd) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    _spi->transfer(cmd);
    digitalWrite(_cs, HIGH);
}

void GDEM102F91::_sendData(uint8_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
}

void GDEM102F91::_waitBusy(uint32_t timeout_ms) {
    uint32_t start = millis();
    while (digitalRead(_busy) == LOW) {
        if (millis() - start > timeout_ms) return;
        delay(10);
    }
}

void GDEM102F91::_reset() {
    digitalWrite(_rst, HIGH); delay(10);
    digitalWrite(_rst, LOW);  delay(10);
    digitalWrite(_rst, HIGH); delay(10);
    _waitBusy();
}

void GDEM102F91::_init() {
    _reset();

    _sendCommand(0x00);
    _sendData(0x0f); _sendData(0x29);

    _sendCommand(0x03);
    _sendData(0x10); _sendData(0x54); _sendData(0x44);

    _sendCommand(0x06);
    _sendData(0x0F); _sendData(0x8B); _sendData(0x93); _sendData(0xA1);

    _sendCommand(0x41); _sendData(0x00);
    _sendCommand(0x50); _sendData(0x37);

    _sendCommand(0x60);
    _sendData(0x02); _sendData(0x02);

    _sendCommand(0x61); // TRES: 960 x 640
    _sendData(0x03); _sendData(0xC0);   // 0x03C0 = 960
    _sendData(0x02); _sendData(0x80);   // 0x0280 = 640

    _sendCommand(0x65);
    _sendData(0x00); _sendData(0x00); _sendData(0x00); _sendData(0x00);

    _sendCommand(0xE7); _sendData(0x1C);
    _sendCommand(0xE3); _sendData(0x00);
    _sendCommand(0xE9); _sendData(0x01);
    _sendCommand(0x30); _sendData(0x08);

    _sendCommand(0x04); // PON
    _waitBusy();
}
