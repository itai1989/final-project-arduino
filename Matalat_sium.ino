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
int isLedON[NUM_OF_LEDS] = { false, false, false, false };
int rnd;

void setup() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Leds[k], OUTPUT);
  }
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    pinMode(Btns[k], INPUT_PULLUP);
  }
  randomSeed(analogRead(A1));
  pinMode(Speaker, OUTPUT);
  playGame();
}

void loop() {

}
void playGame(){
  rndLeds();
  ledsBlink();
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
  for (int i = 0; i < isLedON; i++) {
    if (isLedON[i]) {
      LedBlink(i);
    }
  }
}
void LedBlink(int chnl) {
  digitalWrite(Leds[chnl], HIGH);
  delay(1000);
}
