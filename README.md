# ArdOS

**ArdOS** is a minimal graphical operating system built for the Arduino UNO R4 WiFi, featuring a touch-enabled windowing environment powered by the ILI9341 TFT display. It provides a modular and extensible UI framework with basic input handling and layered screen management.

## Features

- Window manager with movable and closable windows
- Touchscreen input support via XPT2046
- Event-based input architecture
- Modular folder structure: `gui`, `kernel`, `utils`
- Coordinate transformation helper for touchscreen accuracy
- Efficient redraw system (only affected screen regions are updated)
- Menu bar with dynamic window creation

## Hardware Requirements

- Arduino UNO R4 WiFi
- 2.8" ILI9341 SPI TFT LCD Display
- XPT2046 touch controller (CS: D7)
- Breadboard and jumper wires

## Dependencies

This project uses PlatformIO. Required libraries:

```ini
lib_deps =
  adafruit/Adafruit ILI9341 @ ^1.5.6
  adafruit/Adafruit GFX Library @ ^1.11.9
  paulstoffregen/XPT2046_Touchscreen @ ^1.4
```

## Project Structure

```
ArdOs/
├── include/
│   └── ardos/
│       ├── gui/
│       ├── kernel/
│       └── utils/
├── src/
│   └── ardos/
│       ├── gui/
│       ├── kernel/
│       └── utils/
└── src/
    └── main.cpp
```

## Getting Started

1. Clone the repository and open it with PlatformIO.
2. Connect your ILI9341 + XPT2046 setup to the UNO R4 WiFi.
3. Upload the firmware to the board.
4. The screen will boot with a menu bar. Tap it to spawn windows.

## Future Work

- Z-index and active window tracking
- Scrollable views and text boxes
- Reusable UI components (buttons, labels, etc.)
- Application/task registry

## License

MIT License. For educational and hobby use.

---

Developed by [oguzgundogdu](https://github.com/oguzgundogdu)