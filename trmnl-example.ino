#include <SPI.h>
#include <TFT_eSPI.h>

#ifdef EPAPER_ENABLE

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h" // WIFI_SSID, WIFI_PASS (see config.example.h)
#include "weather_logic.h"

// ---- Open-Meteo API URL (Edinburgh, 2-day forecast) ----
const char *weatherURL =
    "https://api.open-meteo.com/v1/forecast?"
    "latitude=55.9533&longitude=-3.1883"
    "&hourly=temperature_2m,precipitation_probability,weathercode,windspeed_10m"
    "&current_weather=true&timezone=Europe%2FLondon&forecast_days=2";

// ---- Data structures ----
struct HourlyForecast
{
  int hour;        // 0-23
  int temp;        // C (rounded)
  int rainPct;     // precipitation probability 0-100%
  int wind;        // km/h
  int weathercode; // WMO code
};

HourlyForecast todayBlocks[6];
int todayCount = 0;
HourlyForecast tomorrowBlocks[4];
int tomorrowCount = 0;

int currentTemp = 0, currentWind = 0, currentWeathercode = 0;
int currentHour = 12;
bool weatherValid = false;

// ---- Battery reading (TRMNL EE04 board) ----
#define PIN_BATTERY 1
#define PIN_VBAT_SWITCH 6

EPaper epaper = EPaper();

int currentCat = 0;
uint32_t targetTime = 0;
uint32_t weatherRefreshTime = 0;
uint32_t batteryRefreshTime = 0;
int batteryPct = -1; // -1 = not yet read

// ---- Forward declarations ----
int readBatteryPct();
void drawBatteryIcon(int x, int y, int pct);
void drawCat0();
void drawCat1();
void drawCat2();
void drawCat3();
void drawCat4();
void drawCat5();
void drawCat6();
void drawCat7();
void drawCat8();
void drawCat9();
void drawCat10();
void drawCat11();
void drawCat12();
void drawCat13();
void drawCat14();
void drawCat15();
void drawCat16();
void drawCat17();
void drawCat18();
void drawCat19();
void drawCat20();
void drawCat21();
void drawCat22();
void drawCat23();
void drawCat24();
void drawCat25();
void drawCat26();
void drawCat27();
void drawCat28();
void drawFullScreen();
void drawWeatherPanel();
void drawCatPanel();
void drawWeatherIcon(int x, int y, int code, int size);
bool fetchWeather();

