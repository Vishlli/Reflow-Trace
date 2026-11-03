# RE:FLOW TRACE 🌱
### Smart Monitoring and Traceability for Menstrual Waste Management

## 📌 About the Project

Menstrual waste is generated every day in schools, colleges, workplaces, public facilities, and other institutions. However, managing this waste responsibly involves more than simply collecting it. It is equally important to know when waste needs to be collected, whether it has been picked up, where it is being transported, and whether it has reached the appropriate treatment facility.

**RE:FLOW TRACE** is a smart menstrual-waste monitoring and traceability system designed to make this process more transparent, organised, and accountable.

The project combines IoT-based bin monitoring with a digital tracking system. It helps monitor the fill level of menstrual-waste collection bins and provides a digital way to track waste as it moves through different stages of collection and treatment.

Our goal is to improve visibility into menstrual-waste management and encourage responsible handling through technology.

---

## ❗ The Problem

Menstrual-waste management faces several challenges:

- **Unmonitored collection bins:** It can be difficult to know when a bin is full and needs to be emptied.
- **Delayed collection:** Without timely information, collection may be delayed.
- **Lack of tracking:** Once waste leaves a collection point, it can be difficult to track its movement.
- **Limited accountability:** There may be no easily accessible record of whether waste was collected, transported, and treated.
- **Lack of transparency:** Institutions may find it difficult to monitor the overall waste-management process.

RE:FLOW TRACE aims to address these challenges by connecting smart monitoring with digital waste tracking.

---

## 💡 Our Solution

RE:FLOW TRACE has two major components:

### 1. Smart Bin Monitoring

An ESP32 microcontroller and an ultrasonic sensor are used to estimate how full a menstrual-waste collection bin is.

The sensor measures the distance between itself and the waste surface. Based on this measurement, the system calculates the approximate fill percentage.

When the bin reaches the configured threshold of **84%**, the system generates a `COLLECTION_REQUIRED` alert.

This information is transmitted through an MQTT network to the backend and displayed on the frontend dashboard.

### 2. Digital Waste Traceability

Monitoring a bin tells us when waste needs to be collected, but it does not tell us what happens after collection.

To address this, RE:FLOW TRACE includes a digital waste-tracking workflow.

Each waste batch can be followed through the following stages:

**Generated → Collected → Transported → Received → Treated → Verified**

This workflow is intended to provide a structured record of the waste's journey and improve accountability between the different stages.

---

## ⚙️ How It Works

The system follows this process:

1. **Waste generation:** Menstrual waste is deposited into a designated collection bin.
2. **Fill-level monitoring:** The ultrasonic sensor measures the distance to the waste surface.
3. **Fill percentage calculation:** The ESP32 calculates the estimated bin fill level.
4. **Collection alert:** When the fill level reaches 84%, the system generates a collection-required status.
5. **MQTT communication:** Sensor information is transmitted to the backend through MQTT.
6. **Dashboard update:** The frontend displays the latest collection-point information.
7. **Waste tracking:** After collection, the waste batch can be tracked through the different custody stages.
8. **Verification:** Recorded information can be checked to identify inconsistencies and improve accountability.

---

## 🏗️ System Architecture

The project connects hardware, communication, backend processing, and a frontend dashboard.

```text
       SMART COLLECTION BIN
                |
                v
        Ultrasonic Sensor
                |
                v
             ESP32
                |
                v
          MQTT Network
                |
                v
             Backend
                |
                v
        Frontend Dashboard
                |
                v
       Collection Point Status
```

The digital waste-tracking workflow operates alongside the monitoring system:

```text
Generated
    |
    v
Collected
    |
    v
Transported
    |
    v
Received
    |
    v
Treated
    |
    v
Verified
```

---

## 🖥️ Technology Stack

| Technology | Purpose |
|---|---|
| ESP32 | Microcontroller used for bin monitoring |
| HC-SR04 Ultrasonic Sensor | Measures the distance to the waste surface |
| Wokwi | Simulates the ESP32 and sensor circuit |
| MQTT | Transfers sensor readings between the device and backend |
| Backend | Receives and processes sensor information |
| Frontend | Displays collection-point status and updates |

---

## 🔬 Current Implementation

The following functionality has been implemented and tested in the simulated environment:

- ESP32-based bin monitoring using an HC-SR04 ultrasonic sensor.
- Automatic calculation of estimated bin fill percentage.
- An 84% threshold for generating collection-required alerts.
- LED indication when the alert threshold is reached.
- MQTT communication between the simulation and backend.
- Backend integration for receiving sensor readings.
- Frontend integration for displaying updated collection-point information.

**End-to-end integration:** The project team has run and verified the Wokwi simulation, MQTT communication, backend processing, and frontend updates. Changes in simulated sensor distance are reflected in the dashboard, including the collection alert when the threshold is crossed.

---

## 🧪 Simulation

The hardware monitoring component has been developed and tested using Wokwi.

You can explore the simulation here:

[RE:FLOW TRACE – Wokwi Simulation](https://wokwi.com/projects/479563238720445441)

---

## 🌍 Expected Impact

RE:FLOW TRACE aims to contribute to better menstrual-waste management by:

- Helping collection teams identify bins that require attention.
- Reducing dependence on manual bin-level checking.
- Improving visibility into collection-point status.
- Providing a structured way to record waste movement.
- Encouraging accountability throughout the waste-management process.
- Supporting more organised and responsible menstrual-waste handling.

---

## 🚀 Future Improvements

Potential future developments include:

- Deployment using physical ESP32 hardware and sensors.
- Testing and calibration with actual collection bins.
- QR-code-based identification of waste batches.
- Digital records for collection and treatment activities.
- Role-based access for collection staff, transporters, and treatment facilities.
- Improved reporting and analytics for institutions.
- Stronger verification mechanisms for waste-treatment records.

---

## ⚠️ Limitations

- The ultrasonic sensor estimates fill level; it does not measure the weight or mass of menstrual waste.
- Sensor accuracy may vary depending on the position and surface of the waste.
- The current hardware integration has been tested through simulation; physical deployment requires additional testing and calibration.
- A collection-required alert does not confirm that collection has actually happened. Collection and treatment activities must be recorded separately.

---

## 👥 Project Vision

**RE:FLOW TRACE — Making menstrual-waste management more visible, traceable, and accountable.**

We believe responsible menstrual-waste management should not end with disposal. It should include proper monitoring, collection, tracking, and verification.

Through the integration of IoT and digital traceability, RE:FLOW TRACE aims to make that journey easier to monitor and manage.
