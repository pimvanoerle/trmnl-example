#include <cassert>
#include <cstdio>
#include <cstring>

#include "../weather_logic.h"

static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) \
  do { \
    tests_run++; \
    printf("  %-50s", name); \
  } while (0)

#define PASS() \
  do { \
    tests_passed++; \
    printf("OK\n"); \
  } while (0)

// ---- weatherDescription tests ----
void test_weatherDescription()
{
  printf("weatherDescription:\n");

  TEST("code 0 -> Clear");
  assert(strcmp(weatherDescription(0), "Clear") == 0);
  PASS();

  TEST("code 1 -> Partly cloudy");
  assert(strcmp(weatherDescription(1), "Partly cloudy") == 0);
  PASS();

  TEST("code 2 -> Partly cloudy");
  assert(strcmp(weatherDescription(2), "Partly cloudy") == 0);
  PASS();

  TEST("code 3 -> Overcast");
  assert(strcmp(weatherDescription(3), "Overcast") == 0);
  PASS();

  TEST("code 45 -> Fog");
  assert(strcmp(weatherDescription(45), "Fog") == 0);
  PASS();

  TEST("code 48 -> Fog");
  assert(strcmp(weatherDescription(48), "Fog") == 0);
  PASS();

  TEST("code 51 -> Drizzle");
  assert(strcmp(weatherDescription(51), "Drizzle") == 0);
  PASS();

  TEST("code 55 -> Drizzle");
  assert(strcmp(weatherDescription(55), "Drizzle") == 0);
  PASS();

  TEST("code 61 -> Rain");
  assert(strcmp(weatherDescription(61), "Rain") == 0);
  PASS();

  TEST("code 65 -> Rain");
  assert(strcmp(weatherDescription(65), "Rain") == 0);
  PASS();

  TEST("code 71 -> Snow");
  assert(strcmp(weatherDescription(71), "Snow") == 0);
  PASS();

  TEST("code 75 -> Snow");
  assert(strcmp(weatherDescription(75), "Snow") == 0);
  PASS();

  TEST("code 80 -> Showers");
  assert(strcmp(weatherDescription(80), "Showers") == 0);
  PASS();

  TEST("code 82 -> Showers");
  assert(strcmp(weatherDescription(82), "Showers") == 0);
  PASS();

  TEST("code 95 -> Thunder");
  assert(strcmp(weatherDescription(95), "Thunder") == 0);
  PASS();

  TEST("code 99 -> Thunder");
  assert(strcmp(weatherDescription(99), "Thunder") == 0);
  PASS();

  TEST("code 100 -> Unknown");
  assert(strcmp(weatherDescription(100), "Unknown") == 0);
  PASS();

  TEST("code -1 -> Partly cloudy (<=2 branch)");
  assert(strcmp(weatherDescription(-1), "Partly cloudy") == 0);
  PASS();
}

// ---- voltageToPercent tests ----
void test_voltageToPercent()
{
  printf("voltageToPercent:\n");

  TEST("3.0V -> 0%%");
  assert(voltageToPercent(3.0f) == 0);
  PASS();

  TEST("4.2V -> 100%%");
  assert(voltageToPercent(4.2f) == 100);
  PASS();

  TEST("below 3.0V -> clamped to 0%%");
  assert(voltageToPercent(2.5f) == 0);
  PASS();

  TEST("above 4.2V -> clamped to 100%%");
  assert(voltageToPercent(5.0f) == 100);
  PASS();

  TEST("3.6V -> 50%%");
  assert(voltageToPercent(3.6f) == 50);
  PASS();

  TEST("3.3V -> 25%%");
  assert(voltageToPercent(3.3f) == 25);
  PASS();

  TEST("3.9V -> 75%%");
  assert(voltageToPercent(3.9f) == 75);
  PASS();
}

// ---- parseHourFromTimeStr tests ----
void test_parseHourFromTimeStr()
{
  printf("parseHourFromTimeStr:\n");

  TEST("14:00 -> 14");
  assert(parseHourFromTimeStr("2025-01-15T14:00") == 14);
  PASS();

  TEST("00:00 -> 0");
  assert(parseHourFromTimeStr("2025-01-15T00:00") == 0);
  PASS();

  TEST("23:59 -> 23");
  assert(parseHourFromTimeStr("2025-12-31T23:59") == 23);
  PASS();

  TEST("09:30 -> 9");
  assert(parseHourFromTimeStr("2025-06-01T09:30") == 9);
  PASS();
}

// ---- parseDayFromTimeStr tests ----
void test_parseDayFromTimeStr()
{
  printf("parseDayFromTimeStr:\n");

  TEST("15th -> 15");
  assert(parseDayFromTimeStr("2025-01-15T14:00") == 15);
  PASS();

  TEST("01st -> 1");
  assert(parseDayFromTimeStr("2025-01-01T00:00") == 1);
  PASS();

  TEST("31st -> 31");
  assert(parseDayFromTimeStr("2025-12-31T23:59") == 31);
  PASS();

  TEST("10th -> 10");
  assert(parseDayFromTimeStr("2025-03-10T12:00") == 10);
  PASS();
}

int main()
{
  printf("Running weather_logic tests...\n\n");

  test_weatherDescription();
  test_voltageToPercent();
  test_parseHourFromTimeStr();
  test_parseDayFromTimeStr();

  printf("\n%d/%d tests passed.\n", tests_passed, tests_run);

  if (tests_passed == tests_run)
  {
    printf("All tests passed!\n");
    return 0;
  }
  else
  {
    printf("SOME TESTS FAILED!\n");
    return 1;
  }
}
