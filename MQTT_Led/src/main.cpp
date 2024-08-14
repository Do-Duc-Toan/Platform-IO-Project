#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Define the Pin
#define internal_led 2
// Change this to point to your Wifi Credentials
const char *ssid = "iPhone of Toan";
const char *password = "abc1234567";
// Your MQTT broker ID
const char *mqttBroker = "172.20.10.2";
const int mqttPort = 1883;
// MQTT topics
const char *publishTopic = "halleffect";
const char *subscribeTopic = "led";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (1000)
char msg[MSG_BUFFER_SIZE];
uint8_t obstacle = 1;
uint8_t location = 1;
uint8_t battery_capacity = 70;
// Connect to Wifi
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback function whenever an MQTT message is received
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++)
  {
    Serial.print(message += (char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if 'ON' was received
   if (message == "TURN LEFT")
  {
    Serial.println("The AGV will turn left at the next node");
    digitalWrite(internal_led, HIGH);
  }
  else if (message == "TURN RIGHT")
  {
    Serial.println("The AGV will turn right at the next node");
    digitalWrite(internal_led, LOW);
  }
  else if (message == "GO STRAIGHT") 
  {
    Serial.println("The AGV will go straight ahead at the next node");
    digitalWrite(internal_led, HIGH);
  }
  else if (message == "STOP") 
  {
    Serial.println("The AGV will stop at the next position");
    digitalWrite(internal_led, LOW);
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Subscribe to topic
      client.subscribe(subscribeTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(internal_led, OUTPUT);
  // Setup the wifi
  setup_wifi();
  // setup the mqtt server and callback
  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback);
}
void loop()
{
  // Listen for mqtt message and reconnect if disconnected
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // publish message after certain time.
  unsigned long now = millis();
  if (now - lastMsg > 10000)
  {
    lastMsg = now;
    // Read the Hall Effect sensor value
    int hallEffectValue = hallRead();

    sprintf(msg, "velocity: %d - location: %d - obstacle: %d - battery_capacity: %d", hallEffectValue, location, obstacle, battery_capacity);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(publishTopic, msg);
    location++;
    obstacle = 0;
  }
}