# WattWatcher: An IoT Energy Monitoring System

Welcome to the WattWatcher repository! This project is a comprehensive Internet of Things (IoT) solution for monitoring residential energy usage in real-time. It is developed as part of Matthew Mc Daid's final thesis for the BSc (Hons) in Applied Computing at the Atlantic Technological University.

## Project Overview

WattWatcher utilizes a 4 Channel ESP-8266 Mains Current Sensor and the ESP-8266 Wi-Fi Module to monitor electricity consumption at the circuit level within households. The system leverages Current Transformer (CT) Clamps to safely measure electricity usage without the need to modify existing electrical installations.

### Key Features

- **Real-Time Monitoring**: Track electricity usage instantaneously and receive updates through a user-friendly interface.
- **Cross-Platform Accessibility**: Access energy data on various devices through a .NET MAUI-based application that provides a seamless user experience.
- **Cloud Integration**: Utilize Firebase for secure and real-time data storage and management.
- **User Alerts**: Get notified about critical energy usage and tariff changes, empowering users to manage consumption more effectively.

## System Architecture

The system architecture encompasses several components working in harmony:

- **ESP-8266 and CT Clamps**: Capture and transmit the current data.
- **Firebase Database**: Stores the energy usage data securely in the cloud.
- **.NET MAUI Application**: Acts as the interface for data visualization and user interaction.

![System Data Flow Diagram](/assets/data_flow_diagram.png) *Data Flow Diagram of the WattWatcher System*

## Getting Started

### Prerequisites

- Arduino IDE
- .NET MAUI SDK
- Firebase account

### Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/L00160463/WattWatcher-Arduino.git
