#include <Adafruit_NeoPixel.h>
#include "pitches.h"
#include "SimpleTimer.h"

const int mic = A1;
const int buzzer = A2;
const int touch = A3;
const int menu = A6;
const int toneGroup[] = {100, 5000};

int soundThreshold = 15;
int prevSound = -1, dis = 0;
int sayCount = 0, finishCount = 0;
int maxCount = 0;
bool isSaying = false;
bool isRunning = false;
int checkSoundTimerId = -1;
int responseTimerId = -1;
int sleepTimerId = -1;
int menuValue;

void say(int type);
SimpleTimer timer, eyeTimer;

boolean playedMusic = false;

void setup() {
  Serial.begin(9600);
  
  initEyes();
}

void loop() {
  /*
  say(SAD);
  delay(1000);
  say(WOW);
  delay(1000);
  say(QUESTION);
  delay(1000);
  return;
  */
  menuValue = analogRead(menu);
  timer.run();
  eyeTimer.run();
  checkTouching();
}

void checkTouching() {
  if (!isRunning) {
    int t = analogRead(touch);
    if (t > 100) {
      isRunning = true;
      startSoundCheck();
      openEyes();
      if (!playedMusic && menuValue > 1020) {
        playedMusic = true;
        timer.setTimeout(2000, birthdayEvent);
      }
    }
  }
}

void birthdayEvent() {
  hapyBirthday();
  delay(1500);
  wow();
  delay(3000);
}

void startSoundCheck() {
  pinMode(buzzer, INPUT);
  maxCount = 0;
  checkSoundTimerId = timer.setInterval(50, checkSound);
}

void stopSoundCheck() {
  timer.deleteTimer(checkSoundTimerId);
  checkSoundTimerId = -1;
}

void checkSound() {
  int s = analogRead(mic);
  int dis = abs(prevSound - s);
  
  if (dis > soundThreshold) {
    sayCount++;
    maxCount++;
    
    digitalWrite(13, HIGH);
    
    finishCount = 0;
    if (!isSaying && sayCount > 5) {
      isSaying = true;

      // Serial.println("[CANCEL SAY]");
      timer.deleteTimer(responseTimerId);
      responseTimerId = -1;
      
      timer.deleteTimer(sleepTimerId);
      sleepTimerId = -1;
    }
  } else {
    digitalWrite(13, LOW);
    
    finishCount++;
    if (finishCount > 10) {
      finishCount = 0;
      sayCount = 0;
      
      if (isSaying) {
        isSaying = false;
        // Serial.println("[SAY]");
        responseTimerId = timer.setTimeout(1000, sayRandom);
        timer.deleteTimer(sleepTimerId);
        sleepTimerId = timer.setTimeout(10000, goToSleep);
      }
    }
  }
  
  prevSound = s;
}

void goToSleep() {
  playedMusic = false;
  isRunning = false;
  closeEyes();
  stopSoundCheck();
}

