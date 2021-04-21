#include "pitches.h"

const int buzzer = A2;

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  jinglebell();
  delay(2000);
}

void jinglebell() {
  static const int melody[][93] = {
    {
      NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_D5,
      NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5,
      NOTE_E5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_FS5,
      NOTE_D6, NOTE_D6, NOTE_C6, NOTE_A5, NOTE_B5, NOTE_G5,
      NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_D5,
      NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5,
      NOTE_E5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_D6, NOTE_D6, NOTE_D6, 
      NOTE_D6, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_A5, NOTE_G5,

      NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, 
      NOTE_B5, NOTE_D6, NOTE_G5, NOTE_A5, NOTE_B5,
      NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_B5, NOTE_B5, NOTE_B5, 
      NOTE_B5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_D6,
      NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, 
      NOTE_B5, NOTE_D6, NOTE_G5, NOTE_A5, NOTE_B5,
      NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_B5, NOTE_B5, NOTE_B5, 
      NOTE_D6, NOTE_D6, NOTE_C6, NOTE_A5, NOTE_G5
    },
    {
      NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4,
      NOTE_B4, NOTE_D5, NOTE_D5, NOTE_D4, NOTE_C4,
      NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5,
      NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_G5, NOTE_G5,
      NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4,
      NOTE_B4, NOTE_D5, NOTE_D5, NOTE_D4, NOTE_C4,
      NOTE_C5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
      NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_D5,

      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
      NOTE_G5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5,
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
      NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_D5
    }
  };


  uint8_t noteDurations[] = {
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 8, 8, 8, 8, 
    8, 8, 8, 8, 2,
    8, 8, 4, 8, 8, 4, 
    8, 8, 6, 16, 2,
    8, 8, 6, 16, 8, 8, 8, 8, 
    8, 8, 8, 8, 4, 4,
    8, 8, 4, 8, 8, 4, 
    8, 8, 6, 16, 2,
    8, 8, 6, 16, 8, 8, 8, 
    8, 8, 8, 8, 8, 2
  };

  int count = sizeof(noteDurations);

  for (int thisNote = 0; thisNote < count; thisNote++) {
    int noteDuration = 1500 / noteDurations[thisNote];
    int chordCount = noteDuration / 10;
    noteDuration = 10;

    noteDuration += random(2);
    int ran = -30 + random(60);
    int pauseBetweenNotes = noteDuration;
    pauseBetweenNotes += random(2);
    pauseBetweenNotes *= 1.10;
   
    for (int j = 0; j < chordCount; j++) {
      tone(buzzer, melody[j % 2][thisNote] + ran, noteDuration);
      delay(pauseBetweenNotes);
    }
    noTone(buzzer);
  }
}
