#include <WiFi.h>
#include <PubSubClient.h>

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int LED_PIN = 2;

const float BIN_HEIGHT_CM = 40.0;
const float ALERT_THRESHOLD = 84.0;

const char* WIFI_SSID  = "Wokwi-GUEST";
const char* WIFI_PASS  = "";
const char* MQTT_HOST  = "broker.hivemq.com";
const int   MQTT_PORT  = 1883;
const char* MQTT_TOPIC = "reflow-trace/sachin0317-demo/bin/BLOCK-D-04";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "reflow-esp32-" + String(random(0xffff), HEX);
    if (mqtt.connect(clientId.c_str())) {
      Serial.println(" connected");
    } else {
      Serial.print(" failed, rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.println("TRACE | Bin monitoring started");

  connectWiFi();
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    Serial.println("SENSOR_ERROR: No echo received");
    delay(2000);
    return;
  }

  float distance = duration * 0.0343 / 2.0;
  float fill = (BIN_HEIGHT_CM - distance) / BIN_HEIGHT_CM * 100.0;
  fill = constrain(fill, 0.0, 100.0);
  bool alert = fill >= ALERT_THRESHOLD;

  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  Serial.print("Point: BLOCK-D-04");
  Serial.print(" | Distance: ");
  Serial.print(distance, 1);
  Serial.print(" cm | Fill: ");
  Serial.print(fill, 1);
  Serial.print("% | Status: ");
  Serial.println(alert ? "COLLECTION_REQUIRED" : "NORMAL");

  char payload[200];
  snprintf(payload, sizeof(payload),
    "{\"point\":\"BLOCK-D-04\",\"distance\":%.1f,\"fill\":%.1f,\"status\":\"%s\",\"alert\":%s,\"uptimeMs\":%lu}",
    distance, fill,
    alert ? "COLLECTION_REQUIRED" : "NORMAL",
    alert ? "true" : "false",
    millis());

  bool ok = mqtt.publish(MQTT_TOPIC, payload);
  Serial.println(ok ? "MQTT publish OK" : "MQTT publish FAILED");

  delay(2000);
}
