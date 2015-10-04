#include <TVout.h>
#include <fontALL.h>
TVout TV;

// Music note frequencies //
#define  NOTE_c 261
#define  NOTE_d 294 
#define  NOTE_e 329 
#define  NOTE_f 349 
#define  NOTE_g 392
#define  NOTE_a 440 
#define  NOTE_b 493 
#define  NOTE_C 523

// Hardware defines //
#if defined(__AVR_ATmega168__)
  #define SCREEN_WIDTH 80
  #define SCREEN_HEIGHT 72
#else 
  #define SCREEN_WIDTH 112
  #define SCREEN_HEIGHT 112
#endif 

// potentiometer game paddle input (analog A2)
#define POTPIN 2 
// game controller pusbbutton (digital D2)
#define BTNPIN 2

// Note plays this long and wait this long between loop iterations
#define SLEEP_TIME 100

// SPRITE BITMAPS //
// (note!: resides in program memory)
PROGMEM const unsigned char HEART_SPRITE[] = {
7,6, 0x7C,0xFE,0xFE,0x7C,0x38,0x10};

int notes[] = {NOTE_c,NOTE_d,NOTE_e,NOTE_f,NOTE_g,NOTE_a,NOTE_b,NOTE_C};
int noteidx = 0;

// GAME STATE //
float potVal = 0;  // paddle (potentiometer) position
boolean buttonPressed = 0; 

void setup() {
  TV.begin(_PAL, SCREEN_WIDTH, SCREEN_HEIGHT);
  TV.clear_screen();
  TV.select_font(font6x8);
  //Serial.begin(9600); // Uncomment for debug

  // Use internal pull-up resistor for the button
  pinMode(BTNPIN, INPUT_PULLUP);
}

void loop() {
  
  // Read paddle pos
  potVal = analogRead(POTPIN)/1024.0;
  boolean buttonPressed = (digitalRead(BTNPIN) == LOW);

  // Play the notes
  TV.tone(notes[noteidx], SLEEP_TIME);
  noteidx++;
  if (noteidx>7)
    noteidx = 0;
  
  // Wait for vblank to avoid flicker
  TV.delay_frame(1);
  TV.clear_screen();

  TV.print(SCREEN_WIDTH/2,0, potVal);
  
  // Take bitmap width into account to avoid overdraw
  TV.bitmap((int)(potVal*(SCREEN_WIDTH-7)), SCREEN_HEIGHT/2, HEART_SPRITE);

  if (buttonPressed)
    TV.invert();

  TV.delay(SLEEP_TIME);
}
