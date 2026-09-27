# ESP32 DHT11 Environment Monitor

An IoT-based temperature and humidity monitoring system using ESP32 and DHT11. The system hosts a web dashboard that displays real-time sensor readings and activates a buzzer when the temperature exceeds a predefined threshold.

## Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- ESP32 Wi-Fi connectivity
- Web-based monitoring dashboard
- Automatic data refresh every 2 seconds
- High-temperature warning
- Buzzer alert system
- Responsive web interface

## Components Required

- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- Buzzer
- Jumper wires
- Breadboard
- USB cable
- Wi-Fi network

## Technologies Used

- ESP32
- Arduino IDE
- C++
- DHT11
- HTML
- CSS
- JavaScript
- WebServer library

## Circuit Connections

| Component | ESP32 Pin |
|-----------|-----------|
| DHT11 Data | GPIO 4 |
| Buzzer | GPIO 25 |
| DHT11 VCC | 3.3V |
| DHT11 GND | GND |

## Working

The DHT11 sensor measures temperature and humidity.

The ESP32 reads the sensor values and hosts a web server.

Users can open the ESP32's IP address in a web browser to view the dashboard.

The dashboard automatically requests updated sensor data every 2 seconds.

If the temperature rises above 35°C, the buzzer is activated and the dashboard displays a high-temperature warning.

## System Flow

DHT11 Sensor
↓
ESP32
↓
Read Temperature and Humidity
↓
Web Server
↓
Web Dashboard

Temperature > 35°C
↓
Buzzer ON
↓
High Temperature Warning

## Dashboard

The dashboard displays:

- Temperature in °C
- Humidity in %
- System status
- High-temperature warning

## Setup

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Install the DHT sensor library.
4. Connect the DHT11 sensor and buzzer to the ESP32.
5. Update the Wi-Fi credentials in the Arduino code.
6. Upload the code to the ESP32.
7. Open Serial Monitor at 115200 baud.
8. Note the IP address displayed by the ESP32.
9. Enter that IP address in a web browser connected to the same Wi-Fi network.

## Temperature Alert

The default temperature threshold is:

35°C

When:

Temperature > 35°C

the buzzer turns ON.

## Future Improvements

- Add temperature and humidity graphs
- Store historical sensor data
- Add mobile notifications
- Add data logging
- Add cloud connectivity
- Add adjustable temperature thresholds
- Improve dashboard design
- Add multiple sensors

## Author

Rajeswari

## License

This project is open source and available for learning and educational purposes.
