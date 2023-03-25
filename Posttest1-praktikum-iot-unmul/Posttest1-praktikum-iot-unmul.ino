#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

#define LED_PIN D0
#define BUZZER_PIN D2

#define INCREASE_LED_BUTTON D5
#define DECREASE_LED_BUTTON D6
#define RESET_LED_BUTTON D7

#define INCREASE_BUZZER_BUTTON D1
#define DECREASE_BUZZER_BUTTON D4
#define RESET_BUZZER_BUTTON D3

const char* ssid = "Universitas Mulawarman";
const char* password = "";

int ledBrightness = 0;
int buzzerLoudness = 100;

ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); // LED
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer

  pinMode(INCREASE_LED_BUTTON, INPUT_PULLUP); // Penambah LED
  pinMode(DECREASE_LED_BUTTON, INPUT_PULLUP); // Pengurang LED
  pinMode(RESET_LED_BUTTON, INPUT_PULLUP); // Reset LED

  pinMode(INCREASE_BUZZER_BUTTON, INPUT_PULLUP); // Penambah buzzer
  pinMode(DECREASE_BUZZER_BUTTON, INPUT_PULLUP); // Pengurang buzzer
  pinMode(RESET_BUZZER_BUTTON, INPUT_PULLUP); // Reset buzzer

  // Conn to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");

  // Show local ip add
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin(); // Memulai web server
}

void loop() {
// dia kebalik, kalau dia ditekan valuenya 0, sebaliknya kalau gak ditekan valuenya 1

  server.handleClient(); // Menangani permintaan dari klien

  // put your main code here, to run repeatedly:
  int increaseLedButtonState = digitalRead(INCREASE_LED_BUTTON);
  int decreaseLedButtonState = digitalRead(DECREASE_LED_BUTTON);
  int resetLedButtonState = digitalRead(RESET_LED_BUTTON);

  int increaseBuzzerButtonState = digitalRead(INCREASE_BUZZER_BUTTON);
  int decreaseBuzzerButtonState = digitalRead(DECREASE_BUZZER_BUTTON);
  int resetBuzzerButtonState = digitalRead(RESET_BUZZER_BUTTON);

  if (!increaseLedButtonState) {
    Serial.println("increase LED");
    increaseLed();
  } else if (!decreaseLedButtonState) {
    Serial.println("decrease LED");
    decreaseLed();
  } else if (!resetLedButtonState) {
    Serial.println("reset LED");
    resetLed();
  }

  if (!increaseBuzzerButtonState) {
    Serial.println("increase Buzzer");
    increaseBuzzer();
  } else if (!decreaseBuzzerButtonState) {
    Serial.println("decrease Buzzer");
    decreaseBuzzer();
  } else if (!resetBuzzerButtonState) {
    Serial.println("reset Buzzer");
    resetBuzzer();
  }

  delay(500);
  analogWrite(LED_PIN, ledBrightness);
  analogWrite(BUZZER_PIN, buzzerLoudness);
}

void handleRoot() {
  server.send(200, "text/html", "<html><body><h2>LED Brightness and Buzzer Loudness Value Monitoring</h2><h3>Led Brightness: " + String(ledBrightness) + "</h3><h3>Buzzer Loudness: " + String(buzzerLoudness) + "</h3></body></html>"); // Menampilkan halaman utama
}

void increaseLed() {
  if (ledBrightness < 250) {
    ledBrightness += 5;
  }
}

void increaseBuzzer() {
  if (buzzerLoudness < 2500) {
    buzzerLoudness += 5;
  }
}

void decreaseLed() {
  if (ledBrightness > 0) {
    ledBrightness -= 5;
  }
}

void decreaseBuzzer() {
  if (buzzerLoudness > 100) {
    buzzerLoudness -= 5;
  }
}

void resetLed() {
  ledBrightness = 0;
}

void resetBuzzer() {
  buzzerLoudness = 100;
}