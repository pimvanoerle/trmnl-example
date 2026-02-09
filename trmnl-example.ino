#include <SPI.h>
#include <TFT_eSPI.h>

#ifdef EPAPER_ENABLE

#include "soc/usb_serial_jtag_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_task_wdt.h"
#include "rom/rtc.h"
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
    "&daily=sunrise,sunset"
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
char sunriseStr[6] = "";  // "HH:MM"
char sunsetStr[6] = "";   // "HH:MM"

// ---- Battery reading (TRMNL EE04 board) ----
#define PIN_BATTERY 1
#define PIN_VBAT_SWITCH 6

EPaper epaper = EPaper();

int currentCat = 0;
uint32_t targetTime = 0;
uint32_t weatherRefreshTime = 0;
uint32_t batteryRefreshTime = 0;
int batteryPct = -1;    // -1 = not yet read
bool batteryCharging = false;

// ---- Crash tracking (survives reboot) ----
RTC_NOINIT_ATTR int lastCatDrawn;
RTC_NOINIT_ATTR char lastDrawPhase[16];

// ---- Forward declarations ----
int readBatteryPct();
void drawBatteryIcon(int x, int y, int pct);
void drawClock();
void drawSunTimes();
void drawBusPanel();
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
void drawCat29();
void drawCat30();
void drawCat31();
void drawCat32();
void drawCat33();
void drawCat34();
void drawCat35();
void drawCat36();
void drawCat37();
void drawCat38();
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

  // Parse sunrise/sunset (ISO format "2025-01-15T08:43")
  const char *rise = doc["daily"]["sunrise"][0].as<const char *>();
  const char *set  = doc["daily"]["sunset"][0].as<const char *>();
  if (rise && strlen(rise) >= 16)
  {
    memcpy(sunriseStr, rise + 11, 5);
    sunriseStr[5] = '\0';
  }
  if (set && strlen(set) >= 16)
  {
    memcpy(sunsetStr, set + 11, 5);
    sunsetStr[5] = '\0';
  }

  weatherValid = true;

  Serial.print("[WEATHER] Sunrise: ");
  Serial.print(sunriseStr);
  Serial.print("  Sunset: ");
  Serial.println(sunsetStr);
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

  // Detect USB by checking if SOF frame counter is incrementing
  uint32_t frame1 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
  delay(2);
  uint32_t frame2 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
  batteryCharging = (frame1 != frame2);

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

  // Lightning bolt overlay when charging
  if (batteryCharging)
  {
    int cx = x + w / 2;
    int cy = y + h / 2;
    // Draw bolt in white over fill, with black outline for contrast
    // Bolt shape: top-left to center-right, then center-left to bottom-right
    epaper.drawLine(cx + 1, cy - 5, cx - 2, cy, TFT_WHITE);
    epaper.drawLine(cx - 2, cy, cx + 2, cy, TFT_WHITE);
    epaper.drawLine(cx + 2, cy, cx - 1, cy + 5, TFT_WHITE);
    // Slightly offset duplicate for thickness
    epaper.drawLine(cx + 2, cy - 5, cx - 1, cy, TFT_WHITE);
    epaper.drawLine(cx - 1, cy, cx + 3, cy, TFT_WHITE);
    epaper.drawLine(cx + 3, cy, cx, cy + 5, TFT_WHITE);
  }
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

  // Sunrise/sunset is drawn separately in drawSunTimes()

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

  lastCatDrawn = currentCat;
  strncpy(lastDrawPhase, "cat", sizeof(lastDrawPhase));
  Serial.print("[DRAW] Drawing cat #");
  Serial.println(currentCat);

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
  case 29:
    drawCat29();
    break;
  case 30:
    drawCat30();
    break;
  case 31:
    drawCat31();
    break;
  case 32:
    drawCat32();
    break;
  case 33:
    drawCat33();
    break;
  case 34:
    drawCat34();
    break;
  case 35:
    drawCat35();
    break;
  case 36:
    drawCat36();
    break;
  case 37:
    drawCat37();
    break;
  case 38:
    drawCat38();
    break;
  }
}

// ---- Draw clock (HH:MM) top-right, left of battery ----
void drawClock()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 5000))
  {
    Serial.println("[CLOCK] NTP time not available");
    return;
  }
  char buf[6];
  snprintf(buf, sizeof(buf), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  epaper.drawRightString(buf, 758, 5, 2);
  epaper.drawRightString(buf, 759, 5, 2);
}

