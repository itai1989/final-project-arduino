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
int score = 0;

int rnd;
unsigned long lastPress;
unsigned long start1Press;
unsigned long endPress;
bool isPress1 = false;
bool gameActive = true;

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
  if (gameActive) {
    for (int k = 0; k < NUM_OF_LEDS; k++) {
      if ((digitalRead(Btns[k]) == LOW) && (lastStateBtn[k] == HIGH) && (millis() - lastPress > 50)) {
        lastStateBtn[k] = LOW;
        if (!isPress1) {
          start1Press = millis();
          isPress1 = true;
        }
        if (!isLedON[k]) {
          gameOver();
          return;
        } else {
          score++;
        }
      } else if ((digitalRead(Btns[k]) == HIGH) && (lastStateBtn[k] == LOW)) {
        lastStateBtn[k] = HIGH;
        if (score >= 3) {
          endPress = millis();
          checkWinCondition();
          return;
        }
      }
    }
  }
}

void checkWinCondition() {
  gameActive = false;
  if (endPress - start1Press < 5000) {  // פחות משנייה
    youWin();
  } else {
    gameOver();
  }
}

void youWin() {
  LedBlink(0);  // הבהוב הנורה הירוקה
  bip(800);
  delay(1000);  // זמן לתצוגה
  playGame();
}

void gameOver() {
  LedBlink(3);  // הבהוב הנורה האדומה
  bip(200);
  delay(1000);  // זמן לתצוגה
  playGame();
}

void playGame() {
  score = 0;
  isPress1 = false;
  gameActive = true;
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    isLedON[k] = false;
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
  tone(Speaker, 0);
}
