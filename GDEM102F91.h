#ifndef GDEM102F91_H
#define GDEM102F91_H

#include <Arduino.h>
#include <SPI.h>

// ─── Display Dimensions ───────────────────────────────────────────────────────
#define EPD_WIDTH       960
#define EPD_HEIGHT      640
#define EPD_ROW_BYTES   (EPD_WIDTH / 4)   // 2 bits/pixel → 4 pixels/byte → 240 bytes/row

// ─── Tile buffer: how many rows to hold in RAM at once.
// 20 rows × 240 bytes = 4,800 bytes. The scene callback is called once per tile.
#define EPD_TILE_ROWS   20
#define EPD_TILE_BYTES  (EPD_TILE_ROWS * EPD_ROW_BYTES)   // 4,800 bytes

// ─── Color Constants (2-bit pixel encoding) ───────────────────────────────────
// Each byte holds 4 pixels packed as [P1 P1 | P2 P2 | P3 P3 | P4 P4]
#define EPD_BLACK   0x00   // 00 00 00 00
#define EPD_WHITE   0x55   // 01 01 01 01
#define EPD_YELLOW  0xAA   // 10 10 10 10
#define EPD_RED     0xFF   // 11 11 11 11

// Single-pixel color values (2-bit)
#define PIXEL_BLACK   0x00
#define PIXEL_WHITE   0x01
#define PIXEL_YELLOW  0x02
#define PIXEL_RED     0x03

// ─── Built-in Font Sizes ──────────────────────────────────────────────────────
#define FONT_SMALL   1   // 6x8 px base
#define FONT_MEDIUM  2   // 12x16 px
#define FONT_LARGE   3   // 18x24 px
#define FONT_XLARGE  4   // 24x32 px

// ─── Common Icons (drawn programmatically) ────────────────────────────────────
#define ICON_CHECK      0
#define ICON_CROSS      1
#define ICON_WARNING    2
#define ICON_INFO       3
#define ICON_ARROW_UP   4
#define ICON_ARROW_DOWN 5
#define ICON_CLOUD      6
#define ICON_SERVER     7
#define ICON_CHART      8
#define ICON_LOCK       9

// ─── Scene callback type ──────────────────────────────────────────────────────
// Your drawing code goes in a function matching this signature.
// The library calls it once per tile with the same display pointer.
typedef void (*SceneCallback)(void* epd);

class GDEM102F91 {
public:
    // ─── Constructor ──────────────────────────────────────────────────────────
    GDEM102F91(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t busy,
               uint8_t sck, uint8_t miso, uint8_t mosi);

    // ─── Lifecycle ────────────────────────────────────────────────────────────
    void begin();

    // Render the full display by calling your scene function once per tile.
    // Usage:  display.render(drawMyDashboard);
    void render(SceneCallback scene, uint8_t bgColor = EPD_WHITE);

    void sleep();   // Deep sleep between refreshes
    void wake();    // Wake and reinit

    // ─── Tile state query (call from inside your scene callback) ──────────────
    int16_t tileY()      { return _tileY; }       // top row of current tile
    int16_t tileHeight() { return _tileH; }        // number of rows in current tile

    // ─── Pixel (clipped to current tile) ─────────────────────────────────────
    void    setPixel(int16_t x, int16_t y, uint8_t color);
    uint8_t getPixel(int16_t x, int16_t y);

    // ─── Primitives ───────────────────────────────────────────────────────────
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
    void drawHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
    void drawVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
    void drawCircle(int16_t cx, int16_t cy, int16_t r, uint8_t color);
    void fillCircle(int16_t cx, int16_t cy, int16_t r, uint8_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                      int16_t x2, int16_t y2, uint8_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                      int16_t x2, int16_t y2, uint8_t color);

