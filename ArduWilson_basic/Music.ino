void hapyBirthday() {
  int melody[] = {
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_B3,
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_C4,
    NOTE_G3, NOTE_G3, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_B3, NOTE_B3, NOTE_A3,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_C4
  };

  uint8_t noteDurations[] = {
    4, 8, 2, 2, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 4, 8, 1,
    4, 8, 2, 2, 4, 8, 1
  };

  int count = sizeof(noteDurations);
 
  for (int thisNote = 0; thisNote < count; thisNote++) {
    int noteDuration = 500 / noteDurations[thisNote];
    noteDuration += random(100);
    int ran = -50 + random(100);
    tone(buzzer, melody[thisNote] + ran, noteDuration);

    int pauseBetweenNotes = noteDuration;
    pauseBetweenNotes += random(100);
    pauseBetweenNotes *= 1.10;
    delay(pauseBetweenNotes);
    noTone(buzzer);
  }
}

