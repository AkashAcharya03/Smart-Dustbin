#define BLYNK_TEMPLATE_ID "TMPL3v8e-bREA"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "BbZeQCjgiwsh4BvxDivahfIlyiYVOjez"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int redLED = 25;
int greenLED = 26;

int trigPin = 5;
int echoPin = 18;
int duration;
int distance;

BlynkTimer timer;

// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Ssup";
char pass[] = "98787898";

void ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  Blynk.virtualWrite(V7, distance);
  if (distance > 5) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

  } else {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    Blynk.logEvent("Dustbin Full", "Dustbin is full");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, ultrasonic);
}
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}