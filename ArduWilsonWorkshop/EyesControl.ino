Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, 9, NEO_RGB + NEO_KHZ800);

int eyeTimerId = -1;
int tgBrightness, brightness;
bool blink = false;
uint32_t eyeColor = pixels.Color(255, 228, 200);

void initEyes() {
  pixels.begin();
  pixels.setBrightness(50);
  closeEyes();

  eyeTimerId = eyeTimer.setInterval(10, changeEyes);
  eyeTimer.setInterval(250, blinkControl);
}

void openEyes() {
  tgBrightness = 50;
  pixels.setPixelColor(0, eyeColor);
  pixels.setPixelColor(1, eyeColor);
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
  
  if (blink) {
    pixels.setBrightness(0);
  } else {
    pixels.setBrightness(brightness);
  }

  pixels.setPixelColor(0, eyeColor);
  pixels.setPixelColor(1, eyeColor);
  pixels.show();
}
