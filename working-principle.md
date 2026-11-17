# Working Principle

1. **Sensing:** The DHT11 measures temperature and relative humidity.
2. **Data acquisition:** The ESP8266 requests readings through the DHT library.
3. **Validation:** The sketch checks for invalid (NaN) readings.
4. **Wi-Fi:** The ESP8266 joins the configured wireless network and obtains a local IP address.
5. **HTTP server:** The ESP8266 serves `/` for the dashboard and `/data` for JSON readings.
6. **Browser update:** JavaScript requests `/data` every three seconds and updates the displayed values.

The latest valid readings are held in device memory. This version does not save historical readings to a database and readings are not retained across a restart.