// ---- Weather icon drawing (bold, scaled to size) ----
void drawWeatherIcon(int x, int y, int code, int size)
{
  // x,y is top-left corner; size is width/height
  int cx = x + size / 2;
  int cy = y + size / 2;
  // Scale factor: size/24 gives 1.0 at default, larger for bigger icons
  int s = size;

  if (code == 0)
  {
    // Sun: filled circle + thick rays
    int r = s * 5 / 24;
    epaper.fillCircle(cx, cy, r, TFT_BLACK);
    epaper.fillCircle(cx, cy, r - 2, TFT_WHITE);
    epaper.fillCircle(cx, cy, r - 3, TFT_WHITE);
    for (int a = 0; a < 360; a += 45)
    {
      float rad = a * 0.0174532925;
      int x1 = cx + (int)((r + 2) * cos(rad));
      int y1 = cy + (int)((r + 2) * sin(rad));
      int x2 = cx + (int)((r + s / 4) * cos(rad));
      int y2 = cy + (int)((r + s / 4) * sin(rad));
      epaper.drawLine(x1, y1, x2, y2, TFT_BLACK);
      epaper.drawLine(x1 + 1, y1, x2 + 1, y2, TFT_BLACK);
    }
  }
  else if (code <= 2)
  {
    // Partly cloudy: bold sun + bold cloud
    int sx = cx - s / 6, sy = cy - s / 6;
    int sr = s / 5;
    epaper.fillCircle(sx, sy, sr, TFT_BLACK);
    epaper.fillCircle(sx, sy, sr - 2, TFT_WHITE);
    for (int a = 0; a < 360; a += 60)
    {
      float rad = a * 0.0174532925;
      int x1 = sx + (int)((sr + 1) * cos(rad));
      int y1 = sy + (int)((sr + 1) * sin(rad));
      int x2 = sx + (int)((sr + 4) * cos(rad));
      int y2 = sy + (int)((sr + 4) * sin(rad));
      epaper.drawLine(x1, y1, x2, y2, TFT_BLACK);
    }
    // Bold cloud overlapping sun
    int clx = cx + s / 8, cly = cy + s / 8;
    int cr = s / 5;
    epaper.fillCircle(clx - cr, cly, cr, TFT_BLACK);
    epaper.fillCircle(clx + cr, cly, cr, TFT_BLACK);
    epaper.fillCircle(clx, cly - cr / 2, cr, TFT_BLACK);
    epaper.fillRect(clx - cr, cly, cr * 2, cr, TFT_BLACK);
    // White interior
    int ci = cr - 2;
    epaper.fillCircle(clx - cr, cly, ci, TFT_WHITE);
    epaper.fillCircle(clx + cr, cly, ci, TFT_WHITE);
    epaper.fillCircle(clx, cly - cr / 2, ci, TFT_WHITE);
    epaper.fillRect(clx - cr + 1, cly - ci / 2, cr * 2 - 2, ci, TFT_WHITE);
  }
  else if (code == 3)
  {
    // Overcast: bold double cloud
    int cr = s / 4;
    epaper.fillCircle(cx - cr, cy + 2, cr, TFT_BLACK);
    epaper.fillCircle(cx + cr, cy + 2, cr, TFT_BLACK);
    epaper.fillCircle(cx, cy - cr / 2, cr + 1, TFT_BLACK);
    epaper.fillRect(cx - cr, cy + 2, cr * 2, cr, TFT_BLACK);
    // White interior
    int ci = cr - 2;
    epaper.fillCircle(cx - cr, cy + 2, ci, TFT_WHITE);
    epaper.fillCircle(cx + cr, cy + 2, ci, TFT_WHITE);
    epaper.fillCircle(cx, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillRect(cx - cr + 1, cy, cr * 2 - 2, ci, TFT_WHITE);
  }
  else if (code == 45 || code == 48)
  {
    // Fog: thick horizontal bars
    int hw = s * 5 / 12;
    for (int i = -2; i <= 2; i++)
    {
      int ly = cy + i * (s / 5);
      epaper.fillRect(cx - hw, ly, hw * 2, 2, TFT_BLACK);
    }
  }
  else if (code >= 51 && code <= 55)
  {
    // Drizzle: bold cloud + dots
    int cr = s / 5;
    epaper.fillCircle(cx - cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx + cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx, cy - cr, cr, TFT_BLACK);
    epaper.fillRect(cx - cr, cy - cr / 2, cr * 2, cr, TFT_BLACK);
    int ci = cr - 2;
    epaper.fillCircle(cx - cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx + cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx, cy - cr, ci, TFT_WHITE);
    epaper.fillRect(cx - cr + 1, cy - cr / 2, cr * 2 - 2, ci, TFT_WHITE);
    // Dots
    epaper.fillCircle(cx - s / 6, cy + s / 4, 2, TFT_BLACK);
    epaper.fillCircle(cx + s / 6, cy + s / 4, 2, TFT_BLACK);
    epaper.fillCircle(cx, cy + s / 3, 2, TFT_BLACK);
  }
  else if ((code >= 61 && code <= 65) || (code >= 80 && code <= 82))
  {
    // Rain: bold cloud + thick rain lines
    int cr = s / 5;
    epaper.fillCircle(cx - cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx + cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx, cy - cr, cr, TFT_BLACK);
    epaper.fillRect(cx - cr, cy - cr / 2, cr * 2, cr, TFT_BLACK);
    int ci = cr - 2;
    epaper.fillCircle(cx - cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx + cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx, cy - cr, ci, TFT_WHITE);
    epaper.fillRect(cx - cr + 1, cy - cr / 2, cr * 2 - 2, ci, TFT_WHITE);
    // Rain lines (thick)
    int ry = cy + s / 6;
    for (int d = -1; d <= 1; d++)
    {
      int rx = cx + d * (s / 4);
      epaper.drawLine(rx, ry, rx - 2, ry + s / 4, TFT_BLACK);
      epaper.drawLine(rx + 1, ry, rx - 1, ry + s / 4, TFT_BLACK);
    }
  }
  else if (code >= 71 && code <= 75)
  {
    // Snow: bold cloud + bold snowflakes
    int cr = s / 5;
    epaper.fillCircle(cx - cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx + cr, cy - cr / 2, cr, TFT_BLACK);
    epaper.fillCircle(cx, cy - cr, cr, TFT_BLACK);
    epaper.fillRect(cx - cr, cy - cr / 2, cr * 2, cr, TFT_BLACK);
    int ci = cr - 2;
    epaper.fillCircle(cx - cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx + cr, cy - cr / 2, ci, TFT_WHITE);
    epaper.fillCircle(cx, cy - cr, ci, TFT_WHITE);
    epaper.fillRect(cx - cr + 1, cy - cr / 2, cr * 2 - 2, ci, TFT_WHITE);
    // Snowflakes (filled circles)
    int sr = s / 10;
    if (sr < 2) sr = 2;
    epaper.fillCircle(cx - s / 6, cy + s / 4, sr, TFT_BLACK);
    epaper.fillCircle(cx + s / 6, cy + s / 4, sr, TFT_BLACK);
    epaper.fillCircle(cx, cy + s / 3 + 2, sr, TFT_BLACK);
  }
  else if (code >= 95 && code <= 99)
  {
    // Thunder: bold cloud + filled lightning bolt
    int cr = s / 5;
    epaper.fillCircle(cx - cr, cy - cr, cr, TFT_BLACK);
    epaper.fillCircle(cx + cr, cy - cr, cr, TFT_BLACK);
    epaper.fillCircle(cx, cy - cr - cr / 2, cr, TFT_BLACK);
    epaper.fillRect(cx - cr, cy - cr, cr * 2, cr, TFT_BLACK);
    int ci = cr - 2;
    epaper.fillCircle(cx - cr, cy - cr, ci, TFT_WHITE);
    epaper.fillCircle(cx + cr, cy - cr, ci, TFT_WHITE);
    epaper.fillCircle(cx, cy - cr - cr / 2, ci, TFT_WHITE);
    epaper.fillRect(cx - cr + 1, cy - cr, cr * 2 - 2, ci, TFT_WHITE);
    // Lightning bolt (filled triangle zigzag)
    int ly = cy + 1;
    epaper.fillTriangle(cx + 2, ly, cx - 4, ly + s / 4, cx + 3, ly + s / 4, TFT_BLACK);
    epaper.fillTriangle(cx - 3, ly + s / 4 - 2, cx - 2, ly + s / 2, cx + 4, ly + s / 4 - 2, TFT_BLACK);
  }
  else
  {
    // Unknown: bold question mark
    epaper.drawCentreString("?", cx, cy - 8, 4);
  }
}

// ---- Fetch and parse weather data ----
bool fetchWeather()
{
  Serial.print("[HTTP] GET ");
  Serial.println(weatherURL);

  HTTPClient http;
  http.begin(weatherURL);
  int httpCode = http.GET();

  Serial.print("[HTTP] Response code: ");
  Serial.println(httpCode);

  if (httpCode != 200)
  {
    http.end();
    Serial.println("[HTTP] Non-200 response, aborting");
    return false;
  }

  String payload = http.getString();
  http.end();

  Serial.print("[JSON] Payload length: ");
  Serial.println(payload.length());

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, payload);
  if (err)
  {
    Serial.print("[JSON] Parse error: ");
    Serial.println(err.c_str());
    return false;
  }
  Serial.println("[JSON] Parsed OK");

  // Current weather
  JsonObject cur = doc["current_weather"];
  if (cur.isNull())
  {
    Serial.println("[JSON] current_weather is null!");
    return false;
  }

  currentTemp = (int)(cur["temperature"].as<float>() + 0.5f);
  currentWind = (int)(cur["windspeed"].as<float>() + 0.5f);
  currentWeathercode = cur["weathercode"].as<int>();

  // Parse current hour from time string "2025-01-15T14:00"
  const char *timeStr = cur["time"].as<const char *>();
  if (!timeStr)
  {
    Serial.println("[JSON] current_weather.time is null!");
    return false;
  }
  Serial.print("[WEATHER] Current time: ");
  Serial.println(timeStr);

  currentHour = parseHourFromTimeStr(timeStr);

  // Parse current date to distinguish today vs tomorrow
  int curDay = parseDayFromTimeStr(timeStr);

  // Parse hourly data
  JsonArray times = doc["hourly"]["time"];
  JsonArray temps = doc["hourly"]["temperature_2m"];
  JsonArray rainPcts = doc["hourly"]["precipitation_probability"];
  JsonArray codes = doc["hourly"]["weathercode"];
  JsonArray winds = doc["hourly"]["windspeed_10m"];

  todayCount = 0;
  tomorrowCount = 0;

  int totalHours = times.size();

  for (int i = 0; i < totalHours && (todayCount < 6 || tomorrowCount < 4); i++)
  {
    const char *t = times[i].as<const char *>();
    int entryDay = parseDayFromTimeStr(t);
    int entryHour = parseHourFromTimeStr(t);

    if (entryDay == curDay && entryHour > currentHour && todayCount < 6)
    {
      // Today: pick entries roughly every 2-3 hours
      int hoursAhead = entryHour - currentHour;
      // Pick at roughly 2, 4, 6, 8, 10, 12 hours ahead (or whatever's available)
      bool pick = false;
      if (todayCount == 0 && hoursAhead >= 1)
        pick = true;
      else if (todayCount > 0)
      {
        int gap = entryHour - todayBlocks[todayCount - 1].hour;
        if (gap >= 2)
          pick = true;
      }

      if (pick)
      {
        todayBlocks[todayCount].hour = entryHour;
        todayBlocks[todayCount].temp = (int)(temps[i].as<float>() + 0.5f);
        todayBlocks[todayCount].rainPct = rainPcts[i].as<int>();
        todayBlocks[todayCount].wind = (int)(winds[i].as<float>() + 0.5f);
        todayBlocks[todayCount].weathercode = codes[i].as<int>();
        todayCount++;
      }
    }
    else if (entryDay != curDay && tomorrowCount < 4)
    {
      // Tomorrow: pick hours 09, 12, 15, 18
      if (entryHour == 9 || entryHour == 12 ||
          entryHour == 15 || entryHour == 18)
      {
        tomorrowBlocks[tomorrowCount].hour = entryHour;
        tomorrowBlocks[tomorrowCount].temp = (int)(temps[i].as<float>() + 0.5f);
        tomorrowBlocks[tomorrowCount].rainPct = rainPcts[i].as<int>();
        tomorrowBlocks[tomorrowCount].wind = (int)(winds[i].as<float>() + 0.5f);
        tomorrowBlocks[tomorrowCount].weathercode = codes[i].as<int>();
        tomorrowCount++;
      }
    }
  }

  weatherValid = true;

  Serial.print("[WEATHER] Now: ");
  Serial.print(currentTemp);
  Serial.print("C, wind ");
  Serial.print(currentWind);
  Serial.print("km/h, code ");
  Serial.print(currentWeathercode);
  Serial.print(" (");
  Serial.print(weatherDescription(currentWeathercode));
  Serial.println(")");
  Serial.print("[WEATHER] Today blocks: ");
  Serial.print(todayCount);
  Serial.print(", Tomorrow blocks: ");
  Serial.println(tomorrowCount);

  return true;
}

