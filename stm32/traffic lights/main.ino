#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int LED_green = PB0;
const int LED_yellow = PB10;
const int LED_red = PB11;
const int BTN_mode = PB3;
const int BTN_switch = PB8;

char txt[64];
const char *modet, *colort;
int isAuto = 0;
int state = 0;
int leds[3] = {LED_green, LED_yellow, LED_red};
TwoWire w(PB7, PB6);

// initialize oled
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &w);

void OLED_display(const char* txt) // lazy
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(txt);
  display.display();
}

void updateScreen()
{
  switch(state)
  {
    case 0: colort="GREEN"; break;
    case 1: colort="YELLOW"; break;
    case 2: colort="RED"; break;
  }
  sprintf(txt, "state code: %d\n\nMODE  | %s\n\nCOLOR | %s", state, modet, colort);
  OLED_display(txt);
}

void setup()
{
  // pin mode
  pinMode(LED_green, OUTPUT);
  pinMode(LED_yellow, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(BTN_mode, INPUT_PULLUP);
  pinMode(BTN_switch, INPUT_PULLUP);

  // default statement: green on (isAuto==0)
  digitalWrite(LED_green, HIGH);
  digitalWrite(LED_yellow, HIGH);
  digitalWrite(LED_red, HIGH);

  w.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(1000);
  digitalWrite(LED_yellow, LOW);
  digitalWrite(LED_red, LOW);
}

void loop()
{
  if(digitalRead(BTN_switch)==LOW && !isAuto) // cond: manual
  {
    digitalWrite(leds[state], LOW);
    state += 1;
    state %= 3;
    digitalWrite(leds[state], HIGH);
    updateScreen();
    delay(100);
  }

  if(digitalRead(BTN_mode)==LOW)
  {
    isAuto = !isAuto;
    delay(100);
    while(digitalRead(BTN_mode)==LOW);
  }

  if(!isAuto)
  {
    modet = "MANUAL";
    updateScreen();
    return;
  }

  digitalWrite(leds[state], LOW);
  modet = "AUTO";
  state += 1;
  state %= 3;
  digitalWrite(leds[state], HIGH);
  updateScreen();
  delay(500);
}