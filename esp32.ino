#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// Wi-Fi Credentials
const char* ssid = "Rajeswari";
const char* password = "9985336788";

// Pin Configuration
#define DHT_PIN 4
#define DHT_TYPE DHT11
#define BUZZER_PIN 25

// High Temperature Threshold (°C)
#define TEMP_THRESHOLD 35.0

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

float temperature = 0.0;
float humidity = 0.0;

// Embedded HTML, CSS, and JavaScript for the Web Page
const char HTML_CONTENT[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32 Climate Dashboard</title>
    <style>
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; text-align: center; background-color: #eef2f5; margin: 0; padding: 20px; }
        h1 { color: #333; margin-bottom: 20px; }
        .card-container { display: flex; justify-content: center; gap: 20px; flex-wrap: wrap; margin-top: 20px; }
        .card { background: white; padding: 25px; border-radius: 15px; box-shadow: 0 6px 15px rgba(0,0,0,0.08); width: 220px; }
        .card h2 { margin: 0 0 10px 0; font-size: 18px; color: #666; }
        .value { font-size: 38px; font-weight: bold; color: #007bff; }
        .humidity-val { color: #17a2b8; }
        .status-box { margin-top: 30px; font-size: 20px; font-weight: 600; padding: 12px; border-radius: 8px; display: inline-block; background: #fff; box-shadow: 0 4px 10px rgba(0,0,0,0.05); }
    </style>
</head>
<body>
    <h1>ESP32 Environment Dashboard</h1>
    <div class="card-container">
        <div class="card">
            <h2>Temperature</h2>
            <div class="value"><span id="temp">--</span> &deg;C</div>
        </div>
        <div class="card">
            <h2>Humidity</h2>
            <div class="value humidity-val"><span id="hum">--</span> %</div>
        </div>
    </div>
    <div class="status-box">
        System Status: <span id="status" style="color: #28a745;">Normal</span>
    </div>

    <script>
        function fetchSensorData() {
            fetch('/data')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('temp').innerText = data.temperature.toFixed(1);
                    document.getElementById('hum').innerText = data.humidity.toFixed(1);
                    
                    let statusElem = document.getElementById('status');
                    if (data.temperature > 35.0) {
                        statusElem.innerText = "WARNING: HIGH TEMP DETECTED!";
                        statusElem.style.color = "#dc3545";
                    } else {
                        statusElem.innerText = "Normal";
                        statusElem.style.color = "#28a745";
                    }
                })
                .catch(err => console.error("Error fetching data:", err));
        }

        // Fetch new data every 2 seconds automatically without refreshing page
        setInterval(fetchSensorData, 2000);
        window.onload = fetchSensorData;
    </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML_CONTENT);
}

void handleData() {
  String json = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  // Connect to Wi-Fi Network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define Server Endpoints
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient(); // Keep listening for web requests

  // Update sensor readings
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t) && !isnan(h)) {
    temperature = t;
    humidity = h;

    // Buzzer threshold control
    if (temperature > TEMP_THRESHOLD) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}