    // ─── Text ─────────────────────────────────────────────────────────────────
    void drawChar(int16_t x, int16_t y, char c, uint8_t color, uint8_t size);
    void drawString(int16_t x, int16_t y, const char* str, uint8_t color, uint8_t size);
    void drawStringCentered(int16_t x, int16_t y, int16_t w, const char* str,
                            uint8_t color, uint8_t size);
    void drawInt(int16_t x, int16_t y, int32_t value, uint8_t color, uint8_t size);
    void drawFloat(int16_t x, int16_t y, float value, uint8_t decimals,
                   uint8_t color, uint8_t size);
    int16_t getStringWidth(const char* str, uint8_t size);
    int16_t getCharHeight(uint8_t size);

    // ─── Bitmaps ──────────────────────────────────────────────────────────────
    // Draw a 2bpp (4-color) bitmap stored in PROGMEM.
    // Pixel encoding matches the display: 4 pixels per byte, MSB-first,
    // 2 bits each: 00=black 01=white 10=yellow 11=red.
    // w must be a multiple of 4.
    void drawBitmap2bpp(int16_t x, int16_t y, int16_t w, int16_t h,
                        const uint8_t* bitmap);

    // Draw a 1bpp monochrome bitmap stored in PROGMEM.
    // Each row is ceil(w/8) bytes, MSB = leftmost pixel.
    // Set bits draw fgColor; clear bits draw bgColor.
    // Pass bgColor = 0xFF to make the background transparent (skip clear pixels).
    void drawBitmap1bpp(int16_t x, int16_t y, int16_t w, int16_t h,
                        const uint8_t* bitmap, uint8_t fgColor,
                        uint8_t bgColor = 0xFF);

    // ─── Icons ────────────────────────────────────────────────────────────────
    void drawIcon(int16_t x, int16_t y, uint8_t icon, uint8_t size, uint8_t color);

    // ─── Dashboard Widgets ────────────────────────────────────────────────────
    void drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h,
                         float percent, uint8_t fg, uint8_t bg, uint8_t border);
    void drawSparkline(int16_t x, int16_t y, int16_t w, int16_t h,
                       float* values, uint8_t count, uint8_t color);
    void drawMetricCard(int16_t x, int16_t y, int16_t w, int16_t h,
                        const char* label, const char* value, const char* unit,
                        uint8_t bg, uint8_t fg, uint8_t accent);
    void drawBadge(int16_t x, int16_t y, const char* text, uint8_t bg, uint8_t fg);
    void drawDivider(int16_t x, int16_t y, int16_t w, uint8_t color,
                     const char* label = nullptr, uint8_t labelColor = EPD_BLACK);
    void drawTrend(int16_t x, int16_t y, float percent, bool up, uint8_t color);

    // ─── Utility ──────────────────────────────────────────────────────────────
    int16_t width()  { return EPD_WIDTH; }
    int16_t height() { return EPD_HEIGHT; }
    bool    isBusy() { return digitalRead(_busy) == LOW; }

private:
    uint8_t  _cs, _dc, _rst, _busy, _sck, _miso, _mosi;
    SPIClass* _spi;

    // ─── Tile state ───────────────────────────────────────────────────────────
    // Only EPD_TILE_BYTES (4,800 bytes) live in RAM at once.
    uint8_t  _buf[EPD_TILE_BYTES];
    int16_t  _tileY;   // display row where this tile starts
    int16_t  _tileH;   // number of rows in current tile

    // ─── Low-level SPI ────────────────────────────────────────────────────────
    void _sendCommand(uint8_t cmd);
    void _sendData(uint8_t data);
    void _waitBusy(uint32_t timeout_ms = 60000);
    void _reset();
    void _init();
    void _flushTile();  // send current tile buffer to display over SPI

    // ─── Internal drawing helpers ─────────────────────────────────────────────
    void _drawCircleHelper(int16_t cx, int16_t cy, int16_t r,
                           uint8_t corners, uint8_t color);
    void _fillCircleHelper(int16_t cx, int16_t cy, int16_t r,
                           uint8_t corners, int16_t delta, uint8_t color);
    void _swap(int16_t &a, int16_t &b) { int16_t t = a; a = b; b = t; }
};

#endif // GDEM102F91_H
