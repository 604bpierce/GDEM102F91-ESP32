/**
 * GDEM102F91 Dashboard Example
 * 
 * Demonstrates the full library API with a cloud metrics dashboard layout.
 * 
 * HOW THE TILE RENDERER WORKS:
 * The display is 960x640 = 153,600 bytes at 2 bits/pixel — too large for
 * ESP32 RAM. Instead, the library renders in 20-row tiles (~4.8KB each).
 * Your scene function is called once per tile (32 times total). Drawing
 * calls automatically clip to the current tile, so your code looks exactly
 * like a normal framebuffer API.
 * 
 * Wiring (Waveshare ESP32 Driver Board Rev 3):
 *   BUSY → GPIO 25,  CS → GPIO 15,  RST → GPIO 26,  DC → GPIO 27
 *   SCK  → GPIO 13,  MISO → GPIO 12,  MOSI → GPIO 14
 * 
 * Install: Sketch → Include Library → Add .ZIP Library → GDEM102F91.zip
 */

#include <GDEM102F91.h>

#define PIN_CS   15
#define PIN_DC   27
#define PIN_RST  26
#define PIN_BUSY 25
#define PIN_SCK  13
#define PIN_MISO 12
#define PIN_MOSI 14

GDEM102F91 display(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY, PIN_SCK, PIN_MISO, PIN_MOSI);

// ─── Metric data (replace with live data from WiFi/MQTT/HTTP) ────────────────
float cpuHistory[]  = { 42, 55, 61, 48, 70, 65, 72, 58, 63, 75, 68, 80 };
float memHistory[]  = { 60, 62, 65, 63, 67, 70, 68, 72, 71, 75, 73, 74 };
float reqHistory[]  = { 120, 145, 132, 167, 155, 178, 162, 190, 175, 188, 195, 210 };

