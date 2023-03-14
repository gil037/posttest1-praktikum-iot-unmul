#define LED_PIN D0
#define BUZZER_PIN D2

#define INCREASE_BUTTON D5
#define DECREASE_BUTTON D6
#define RESET_BUTTON D7

#define INCREASE_BUZZER_BUTTON D1
#define DECREASE_BUZZER_BUTTON D4
#define RESET_BUZZER_BUTTON D3

int ledBrightness = 0;
int buzzerLoudness = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); // LED
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer

  pinMode(INCREASE_BUTTON, INPUT_PULLUP); // Penambah
  pinMode(DECREASE_BUTTON, INPUT_PULLUP); // Pengurang
  pinMode(RESET_BUTTON, INPUT_PULLUP); // Reset

  pinMode(INCREASE_BUZZER_BUTTON, INPUT_PULLUP); // Penambah buzzer
  pinMode(DECREASE_BUZZER_BUTTON, INPUT_PULLUP); // Pengurang buzzer
  pinMode(RESET_BUZZER_BUTTON, INPUT_PULLUP); // Reset buzzer
}

void loop() {
// dia kebalik, kalau dia ditekan valuenya 0, sebaliknya kalau gak ditekan valuenya 1

  // put your main code here, to run repeatedly:
  int increaseButtonState = digitalRead(INCREASE_BUTTON);
  int decreaseButtonState = digitalRead(DECREASE_BUTTON);
  int resetButtonState = digitalRead(RESET_BUTTON);

  int increaseBuzzerButtonState = digitalRead(INCREASE_BUZZER_BUTTON);
  int decreaseBuzzerButtonState = digitalRead(DECREASE_BUZZER_BUTTON);
  int resetBuzzerButtonState = digitalRead(RESET_BUZZER_BUTTON);

  if (!increaseButtonState) {
    Serial.println("increase");
    increase();
  } else if (!decreaseButtonState) {
    Serial.println("decrease");
    decrease();
  } else if (!resetButtonState) {
    Serial.println("reset");
    reset();
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

void increase() {
  if (ledBrightness < 250) {
    ledBrightness += 5;
  }
}

void decrease() {
  if (ledBrightness > 0) {
    ledBrightness -= 5;
  }
}

void reset() {
  ledBrightness = 0;
}

void increaseBuzzer() {
  if (buzzerLoudness < 2500) {
    buzzerLoudness += 5;
  }
}

void decreaseBuzzer() {
  if (buzzerLoudness > 100) {
    buzzerLoudness -= 5;
  }
}

void resetBuzzer() {
  buzzerLoudness = 100;
}