// ---- Draw a dotted horizontal line ----
void drawDottedLine(int x1, int x2, int y)
{
  for (int x = x1; x < x2; x += 4)
  {
    epaper.drawPixel(x, y, TFT_BLACK);
  }
}

// ---- Battery reading (TRMNL EE04: load switch on GPIO6, ADC on GPIO1) ----
int readBatteryPct()
{
  pinMode(PIN_VBAT_SWITCH, OUTPUT);
  digitalWrite(PIN_VBAT_SWITCH, HIGH);
  delay(10);

  analogRead(PIN_BATTERY); // throwaway read to init ADC
  int32_t adc = 0;
  for (int i = 0; i < 8; i++)
  {
    adc += analogReadMilliVolts(PIN_BATTERY);
  }

  digitalWrite(PIN_VBAT_SWITCH, LOW);

  int mv = (adc / 8) * 2; // average, then x2 for voltage divider
  float voltage = mv / 1000.0f;

  Serial.print("[BATTERY] Voltage: ");
  Serial.print(voltage, 2);
  Serial.println("V");

  return voltageToPercent(voltage);
}

// ---- Draw battery icon (top-right corner) ----
void drawBatteryIcon(int x, int y, int pct)
{
  // Battery body: 28x14, nub on right: 3x6
  int w = 28, h = 14;
  epaper.drawRect(x, y, w, h, TFT_BLACK);
  epaper.drawRect(x + 1, y + 1, w - 2, h - 2, TFT_BLACK);
  // Terminal nub
  epaper.fillRect(x + w, y + 4, 3, 6, TFT_BLACK);

  // Fill level (inside the outline, 2px margin)
  int fillW = (w - 6) * pct / 100;
  if (fillW > 0)
    epaper.fillRect(x + 3, y + 3, fillW, h - 6, TFT_BLACK);
}

