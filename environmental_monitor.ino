/*
  IoT Environmental Monitoring System
  Board: ESP8266 NodeMCU
  Sensor: DHT11
  Dashboard: locally hosted by the ESP8266

  Reconstructed implementation, not verified original firmware.
  Assumed wiring: DHT11 DATA -> NodeMCU D4 (GPIO2),
  VCC -> 3V3, GND -> GND.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Enter credentials locally. Do not publish real credentials.
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

#define DHT_PIN D4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
ESP8266WebServer server(80);

float latestTemperatureC = NAN;
float latestHumidity = NAN;
bool latestReadingValid = false;

unsigned long lastSensorReadMs = 0;
const unsigned long SENSOR_INTERVAL_MS = 2500;

const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Environmental Monitor</title>
<style>
*{box-sizing:border-box}
body{margin:0;font-family:Arial,sans-serif;background:#f3f6fa;color:#172033}
header{background:#172b4d;color:white;padding:24px 18px;text-align:center}
header h1{margin:0 0 8px;font-size:1.55rem}
header p{margin:0;color:#d7e2f2}
main{width:min(900px,92%);margin:28px auto}
.status{padding:12px 15px;border-radius:9px;background:white;margin-bottom:18px;border:1px solid #dce3ed}
.cards{display:grid;grid-template-columns:repeat(auto-fit,minmax(220px,1fr));gap:16px}
.card{background:white;border:1px solid #dce3ed;border-radius:13px;padding:23px;box-shadow:0 3px 12px rgba(20,40,70,.05)}
.label{color:#65738a;font-size:.95rem}
.value{font-size:2.5rem;font-weight:700;margin:14px 0 5px}
.unit,.meta{color:#65738a}
.meta{margin-top:20px;font-size:.88rem}
footer{text-align:center;color:#65738a;padding:20px;font-size:.85rem}
</style>
</head>
<body>
<header><h1>IoT Environmental Monitoring</h1><p>Local temperature and humidity dashboard</p></header>
<main>
<div class="status" id="status">Connecting to sensor data...</div>
<section class="cards">
<article class="card"><div class="label">Temperature</div><div class="value" id="temperature">--</div><div class="unit">degrees Celsius (°C)</div></article>
<article class="card"><div class="label">Relative Humidity</div><div class="value" id="humidity">--</div><div class="unit">percent (%)</div></article>
</section>
<div class="meta">Last update: <span id="updated">Waiting for data</span><br>Refresh interval: 3 seconds</div>
</main>
<footer>ESP8266 local web server · DHT11 sensor</footer>
<script>
async function updateReadings(){
  const status=document.getElementById("status");
  try{
    const response=await fetch("/data",{cache:"no-store"});
    if(!response.ok) throw new Error("HTTP "+response.status);
    const data=await response.json();
    if(!data.valid){
      document.getElementById("temperature").textContent="--";
      document.getElementById("humidity").textContent="--";
      status.textContent="Sensor reading unavailable. Check the DHT11 connection.";
      return;
    }
    document.getElementById("temperature").textContent=Number(data.temperature_c).toFixed(1);
    document.getElementById("humidity").textContent=Number(data.humidity_percent).toFixed(1);
    document.getElementById("updated").textContent=new Date().toLocaleTimeString();
    status.textContent="Sensor connected · Latest reading received";
  }catch(error){status.textContent="Unable to retrieve data: "+error.message;}
}
updateReadings();
setInterval(updateReadings,3000);
</script>
</body>
</html>
)rawliteral";

void readSensor() {
  unsigned long now = millis();
  if (lastSensorReadMs != 0 &&
      now - lastSensorReadMs < SENSOR_INTERVAL_MS) return;

  lastSensorReadMs = now;
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    latestReadingValid = false;
    Serial.println("DHT11 reading failed. Check sensor wiring.");
    return;
  }

  latestHumidity = humidity;
  latestTemperatureC = temperature;
  latestReadingValid = true;

  Serial.print("Temperature: ");
  Serial.print(latestTemperatureC, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(latestHumidity, 1);
  Serial.println(" %");
}

void handleRoot() {
  server.send_P(200, "text/html", DASHBOARD_HTML);
}

void handleData() {
  readSensor();
  String json = "{";

  if (latestReadingValid) {
    json += "\"temperature_c\":" + String(latestTemperatureC, 1);
    json += ",\"humidity_percent\":" + String(latestHumidity, 1);
    json += ",\"valid\":true";
  } else {
    json += "\"temperature_c\":null,\"humidity_percent\":null,\"valid\":false";
  }

  json += "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", json);
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Endpoint not found");
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  unsigned long startAttempt = millis();
  const unsigned long WIFI_TIMEOUT_MS = 30000;

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < WIFI_TIMEOUT_MS) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected.");
    Serial.print("Dashboard URL: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Wi-Fi connection timed out. Check credentials and restart.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("IoT Environmental Monitoring System");
  Serial.println("ESP8266 + DHT11 + Local Web Dashboard");

  dht.begin();
  connectToWiFi();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
  readSensor();

  static unsigned long lastWiFiCheckMs = 0;
  if (millis() - lastWiFiCheckMs >= 10000) {
    lastWiFiCheckMs = millis();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi disconnected. Reconnecting...");
      WiFi.reconnect();
    }
  }
}
