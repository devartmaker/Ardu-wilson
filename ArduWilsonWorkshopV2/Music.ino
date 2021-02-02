int singTimer = -1;
int thisNote = 0;

void sing() {
  thisNote = 0;
  talking = true;
  happyBirthday();
}

void happyBirthday() {
  static int melody[] = {
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_B3,
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_C4,
    NOTE_G3, NOTE_G3, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_B3, NOTE_B3, NOTE_A3,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_C4
  };

  static uint8_t noteDurations[] = {
    4, 8, 2, 2, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 1
  };

  static int count = sizeof(noteDurations);

  noTone(buzzer);
  
  int noteDuration = 500 / noteDurations[thisNote];
  noteDuration += random(100);
  int ran = -50 + random(100);
  tone(buzzer, melody[thisNote] + ran, noteDuration);

  int pauseBetweenNotes = noteDuration;
  pauseBetweenNotes += random(100);
  pauseBetweenNotes *= 1.10;

  if (thisNote < count - 1) {
    thisNote++;
    singTimer = timer.setTimeout(pauseBetweenNotes, happyBirthday);
  } else {
    thisNote = 0;
    talking = false;
  }
}