// ---- Column positions for forecast rows ----
// TIME    ICON   TEMP    RAIN%    WIND
// 15      85     115     205      290
#define COL_TIME  15
#define COL_ICON  80
#define COL_TEMP  120
#define COL_RAIN  210
#define COL_WIND  295

// ---- Draw a single forecast row at fixed columns ----
void drawForecastRow(int y, const HourlyForecast &f)
{
  char buf[20];

  // Time
  snprintf(buf, sizeof(buf), "%02d:00", f.hour);
  epaper.drawString(buf, COL_TIME, y, 4);

  // Icon
  drawWeatherIcon(COL_ICON, y - 4, f.weathercode, 28);

  // Temperature (right-aligned at COL_RAIN - gap)
  snprintf(buf, sizeof(buf), "%d%cC", f.temp, (char)247);
  epaper.drawString(buf, COL_TEMP, y, 4);

  // Rain probability
  snprintf(buf, sizeof(buf), "%d%%", f.rainPct);
  epaper.drawString(buf, COL_RAIN, y, 4);

  // Wind
  snprintf(buf, sizeof(buf), "%dkm/h", f.wind);
  epaper.drawString(buf, COL_WIND, y, 4);
}

// ---- Draw weather panel (left half: x 10-390) ----
void drawWeatherPanel()
{
  if (!weatherValid)
  {
    epaper.setTextColor(TFT_BLACK, TFT_WHITE);
    epaper.drawCentreString("No weather data", 200, 200, 4);
    return;
  }

  epaper.setTextColor(TFT_BLACK, TFT_WHITE);

  // Header — city skyline behind title
  // Skyline sits on the separator line (y=34), buildings rise up behind text
  int baseY = 34; // ground level = separator line

  // Far-left cluster
  epaper.fillRect(14, baseY - 14, 8, 14, TFT_BLACK);   // short block
  epaper.fillRect(24, baseY - 20, 6, 20, TFT_BLACK);    // taller narrow
  epaper.fillRect(32, baseY - 10, 10, 10, TFT_BLACK);   // squat
  epaper.fillRect(44, baseY - 16, 7, 16, TFT_BLACK);    // medium

  // Left buildings
  epaper.fillRect(58, baseY - 22, 10, 22, TFT_BLACK);   // tower
  epaper.fillRect(55, baseY - 22, 16, 3, TFT_BLACK);    // ledge
  epaper.fillRect(70, baseY - 12, 12, 12, TFT_BLACK);   // wide low
  epaper.fillRect(84, baseY - 18, 8, 18, TFT_BLACK);    // narrow tall

  // Castle rock / Edinburgh Castle (left of center)
  epaper.fillRect(100, baseY - 14, 20, 14, TFT_BLACK);  // castle base
  epaper.fillRect(104, baseY - 20, 5, 6, TFT_BLACK);    // turret left
  epaper.fillRect(112, baseY - 22, 5, 8, TFT_BLACK);    // turret right
  epaper.fillTriangle(106, baseY - 20, 104, baseY - 20, 105, baseY - 24, TFT_BLACK); // flag pole turret
  epaper.fillRect(96, baseY - 8, 28, 8, TFT_BLACK);     // rock base wider

  // Scott Monument / spire (center-left, peeks above text)
  epaper.fillRect(140, baseY - 18, 6, 18, TFT_BLACK);   // spire base
  epaper.fillTriangle(139, baseY - 18, 147, baseY - 18, 143, baseY - 30, TFT_BLACK); // spire top

  // Center gap — "Edinburgh" text lives here (roughly x=135-265)
  // Keep buildings low or absent in center so text is readable

  // Calton Hill / monument (center-right)
  epaper.fillRect(270, baseY - 12, 22, 12, TFT_BLACK);  // hill base
  epaper.fillRect(275, baseY - 20, 3, 8, TFT_BLACK);    // column left
  epaper.fillRect(282, baseY - 20, 3, 8, TFT_BLACK);    // column right
  epaper.drawLine(274, baseY - 20, 286, baseY - 20, TFT_BLACK); // lintel
  epaper.drawLine(274, baseY - 21, 286, baseY - 21, TFT_BLACK); // lintel thick

  // W Hotel / St James Centre "jobby" — bulging barrel shape next to Calton Hill
  {
    int wx = 296; // center x of the W Hotel
    // Rectangular base (St James Quarter mall underneath)
    epaper.fillRect(wx - 8, baseY - 10, 16, 10, TFT_BLACK);
    // Bulging barrel body — stack of circles to make the curved blob
    epaper.fillCircle(wx, baseY - 14, 7, TFT_BLACK);
    epaper.fillCircle(wx, baseY - 19, 8, TFT_BLACK);  // widest bulge
    epaper.fillCircle(wx, baseY - 24, 7, TFT_BLACK);
    epaper.fillCircle(wx, baseY - 28, 5, TFT_BLACK);  // tapers at top
    // Fill the gaps between circles for solid silhouette
    epaper.fillRect(wx - 8, baseY - 22, 16, 12, TFT_BLACK);
  }

  // Right buildings
  epaper.fillRect(310, baseY - 16, 8, 16, TFT_BLACK);
  epaper.fillRect(320, baseY - 24, 7, 24, TFT_BLACK);   // tall tower
  epaper.fillTriangle(319, baseY - 24, 328, baseY - 24, 323, baseY - 30, TFT_BLACK); // pointed roof
  epaper.fillRect(330, baseY - 10, 12, 10, TFT_BLACK);  // low wide
  epaper.fillRect(344, baseY - 18, 8, 18, TFT_BLACK);   // medium

  // Far-right cluster
  epaper.fillRect(356, baseY - 14, 10, 14, TFT_BLACK);
  epaper.fillRect(368, baseY - 20, 6, 20, TFT_BLACK);
  epaper.fillRect(376, baseY - 8, 12, 8, TFT_BLACK);    // squat
  epaper.fillRect(382, baseY - 12, 8, 12, TFT_BLACK);

  // Ground / separator lines (drawn on top of buildings base)
  epaper.drawLine(10, baseY - 1, 390, baseY - 1, TFT_BLACK);
  epaper.drawLine(10, baseY, 390, baseY, TFT_BLACK);

  // Title text on top of skyline (white background box behind text for readability)
  epaper.fillRect(130, 2, 140, 28, TFT_WHITE);  // clear area behind text
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Edinburgh", 200, 6, 4);

  // "Now" section — bold font 4
  drawWeatherIcon(12, 40, currentWeathercode, 32);
  char nowBuf[60];
  snprintf(nowBuf, sizeof(nowBuf), "%d%cC  %s  %dkm/h",
           currentTemp, (char)247, weatherDescription(currentWeathercode), currentWind);
  epaper.drawString(nowBuf, 54, 46, 4);
  epaper.drawLine(10, 74, 390, 74, TFT_BLACK);
  epaper.drawLine(10, 76, 390, 76, TFT_BLACK);

  // "Today" subheader
  epaper.drawString("Today", 15, 82, 4);

  // Today rows (up to 6, font 4, 36px row height)
  int rowH = 36;
  int todayStartY = 110;
  for (int i = 0; i < todayCount; i++)
  {
    int y = todayStartY + i * rowH;

    // Alternating shaded band on odd rows
    if (i % 2 == 1)
    {
      for (int py = y - 2; py < y + rowH - 4; py += 2)
        for (int px = 12; px < 388; px += 3)
          epaper.drawPixel(px, py, TFT_BLACK);
    }

    drawForecastRow(y, todayBlocks[i]);

    // Dotted separator after each row (except last)
    if (i < todayCount - 1)
      drawDottedLine(15, 388, y + rowH - 4);
  }

  // Separator before tomorrow
  int tomorrowSepY = todayStartY + todayCount * rowH + 4;
  if (tomorrowSepY < 310)
    tomorrowSepY = 310;
  epaper.drawLine(10, tomorrowSepY, 390, tomorrowSepY, TFT_BLACK);
  epaper.drawLine(10, tomorrowSepY + 2, 390, tomorrowSepY + 2, TFT_BLACK);

  // "Tomorrow" subheader
  int tmrHeaderY = tomorrowSepY + 8;
  epaper.drawString("Tomorrow", 15, tmrHeaderY, 4);

  // Tomorrow rows (up to 4, font 4, 34px row height)
  int tmrRowH = 34;
  int tmrStartY = tmrHeaderY + 30;
  for (int i = 0; i < tomorrowCount; i++)
  {
    int y = tmrStartY + i * tmrRowH;

    // Alternating shaded band on odd rows
    if (i % 2 == 1)
    {
      for (int py = y - 2; py < y + tmrRowH - 4; py += 2)
        for (int px = 12; px < 388; px += 3)
          epaper.drawPixel(px, py, TFT_BLACK);
    }

    drawForecastRow(y, tomorrowBlocks[i]);

    // Dotted separator after each row (except last)
    if (i < tomorrowCount - 1)
      drawDottedLine(15, 388, y + tmrRowH - 4);
  }
}