// ─── Scene function — called once per tile by display.render() ────────────────
void drawDashboard(void* epd) {
    GDEM102F91* d = (GDEM102F91*)epd;

    // ── Header bar ───────────────────────────────────────────────────────────
    d->fillRect(0, 0, 960, 48, EPD_BLACK);
    d->drawString(16, 14, "CLOUD INFRASTRUCTURE DASHBOARD", EPD_WHITE, 2);
    d->drawString(740, 14, "2025-04-03  08:00", EPD_WHITE, 1);
    d->drawBadge(870, 10, "LIVE", EPD_RED, EPD_WHITE);
    d->drawHLine(0, 48, 960, EPD_BLACK);

    // ── Row 1: Metric cards ───────────────────────────────────────────────────
    d->drawMetricCard(10,  60, 215, 140, "CPU USAGE",    "68%",   "",      EPD_WHITE, EPD_BLACK, EPD_RED);
    d->drawMetricCard(235, 60, 215, 140, "MEMORY",       "74%",   "",      EPD_WHITE, EPD_BLACK, EPD_YELLOW);
    d->drawMetricCard(460, 60, 215, 140, "REQUESTS/MIN", "2,847", "req/m", EPD_WHITE, EPD_BLACK, EPD_BLACK);
    d->drawMetricCard(685, 60, 215, 140, "ERROR RATE",   "0.3%",  "",      EPD_WHITE, EPD_BLACK, EPD_RED);

    // Trend indicators
    d->drawTrend(20,  205, 12.5, true,  EPD_BLACK);
    d->drawTrend(245, 205, 3.2,  true,  EPD_BLACK);
    d->drawTrend(470, 205, 8.1,  true,  EPD_BLACK);
    d->drawTrend(695, 205, 0.1,  false, EPD_BLACK);

    // ── Section divider ───────────────────────────────────────────────────────
    d->drawDivider(10, 225, 940, EPD_BLACK, "PERFORMANCE HISTORY", EPD_BLACK);

    // ── Sparkline charts ──────────────────────────────────────────────────────
    int16_t chartY = 245, chartH = 80;
    uint8_t histLen = 12;

    d->drawRect(10, chartY, 295, chartH + 20, EPD_BLACK);
    d->drawString(16, chartY + 4, "CPU %", EPD_BLACK, 1);
    d->drawSparkline(16, chartY + 16, 283, chartH, cpuHistory, histLen, EPD_RED);

    d->drawRect(325, chartY, 295, chartH + 20, EPD_BLACK);
    d->drawString(331, chartY + 4, "MEMORY %", EPD_BLACK, 1);
    d->drawSparkline(331, chartY + 16, 283, chartH, memHistory, histLen, EPD_BLACK);

    d->drawRect(640, chartY, 305, chartH + 20, EPD_BLACK);
    d->drawString(646, chartY + 4, "REQUESTS/MIN", EPD_BLACK, 1);
    d->drawSparkline(646, chartY + 16, 293, chartH, reqHistory, histLen, EPD_YELLOW);

    // ── Section divider ───────────────────────────────────────────────────────
    d->drawDivider(10, 360, 940, EPD_BLACK, "SERVICE STATUS", EPD_BLACK);

    // ── Service status table ──────────────────────────────────────────────────
    int16_t svcY = 380, svcH = 36;
    const char* services[] = { "api-gateway", "auth-service", "db-primary",
                                "cache-layer", "queue-worker", "cdn-edge" };
    const char* statuses[]  = { "OK", "OK", "OK", "WARN", "OK", "DEGRADED" };
    uint8_t statusColors[]  = { EPD_BLACK, EPD_BLACK, EPD_BLACK,
                                 EPD_YELLOW, EPD_BLACK, EPD_RED };
    float   uptimes[]       = { 99.98, 99.95, 100.0, 97.2, 99.91, 94.5 };
    uint8_t iconTypes[]     = { ICON_CHECK, ICON_CHECK, ICON_SERVER,
                                 ICON_WARNING, ICON_CHECK, ICON_CROSS };
    const char* latencies[] = { "12ms", "8ms", "2ms", "48ms", "5ms", "220ms" };
    const char* requests[]  = { "1,847", "923", "384", "2,103", "567", "445" };

    // Header row
    d->fillRect(10, svcY, 940, svcH - 4, EPD_BLACK);
    d->drawString(20,  svcY + 10, "SERVICE",  EPD_WHITE, 1);
    d->drawString(220, svcY + 10, "STATUS",   EPD_WHITE, 1);
    d->drawString(360, svcY + 10, "UPTIME",   EPD_WHITE, 1);
    d->drawString(500, svcY + 10, "LATENCY",  EPD_WHITE, 1);
    d->drawString(680, svcY + 10, "REQUESTS", EPD_WHITE, 1);
    d->drawString(820, svcY + 10, "HEALTH",   EPD_WHITE, 1);

    // Data rows
    for (uint8_t i = 0; i < 6; i++) {
        int16_t rowY = svcY + svcH + i * svcH;
        if (i % 2 == 0) d->fillRect(10, rowY, 940, svcH - 2, EPD_WHITE);
        d->drawRect(10, rowY, 940, svcH - 2, EPD_BLACK);
        d->drawIcon(16, rowY + 8, iconTypes[i], 1, statusColors[i]);
        d->drawString(36, rowY + 12, services[i], EPD_BLACK, 1);
        d->drawBadge(220, rowY + 10, statuses[i], statusColors[i],
                     (statusColors[i] == EPD_BLACK || statusColors[i] == EPD_RED)
                     ? EPD_WHITE : EPD_BLACK);
        char uptimeBuf[10];
        snprintf(uptimeBuf, sizeof(uptimeBuf), "%.2f%%", uptimes[i]);
        d->drawString(360, rowY + 12, uptimeBuf, EPD_BLACK, 1);
        d->drawString(500, rowY + 12, latencies[i], EPD_BLACK, 1);
        d->drawString(680, rowY + 12, requests[i],  EPD_BLACK, 1);
        d->drawProgressBar(820, rowY + 10, 110, 14,
                           uptimes[i], statusColors[i], EPD_WHITE, EPD_BLACK);
    }

    // ── Footer ────────────────────────────────────────────────────────────────
    d->fillRect(0, 618, 960, 22, EPD_BLACK);
    d->drawString(10,  622, "Region: us-east-1",     EPD_WHITE, 1);
    d->drawString(250, 622, "Cluster: prod-k8s-01",  EPD_WHITE, 1);
    d->drawString(500, 622, "Nodes: 12/12 healthy",  EPD_WHITE, 1);
    d->drawString(750, 622, "Next refresh: 5 min",   EPD_WHITE, 1);
}

// ─── Setup ────────────────────────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");
    display.begin();

    Serial.println("Rendering dashboard (32 tiles)...");
    display.render(drawDashboard, EPD_WHITE);

    display.sleep();
    Serial.println("Done.");
}

void loop() {
    // Update metrics from your data source, then call render() again.
    // E-ink is not suited for rapid updates — refresh every 5+ minutes.
    delay(300000); // 5 minutes
    // display.render(drawDashboard, EPD_WHITE);
    // display.sleep();
}
