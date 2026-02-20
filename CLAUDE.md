# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Arduino CLI project that displays weather, cats, a WiFi QR code, and a clock on a TRMNL OG 7.5" e-paper display. Targets a Seeed XIAO ESP32-S3 board with a 7.5" monochrome ePaper screen (UC8179 driver). Wakes every 30 minutes from deep sleep, refreshes the display, then sleeps again.

## Build and Upload

This is an arduino-cli project. Board FQBN: `esp32:esp32:XIAO_ESP32S3_Plus`.

- **Compile:** `arduino-cli compile --fqbn esp32:esp32:XIAO_ESP32S3_Plus .`
- **Upload:** Auto-detect the port (it changes between USB-C ports):
  ```
  arduino-cli upload --fqbn esp32:esp32:XIAO_ESP32S3_Plus -p $(arduino-cli board list --format json | python3 -c "import sys,json; boards=json.load(sys.stdin)['detected_ports']; print(next(p['port']['address'] for p in boards if 'esp32' in p['port']['address'].lower() or any('esp32' in str(b).lower() for b in p.get('matching_boards',[]))))" 2>/dev/null || echo "/dev/cu.usbmodem*") .
  ```
  Or simply: `arduino-cli upload --fqbn esp32:esp32:XIAO_ESP32S3_Plus -p /dev/cu.usbmodem* .`
- **Deep sleep vs upload**: The device enters deep sleep ~30s after boot, which kills the USB serial port. To upload reliably, hold **BOOT** while pressing **RESET** on the XIAO board — this enters download mode where the port stays alive indefinitely.
- Ensure `EPAPER_ENABLE` is defined in the TFT_eSPI library's `User_Setup.h`

## Architecture

**Two files total:**
- `trmnl-example.ino` — entire application: display init, clock face drawing, and hand animation loop
- `driver.h` — hardware config constants (`BOARD_SCREEN_COMBO 502`, `USE_XIAO_EPAPER_DISPLAY_BOARD_EE04`)

**Dependencies:** `SPI.h`, `TFT_eSPI.h` (which provides the `EPaper` class)

**Key design points:**
- All code is guarded by `#ifdef EPAPER_ENABLE` conditional compilation
- Uses a **deep sleep wake cycle**: on each wake the ESP32 connects to WiFi, fetches weather, draws the full screen once, then enters deep sleep for 30 minutes (~7µA). The `loop()` function is effectively unused.
- `currentCat` and crash-tracking variables use `RTC_NOINIT_ATTR` to survive deep sleep reboots
- Clock time is obtained via NTP on each wake cycle
- Weather icons use trigonometric positioning (degrees → radians with the constant `0.0174532925`)

## Constraints

- **Battery efficiency is the top priority.** This device is a wall-mounted e-ink display. E-ink only draws power on refresh, so minimise display updates — there is no need for second-by-second or even minute-by-minute refreshes. Prefer deep sleep between infrequent updates (e.g. every 5–15 minutes) over active polling loops. Every code change should be evaluated for its impact on battery life.
