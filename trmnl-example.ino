#include <SPI.h>
#include <TFT_eSPI.h>

#ifdef EPAPER_ENABLE

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h" // WIFI_SSID, WIFI_PASS (see config.example.h)

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

EPaper epaper = EPaper();

int currentCat = 0;
uint32_t targetTime = 0;
uint32_t weatherRefreshTime = 0;

// ---- Forward declarations ----
void drawCat0();
void drawCat1();
void drawCat2();
void drawCat3();
void drawCat4();
void drawCat5();
void drawCat6();
void drawCat7();
void drawFullScreen();
void drawWeatherPanel();
void drawCatPanel();
void drawWeatherIcon(int x, int y, int code, int size);
bool fetchWeather();
const char *weatherDescription(int code);

// ---- Weather icon drawing (primitives, ~25x25px) ----
void drawWeatherIcon(int x, int y, int code, int size)
{
  // x,y is top-left corner of icon area; size is width/height
  int cx = x + size / 2;
  int cy = y + size / 2;
  int r = size / 3;

  if (code == 0)
  {
    // Sun: circle + rays
    epaper.drawCircle(cx, cy, r, TFT_BLACK);
    epaper.drawCircle(cx, cy, r - 1, TFT_BLACK);
    for (int a = 0; a < 360; a += 45)
    {
      float rad = a * 0.0174532925;
      int x1 = cx + (int)((r + 3) * cos(rad));
      int y1 = cy + (int)((r + 3) * sin(rad));
      int x2 = cx + (int)((r + 7) * cos(rad));
      int y2 = cy + (int)((r + 7) * sin(rad));
      epaper.drawLine(x1, y1, x2, y2, TFT_BLACK);
    }
  }
  else if (code <= 2)
  {
    // Partly cloudy: small sun + cloud
    int sx = cx - 4, sy = cy - 4;
    epaper.drawCircle(sx, sy, r - 3, TFT_BLACK);
    for (int a = 0; a < 360; a += 60)
    {
      float rad = a * 0.0174532925;
      epaper.drawLine(sx + (int)((r - 1) * cos(rad)), sy + (int)((r - 1) * sin(rad)),
                      sx + (int)((r + 3) * cos(rad)), sy + (int)((r + 3) * sin(rad)), TFT_BLACK);
    }
    // Cloud overlapping
    int clx = cx + 3, cly = cy + 3;
    epaper.fillCircle(clx - 5, cly, 5, TFT_WHITE);
    epaper.fillCircle(clx + 5, cly, 5, TFT_WHITE);
    epaper.fillCircle(clx, cly - 3, 5, TFT_WHITE);
    epaper.drawCircle(clx - 5, cly, 5, TFT_BLACK);
    epaper.drawCircle(clx + 5, cly, 5, TFT_BLACK);
    epaper.drawCircle(clx, cly - 3, 5, TFT_BLACK);
  }
  else if (code == 3)
  {
    // Overcast: cloud shape
    epaper.fillCircle(cx - 6, cy + 2, 6, TFT_WHITE);
    epaper.fillCircle(cx + 6, cy + 2, 6, TFT_WHITE);
    epaper.fillCircle(cx, cy - 3, 7, TFT_WHITE);
    epaper.drawCircle(cx - 6, cy + 2, 6, TFT_BLACK);
    epaper.drawCircle(cx + 6, cy + 2, 6, TFT_BLACK);
    epaper.drawCircle(cx, cy - 3, 7, TFT_BLACK);
    // Fill bottom flat
    epaper.fillRect(cx - 12, cy + 2, 25, 7, TFT_WHITE);
    epaper.drawLine(cx - 12, cy + 8, cx + 12, cy + 8, TFT_BLACK);
  }
  else if (code == 45 || code == 48)
  {
    // Fog: horizontal dashed lines
    for (int i = -2; i <= 2; i++)
    {
      int ly = cy + i * 5;
      for (int dx = -10; dx < 10; dx += 6)
      {
        epaper.drawLine(cx + dx, ly, cx + dx + 3, ly, TFT_BLACK);
      }
    }
  }
  else if (code >= 51 && code <= 55)
  {
    // Drizzle: cloud + small dots
    epaper.drawCircle(cx - 5, cy - 3, 5, TFT_BLACK);
    epaper.drawCircle(cx + 5, cy - 3, 5, TFT_BLACK);
    epaper.drawCircle(cx, cy - 6, 5, TFT_BLACK);
    epaper.fillCircle(cx - 4, cy + 8, 1, TFT_BLACK);
    epaper.fillCircle(cx + 4, cy + 8, 1, TFT_BLACK);
    epaper.fillCircle(cx, cy + 11, 1, TFT_BLACK);
  }
  else if ((code >= 61 && code <= 65) || (code >= 80 && code <= 82))
  {
    // Rain: cloud + diagonal lines
    epaper.drawCircle(cx - 5, cy - 4, 5, TFT_BLACK);
    epaper.drawCircle(cx + 5, cy - 4, 5, TFT_BLACK);
    epaper.drawCircle(cx, cy - 7, 5, TFT_BLACK);
    epaper.drawLine(cx - 6, cy + 5, cx - 8, cy + 11, TFT_BLACK);
    epaper.drawLine(cx, cy + 5, cx - 2, cy + 11, TFT_BLACK);
    epaper.drawLine(cx + 6, cy + 5, cx + 4, cy + 11, TFT_BLACK);
  }
  else if (code >= 71 && code <= 75)
  {
    // Snow: cloud + dots/asterisks
    epaper.drawCircle(cx - 5, cy - 4, 5, TFT_BLACK);
    epaper.drawCircle(cx + 5, cy - 4, 5, TFT_BLACK);
    epaper.drawCircle(cx, cy - 7, 5, TFT_BLACK);
    // Snowflakes
    epaper.fillCircle(cx - 5, cy + 7, 2, TFT_BLACK);
    epaper.fillCircle(cx + 5, cy + 7, 2, TFT_BLACK);
    epaper.fillCircle(cx, cy + 11, 2, TFT_BLACK);
  }
  else if (code >= 95 && code <= 99)
  {
    // Thunder: cloud + zigzag
    epaper.drawCircle(cx - 5, cy - 5, 5, TFT_BLACK);
    epaper.drawCircle(cx + 5, cy - 5, 5, TFT_BLACK);
    epaper.drawCircle(cx, cy - 8, 5, TFT_BLACK);
    // Lightning bolt
    epaper.drawLine(cx, cy + 2, cx - 3, cy + 7, TFT_BLACK);
    epaper.drawLine(cx - 3, cy + 7, cx + 2, cy + 7, TFT_BLACK);
    epaper.drawLine(cx + 2, cy + 7, cx - 1, cy + 13, TFT_BLACK);
  }
  else
  {
    // Unknown: question mark
    epaper.drawCentreString("?", cx, cy - 6, 2);
  }
}

