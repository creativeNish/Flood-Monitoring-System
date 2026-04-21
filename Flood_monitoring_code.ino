#define BLYNK_TEMPLATE_ID "TMPL3wuMzre4X"
#define BLYNK_TEMPLATE_NAME "flood_alert"
#define BLYNK_AUTH_TOKEN "mcOy_1Clz1PLet1RR3mqwoTev_FtFvDd"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ultrasonic + Output Pins
#define TRIG D5
#define ECHO D6
#define LED D0
#define BUZZER D7

// OLED I2C Pins
#define OLED_SDA D2
#define OLED_SCL D1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WiFi Credentials
char ssid[] = "iPhone";
char pass[] = "22222222";

// Danger Distance
const int dangerDistance = 6;  // cm

unsigned long lastAlertTime = 0;
const long alertCooldown = 10000; // 10 sec

BlynkTimer timer;

// ================= DISTANCE FUNCTION =================

long getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ================= SEND TO BLYNK =================

void sendToBlynk(long distance) {

  Blynk.virtualWrite(V0, distance);

  if (distance <= dangerDistance) {

    if (millis() - lastAlertTime > alertCooldown) {

      Blynk.logEvent("flood_alert",
                     "⚠️ Water Level HIGH!");

      lastAlertTime = millis();
    }
  }
}

// ================= MAIN SENSOR TASK =================

void loopTask() {

  long sum = 0;
  int validReadings = 0;

  // Reduced readings for stability
  for (int i = 0; i < 10; i++) {

    long d = getDistance();

    if (d > 0 && d < 400) {

      sum += d;
      validReadings++;
    }

    delay(20);
  }

  long meanDistance =
    (validReadings > 0) ?
    (sum / validReadings) : -1;

  Serial.print("Distance: ");
  Serial.println(meanDistance);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  if (meanDistance == -1) {

    display.print("ERROR");
    display.setCursor(0, 30);
    display.print("Sensor");

    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

  }

  else {

    display.print(meanDistance);
    display.print(" cm");

    display.setCursor(0, 30);

    if (meanDistance <= dangerDistance) {

      display.print("DANGER");

      digitalWrite(LED, HIGH);
      digitalWrite(BUZZER, HIGH);

    }

    else {

      display.print("SAFE");

      digitalWrite(LED, LOW);
      digitalWrite(BUZZER, LOW);

    }

    sendToBlynk(meanDistance);
  }

  display.display();
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(TRIG, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED not found");

    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  // Connect Blynk
  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  // Run every 2 seconds
  timer.setInterval(
    2000L,
    loopTask
  );
}

// ================= LOOP =================

void loop() {

  Blynk.run();
  timer.run();
}