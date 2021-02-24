int sayTimer = -1;
int words = 0;
int currentWord = 0;
int charCount = 0;
int charIndex = 0;

void sayRandom() {
  int ran = random(10);
  say(ran);
}

void say(int type = 0) {
  talking = true;
  
  stopSaying();
  openEyes();
  
  switch (type) {
    case 0 : question(); break;
    case 1 : wow(); break;
    case 2 : sad(); break;
    default : sayWords();
  }
}

void sayWords() {
  words = listeningCount / 50;
  int r = random(10);
  if (r < 2) words *= 0.5;
  else if (r < 3) words *= 1.5;
  words = constrain(words, 1, 5);

  currentWord = 0;
  charIndex = -1;
 
  nextWordSound();
}

void nextWordSound() {
  if (charIndex == -1) {
    charCount = random(10, 30);
  }
  
  int ran = random(toneRange[0], toneRange[1]);
  int d = random(10, 40);

  tone(buzzer, ran, d);
  charIndex++;

  if (charIndex >= charCount) {
    currentWord++;
    charIndex = -1;
    d += random(50, 200);
  }

  if (words >= currentWord) {
    sayTimer = timer.setTimeout(d, nextWordSound);
  } else {
    sayTimer = -1;
    noTone(buzzer);
    finishTalk();
  }
}

void question() {
  int start = random(toneRange[0], toneRange[0] + 1000);
  int end = start + random(300, 500);

  start = constrain(start, toneRange[0], toneRange[1]);
  end = constrain(end, toneRange[0], toneRange[1]);
  
  for (int i = start; i < end; i++) {
    tone(buzzer, i);
    delay(1);
  }

  noTone(buzzer);
  finishTalk();
}

void wow() {
  int start = random(toneRange[0], toneRange[0] + 1000);
  int end = start + random(400, 700);

  start = constrain(start, toneRange[0], toneRange[1]);
  end = constrain(end, toneRange[0], toneRange[1]);

  for (int i = start; i < end; i+=2) {
    tone(buzzer, i);
    delay(1);
  }
  for (int i = end; i >= start; i-=3) {
    tone(buzzer, i);
    delay(1);
  }
  
  noTone(buzzer);
  finishTalk();
}

void sad() {
  int start = random(toneRange[1], toneRange[1] - 1000);
  int end = start - random(300, 500);

  start = constrain(start, toneRange[0], toneRange[1]);
  end = constrain(end, toneRange[0], toneRange[1]);
  
  for (int i = start; i < end; i++) {
    tone(buzzer, i);
    delay(2);
  }

  noTone(buzzer);
  finishTalk();
}

void stopSaying() {
  if (sayTimer != -1) {
    timer.deleteTimer(sayTimer);
    sayTimer = -1;
  }
}
