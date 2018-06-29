void sayRandom() {
  int ran = random(10);
  say(ran);
}

void say(int type = 0) {
  stopSoundCheck();

  switch (type) {
    case QUESTION : question(); break;
    case WOW : wow(); break;
    case SAD : sad(); break;
    case WORDS : sayWords();
    default : sayWords();
  }

  noTone(buzzer);
  startSoundCheck();
}

void sayWords() {
  int words = maxCount / 10;
  if (random(10) < 3) words *= 0.5;
  words = constrain(words, 1, 5);

  for (int i = 0; i < words; i++) {
    int len = random(10, 30);
    for (int j = 0; j < len; j++) {
      int ran = random(toneGroup[0], toneGroup[1]);
      int d = random(10, 30);

      tone(buzzer, ran, d);
      delay(d);
    }
    delay(random(50, 200));
  }
}

void question() {
  int start = random(toneGroup[0], toneGroup[0] + 1000);
  int end = start + random(300, 500);

  start = constrain(start, toneGroup[0], toneGroup[1]);
  end = constrain(end, toneGroup[0], toneGroup[1]);
  
  for (int i = start; i < end; i++) {
    tone(buzzer, i);
    delay(1);
  }
}

void wow() {
  int start = random(toneGroup[0], toneGroup[0] + 1000);
  int end = start + random(400, 700);

  start = constrain(start, toneGroup[0], toneGroup[1]);
  end = constrain(end, toneGroup[0], toneGroup[1]);
  
  for (int i = start; i < end; i+=2) {
    tone(buzzer, i);
    delay(1);
  }
  for (int i = end; i >= start; i-=3) {
    tone(buzzer, i);
    delay(1);
  }
  noTone(buzzer);
}

void sad() {
  int start = random(toneGroup[1], toneGroup[1] - 1000);
  int end = start - random(300, 500);

  start = constrain(start, toneGroup[0], toneGroup[1]);
  end = constrain(end, toneGroup[0], toneGroup[1]);
  
  for (int i = start; i < end; i++) {
    tone(buzzer, i);
    delay(2);
  }
}

