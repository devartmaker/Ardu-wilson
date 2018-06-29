Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, 9, NEO_RGB + NEO_KHZ800);
int eyeTimerId = -1;
int tgBrightness, brightness;
bool blink = false;

void initEyes() {
  pixels.begin();
  pixels.setBrightness(50);
  closeEyes();

  eyeTimerId = eyeTimer.setInterval(10, changeEyes);
  eyeTimer.setInterval(250, blinkControl);
}

void openEyes() {
  tgBrightness = 50;
  pixels.setPixelColor(0, 255, 255, 255);
  pixels.setPixelColor(1, 255, 255, 255);
  pixels.show();
}

void closeEyes() {
  tgBrightness = 0;

  pixels.clear();
  pixels.show();
}

void blinkControl() {
  if (random(10) < 1) {
    blink = true;

    int duration = random(50, 100);
    eyeTimer.setTimeout(duration, resetBlink);
  }
}

void resetBlink() {
  blink = false;
}

void changeEyes() {
  if (tgBrightness < brightness) {
    brightness--;
  } else if (tgBrightness > brightness) {
    brightness++;
  }

  /*
  Serial.print(brightness);
  Serial.print("/");
  Serial.println(blink);
  */
  
  if (blink) {
    pixels.setBrightness(0);
  } else {
    pixels.setBrightness(brightness);
  }

  pixels.setPixelColor(0, 255, 255, 255);
  pixels.setPixelColor(1, 255, 255, 255);
  pixels.show();
}

