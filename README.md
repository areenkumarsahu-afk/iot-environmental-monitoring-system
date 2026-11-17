# IoT Environmental Monitoring System

An ESP8266 NodeMCU-based prototype that measures temperature and relative humidity with a DHT11 sensor and displays the latest readings on a web dashboard hosted locally by the ESP8266.

## Features
- Temperature in degrees Celsius.
- Relative humidity in percent.
- Local dashboard hosted on the ESP8266.
- Automatic browser refresh.
- JSON endpoint at `/data`.
- No cloud service or external web server required.

## Hardware
| Component | Quantity | Purpose |
|---|---:|---|
| ESP8266 NodeMCU | 1 | Reads sensor and hosts web server |
| DHT11 sensor/module | 1 | Temperature and humidity |
| Jumper wires | As required | Connections |
| USB cable/power supply | 1 | Power and programming |

This documented version does not use a relay or servo. Do not claim those components as implemented features unless they are actually used.

## Software
- Arduino IDE
- ESP8266 board package
- Adafruit DHT sensor library
- Adafruit Unified Sensor library

## Architecture
DHT11 → ESP8266 → Wi-Fi local network → browser dashboard.
The browser requests `/data`; the ESP8266 returns the latest reading as JSON.

## Repository structure
- `src/environmental_monitor/`: Arduino source
- `docs/`: technical documentation
- `hardware/`: component and pin details
- `images/`: genuine prototype photos and diagrams
- `tests/`: test records

## Setup
1. Install ESP8266 board support through Arduino IDE Boards Manager.
2. Install `DHT sensor library` by Adafruit and `Adafruit Unified Sensor` through Library Manager.
3. Open `src/environmental_monitor/environmental_monitor.ino`.
4. Replace `YOUR_WIFI_NAME` and `YOUR_WIFI_PASSWORD` locally.
5. Verify the wiring: DHT11 DATA is assumed to connect to NodeMCU D4 (GPIO2), VCC to 3V3, GND to GND.
6. Select the correct ESP8266 NodeMCU board and port, then upload.
7. Open Serial Monitor at 115200 baud.
8. When the board prints its local IP address, open `http://<printed-IP>` in a browser on the same Wi-Fi network.

Do not commit real Wi-Fi credentials to a public repository.

## Endpoints
| Route | Purpose |
|---|---|
| `/` | Dashboard webpage |
| `/data` | Latest reading as JSON |

Example response (illustrative only):
```json
{"temperature_c":27.5,"humidity_percent":62.0,"valid":true}
```

## Testing
Record actual measurements and test outcomes in `docs/testing-and-results.md` and `tests/test-results.md`. Do not present illustrative values as experimental results.

## Limitations
- DHT11 has limited accuracy and measurement range compared with higher-grade sensors.
- Dashboard is intended for local-network access.
- No historical database, cloud access, alerts, or data export is implemented.
- Wi-Fi availability affects access.
- This is an educational prototype, not a certified environmental instrument.

## Safety and privacy
Keep Wi-Fi credentials private. Do not expose the ESP8266 web server directly to the public internet without appropriate security controls.

## License
See `LICENSE`.
