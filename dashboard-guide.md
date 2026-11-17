# Dashboard Guide

## Purpose
The dashboard displays the latest DHT11 temperature and relative-humidity readings.

## Access
1. Enter Wi-Fi credentials locally in the sketch.
2. Upload the sketch.
3. Open Serial Monitor at 115200 baud.
4. Wait for the ESP8266 to connect and print its IP address.
5. Connect a phone or computer to the same local Wi-Fi network.
6. Open `http://` followed by the IP address printed by the board.

For example, if the board prints `192.168.1.50`, open `http://192.168.1.50`. This is only an example; use the actual address.

## Elements
- Temperature in degrees Celsius.
- Relative humidity in percent.
- Status message for sensor data.
- Browser time of the last valid update.

## Endpoints
| Route | Purpose |
|---|---|
| `/` | Dashboard page |
| `/data` | Latest sensor data as JSON |

The browser refreshes the display every three seconds. Access can be blocked by guest-network isolation, client isolation, firewall rules, or different network segments.
