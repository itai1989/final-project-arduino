#define pinLed_G 6
#define pinLed_Y 9
#define pinLed_B 10
#define pinLed_R 11

#define pinBtn_G 1
#define pinBtn_Y 2
#define pinBtn_B 3
#define pinBtn_R 4

#define Speaker 8

#define NUM_OF_LEDS 4
int Leds[NUM_OF_LEDS] = { pinLed_G, pinLed_Y, pinLed_B, pinLed_R };
int Btns[NUM_OF_LEDS] = { pinBtn_G, pinBtn_Y, pinBtn_B, pinBtn_R };
int isLedON[NUM_OF_LEDS];
int lastStateBtn[NUM_OF_LEDS] = { HIGH, HIGH, HIGH, HIGH };

int rnd;
unsigned long lastPress;

void setup() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Leds[k], OUTPUT);
  }
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Btns[k], INPUT_PULLUP);
  }
  randomSeed(analogRead(A1));
  pinMode(Speaker, OUTPUT);
  lastPress = millis();
  playGame();
}

void loop() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    if ((digitalRead(bts[k]) == LOW) && (lastStateBtn[k] == HIGH) && (millis() - lastPress > 50)) {
      lastStateBtn[k] = LOW;
      if (!isLedON[k]) {
        gameOver();
      }
    } else if ((digitalRead(bts[k]) == HIGH)) {
      lastStateBtn[k] = HIGH;
    }
  }
}
void gameOver() {
  LedBlink(3);
  bip(100);
  playGame();
}
void playGame() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    isLedON[k] = false;
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
      LedBlink(i);
    }
  }
}
void LedBlink(int chnl) {
  digitalWrite(Leds[chnl], HIGH);
  delay(1000);
}
void bip(int val) {
  tone(Speaker, val);
  delay(500);
  tone(Speaker, 0);
}
