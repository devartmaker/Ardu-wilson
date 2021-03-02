#include "Adafruit_NeoPixel.h"
#include "pitches.h"
#include "SimpleTimer.h"
#include "EEPROM.h"

const int statusLED = 13;
const int neopixel = 9;
const int mic = A1;
const int buzzer = A2;

////////////////////////////////////////////////////////
const int toneRange[] = {500, 5000}; // 저음, 고음
int soundThreshold = 2; // 사운드 센서 민감도
int sleepDuration = 30000; // 대화가 없을 때 잠자기까지의 시간
int waitCount = 10; // 듣고 나서 말하기까지 기다리는 시간
////////////////////////////////////////////////////////

int silentValue;
float soundValue = 0.0f;
int listeningCount = 0, finishCount = 0;
bool listening = false;
bool isRunning = false;
bool talking = false;
int checkSoundTimerId = -1;
int sleepTimerId = -1;

void say(int type);
void sing();

SimpleTimer timer, eyeTimer;

boolean playedMusic = true;

void setup() {
  Serial.begin(9600);
  pinMode(statusLED, OUTPUT);

  initEyes();

  initSound();
  timer.setInterval(2, checkTouching);
  timer.setInterval(25, checkSound);
}

void loop() {
  timer.run();
  eyeTimer.run();
}

void initSound() {
  long micValue = 0;

  int checkCount = 20;
  for (int i = 0; i < checkCount; i++) {
    int v = analogRead(mic);
    micValue += v;
    digitalWrite(statusLED, !digitalRead(statusLED));
    delay(50);
  }

  silentValue = micValue / checkCount;
  Serial.print("silentValue = ");
  Serial.println(silentValue);
}

void checkTouching() {
  if (isRunning) return;

  int t = analogRead(buzzer);
  // Serial.println(t);

  if (t > 70) {
    isRunning = true;

    if (EEPROM.read(0) != 0) {
      delay(1000);
      sing();
      EEPROM.write(0, 0);
    } else {
      startSleepTimer();
    }

    openEyes();
  }
}

void checkSound() {
  if (talking || !isRunning) return;

  int micValue = analogRead(mic);
  int v = abs(silentValue - micValue);
  soundValue += (v - soundValue) * 0.02f;
  
  /*
  Serial.print(micValue);
  Serial.print(',');
  Serial.println(v);
  */
  
  if (soundValue > soundThreshold) {
    listeningCount++;
    digitalWrite(statusLED, HIGH);

    finishCount = 0;
    deleteSleepTimer();
  } else {
    digitalWrite(statusLED, LOW);

    finishCount++;
    if (finishCount == waitCount) {
      if (listeningCount > 5) {
        Serial.println("[SAY]");
        sayRandom();
      }

      startSleepTimer();
    }
  }
}

void startSleepTimer() {
  deleteSleepTimer();
  sleepTimerId = timer.setTimeout(sleepDuration, goToSleep);
}

void deleteSleepTimer() {
  if (sleepTimerId != -1) {
    timer.deleteTimer(sleepTimerId);
    sleepTimerId = -1;
  }
}

void finishTalk() {
  listeningCount = 0;
  talking = false;
}

void goToSleep() {
  playedMusic = false;
  isRunning = false;
  closeEyes();
  pinMode(buzzer, INPUT);
}

void serialEvent() {
  char c = Serial.read();
  if (c == '1') {
    say(0);
  } else if (c == '2') {
    say(1);
  } else if (c == '3') {
    say(2);
  } else if (c == '4') {
    say(3);
  }
}
