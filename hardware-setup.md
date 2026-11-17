# Hardware Setup

## Required components
- ESP8266 NodeMCU development board
- DHT11 sensor or breakout module
- Jumper wires
- USB cable or suitable power source

## Component roles
- **ESP8266 NodeMCU:** reads the sensor, connects to Wi-Fi, and hosts the web server.
- **DHT11:** measures temperature and relative humidity.
- **Power:** the NodeMCU can be powered through USB during development.

## Assembly
1. Identify VCC, GND, and DATA on the DHT11 module.
2. Connect DATA to NodeMCU D4 (GPIO2), as assumed by the sketch.
3. Connect GND to GND.
4. Connect VCC to 3V3 for the documented wiring.
5. Verify the module's pin labels and voltage requirements.
6. Connect NodeMCU to the computer, upload the sketch, and inspect Serial Monitor.

Some breakout modules have different pin layouts. A bare DHT11 may require a pull-up resistor; many modules include one.
