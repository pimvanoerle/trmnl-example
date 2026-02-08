#pragma once

inline const char *weatherDescription(int code)
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

inline int voltageToPercent(float voltage)
{
  int pct = (int)((voltage - 3.0f) / 1.2f * 100.0f + 0.5f);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return pct;
}

inline int parseHourFromTimeStr(const char *s)
{
  return (s[11] - '0') * 10 + (s[12] - '0');
}

inline int parseDayFromTimeStr(const char *s)
{
  return (s[8] - '0') * 10 + (s[9] - '0');
}
