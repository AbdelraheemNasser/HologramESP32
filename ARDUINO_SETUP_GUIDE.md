# Arduino IDE Setup Guide for ESP32 Hologram POV

Complete step-by-step guide to upload the firmware using Arduino IDE.

---

## 📋 Prerequisites

- Arduino IDE 1.8.19 or newer (or Arduino IDE 2.x)
- ESP32 development board
- USB cable (data cable, not just charging)
- Windows/Mac/Linux computer

---

## 🔧 Step 1: Install Arduino IDE

### Download Arduino IDE

**Option 1: Arduino IDE 2.x (Recommended)**
- Download from: https://www.arduino.cc/en/software
- Modern interface, faster, better

**Option 2: Arduino IDE 1.8.x (Classic)**
- Download from: https://www.arduino.cc/en/software
- More stable, widely used

Install and open Arduino IDE.

---

## 📦 Step 2: Install ESP32 Board Support

### Method 1: Using Board Manager (Recommended)

1. **Open Preferences**
   - File → Preferences (Windows/Linux)
   - Arduino IDE → Preferences (Mac)

2. **Add ESP32 Board Manager URL**
   - Find "Additional Board Manager URLs"
   - Paste this URL:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
   - If you have other URLs, separate with comma
   - Click OK

3. **Open Boards Manager**
   - Tools → Board → Boards Manager
   - Wait for index to download

4. **Install ESP32**
   - Search for "esp32"
   - Find "esp32 by Espressif Systems"
   - Click Install
   - Wait for installation (may take 5-10 minutes)
   - Click Close when done

5. **Verify Installation**
   - Tools → Board → ESP32 Arduino
   - You should see many ESP32 boards listed

---

## 📚 Step 3: Install Required Libraries

### Install FastLED Library

1. **Open Library Manager**
   - Tools → Manage Libraries (or Sketch → Include Library → Manage Libraries)

2. **Search and Install FastLED**
   - Type "FastLED" in search box
   - Find "FastLED by Daniel Garcia"
   - Click Install
   - Wait for installation
   - Click Close

### Install ArduinoJson Library

1. **In Library Manager**
   - Type "ArduinoJson" in search box
   - Find "ArduinoJson by Benoit Blanchon"
   - **Important**: Install version 6.x (not 7.x)
   - Click Install
   - Click Close

### Verify Libraries Installed

- Sketch → Include Library
- You should see "FastLED" and "ArduinoJson" in the list

---

## 📝 Step 4: Open the Sketch

1. **Navigate to the sketch folder**
   - Go to: `esp32-firmware-arduino/hologram_pov_esp32/`
   - Double-click: `hologram_pov_esp32.ino`

2. **Arduino IDE should open with the sketch**

---

## ⚙️ Step 5: Configure the Sketch

### Edit WiFi Credentials

Find these lines near the top of the sketch:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

**Change to your WiFi:**
```cpp
const char* WIFI_SSID = "MyHomeWiFi";        // Your WiFi name
const char* WIFI_PASSWORD = "mypassword123";  // Your WiFi password
```

