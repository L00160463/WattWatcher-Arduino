# WattWatcher: IoT Energy Monitoring System

## Introduction
WattWatcher is an IoT solution developed by Matthew Mc Daid for monitoring residential energy use in real-time as part of his BSc (Hons) in Applied Computing thesis at Atlantic Technological University.

## Features
- **Real-Time Monitoring:** Instant updates on electricity use.
- **Cross-Platform App:** Accessible via a .NET MAUI application.
- **Cloud Integration:** Uses Firebase for data management.
- **Alerts:** Notifications for significant usage or tariff changes.

## System Components
- **Hardware:** ESP-32 module and Current Transformer Clamps.
- **Database:** Firebase.
- **Application:** .NET MAUI for user interface.

## Setup
### Prerequisites
- Arduino IDE
- .NET MAUI SDK
- Firebase account

### Installation Steps
1. Clone the repo:
git clone https://github.com/L00160463/WattWatcher-Arduino.git
2. Setup Arduino:
- Install libraries in Arduino IDE.
- Upload scripts to ESP-32.
3. Setup Firebase:
- Create a project.
- Update .NET MAUI app with Firebase keys.
4. Run .NET MAUI app:
- Open in Visual Studio and run.

## Usage
Start the system to monitor electricity. The app displays current and historical usage.

