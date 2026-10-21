# esp32_bootloader

Work-in-progress ESP-IDF project for an OTA (over-the-air) update setup on the ESP32, with a custom dual-OTA partition table.

> **Status:** early stage / work in progress. The repository currently contains the project skeleton, the partition layout and the first OTA-related code. It is not yet a complete, buildable application (see [Current state](#current-state)).

## Overview

What is in the code today:

- **ESP-IDF project** (CMake build system), configured for the **ESP32** with ESP-IDF **5.4.1** (`sdkconfig`).
- **Custom partition table** (`partitions.csv`) with a factory app slot plus two OTA slots, so a new firmware image can be written to the inactive slot while the current one keeps running:

  | Name       | Type | SubType | Offset     | Size   |
  |------------|------|---------|------------|--------|
  | `nvs`      | data | nvs     | `0x9000`   | 16 KB  |
  | `otadata`  | data | ota     | `0xd000`   | 8 KB   |
  | `phy_init` | data | phy     | `0xf000`   | 4 KB   |
  | `factory`  | app  | factory | `0x10000`  | 1 MB   |
  | `ota_0`    | app  | ota_0   | `0x110000` | 1 MB   |
  | `ota_1`    | app  | ota_1   | `0x210000` | 1 MB   |

  The `sdkconfig` selects this custom table and a 4 MB flash size.
- **OTA groundwork** (`main/bootloader.c`): includes the ESP-IDF OTA, partition, app-format and HTTP-client APIs and starts querying the running partition and OTA image state (`esp_ota_get_running_partition()`, `esp_ota_img_states_t`).
- **Wi-Fi application stub** (`main/wifi_app.c`): `wifi_app_init()` initializes NVS flash, the network interface (`esp_netif`) and the default event loop.

## Hardware / target

- **Chip:** ESP32 (Xtensa), `CONFIG_IDF_TARGET="esp32"`
- **Flash:** 4 MB (the partition table uses ~3.1 MB)
- **Framework / toolchain:** ESP-IDF 5.4.1, CMake

## Repository layout

```
esp32_bootloader/
├── CMakeLists.txt     # ESP-IDF top-level project file
├── partitions.csv     # custom partition table (factory + ota_0 + ota_1)
├── sdkconfig          # ESP-IDF configuration (ESP32, 4 MB flash, custom partitions)
├── main/
│   ├── main.c         # entry point (placeholder)
│   ├── bootloader.c   # OTA / partition handling (in progress)
│   ├── wifi_app.c     # NVS + netif + event loop initialization
│   └── wifi_app.h
└── LICENSE
```

## Current state

The project does not build as-is yet:

- `main/CMakeLists.txt` (the `idf_component_register(...)` file ESP-IDF needs for the `main` component) is not in the repository.
- `main/main.c` defines `int main(void)` instead of the ESP-IDF entry point `app_main()`, and does not call the other modules yet.
- `main/bootloader.c` calls `esp_ota_get_running_partition()` in a global initializer, which C does not allow; it needs to move into a function.
- `protocol_examples_common.h` is included, which requires the ESP-IDF `protocol_examples_common` example component to be added to the project.

## Building and flashing

Once the points above are in place, the standard ESP-IDF workflow applies:

```bash
# with ESP-IDF 5.4.x installed and exported (. $IDF_PATH/export.sh)
idf.py set-target esp32
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor   # replace with your serial port
```

`idf.py flash` writes the bootloader, the custom partition table and the application (to the `factory` slot).

## License

MIT, see [LICENSE](LICENSE).