**Important**: 
- Use 2.4GHz WiFi (ESP32 doesn't support 5GHz)
- WiFi name is case-sensitive
- Use double quotes

### Edit Server URL

Find this line:

```cpp
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";
```

**Change to your server IP:**
```cpp
const char* SERVER_URL = "http://192.168.1.50:3000/api/latest";
```

Replace `192.168.1.50` with your backend server's IP address.

### Optional: Adjust Settings

```cpp
#define BRIGHTNESS 200         // LED brightness (0-255)
#define HALL_THRESHOLD 2000    // Hall sensor threshold (calibrate later)
```

---

## 🔌 Step 6: Connect ESP32

1. **Connect ESP32 to computer via USB cable**
   - Use a data cable (not just charging cable)
   - ESP32 power LED should light up

2. **Install USB Drivers (if needed)**

   **Windows:**
   - If ESP32 not detected, install CP210x or CH340 drivers
   - CP210x: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - CH340: http://www.wch-ic.com/downloads/CH341SER_EXE.html

   **Mac:**
   - Usually works without drivers
   - If not, install CP210x drivers

   **Linux:**
   - Usually works without drivers
   - May need to add user to dialout group:
   ```bash
   sudo usermod -a -G dialout $USER
   ```
   - Log out and log back in

3. **Verify Connection**
   - Tools → Port
   - You should see a COM port (Windows) or /dev/cu.* (Mac) or /dev/ttyUSB* (Linux)

---

## 🎯 Step 7: Configure Board Settings

### Select Board

1. **Tools → Board → ESP32 Arduino**
2. **Select: "ESP32 Dev Module"**

### Configure Board Settings

Set these options in Tools menu:

| Setting | Value |
|---------|-------|
| Board | ESP32 Dev Module |
| Upload Speed | 921600 |
| CPU Frequency | 240MHz (WiFi/BT) |
| Flash Frequency | 80MHz |
| Flash Mode | QIO |
| Flash Size | 4MB (32Mb) |
| Partition Scheme | Default 4MB with spiffs |
| Core Debug Level | None |
| PSRAM | Disabled |
| Port | (Select your COM port) |

**Important**: Make sure to select the correct **Port**!

---

## 📤 Step 8: Upload the Sketch

1. **Click the Upload button** (→ arrow icon)
   - Or: Sketch → Upload
   - Or: Ctrl+U (Windows/Linux) / Cmd+U (Mac)

2. **Wait for compilation**
   - You'll see "Compiling sketch..." at the bottom
   - May take 1-2 minutes first time

3. **Wait for upload**
   - You'll see "Uploading..." 
   - ESP32 LEDs may blink
   - Progress bar shows upload status

4. **Upload Complete**
   - You'll see "Done uploading" message
   - ESP32 will automatically restart

### If Upload Fails

**"Failed to connect to ESP32":**
- Hold BOOT button on ESP32
- Click Upload
- Keep holding BOOT until "Connecting..." appears
- Release BOOT button

**"Port not found":**
- Check USB cable (use data cable)
- Check drivers installed
- Try different USB port
- Restart Arduino IDE

**"Compilation error":**
- Check libraries installed (FastLED, ArduinoJson)
- Check board selected (ESP32 Dev Module)
- Check code for typos

---

## 📊 Step 9: Monitor Serial Output

1. **Open Serial Monitor**
   - Tools → Serial Monitor
   - Or: Ctrl+Shift+M (Windows/Linux) / Cmd+Shift+M (Mac)

2. **Set Baud Rate**
   - Bottom right corner: Select **115200 baud**

3. **You should see output like:**

```
========================================
   Hologram POV Display - ESP32
========================================

Initializing LED strip...
✓ LED strip initialized
Playing startup animation...
✓ Startup animation complete
Initializing Hall sensor...
✓ Hall sensor initialized. Initial value: 1234
Connecting to WiFi: MyHomeWiFi
.....
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

---

## 🔧 Step 10: Calibrate Hall Sensor

### Find Threshold Value

1. **Check Serial Monitor** for initial Hall sensor value:
   ```
   ✓ Hall sensor initialized. Initial value: 1234
   ```

2. **Bring magnet close** to Hall sensor

3. **Watch statistics** (printed every 5 seconds):
   ```
   --- Statistics ---
   Hall Sensor Value: 3500
   ```

4. **Calculate threshold**:
   ```
   Threshold = (Initial + Peak) / 2
   Example: (1234 + 3500) / 2 = 2367
   ```

5. **Update in sketch**:
   ```cpp
   #define HALL_THRESHOLD 2367  // Your calculated value
   ```

6. **Upload again** (click Upload button)

---

## ✅ Verification Checklist

After upload, verify:

- [ ] ESP32 powers on
- [ ] LEDs show startup animation (rainbow)
- [ ] WiFi connects (check Serial Monitor)
- [ ] IP address displayed
- [ ] POV data fetched successfully
- [ ] Statistics printed every 5 seconds
- [ ] Hall sensor reading shown

---

## 🐛 Troubleshooting

### WiFi Won't Connect

**Check:**
- SSID and password are correct (case-sensitive)
- Using 2.4GHz WiFi (not 5GHz)
- ESP32 is within WiFi range
- WiFi network is working

**Try:**
- Move ESP32 closer to router
- Restart router
- Check for special characters in password
- Try different WiFi network

### LEDs Not Working

**Check:**
- LED strip connected to GPIO 5
- LED strip powered (5V and GND)
- LED strip data direction (DIN → DOUT)
- 470Ω resistor between ESP32 and LED data

**Try:**
- Test with simple FastLED example
- Check LED strip with multimeter
- Verify 5V power supply

### Can't Fetch POV Data

**Check:**
- Backend server is running
- Server URL is correct
- ESP32 and server on same network
- Firewall not blocking

**Try:**
- Test server URL in browser
- Ping server from computer
- Check server logs
- Upload image from mobile app first

### Upload Fails

**Check:**
- USB cable is data cable (not just charging)
- Correct COM port selected
- Drivers installed
- No other program using serial port

**Try:**
- Hold BOOT button during upload
- Try different USB port
- Restart Arduino IDE
- Restart computer

---

## 📁 File Location

After installation, your sketch is at:
```
esp32-firmware-arduino/
└── hologram_pov_esp32/
    └── hologram_pov_esp32.ino
```

---

## 🎓 Arduino IDE Tips

### Keyboard Shortcuts

| Action | Windows/Linux | Mac |
|--------|---------------|-----|
| Verify | Ctrl+R | Cmd+R |
| Upload | Ctrl+U | Cmd+U |
| Serial Monitor | Ctrl+Shift+M | Cmd+Shift+M |
| Save | Ctrl+S | Cmd+S |

### Useful Menu Items

- **Sketch → Verify/Compile**: Check for errors without uploading
- **Tools → Serial Monitor**: View ESP32 output
- **Tools → Serial Plotter**: Graph sensor values
- **File → Examples**: Browse example sketches

---

## 🔄 Updating the Code

To make changes:

1. Edit the `.ino` file
2. Click Verify (✓) to check for errors
3. Click Upload (→) to upload changes
4. Open Serial Monitor to see output

---

## 📚 Additional Resources

### ESP32 Documentation
- ESP32 Arduino Core: https://docs.espressif.com/projects/arduino-esp32/
- ESP32 Pinout: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

### Library Documentation
- FastLED: https://fastled.io/
- ArduinoJson: https://arduinojson.org/

### Tutorials
- ESP32 Getting Started: https://randomnerdtutorials.com/getting-started-with-esp32/
- FastLED Tutorial: https://github.com/FastLED/FastLED/wiki

---

## ✨ You're Ready!

Once you see this in Serial Monitor:
```
System Ready! Starting POV Display...
```

Your ESP32 is ready to display holograms! 🎉

Now:
1. Upload an image from mobile app
2. Wait 5 seconds for ESP32 to fetch it
3. Start the motor at 3000 RPM
4. Watch your hologram appear! ✨

---

**Need help? Check the Serial Monitor output for error messages!**