// ---- Draw sunrise/sunset in cat panel top-left ----
void drawSunTimes()
{
  if (!sunriseStr[0] || !sunsetStr[0])
    return;

  int x = 408;
  int y = 4;

  // --- Sunrise icon: half-sun above horizon with rays ---
  int cx = x + 8, cy = y + 12; // center of horizon line
  // Horizon line
  epaper.drawLine(cx - 8, cy, cx + 8, cy, TFT_BLACK);
  epaper.drawLine(cx - 8, cy + 1, cx + 8, cy + 1, TFT_BLACK);
  // Half-circle (upper) for rising sun
  for (int a = 180; a <= 360; a += 2)
  {
    int px = cx + (int)(6 * cos(a * 0.0174532925));
    int py = cy + (int)(6 * sin(a * 0.0174532925));
    epaper.drawPixel(px, py, TFT_BLACK);
    epaper.drawPixel(px + 1, py, TFT_BLACK);
  }
  // Rays above
  epaper.drawLine(cx, cy - 8, cx, cy - 11, TFT_BLACK);
  epaper.drawLine(cx - 5, cy - 6, cx - 7, cy - 9, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 6, cx + 7, cy - 9, TFT_BLACK);

  // Sunrise time (bold, font 2)
  epaper.drawString(sunriseStr, x + 20, y, 2);
  epaper.drawString(sunriseStr, x + 21, y, 2);

  // --- Sunset icon: half-sun below horizon with rays going down ---
  int x2 = x + 80;
  int cx2 = x2 + 8, cy2 = y + 12;
  // Horizon line
  epaper.drawLine(cx2 - 8, cy2, cx2 + 8, cy2, TFT_BLACK);
  epaper.drawLine(cx2 - 8, cy2 + 1, cx2 + 8, cy2 + 1, TFT_BLACK);
  // Half-circle (lower) for setting sun
  for (int a = 0; a <= 180; a += 2)
  {
    int px = cx2 + (int)(6 * cos(a * 0.0174532925));
    int py = cy2 + (int)(6 * sin(a * 0.0174532925));
    epaper.drawPixel(px, py, TFT_BLACK);
    epaper.drawPixel(px + 1, py, TFT_BLACK);
  }
  // Rays below
  epaper.drawLine(cx2, cy2 + 4, cx2, cy2 + 7, TFT_BLACK);
  epaper.drawLine(cx2 - 5, cy2 + 3, cx2 - 7, cy2 + 5, TFT_BLACK);
  epaper.drawLine(cx2 + 5, cy2 + 3, cx2 + 7, cy2 + 5, TFT_BLACK);

  // Sunset time (bold, font 2)
  epaper.drawString(sunsetStr, x2 + 20, y, 2);
  epaper.drawString(sunsetStr, x2 + 21, y, 2);
}

// ---- Draw bus departure panel (Lothian Buses style, bottom of cat panel) ----
void drawBusPanel()
{
  int px = 401; // panel left (just past divider)
  int py = 325; // panel top
  int pw = 399; // panel width
  int ph = 155; // panel height

  // -- Header bar (dark background, white text, TfE style) --
  epaper.fillRect(px, py, pw, 26, TFT_BLACK);
  epaper.setTextColor(TFT_WHITE, TFT_BLACK);
  epaper.drawString("BUS DEPARTURES", px + 8, py + 5, 2);
  epaper.drawString("BUS DEPARTURES", px + 9, py + 5, 2); // bold
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);

  // -- Column headers --
  int hy = py + 30;
  epaper.drawString("Service", px + 8, hy, 1);
  epaper.drawString("Destination", px + 70, hy, 1);
  epaper.drawString("Departs", px + 310, hy, 1);
  epaper.drawLine(px, hy + 12, px + pw, hy + 12, TFT_BLACK);

  // -- Placeholder bus data (3 rows) --
  const char *routes[]  = {"10",  "27",  "45"};
  const char *dests[]   = {"Torphin",  "Silverknowes",  "Heriot-Watt"};
  const char *times[]   = {"Due",  "4 min",  "12 min"};

  int rowY = hy + 18;
  int rowH = 36;

  for (int i = 0; i < 3; i++)
  {
    int ry = rowY + i * rowH;

    // Route number in rounded box (Lothian style)
    int boxX = px + 8;
    int boxW = 38;
    int boxH = 24;
    int boxY = ry + 2;
    // Rounded box: fill + rounded corners
    epaper.fillRect(boxX + 3, boxY, boxW - 6, boxH, TFT_BLACK);
    epaper.fillRect(boxX, boxY + 3, boxW, boxH - 6, TFT_BLACK);
    epaper.fillCircle(boxX + 3, boxY + 3, 3, TFT_BLACK);
    epaper.fillCircle(boxX + boxW - 4, boxY + 3, 3, TFT_BLACK);
    epaper.fillCircle(boxX + 3, boxY + boxH - 4, 3, TFT_BLACK);
    epaper.fillCircle(boxX + boxW - 4, boxY + boxH - 4, 3, TFT_BLACK);
    // Route number (white on black, centred in box)
    epaper.setTextColor(TFT_WHITE, TFT_BLACK);
    int textW = epaper.textWidth(routes[i], 2);
    epaper.drawString(routes[i], boxX + (boxW - textW) / 2, boxY + 4, 2);
    epaper.setTextColor(TFT_BLACK, TFT_WHITE);

    // Destination
    epaper.drawString(dests[i], px + 70, ry + 4, 2);
    epaper.drawString(dests[i], px + 71, ry + 4, 2); // bold

    // Departure time (right-aligned)
    epaper.drawRightString(times[i], px + pw - 8, ry + 4, 2);
    epaper.drawRightString(times[i], px + pw - 7, ry + 4, 2); // bold

    // Row separator (except after last)
    if (i < 2)
    {
      int sepY = ry + rowH - 2;
      epaper.drawLine(px + 4, sepY, px + pw - 4, sepY, TFT_BLACK);
    }
  }
}

