/*
 * Hologram POV Display - ESP32 Firmware (Arduino IDE Version)
 * 
 * Hardware:
 * - ESP32
 * - 60x WS2812B LED Strip
 * - Hall Effect Sensor A3144
 * - 2x 18650 Batteries (Series)
 * - Buck Converter
 * 
 * Motor: 775 DC Motor @ 3000 RPM (constant speed)
 * 
 * Arduino IDE Setup:
 * 1. Install ESP32 board support
 * 2. Install FastLED library
 * 3. Install ArduinoJson library
 * 4. Select Board: "ESP32 Dev Module"
 * 5. Upload this sketch
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h>

// ==================== CONFIGURATION ====================
// CHANGE THESE VALUES!

// WiFi Credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";           // Change this!
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";   // Change this!

// Server Configuration
const char* SERVER_URL = "http://192.168.1.100:3000/api/latest";  // Change to your server IP!

// LED Configuration
#define LED_PIN 5              // GPIO pin for WS2812B data
#define NUM_LEDS 60            // Number of LEDs
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 200         // 0-255 (adjust for your environment)

// Hall Sensor Configuration
#define HALL_SENSOR_PIN 34     // GPIO pin for Hall sensor (analog capable)
#define HALL_THRESHOLD 2000    // Threshold for magnet detection (calibrate this!)

// Motor Configuration
#define MOTOR_RPM 3000         // Constant motor speed
#define ROTATION_TIME_US 20000 // Microseconds per rotation (60/3000 * 1000000)

// Timing
#define FETCH_INTERVAL 5000    // Fetch new data every 5 seconds
#define WIFI_TIMEOUT 10000     // WiFi connection timeout

// ==================== GLOBAL VARIABLES ====================

CRGB leds[NUM_LEDS];

// POV Data Storage
struct POVSlice {
  float angle;
  CRGB colors[NUM_LEDS];
};

std::vector<POVSlice> currentFrame;
int totalSlices = 0;
float degreesPerSlice = 0;
unsigned long microsecondsPerSlice = 0;

// Timing
unsigned long lastFetchTime = 0;
unsigned long rotationStartTime = 0;
bool rotationDetected = false;

// Statistics
unsigned long frameCount = 0;
unsigned long lastStatsTime = 0;

// ==================== SETUP ====================

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("   Hologram POV Display - ESP32");
  Serial.println("========================================");
  Serial.println();
  
  // Initialize LEDs
  setupLEDs();
  showStartupAnimation();
  
  // Initialize Hall Sensor
  setupHallSensor();
  
  // Connect to WiFi
  setupWiFi();
  
  // Fetch initial POV data
  Serial.println("Fetching initial POV data...");
  if (fetchPOVData()) {
    Serial.println("✓ POV data loaded successfully!");
  } else {
    Serial.println("✗ Failed to load POV data");
  }
  
  Serial.println("\n========================================");
  Serial.println("System Ready! Starting POV Display...");
  Serial.println("========================================\n");
  
  lastStatsTime = millis();
}

// ==================== MAIN LOOP ====================

void loop() {
  // Check Hall sensor for rotation detection
  int hallValue = analogRead(HALL_SENSOR_PIN);
  
  // Detect magnet passing (start of rotation)
  if (hallValue > HALL_THRESHOLD && !rotationDetected) {
    rotationDetected = true;
    rotationStartTime = micros();
    frameCount++;
  } else if (hallValue < HALL_THRESHOLD) {
    rotationDetected = false;
  }
  
  // Display POV frame if we have data
  if (totalSlices > 0) {
    displayPOVFrame();
  } else {
    clearLEDs();
  }
  
  // Fetch new data periodically
  if (millis() - lastFetchTime > FETCH_INTERVAL) {
    lastFetchTime = millis();
    fetchPOVData();
  }
  
  // Print statistics every 5 seconds
  if (millis() - lastStatsTime > 5000) {
    printStats();
    lastStatsTime = millis();
  }
}

// ==================== WIFI SETUP ====================

void setupWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    if (millis() - startTime > WIFI_TIMEOUT) {
      Serial.println("\n✗ WiFi connection timeout!");
      Serial.println("Please check your credentials and try again.");
      return;
    }
  }
  
  Serial.println("\n✓ WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal Strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

// ==================== LED SETUP ====================

void setupLEDs() {
  Serial.println("Initializing LED strip...");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  Serial.println("✓ LED strip initialized");
}

// ==================== HALL SENSOR SETUP ====================

void setupHallSensor() {
  Serial.println("Initializing Hall sensor...");
  pinMode(HALL_SENSOR_PIN, INPUT);
  
  // Read initial value
  int initialValue = analogRead(HALL_SENSOR_PIN);
  Serial.print("✓ Hall sensor initialized. Initial value: ");
  Serial.println(initialValue);
  Serial.println("NOTE: Bring magnet close and check if value changes.");
  Serial.println("      Set HALL_THRESHOLD to midpoint between values.");
}

// ==================== FETCH POV DATA ====================

bool fetchPOVData() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("✗ WiFi not connected. Cannot fetch data.");
    return false;
  }
  
  HTTPClient http;
  http.begin(SERVER_URL);
  http.setTimeout(5000);
  
  Serial.println("Fetching POV data from server...");
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    
    // Parse JSON
    DynamicJsonDocument doc(65536); // 64KB buffer
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      Serial.print("✗ JSON parsing failed: ");
      Serial.println(error.c_str());
      http.end();
      return false;
    }
    
    // Clear existing data
    currentFrame.clear();
    
    // Extract configuration
    JsonObject config = doc["config"];
    int motorRPM = config["motorRPM"] | MOTOR_RPM;
    microsecondsPerSlice = config["microsecondsPerRotation"] | ROTATION_TIME_US;
    
    // Extract frame data
    JsonArray frames = doc["frames"];
    if (frames.size() > 0) {
      JsonObject frame = frames[0]; // Use first frame for now
      totalSlices = frame["sliceCount"] | 0;
      degreesPerSlice = 360.0 / totalSlices;
      microsecondsPerSlice = ROTATION_TIME_US / totalSlices;
      
      JsonArray slices = frame["slices"];
      
      for (JsonObject slice : slices) {
        POVSlice povSlice;
        povSlice.angle = slice["angle"] | 0.0;
        
        JsonArray leds = slice["leds"];
        int ledIndex = 0;
        for (JsonObject led : leds) {
          if (ledIndex < NUM_LEDS) {
            povSlice.colors[ledIndex] = CRGB(
              led["r"] | 0,
              led["g"] | 0,
              led["b"] | 0
            );
            ledIndex++;
          }
        }
        
        currentFrame.push_back(povSlice);
      }
      
      Serial.println("✓ POV data loaded successfully!");
      Serial.print("  Total slices: ");
      Serial.println(totalSlices);
      Serial.print("  Degrees per slice: ");
      Serial.println(degreesPerSlice);
      Serial.print("  Microseconds per slice: ");
      Serial.println(microsecondsPerSlice);
      
      http.end();
      return true;
    }
  } else {
    Serial.print("✗ HTTP request failed. Code: ");
    Serial.println(httpCode);
    if (httpCode == -1) {
      Serial.println("  Check if server is running and URL is correct.");
    }
  }
  
  http.end();
  return false;
}

// ==================== DISPLAY POV FRAME ====================

void displayPOVFrame() {
  if (totalSlices == 0 || currentFrame.empty()) {
    return;
  }
  
  // Calculate current angle based on time since rotation start
  unsigned long elapsedTime = micros() - rotationStartTime;
  int sliceIndex = (elapsedTime / microsecondsPerSlice) % totalSlices;
  
  // Ensure valid index
  if (sliceIndex >= 0 && sliceIndex < currentFrame.size()) {
    POVSlice& slice = currentFrame[sliceIndex];
    
    // Update LEDs with current slice colors
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = slice.colors[i];
    }
    
    FastLED.show();
  }
}

// ==================== UTILITY FUNCTIONS ====================

void clearLEDs() {
  FastLED.clear();
  FastLED.show();
}

void showStartupAnimation() {
  Serial.println("Playing startup animation...");
  
  // Rainbow wave
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i * 255 / NUM_LEDS, 255, 255);
      FastLED.show();
      delay(10);
    }
  }
  
  // Fade out
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(10);
  }
  
  FastLED.setBrightness(BRIGHTNESS);
  clearLEDs();
  Serial.println("✓ Startup animation complete");
}

void printStats() {
  Serial.println("\n--- Statistics ---");
  Serial.print("WiFi Status: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  }
  
  Serial.print("Total Rotations: ");
  Serial.println(frameCount);
  Serial.print("Current Slices: ");
  Serial.println(totalSlices);
  Serial.print("Hall Sensor Value: ");
  Serial.println(analogRead(HALL_SENSOR_PIN));
  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
  Serial.println("------------------\n");
}
