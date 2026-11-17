# Software Architecture

## Libraries
- `ESP8266WiFi.h`: Wi-Fi connection.
- `ESP8266WebServer.h`: local HTTP server.
- `DHT.h`: DHT11 sensor communication.

## Main functions
- `setup()`: initializes Serial, sensor, Wi-Fi, HTTP routes, and server.
- `loop()`: handles web requests, periodically reads the sensor, and checks Wi-Fi status.
- `readSensor()`: reads temperature and humidity, validates them, and updates the latest values.
- `handleRoot()`: serves the dashboard HTML.
- `handleData()`: returns the latest reading as JSON.
- `handleNotFound()`: returns HTTP 404 for unknown routes.
- `connectToWiFi()`: connects to the configured network and prints the local IP.

## Browser code
The webpage uses HTML for structure, CSS for layout, and JavaScript `fetch()` to request `/data` every three seconds.

## Example JSON (illustrative only)
```json
{"temperature_c":26.0,"humidity_percent":58.0,"valid":true}
```
