
RE:FLOW — TRACE
Menstrual-waste collection monitoring and chain-of-custody prototype
TRACE is a prototype for improving visibility and accountability in menstrual-waste collection. It combines a collection-point monitoring device with an application for viewing fill levels, identifying collection needs, and tracking waste batches through the chain of custody.

The project brings together three parts:

ESP32 + Wokwi simulation — estimates the fill level of a collection bin using an ultrasonic distance sensor and signals when collection is needed.
MQTT messaging — carries telemetry from the simulated device into the software pipeline.
Backend + frontend dashboard — receives/handles device data and presents the resulting readings and collection status in the TRACE interface.
The project is a prototype. Simulated readings and successful software integration demonstrate the workflow, but do not by themselves establish that a physical deployment, regulated waste-treatment process, or production-grade security system has been validated.

Problem
Menstrual-waste collection can be difficult to monitor consistently across multiple collection points. Staff may not know which bins need attention, and a collection record alone does not prove that waste was received and treated.

TRACE aims to make collection-point status more visible and to support a traceable record of a waste batch from generation and collection through transport, receipt, treatment, and verification.

Current project status
Based on the implementation and testing reported by the project team:


Built the TRACE frontend dashboard and chain-of-custody interface.

Created an ESP32-based bin-fill monitoring simulation in Wokwi.

Ran the Wokwi simulation and observed sensor-derived fill calculations and threshold status.

Connected the simulated device to an MQTT network.

Connected the device-data path to the backend.

Connected the frontend to the software data path so the dashboard reflects incoming changes.

Ran and verified an end-to-end integration test: changing the simulated sensor distance changed the calculated fill percentage; crossing the 84% threshold triggered the collection alert; the MQTT message reached the backend; and the corresponding collection-point information updated in the frontend dashboard.

Implemented rule-based waste quantity reconciliation and discrepancy states in the application prototype.

Added configurable fill thresholds and stale-reading concepts to the dashboard prototype.
Important version note: the uploaded source archive previously reviewed in this project contained an earlier frontend-only snapshot. The integration status above reflects the team's subsequent report that MQTT, backend, and frontend are now connected. Confirm the latest repository files and configuration before using the commands below in a fresh environment.

System overview
HC-SR04 ultrasonic sensor
          |
          v
       ESP32
  distance -> fill %
  threshold -> LED/status
          |
          | MQTT telemetry
          v
      MQTT broker
          |
          v
      TRACE backend
          |
          v
  TRACE frontend dashboard
  readings / point status /
  collection attention
The backend is the bridge between device telemetry and the frontend. The browser dashboard should not need to connect directly to the sensor. Keep broker credentials, API secrets, and database credentials in local environment configuration rather than committing them to source control.

Wokwi sensor simulation
The current simulation uses the following configuration:

Item	Configuration
Controller	ESP32 DevKit
Distance sensor	HC-SR04 ultrasonic sensor
Trigger pin	GPIO 5
Echo pin	GPIO 18
Indicator	Red LED on GPIO 2, through a 220 Ω resistor
Assumed usable bin height	40 cm
Collection alert threshold	84%
Reported point ID	BLOCK-D-04
Serial monitor speed	115200 baud
Measurement interval	Approximately 2 seconds
Fill calculation
The sensor measures the distance between the sensor and the waste surface. The firmware estimates the percentage of the assumed bin height occupied by waste:

fill_percent = ((bin_height_cm - distance_cm) / bin_height_cm) * 100
The calculated value is constrained to the range 0–100%.

With a configured bin height of 40 cm, an estimated distance of 6.4 cm corresponds to approximately 84% full. At or above the configured 84% threshold, the firmware turns on the red LED and reports COLLECTION_REQUIRED; below the threshold, it reports NORMAL.

If the sensor does not receive an echo before its timeout, the firmware prints a sensor-error message and retries.

What the sensor does and does not establish
It estimates fill level from distance; it does not measure waste mass.
The 40 cm height is a configured assumption and should be calibrated for a real bin.
An irregular waste surface can affect readings.
A full-bin alert means collection may be needed. It does not prove that a collection, handoff, transport, or treatment occurred.
Wokwi results are simulated device readings, not measurements from deployed physical hardware.
Application capabilities
The TRACE application prototype is designed around two connected workflows.

Collection-point monitoring
View collection points and their latest fill readings.
Identify points that may require collection.
Represent device/readings status and freshness.
Use fill thresholds to distinguish warning and critical levels.
Show reading history and forecast time-to-threshold where enough readings are available.
Waste-batch chain of custody
The application models the following stages:

Generated — a waste batch is created at a collection point.
Collected — collection is recorded.
Transported — custody is transferred to a transporter.
Received — the receiving facility records receipt.
Treated — treatment is recorded.
Verified — the available records are evaluated against the application's rules.
The prototype includes batch records, handoff entry, discrepancy review, evidence views, audit views, point QR pages, network/facility views, and control settings. The exact persistence and availability of each feature depend on the currently deployed version.

Rule-based reconciliation
The application includes rule-based logic for comparing recorded mass between custody stages. The default quantity tolerance in the earlier frontend snapshot was ±5%, and timing windows were configurable. The engine can distinguish states such as:

