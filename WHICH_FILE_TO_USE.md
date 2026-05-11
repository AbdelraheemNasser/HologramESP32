# Which ESP32 File to Upload?

## ✅ **Use This File for Arduino IDE:**

```
esp32-firmware-arduino/hologram_pov_esp32/hologram_pov_esp32.ino
```

**Full Path:**
```
HologramProject/
└── esp32-firmware-arduino/
    └── hologram_pov_esp32/
        └── hologram_pov_esp32.ino  ← THIS FILE!
```

---

## 📁 **Project Structure Explained**

You have **TWO** ESP32 firmware folders:

### 1. **esp32-firmware/** (PlatformIO Version)
```
esp32-firmware/
├── platformio.ini
└── src/
    └── main.cpp
```
- ❌ **Don't use this** if you're using Arduino IDE
- ✅ Use this only if you have PlatformIO installed

### 2. **esp32-firmware-arduino/** (Arduino IDE Version) ⭐
```
esp32-firmware-arduino/
├── hologram_pov_esp32/
│   └── hologram_pov_esp32.ino  ← USE THIS!
├── ARDUINO_SETUP_GUIDE.md
├── QUICK_REFERENCE.md
└── README.md
```
- ✅ **Use this** for Arduino IDE
- ✅ This is the correct file!

---

## 🚀 **How to Open in Arduino IDE**

### Method 1: Double-Click
1. Navigate to: `esp32-firmware-arduino/hologram_pov_esp32/`
2. Double-click: `hologram_pov_esp32.ino`
3. Arduino IDE will open automatically

### Method 2: From Arduino IDE
1. Open Arduino IDE
2. File → Open
3. Navigate to: `esp32-firmware-arduino/hologram_pov_esp32/`
4. Select: `hologram_pov_esp32.ino`
5. Click Open

---

## ⚙️ **What's Been Fixed**

### ✅ **Backend Connection Fixed**
The ESP32 code now properly:
- Fetches data from `/api/latest` endpoint
- Parses the complete JSON structure
- Extracts `config` and `frames` correctly
- Handles errors with detailed messages
- Shows progress while loading slices

### ✅ **Better Error Messages**
Now you'll see:
- HTTP response codes
- JSON parsing errors
- Missing data warnings
- Progress updates
- Memory usage

---

## 📝 **Before Uploading**

Edit these lines in `hologram_pov_esp32.ino`:

```cpp
// Line 24-26: WiFi Credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";           // Change this!
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";   // Change this!

// Line 29: Server URL
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";  // Change IP!
```

**Replace:**
- `YOUR_WIFI_SSID` → Your WiFi network name
- `YOUR_WIFI_PASSWORD` → Your WiFi password
- `192.168.1.100` → Your backend server IP address

---

## 🔧 **Upload Steps**

1. **Open the file**: `hologram_pov_esp32.ino`
2. **Edit WiFi and Server settings** (see above)
3. **Connect ESP32** via USB
4. **Select Board**: Tools → Board → ESP32 Dev Module
5. **Select Port**: Tools → Port → (Your COM port)
6. **Click Upload** (→ button)
7. **Open Serial Monitor**: Tools → Serial Monitor (115200 baud)

---

## 📊 **Expected Serial Output**

After uploading, you should see:

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
Connecting to WiFi: MyWiFi
.....
✓ WiFi connected!
IP Address: 192.168.1.150
Signal Strength: -45 dBm

Fetching POV data from server...
URL: http://192.168.1.100:3000/api/latest
HTTP Response Code: 200
Payload size: 45678 bytes
Config loaded:
  Motor RPM: 3000
  Rotation time (us): 20000
Found 1 frame(s)
Processing 120 slices...
  Loaded 20/120
  Loaded 40/120
  Loaded 60/120
  Loaded 80/120
  Loaded 100/120
  Loaded 120/120
✓ POV data loaded successfully!
  Total slices: 120
  Degrees per slice: 3.00
  Microseconds per slice: 166
  Memory used: ~21 KB

========================================
System Ready! Starting POV Display...
========================================
```

---

## 🐛 **Troubleshooting**

### "HTTP Response Code: 404"
```
✗ No images found on server (404)
  Upload an image from the mobile app first!
```
**Solution**: Upload an image using the mobile app first!

### "HTTP Response Code: -1"
```
✗ Connection failed
  Check if server is running and URL is correct.
```
**Solution**: 
- Verify backend server is running
- Check SERVER_URL is correct
- Ensure ESP32 and server on same network

### "JSON parsing failed"
```
✗ JSON parsing failed: ...
```
**Solution**: 
- Check backend is returning valid JSON
- Test URL in browser: `http://YOUR_IP:3000/api/latest`
- Increase JSON buffer size if needed

### "Invalid JSON structure"
```
✗ Invalid JSON structure. Missing 'config' or 'frames'
```
**Solution**: 
- Backend might not be processing images correctly
- Check backend console for errors
- Re-upload image from mobile app

---

## ✅ **Verification Checklist**

Before asking for help, verify:

- [ ] Using correct file: `hologram_pov_esp32.ino`
- [ ] WiFi credentials are correct
- [ ] Server URL is correct (with `/api/latest`)
- [ ] Backend server is running
- [ ] Image uploaded from mobile app
- [ ] ESP32 and server on same network
- [ ] Serial Monitor set to 115200 baud
- [ ] Checked Serial Monitor output for errors

---

## 📚 **Related Files**

- **Setup Guide**: `ARDUINO_SETUP_GUIDE.md`
- **Quick Reference**: `QUICK_REFERENCE.md`
- **Main README**: `README.md`

---

## 🎯 **Summary**

**File to use**: `esp32-firmware-arduino/hologram_pov_esp32/hologram_pov_esp32.ino`

**Steps**:
1. Open file in Arduino IDE
2. Edit WiFi and Server settings
3. Upload to ESP32
4. Check Serial Monitor

**That's it!** 🚀
