# ESP32 Quick Reference Card

## 🚀 Quick Upload Steps

1. **Install Arduino IDE** → https://www.arduino.cc/en/software
2. **Add ESP32 Board URL** → File → Preferences → Additional Board Manager URLs:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. **Install ESP32 Board** → Tools → Board → Boards Manager → Search "esp32" → Install
4. **Install Libraries** → Tools → Manage Libraries:
   - Install **FastLED**
   - Install **ArduinoJson** (version 6.x)
5. **Open Sketch** → `hologram_pov_esp32.ino`
6. **Edit WiFi** → Change SSID and password in code
7. **Edit Server URL** → Change to your server IP
8. **Select Board** → Tools → Board → ESP32 Dev Module
9. **Select Port** → Tools → Port → (Your COM port)
10. **Upload** → Click Upload button (→)
11. **Open Serial Monitor** → Tools → Serial Monitor → Set 115200 baud

---

## ⚙️ Configuration (Edit in .ino file)

```cpp
// WiFi Settings
const char* WIFI_SSID = "YourWiFiName";
const char* WIFI_PASSWORD = "YourPassword";

// Server Settings
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";

// LED Settings
#define LED_PIN 5
#define NUM_LEDS 60
#define BRIGHTNESS 200        // 0-255

// Hall Sensor Settings
#define HALL_SENSOR_PIN 34
#define HALL_THRESHOLD 2000   // Calibrate this!

// Motor Settings
#define MOTOR_RPM 3000
```

---

## 🔌 Pin Connections

| ESP32 Pin | Connects To | Purpose |
|-----------|-------------|---------|
| 5V | Buck converter output | Power |
| GND | Common ground | Ground |
| GPIO 5 | LED strip DIN (via 470Ω) | LED data |
| GPIO 34 | Hall sensor OUT | Rotation detect |

---

## 📊 Board Settings (Tools Menu)

| Setting | Value |
|---------|-------|
| Board | ESP32 Dev Module |
| Upload Speed | 921600 |
| CPU Frequency | 240MHz (WiFi/BT) |
| Flash Size | 4MB (32Mb) |
| Port | (Your COM port) |

---

## 🔧 Hall Sensor Calibration

1. Upload code and open Serial Monitor
2. Note initial value: `Initial value: 1234`
3. Bring magnet close
4. Note peak value in statistics: `Hall Sensor Value: 3500`
5. Calculate: `(1234 + 3500) / 2 = 2367`
6. Update: `#define HALL_THRESHOLD 2367`
7. Upload again

---

## 📝 Expected Serial Output

```
========================================
   Hologram POV Display - ESP32
========================================

✓ LED strip initialized
✓ Startup animation complete
✓ Hall sensor initialized. Initial value: 1234
✓ WiFi connected!
IP Address: 192.168.1.150
✓ POV data loaded successfully!
  Total slices: 120

System Ready! Starting POV Display...
```

---

## 🐛 Common Issues

### Upload Fails
- Hold BOOT button during upload
- Check USB cable (must be data cable)
- Try different USB port
- Install drivers (CP210x or CH340)

### WiFi Won't Connect
- Check SSID/password (case-sensitive)
- Use 2.4GHz WiFi (not 5GHz)
- Move closer to router

### LEDs Not Working
- Check GPIO 5 connection
- Verify 5V power supply
- Check LED strip direction (DIN → DOUT)
- Add 470Ω resistor to data line

### Can't Fetch Data
- Check server is running
- Verify server URL
- Upload image from mobile app first
- Check firewall settings

---

## 📞 Quick Help

**Serial Monitor shows errors?**
- Read the error message carefully
- Check configuration values
- Verify all connections

**Need to change settings?**
- Edit the .ino file
- Click Upload button
- Wait for upload to complete

**Want to see sensor values?**
- Open Serial Monitor
- Statistics print every 5 seconds
- Shows Hall sensor, WiFi, memory

---

## ✅ Success Checklist

- [ ] Arduino IDE installed
- [ ] ESP32 board support installed
- [ ] FastLED library installed
- [ ] ArduinoJson library installed
- [ ] WiFi credentials configured
- [ ] Server URL configured
- [ ] Board settings correct
- [ ] Upload successful
- [ ] WiFi connected
- [ ] POV data loaded
- [ ] LEDs working
- [ ] Hall sensor calibrated

---

## 🎯 Next Steps

1. **Test LEDs**: Should show rainbow animation on startup
2. **Test WiFi**: Check Serial Monitor for IP address
3. **Test Server**: Upload image from mobile app
4. **Test Hall Sensor**: Bring magnet close, check value changes
5. **Start Motor**: Run at 3000 RPM
6. **See Hologram**: Watch the magic! ✨

---

**For detailed instructions, see: ARDUINO_SETUP_GUIDE.md**
