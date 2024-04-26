#include <EmonLib.h>        // Include EmonLib for energy monitoring
#include <WiFi.h>           // WiFi library for ESP32
#include <ESP32Firebase.h>  // Firebase library for ESP32
#include <time.h>           // Include the time library for NTP time synchronization

// Firebase configuration
#define _SSID "Get your own WIFI."
#define _PASSWORD "Alfie1234567"
#define REFERENCE_URL "wattwatcher-pro-default-rtdb.firebaseio.com/"

// Initialize Firebase
Firebase firebase(REFERENCE_URL);

// Create two instances of EnergyMonitor for two circuits
EnergyMonitor emon1;
EnergyMonitor emon2;

const float voltage = 230.0;
unsigned long lastMillis = 0;
double dailyTotalPowerWatts1 = 0, dailyTotalCurrentAmps1 = 0, dailyTotalEnergyKWh1 = 0;
double dailyTotalPowerWatts2 = 0, dailyTotalCurrentAmps2 = 0, dailyTotalEnergyKWh2 = 0;
unsigned long lastDailyUpdateMillis = 0; 
const unsigned long dailyUpdateInterval = 86400000; // 24 hours in milliseconds
int dailyMeasurementCount = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Time set");

  emon1.current(34, 22);
  emon2.current(35, 22);

  lastMillis = millis();
  lastDailyUpdateMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  time_t now = time(nullptr);

  if (currentMillis - lastMillis >= 1000) {
    lastMillis = currentMillis;
    double elapsedTime = 1.0; // Elapsed time is 1 second

    double Irms1 = emon1.calcIrms(1480);
    double powerWatts1 = Irms1 * voltage;
    double currentAmps1 = Irms1;
    double energyKWh1 = (powerWatts1 * elapsedTime) / 3600000.0;

    double Irms2 = emon2.calcIrms(1480);
    double powerWatts2 = Irms2 * voltage;
    double currentAmps2 = Irms2;
    double energyKWh2 = (powerWatts2 * elapsedTime) / 3600000.0;

    // Update Firebase with real-time data
    firebase.setFloat("circuit1/Watts", powerWatts1);
    firebase.setFloat("circuit1/Kwh", energyKWh1);
    firebase.setFloat("circuit1/Amps", currentAmps1);
    firebase.setFloat("circuit1/TimeStamp", now);

    firebase.setFloat("circuit2/Watts", powerWatts2);
    firebase.setFloat("circuit2/Kwh", energyKWh2);
    firebase.setFloat("circuit2/Amps", currentAmps2);
    firebase.setFloat("circuit2/TimeStamp", now);

    // Accumulate daily totals
    dailyTotalPowerWatts1 += powerWatts1;
    dailyTotalCurrentAmps1 += currentAmps1;
    dailyTotalEnergyKWh1 += energyKWh1;
    dailyTotalPowerWatts2 += powerWatts2;
    dailyTotalCurrentAmps2 += currentAmps2;
    dailyTotalEnergyKWh2 += energyKWh2;
    dailyMeasurementCount++;
  }

  // Send daily averages to Firebase once every 24 hours
  if (currentMillis - lastDailyUpdateMillis >= dailyUpdateInterval) {
    if (dailyMeasurementCount > 0) {  // Prevent division by zero
      double dailyAvgPowerWatts1 = dailyTotalPowerWatts1 / dailyMeasurementCount;
      double dailyAvgCurrentAmps1 = dailyTotalCurrentAmps1 / dailyMeasurementCount;
      double dailyAvgEnergyKWh1 = dailyTotalEnergyKWh1 / dailyMeasurementCount;

      double dailyAvgPowerWatts2 = dailyTotalPowerWatts2 / dailyMeasurementCount;
      double dailyAvgCurrentAmps2 = dailyTotalCurrentAmps2 / dailyMeasurementCount;
      double dailyAvgEnergyKWh2 = dailyTotalEnergyKWh2 / dailyMeasurementCount;

      // Update Firebase with daily averages
      firebase.setFloat("averages/circuit1/AvgWatts", dailyAvgPowerWatts1);
      firebase.setFloat("averages/circuit1/AvgKwh", dailyAvgEnergyKWh1);
      firebase.setFloat("averages/circuit1/AvgAmps", dailyAvgCurrentAmps1);
      firebase.setFloat("averages/circuit1/TimeStamp", now);

      firebase.setFloat("averages/circuit2/AvgWatts", dailyAvgPowerWatts2);
      firebase.setFloat("averages/circuit2/AvgKwh", dailyAvgEnergyKWh2);
      firebase.setFloat("averages/circuit2/AvgAmps", dailyAvgCurrentAmps2);
      firebase.setFloat("averages/circuit2/TimeStamp", now);

      // Reset daily totals and counter
      dailyTotalPowerWatts1 = dailyTotalCurrentAmps1 = dailyTotalEnergyKWh1 = 0;
      dailyTotalPowerWatts2 = dailyTotalCurrentAmps2 = dailyTotalEnergyKWh2 = 0;
      dailyMeasurementCount = 0;
    }
    lastDailyUpdateMillis = currentMillis;
  }
}
