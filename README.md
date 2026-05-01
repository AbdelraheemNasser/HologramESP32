# Hologram POV - ESP32 Firmware

ESP32 firmware for controlling 60 WS2812B LEDs to create a POV (Persistence of Vision) hologram display.

![ESP32](https://img.shields.io/badge/ESP32-Arduino-blue.svg)
![FastLED](https://img.shields.io/badge/FastLED-3.6+-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## 🌟 Features

- ✅ WiFi connectivity
- ✅ Automatic POV data fetching from server
- ✅ Hall sensor rotation detection (A3144)
- ✅ Controls 60 WS2812B LEDs
- ✅ Precise timing for 3000 RPM motor
- ✅ Serial monitoring and debugging
- ✅ Startup animation
- ✅ Statistics reporting

## 🔧 Hardware Requirements

### Rotating Part (Battery Powered)
- ESP32 Development Board
- 60x WS2812B LED Strip (1 meter)
- Hall Effect Sensor A3144
- 2x 18650 Batteries (series connection)
- Buck Converter (7.4V → 5V)
- 1000µF Capacitor
- 470Ω Resistor

### Static Part (External Power)
- DC Motor 775 (3000 RPM)
- Motor Driver (L298N or similar)
- 12V Power Supply (2A+)
- Small Neodymium Magnet

## 📋 Prerequisites

- Arduino IDE 1.8.19+ or Arduino IDE 2.x
- ESP32 board support installed
- FastLED library
- ArduinoJson library (version 6.x)

## 🚀 Quick Start

### 1. Install Arduino IDE

Download from: https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Open Arduino IDE
2. File → Preferences
3. Add to "Additional Board Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Tools → Board → Boards Manager
5. Search "esp32" and install "esp32 by Espressif Systems"

### 3. Install Required Libraries

Tools → Manage Libraries:
- Install **FastLED** by Daniel Garcia
- Install **ArduinoJson** by Benoit Blanchon (version 6.x)

### 4. Open the Sketch

Open: `hologram_pov_esp32/hologram_pov_esp32.ino`

### 5. Configure WiFi and Server

Edit these lines in the sketch:

```cpp
const char* WIFI_SSID = "YourWiFiName";
const char* WIFI_PASSWORD = "YourPassword";
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";
```

### 6. Upload to ESP32

1. Connect ESP32 via USB
2. Tools → Board → ESP32 Dev Module
3. Tools → Port → (Select your COM port)
4. Click Upload button (→)

### 7. Monitor Output

1. Tools → Serial Monitor
2. Set baud rate to **115200**
3. You should see startup messages

## 🔌 Pin Connections

| ESP32 Pin | Connects To | Purpose |
|-----------|-------------|---------|
| 5V | Buck converter output | Power |
| GND | Common ground | Ground |
| GPIO 5 | LED strip DIN (via 470Ω) | LED data |
| GPIO 34 | Hall sensor OUT | Rotation detect |

## ⚙️ Configuration

### WiFi Settings
```cpp
const char* WIFI_SSID = "YourWiFiName";
const char* WIFI_PASSWORD = "YourPassword";
```

### Server Settings
```cpp
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";
```

### LED Settings
```cpp
#define LED_PIN 5              // GPIO pin
#define NUM_LEDS 60            // Number of LEDs
#define BRIGHTNESS 200         // 0-255
```

### Hall Sensor Settings
```cpp
#define HALL_SENSOR_PIN 34     // GPIO pin
#define HALL_THRESHOLD 2000    // Calibrate this!
```

### Motor Settings
```cpp
#define MOTOR_RPM 3000         // Constant speed
```

## 🔧 Calibrating Hall Sensor

1. Upload code and open Serial Monitor
2. Note initial value (e.g., 1234)
3. Bring magnet close to sensor
4. Note peak value (e.g., 3500)
5. Calculate threshold: `(1234 + 3500) / 2 = 2367`
6. Update `HALL_THRESHOLD` in code
7. Upload again

## 📊 Expected Output

After successful upload:

```
========================================
   Hologram POV Display - ESP32
========================================

✓ LED strip initialized
✓ Startup animation complete
✓ Hall sensor initialized. Initial value: 1234
Connecting to WiFi: MyWiFi
✓ WiFi connected!
IP Address: 192.168.1.150
Signal Strength: -45 dBm
Fetching initial POV data...
✓ POV data loaded successfully!
  Total slices: 120
  Degrees per slice: 3.00
  Microseconds per slice: 166

========================================
System Ready! Starting POV Display...
========================================
```

## 🐛 Troubleshooting

### Upload Fails
- Hold BOOT button on ESP32 during upload
- Check USB cable (must be data cable)
- Install CP210x or CH340 drivers
- Try different USB port

### WiFi Won't Connect
- Verify SSID and password (case-sensitive)
- Use 2.4GHz WiFi (ESP32 doesn't support 5GHz)
- Move ESP32 closer to router

### LEDs Not Working
- Check GPIO 5 connection
- Verify 5V power supply
- Check LED strip direction (DIN → DOUT)
- Add 470Ω resistor to data line

### Can't Fetch POV Data
- Ensure backend server is running
- Verify SERVER_URL is correct
- Upload image from mobile app first
- Check ESP32 and server on same network

### Hall Sensor Not Detecting
- Verify GPIO 34 connection
- Check sensor orientation
- Bring magnet closer
- Calibrate HALL_THRESHOLD value

## 📁 Project Structure

```
esp32-firmware-arduino/
├── hologram_pov_esp32/
│   └── hologram_pov_esp32.ino    # Main Arduino sketch
├── ARDUINO_SETUP_GUIDE.md         # Complete setup guide
├── QUICK_REFERENCE.md             # Quick reference card
└── README.md                      # This file
```

## 🔄 How It Works

1. **Startup**: ESP32 initializes LEDs, Hall sensor, and WiFi
2. **Connect**: Connects to WiFi network
3. **Fetch**: Downloads POV data from backend server
4. **Detect**: Hall sensor detects magnet passing (rotation start)
5. **Calculate**: Calculates current angle based on time
6. **Display**: Shows correct LED slice for current angle
7. **Repeat**: Loop continues at high speed
8. **Update**: Fetches new data every 5 seconds

## 📈 Performance

- **Rotation Speed**: 3000 RPM (50 Hz)
- **Rotation Period**: 20 milliseconds
- **Typical Slices**: 120 per rotation
- **Time per Slice**: ~166 microseconds
- **LED Update Rate**: ~6000 updates/second
- **Data Fetch**: Every 5 seconds

## 💡 Tips

### For Best Results
- Use fresh, high-quality 18650 batteries
- Ensure motor speed is exactly 3000 RPM
- Calibrate Hall sensor threshold carefully
- Keep ESP32 close to WiFi router
- Use dark environment for best visibility
- Balance rotating arm to reduce vibration

### For Debugging
- Always check Serial Monitor first
- Statistics print every 5 seconds
- Hall sensor value shown in statistics
- WiFi signal strength displayed
- Free heap memory monitored

## 🔗 Related Repositories

- **Backend Server**: https://github.com/AbdelraheemNasser/HologramBackend
- **Mobile App**: https://github.com/AbdelraheemNasser/HologramMobileApp

## 📄 License

MIT License - Feel free to use and modify!

## 👨‍💻 Author

Abdelraheem Nasser

## 🙏 Acknowledgments

- FastLED library for LED control
- ArduinoJson for JSON parsing
- ESP32 Arduino Core by Espressif
- Arduino community for support

## ⚠️ Safety Warning

- Keep hands away from rotating parts
- Use protected 18650 batteries
- Verify all voltages before powering on
- Secure all rotating components
- Have emergency stop switch ready
