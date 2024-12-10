#include <Adafruit_NeoPixel.h>

#define LED_PIN 6     // Pin connected to the data line of the LED strip
#define LED_COUNT 500  // Total number of LEDs in the strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(128); // 50% brightness
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Run the police beacon effect on LEDs 0–10
  policeBeacon(0, 11, strip.Color(255, 0, 0), strip.Color(0, 0, 255)); // Red and Blue

  // Run the revolving effect on LEDs 11–30
  smoothScroll(22, 83); // Start from LED 11 (index 10) for 20 LEDs

  // Run the fading effect from blue to purple on LEDs 84 and beyond
  fadeBlueToPurpleEffect(105, LED_COUNT);

  // Update the strip to display both effects
  strip.show();

  delay(5); // Adjust delay to control effect speed
}

// Function for police beacon effect
void policeBeacon(int start, int groupSize, uint32_t color1, uint32_t color2) {
  static bool toggle = false; // Alternates between red and blue

  // First group of LEDs
  for (int i = start; i < start + groupSize; i++) {
    strip.setPixelColor(i, toggle ? color1 : color2);
  }

  // Second group of LEDs
  for (int i = start + groupSize; i < start + (2 * groupSize); i++) {
    strip.setPixelColor(i, toggle ? color2 : color1);
  }

  // Flip toggle for the next cycle
  toggle = !toggle;

  delay(100); // Adjust speed of flashing
}

// Function for smooth scrolling effect
void smoothScroll(int start, int count) {
  static int offset = 0; // Tracks the rotation position

  // Define segment size for Red, Green, and White
  int segmentSize = count / 3;

  // Set Green segment
  for (int i = 0; i < segmentSize; i++) {
    int index = (start + i + offset + segmentSize) % count + start;
    strip.setPixelColor(index, strip.Color(0, 255, 0)); // Green
  }

  // Set Red segment
  for (int i = 0; i < segmentSize; i++) {
    int index = (start + i + offset) % count + start;
    strip.setPixelColor(index, strip.Color(255, 0, 0)); // Red
  }

  // Set White segment
  for (int i = 0; i < segmentSize; i++) {
    int index = (start + i + offset + 2 * segmentSize) % count + start;
    strip.setPixelColor(index, strip.Color(255, 255, 255)); // White
  }

  // Increment offset for the next rotation
  offset = (offset + 3) % count;
}

// Function for fading from blue to purple effect on LEDs from 'start' to 'end'
void fadeBlueToPurpleEffect(int start, int end) {
  static int fadeValue = 0; // Used to control the fade effect

  // Fade from blue to purple by increasing red while keeping blue constant
  for (int i = start; i < end; i++) {
    int blue = 255;  // Blue remains constant
    int red = fadeValue;  // Red increases gradually

    strip.setPixelColor(i, red, 0, blue);  // Fade from blue to purple (increasing red)
  }

  // Increase fadeValue faster to speed up the transition
  fadeValue = (fadeValue + 5) % 256; // Increase the fade rate by adjusting the step (5)
}