// ---- Draw cat panel (right half: x 400-800) ----
void drawCatPanel()
{
  // Vertical divider
  epaper.drawLine(400, 0, 400, 480, TFT_BLACK);

  switch (currentCat)
  {
  case 0:
    drawCat0();
    break;
  case 1:
    drawCat1();
    break;
  case 2:
    drawCat2();
    break;
  case 3:
    drawCat3();
    break;
  case 4:
    drawCat4();
    break;
  case 5:
    drawCat5();
    break;
  case 6:
    drawCat6();
    break;
  case 7:
    drawCat7();
    break;
  case 8:
    drawCat8();
    break;
  case 9:
    drawCat9();
    break;
  case 10:
    drawCat10();
    break;
  case 11:
    drawCat11();
    break;
  case 12:
    drawCat12();
    break;
  case 13:
    drawCat13();
    break;
  case 14:
    drawCat14();
    break;
  case 15:
    drawCat15();
    break;
  case 16:
    drawCat16();
    break;
  case 17:
    drawCat17();
    break;
  case 18:
    drawCat18();
    break;
  case 19:
    drawCat19();
    break;
  case 20:
    drawCat20();
    break;
  case 21:
    drawCat21();
    break;
  case 22:
    drawCat22();
    break;
  case 23:
    drawCat23();
    break;
  case 24:
    drawCat24();
    break;
  case 25:
    drawCat25();
    break;
  case 26:
    drawCat26();
    break;
  case 27:
    drawCat27();
    break;
  case 28:
    drawCat28();
    break;
  }
}