Verified — required digital records are present and checks pass.
Attested — records rely on an attestation or a facility that cannot record digitally.
Discrepancy — a configured quantity or timing rule is breached.
Pending — required stages or synchronization are still missing.
These are software verdicts based on recorded data and configured rules; they are not independent proof of legal compliance or treatment quality. Do not describe the rules engine as AI or machine learning.

MQTT and software integration
The reported integration path is:

The ESP32 simulation calculates distance, fill percentage, and collection status.
The device publishes telemetry through the configured MQTT connection.
The backend consumes the incoming telemetry and makes the relevant reading/state available to the application.
The frontend reflects the updated point reading and status.
Use the actual topic names, payload schema, broker address, and backend configuration present in the current source files. They are intentionally not hard-coded into this README because they must match the running configuration.

Integration checks — completed and verified
The project team has reported that the following end-to-end checks have already been run successfully:

Simulation: the Wokwi simulation was started and run.
Sensor response: changing the simulated sensor distance changed the calculated fill percentage.
Threshold behaviour: crossing the 84% threshold triggered the COLLECTION_REQUIRED status and red LED.
MQTT delivery: the telemetry message was observed reaching the MQTT/backend data path.
Backend processing: the backend reflected the incoming device reading.
Frontend update: the corresponding collection-point information updated in the TRACE dashboard.
This confirms the reported end-to-end demonstration path from the simulated sensor to the dashboard. It does not, by itself, validate physical hardware performance or production deployment reliability.

For reproducibility, keep the exact startup commands, environment-variable names (never their secret values), broker details, MQTT topic, payload example, and observed test output alongside the current code. Those project-specific values should be copied from the working configuration rather than guessed.

If the device identifier in the firmware is BLOCK-D-04, make sure the backend and frontend map that identifier to the intended TRACE collection point. Avoid silently mapping it to a different point ID.

Additional resilience checks—such as reconnect behaviour, duplicate messages, malformed payloads, and stale readings—should be tested separately if they have not already been covered.

Getting started
The exact startup commands depend on the current repository layout and environment configuration. Use the scripts and configuration files present in the latest checked-out version.

Prerequisites
Git
Node.js and npm for the web application
An MQTT broker reachable by the device and backend
The backend runtime and database, if the current deployment uses one
A Wokwi account or the Wokwi project/simulation files
General setup sequence
Clone the repository and install dependencies for the frontend and backend from their respective project directories.
Configure the MQTT broker connection and any backend/database settings using local environment files or the configuration mechanism used by the project.
Start the MQTT broker.
Start the backend and confirm that it connects to the broker.
Start the frontend using the development command defined in its package.json.
Run the Wokwi simulation and confirm that telemetry is received by the backend and reflected in the dashboard.
Do not commit .env files, passwords, access tokens, private broker credentials, or production secrets. If a secret has been committed, rotate it; deleting it from the latest commit alone may not remove it from Git history.

Wokwi project
Simulation: https://wokwi.com/projects/479563238720445441

Use the firmware source and circuit diagram associated with the current Wokwi project as the source of truth for pin assignments and telemetry behaviour.

Demonstration flow
A short end-to-end demonstration can follow this sequence:

Open the TRACE dashboard and select the configured collection point.
Start the Wokwi simulation.
Change the simulated distance to the waste surface.
Show the calculated distance and fill percentage in the serial monitor.
Cross the 84% threshold and show COLLECTION_REQUIRED and the red LED.
Show the telemetry message arriving over MQTT and being processed by the backend.
Show the corresponding reading/status change on the frontend.
Explain that the collection alert is an operational prompt, while actual collection and downstream treatment must be recorded as separate custody events.
Limitations and next steps
The following should be confirmed or completed before describing the project as production-ready:

Document the actual MQTT topic names, message schema, and broker configuration.
Document backend routes, persistence, startup scripts, and health checks.
Confirm that the firmware point ID maps to the correct frontend/backend point.
Decide how the device threshold (84%) relates to the frontend's configurable warning/critical thresholds.
Test reconnect behaviour, duplicate messages, stale readings, and malformed payloads.
Add appropriate authentication and transport security for any non-local deployment.
Calibrate the fill calculation against the intended physical bin geometry.
Test with a physical sensor before claiming real-world hardware validation.
Keep sensor alerts separate from custody events; do not automatically mark waste as collected or treated because a bin is full.
Review privacy, auditability, and local waste-management requirements before any operational deployment.
Technology
The earlier uploaded frontend snapshot uses React, TypeScript, Vite, React Router, and Zustand. The reported device-data path uses MQTT between the ESP32 simulation and backend. Verify the latest repository manifests before treating this list as a complete inventory of the current stack.

Project purpose
TRACE is intended to make menstrual-waste collection more visible and accountable without tracking individual users. The focus is on collection-point status, batch custody records, quantity reconciliation, and clear indication of missing or inconsistent records.

Status: Prototype / hackathon project. The project team reports that the Wokwi-to-MQTT-to-backend-to-frontend flow has been run and verified end to end, including fill-level changes and the 84% collection alert. This is a successful simulated integration test, not a claim of physical-device or production deployment validation.

⋮⋮⋮⋮