// ---- Weather code to description ----
const char *weatherDescription(int code)
{
  if (code == 0) return "Clear";
  if (code <= 2) return "Partly cloudy";
  if (code == 3) return "Overcast";
  if (code == 45 || code == 48) return "Fog";
  if (code >= 51 && code <= 55) return "Drizzle";
  if (code >= 61 && code <= 65) return "Rain";
  if (code >= 71 && code <= 75) return "Snow";
  if (code >= 80 && code <= 82) return "Showers";
  if (code >= 95 && code <= 99) return "Thunder";
  return "Unknown";
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

  currentHour = (timeStr[11] - '0') * 10 + (timeStr[12] - '0');

  // Parse current date to distinguish today vs tomorrow
  // Format: "2025-01-15T14:00"
  int curDay = (timeStr[8] - '0') * 10 + (timeStr[9] - '0');

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
    int entryDay = (t[8] - '0') * 10 + (t[9] - '0');
    int entryHour = (t[11] - '0') * 10 + (t[12] - '0');

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

// ---- Column positions for forecast rows ----
// TIME    ICON   TEMP    RAIN%    WIND
// 15      85     115     205      290
#define COL_TIME  15
#define COL_ICON  85
#define COL_TEMP  115
#define COL_RAIN  210
#define COL_WIND  290

// ---- Draw a single forecast row at fixed columns ----
void drawForecastRow(int y, const HourlyForecast &f)
{
  char buf[20];

  // Time
  snprintf(buf, sizeof(buf), "%02d:00", f.hour);
  epaper.drawString(buf, COL_TIME, y, 4);

  // Icon
  drawWeatherIcon(COL_ICON, y - 2, f.weathercode, 24);

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

  // Header — double line for emphasis
  epaper.drawCentreString("Edinburgh", 200, 6, 4);
  epaper.drawLine(10, 32, 390, 32, TFT_BLACK);
  epaper.drawLine(10, 34, 390, 34, TFT_BLACK);

  // "Now" section — bold font 4
  drawWeatherIcon(15, 42, currentWeathercode, 28);
  char nowBuf[60];
  snprintf(nowBuf, sizeof(nowBuf), "%d%cC  %s  %dkm/h",
           currentTemp, (char)247, weatherDescription(currentWeathercode), currentWind);
  epaper.drawString(nowBuf, 50, 46, 4);
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
  }
}

// ---- Draw full screen ----
void drawFullScreen()
{
  epaper.fillScreen(TFT_WHITE);
  drawWeatherPanel();
  drawCatPanel();
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

  // Draw full screen (weather + cat)
  Serial.println("[DRAW] Drawing full screen");
  drawFullScreen();

  targetTime = millis() + 60000;
  weatherRefreshTime = millis() + 1800000; // 30 minutes
  Serial.println("[INIT] Setup complete");
#endif
}

void loop()
{
#ifdef EPAPER_ENABLE
  // Cycle cat every 60 seconds
  if (millis() > targetTime)
  {
    currentCat = (currentCat + 1) % 8;
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
#endif
}