// ---- Draw full screen ----
void drawFullScreen()
{
  epaper.fillScreen(TFT_WHITE);
  drawWeatherPanel();
  drawCatPanel();
  // Battery icon top-right
  if (batteryPct >= 0)
    drawBatteryIcon(765, 5, batteryPct);
  epaper.update();
}

#include "cats.h"

#endif

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
  Serial.println("TRMNL Weather+Cats starting...");

#ifdef EPAPER_ENABLE
  Serial.println("[INIT] epaper.begin()");
  epaper.begin();
  epaper.setRotation(0);
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);

  // Show connecting splash
  epaper.fillScreen(TFT_WHITE);
  epaper.drawCentreString("Connecting to WiFi...", 400, 220, 4);
  epaper.update();

  // Connect to WiFi
  Serial.print("[WIFI] Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 15000)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("[WIFI] Connected! IP: ");
    Serial.println(WiFi.localIP());

    // Show fetching splash
    epaper.fillScreen(TFT_WHITE);
    epaper.drawCentreString("Fetching weather...", 400, 220, 4);
    epaper.update();

    Serial.println("[WEATHER] Fetching weather data...");
    bool ok = fetchWeather();
    Serial.print("[WEATHER] Fetch result: ");
    Serial.println(ok ? "OK" : "FAILED");
  }
  else
  {
    Serial.print("[WIFI] Connection failed! Status: ");
    Serial.println(WiFi.status());
  }

  // Read battery level
  batteryPct = readBatteryPct();
  Serial.print("[BATTERY] Level: ");
  Serial.print(batteryPct);
  Serial.println("%");

  // Draw full screen (weather + cat)
  Serial.println("[DRAW] Drawing full screen");
  drawFullScreen();

  targetTime = millis() + 60000;
  weatherRefreshTime = millis() + 1800000;  // 30 minutes
  batteryRefreshTime = millis() + 3600000;  // 1 hour
  Serial.println("[INIT] Setup complete");
#endif
}

void loop()
{
#ifdef EPAPER_ENABLE
  // Cycle cat every 60 seconds
  if (millis() > targetTime)
  {
    currentCat = (currentCat + 1) % 29;
    drawFullScreen();
    targetTime = millis() + 60000;
  }

  // Refresh weather every 30 minutes
  if (millis() > weatherRefreshTime)
  {
    Serial.println("[LOOP] Weather refresh triggered");
    if (WiFi.status() == WL_CONNECTED)
    {
      fetchWeather();
    }
    else
    {
      Serial.print("[LOOP] WiFi not connected, status: ");
      Serial.println(WiFi.status());
    }
    weatherRefreshTime = millis() + 1800000;
  }

  // Refresh battery every hour
  if (millis() > batteryRefreshTime)
  {
    batteryPct = readBatteryPct();
    Serial.print("[LOOP] Battery: ");
    Serial.print(batteryPct);
    Serial.println("%");
    batteryRefreshTime = millis() + 3600000;
  }
#endif
}
