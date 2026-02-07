# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Arduino sketch project that displays an analog clock on a TRMNL e-paper display. Targets a Seeed XIAO board with a 7.5" monochrome ePaper screen (UC8179 driver).

## Build and Upload

This is an Arduino IDE project (`.ino` sketch). There is no CLI build system, test framework, or linter configured.

- Open `trmnl-example.ino` in Arduino IDE
- Ensure `EPAPER_ENABLE` is defined in the TFT_eSPI library's `User_Setup.h`
- Compile and upload to the connected board

## Architecture

**Two files total:**
- `trmnl-example.ino` — entire application: display init, clock face drawing, and hand animation loop
- `driver.h` — hardware config constants (`BOARD_SCREEN_COMBO 502`, `USE_XIAO_EPAPER_DISPLAY_BOARD_EE04`)

**Dependencies:** `SPI.h`, `TFT_eSPI.h` (which provides the `EPaper` class)

**Key design points:**
- All code is guarded by `#ifdef EPAPER_ENABLE` conditional compilation
- Time is seeded from compile-time (`__TIME__` macro) and incremented manually via `millis()` in the loop
- Clock hands use trigonometric positioning (degrees → radians with the constant `0.0174532925`)
- Hour/minute hands are only erased and redrawn every 60 seconds (or on first frame) to reduce e-paper flicker; the second hand redraws every second
- Display center is at pixel (120, 121); hand lengths are 62px (hour), 84px (minute), 90px (second)
