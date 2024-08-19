#define pinLed_G 6
#define pinLed_Y 9
#define pinLed_B 10
#define pinLed_R 11

#define pinBtn_G 2
#define pinBtn_Y 3
#define pinBtn_B 4
#define pinBtn_R 12

#define Speaker 8

#define NUM_OF_LEDS 4
int Leds[NUM_OF_LEDS] = { pinLed_G, pinLed_Y, pinLed_B, pinLed_R };
int Btns[NUM_OF_LEDS] = { pinBtn_G, pinBtn_Y, pinBtn_B, pinBtn_R };
bool isLedON[NUM_OF_LEDS];
bool isBtnPressed[NUM_OF_LEDS] = { false, false, false, false };
int lastStateBtn[NUM_OF_LEDS] = { HIGH, HIGH, HIGH, HIGH };
int cnt = 0;

int rnd;
unsigned long start1Press;
unsigned long endPress;
unsigned long lastPress;

void setup() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Leds[k], OUTPUT);
  }
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Btns[k], INPUT_PULLUP);
  }
  randomSeed(analogRead(A0));
  pinMode(Speaker, OUTPUT);
  lastPress = millis();
  LedOff();
  playGame();
}

void loop() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if ((digitalRead(Btns[k]) == LOW) && (lastStateBtn[k] == HIGH) && (millis() - lastPress > 50)) {
      lastStateBtn[k] = LOW;
      lastPress = millis();

      if (!isLedON[k]) {
        gameOver();
        return;
      }

      if (!isBtnPressed[k]) {
        if (cnt == 0) {
          start1Press = millis();
        }
        cnt++;
        isBtnPressed[k] = true;
      }

    } else if (digitalRead(Btns[k]) == HIGH && lastStateBtn[k] == LOW) {
      lastStateBtn[k] = HIGH;

      if (cnt == 3) {
        endPress = millis();
        if (endPress - start1Press < 1000) {
          youWin();
        } else {
          gameOver();
        }
      }
    }
  }
}

void youWin() {
  LedBlink(0);
  bip(800);
  delay(1000);
  playGame();
}

void gameOver() {
  LedBlink(3);
  bip(200);
  delay(1000);
  playGame();
}

void playGame() {
  cnt = 0;
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    isLedON[k] = false;
    isBtnPressed[k] = false;
    lastStateBtn[k] = HIGH;
  }
  rndLeds();
  ledsBlink();
  delay(500);
  bip(600);
}

void rndLeds() {
  for (int i = 0; i < 3; i++) {
    rnd = random(0, 4);
    while (isLedON[rnd]) {
      rnd = random(0, 4);
    }
    isLedON[rnd] = true;
  }
}

void ledsBlink() {
  for (int i = 0; i < NUM_OF_LEDS; i++) {
    if (isLedON[i]) {
      LedOn(i);
    }
  }
  delay(1000);
  LedOff();
}

void LedOn(int chnl) {
  digitalWrite(Leds[chnl], HIGH);
}

void LedBlink(int chnl) {
  digitalWrite(Leds[chnl], HIGH);
  delay(1000);
  digitalWrite(Leds[chnl], LOW);
}

void LedOff() {
  for (int i = 0; i < NUM_OF_LEDS; i++) {
    digitalWrite(Leds[i], LOW);
  }
}

void bip(int val) {
  tone(Speaker, val);
  delay(500);
  noTone(Speaker);
}