// ---- Draw full screen ----
void drawFullScreen()
{
  epaper.fillScreen(TFT_WHITE);

  strncpy(lastDrawPhase, "weather", sizeof(lastDrawPhase));
  Serial.println("[DRAW] Weather panel");
  drawWeatherPanel();

  strncpy(lastDrawPhase, "cat", sizeof(lastDrawPhase));
  Serial.println("[DRAW] Cat panel");
  drawCatPanel();

  strncpy(lastDrawPhase, "bus", sizeof(lastDrawPhase));
  Serial.println("[DRAW] Bus panel");
  drawBusPanel();

  strncpy(lastDrawPhase, "sunTimes", sizeof(lastDrawPhase));
  drawSunTimes();

  strncpy(lastDrawPhase, "clock", sizeof(lastDrawPhase));
  drawClock();

  // Battery icon top-right
  if (batteryPct >= 0)
    drawBatteryIcon(765, 5, batteryPct);

  strncpy(lastDrawPhase, "epd_update", sizeof(lastDrawPhase));
  Serial.println("[DRAW] Updating e-paper");
  esp_task_wdt_reset();
  epaper.update();

  strncpy(lastDrawPhase, "done", sizeof(lastDrawPhase));
  Serial.println("[DRAW] Done");
  esp_task_wdt_reset();
}

#include "cats.h"

#endif

void setup()
{
  // Enable brownout detector — triggers clean reboot on USB disconnect voltage dip
  REG_SET_BIT(RTC_CNTL_BROWN_OUT_REG, RTC_CNTL_BROWN_OUT_ENA);

  Serial.begin(115200);
  unsigned long serialWait = millis();
  while (!Serial && millis() - serialWait < 2000)
    delay(10);
  Serial.println("TRMNL Weather+Cats starting...");

#ifdef EPAPER_ENABLE
  // Check if last reboot was a watchdog crash
  RESET_REASON reason = rtc_get_reset_reason(0);
  if (reason == TG0WDT_SYS_RESET || reason == TG1WDT_SYS_RESET ||
      reason == RTCWDT_SYS_RESET || reason == RTCWDT_CPU_RESET)
  {
    Serial.println("!!! WATCHDOG REBOOT DETECTED !!!");
    Serial.print("[CRASH] Last draw phase: ");
    Serial.println(lastDrawPhase);
    Serial.print("[CRASH] Last cat drawn: #");
    Serial.println(lastCatDrawn);
  }

  // Enable task watchdog (8s timeout, panic on trigger = auto reboot)
  esp_task_wdt_config_t wdt_config = {
      .timeout_ms = 8000,
      .idle_core_mask = 0,
      .trigger_panic = true,
  };
  esp_task_wdt_reconfigure(&wdt_config);
  esp_task_wdt_add(NULL);
  Serial.println("[WDT] Watchdog enabled (8s)");

  randomSeed(analogRead(0));
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
    esp_task_wdt_reset();
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
    esp_task_wdt_reset();

    Serial.println("[WEATHER] Fetching weather data...");
    esp_task_wdt_reset();
    bool ok = fetchWeather();
    esp_task_wdt_reset();
    Serial.print("[WEATHER] Fetch result: ");
    Serial.println(ok ? "OK" : "FAILED");

    // Sync time via NTP (Europe/London with BST auto-switch)
    configTime(0, 0, "pool.ntp.org");
    setenv("TZ", "GMT0BST,M3.5.0/1,M10.5.0", 1);
    tzset();
    Serial.println("[NTP] Time sync configured");
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
    // 1-in-4 chance of Scottish cat (29-38), 3-in-4 chance of others (0-28)
    if (random(4) == 0)
      currentCat = 29 + random(10); // Scottish cats
    else
      currentCat = random(29); // All others
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

  esp_task_wdt_reset();
#endif
}
