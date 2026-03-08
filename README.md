# ArdOS

**ArdOS** is a minimal graphical operating system built for the **Arduino UNO R4 WiFi**, featuring a touch-enabled windowing environment powered by the ILI9341 TFT display. It provides a modular, event-driven architecture with a message bus, process management, GUI framework, file system, and power management.

## Features

- **Window Manager** — Movable and closable windows with z-index layering and active window tracking
- **GUI Components** — Panels, Containers, Windows, Buttons, Labels, MenuBar, ContextMenu
- **Touchscreen Input** — XPT2046 support with coordinate transformation and multi-stage event handling
- **Message Bus** — Pub/sub topic-based message routing for decoupled communication
- **Process Management** — PID allocation, process lifecycle (Created → Running → Stopped → Terminated), per-process context
- **Application Framework** — Base `Application` class with event dispatching for building user apps
- **File System** — In-memory file system with directories, files, and path navigation
- **Power Management** — Automatic power save and sleep modes with configurable timeouts
- **Real-Time Clock** — RTC integration for system time and clock display
- **Compositor** — Efficient rendering engine that manages the window stack and dispatches draw calls

## Hardware Requirements

- Arduino UNO R4 WiFi
- 2.8" ILI9341 SPI TFT LCD Display (320x240)
- XPT2046 touch controller (CS: D7)
- Breadboard and jumper wires

### Pin Configuration

| Function      | Pin |
|---------------|-----|
| TFT CS        | D10 |
| TFT DC        | D9  |
| TFT RST       | D8  |
| TFT LED       | D6  |
| Touch CS       | D7  |

## Dependencies

This project uses **PlatformIO** with the Arduino framework on the Renesas-RA platform. Required libraries:

```ini
lib_deps =
  adafruit/Adafruit ILI9341
  adafruit/Adafruit GFX Library
  paulstoffregen/XPT2046_Touchscreen
  adafruit/RTClib @ ^2.0.3
```

## Project Structure

```
ArdOs/
├── include/ardos/
│   ├── api/              # Public C API exports
│   ├── app/              # Application layer (Desktop)
│   ├── bus/              # Message bus and messaging
│   ├── drivers/          # Hardware drivers (Display, Input, RTC, Serial)
│   ├── gui/              # GUI components and compositor
│   ├── kernel/           # Core kernel, managers, state, config
│   │   └── fs/           # File system abstraction
│   ├── platform/         # Platform utilities (serial logging)
│   ├── process/          # Process management framework
│   └── user/             # User-facing application APIs
├── src/ardos/            # Corresponding implementations
│   ├── app/
│   ├── bus/
│   ├── drivers/
│   ├── gui/
│   │   ├── components/
│   │   ├── compositor/
│   │   └── event/
│   ├── kernel/
│   │   ├── fs/
│   │   └── process/
│   ├── process/
│   └── user/
├── src/main.cpp          # Arduino entry point (setup/loop)
└── platformio.ini        # Build configuration
```

## Architecture

```
┌──────────────────────────────────────────────────────────┐
│                    KERNEL (Orchestrator)                  │
│   Initialization · Process Scheduling · State Management │
├──────────┬────────────┬─────────────┬────────────────────┤
│ Drivers  │  Managers  │  Processes  │   Message Bus      │
│──────────│────────────│─────────────│────────────────────│
│ Display  │ Input      │ Desktop     │ Pub/Sub topics:    │
│ Input    │ Display    │ User Apps   │  touch/*           │
│ RTC      │ Time       │ AppRegistry │  display/*         │
│ Serial   │ Power      │             │                    │
│          │ Logger     │             │                    │
├──────────┴────────────┴─────────────┴────────────────────┤
│              GUI Framework (Compositor)                   │
│  Panel ─┬─ Container ─┬─ Window                          │
│         │              ├─ MenuBar                         │
│         │              └─ ContextMenu                     │
│         ├─ Button                                         │
│         └─ Label                                          │
├──────────────────────────────────────────────────────────┤
│          Hardware (ILI9341 SPI + XPT2046 Touch)          │
└──────────────────────────────────────────────────────────┘
```

**Event Flow:**
```
Touch Hardware → InputDriver → InputManager → Compositor → EventDispatcher → Application
```

## Getting Started

1. Clone the repository and open it with PlatformIO.
2. Connect the ILI9341 + XPT2046 display to the UNO R4 WiFi using the pin configuration above.
3. Build and upload the firmware:
   ```bash
   pio run --target upload
   ```
4. Open the serial monitor at **250000 baud** for debug output.
5. The screen boots with a menu bar. Tap to interact with the system.

## Future Work

- Scrollable views and text input components
- Persistent file system (SD card or flash storage)
- Networking capabilities via the R4 WiFi module
- Multi-window task switching UI

## License

MIT License. See [LICENSE](LICENSE) for details.

---

Developed by [oguzgundogdu](https://github.com/oguzgundogdu)
