#include<FastLED.h>

#define LED_PIN1   D0
#define LED_PIN2   D5
#define LED_PIN3   D6
#define LED_PIN4   D7
#define LED_PIN5   D8

#define NUM_LEDS  12

CRGB led1s[NUM_LEDS];
CRGB led2s[NUM_LEDS];
CRGB led3s[NUM_LEDS];
CRGB led4s[NUM_LEDS];
CRGB led5s[NUM_LEDS];

//燈號變換時間
unsigned long int time1 = 0;       // 行人綠燈 車行紅燈
unsigned long int time2 = 11;      // 行人閃燈 車行紅燈
unsigned long int time3 = 16;      // 行人紅燈 車行綠燈
unsigned long int time4 = 26;      // 行人紅燈 車行黃燈

//週期循環
int cycletime = 30;

//閃黃燈速度
int delaytime = 250;

void setup(void) {
  Serial.begin(115200);

  FastLED.addLeds<WS2812B, LED_PIN1, RGB>(led1s /*CRGB*/ , NUM_LEDS /*LEDNumber*/ );
  FastLED.addLeds<WS2812B, LED_PIN2, RGB>(led2s /*CRGB*/ , NUM_LEDS /*LEDNumber*/ );
  FastLED.addLeds<WS2812B, LED_PIN3, RGB>(led3s /*CRGB*/ , NUM_LEDS /*LEDNumber*/ );
  FastLED.addLeds<WS2812B, LED_PIN4, RGB>(led4s /*CRGB*/ , NUM_LEDS /*LEDNumber*/ );
  FastLED.addLeds<WS2812B, LED_PIN5, RGB>(led5s /*CRGB*/ , NUM_LEDS /*LEDNumber*/ );

  FastLED.clear();
  //行人紅燈1
  for (int i = 0; i < NUM_LEDS; i++) {
    led1s[i] = CRGB(0, 0, 0);
  }
  //行人綠燈2
  for (int i = 0; i < NUM_LEDS; i++) {
    led2s[i] = CRGB(0, 0, 0);
  }
  //車行人綠燈3
  for (int i = 0; i < NUM_LEDS; i++) {
    led3s[i] = CRGB(0, 0, 0);
  }
  //車行黃燈4
  for (int i = 0; i < NUM_LEDS; i++) {
    led4s[i] = CRGB(0, 0, 0);
  }
  //車行紅燈5
  for (int i = 0; i < NUM_LEDS; i++) {
    led5s[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void loop(void) {
  unsigned long currentMillis = millis() / 1000;
  
  //1行人綠燈車行紅燈
  if (currentMillis >= time1) {
    FastLED.clear();
    //行人綠燈2
    for (int i = 0; i < NUM_LEDS; i++) {
      led2s[i] = CRGB(255, 0, 0);
    }
    //車行紅燈5
    for (int i = 0; i < NUM_LEDS; i++) {
      led5s[i] = CRGB(0, 255, 0);
    }
    FastLED.show();
    time1 = currentMillis + cycletime;
    //Serial.print("TIME1:  ");
    //Serial.println(time1);
  }

  //2行人綠閃燈車行紅燈
  if (currentMillis >= time2) {
    for (int a = 1; a <= (time3 - time2) * 2; a++) {
      FastLED.clear();
      //行人綠燈2
      for (int i = 0; i < NUM_LEDS; i++) {
        led2s[i] = CRGB(0, 0, 0);
      }
      //車行紅燈5
      for (int i = 0; i < NUM_LEDS; i++) {
        led5s[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
      delay(delaytime);
      FastLED.clear();
      //行人綠燈2
      for (int i = 0; i < NUM_LEDS; i++) {
        led2s[i] = CRGB(255, 0, 0);
      }
      //車行紅燈5
      for (int i = 0; i < NUM_LEDS; i++) {
        led5s[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
      delay(delaytime);
    }
    time2 = currentMillis + cycletime;
    //Serial.print("TIME2:  ");
    //Serial.println(time2);
  }

  //3行人紅燈車行綠燈
  if (currentMillis >= time3) {
    FastLED.clear();
    //行人紅燈1
    for (int i = 0; i < NUM_LEDS; i++) {
      led1s[i] = CRGB(0, 255, 0);
    }
    //車行綠燈3
    for (int i = 0; i < NUM_LEDS; i++) {
      led3s[i] = CRGB(255, 0, 0);
    }
    FastLED.show();
    time3 = currentMillis + cycletime;
    //Serial.print("TIME3:  ");
    //Serial.println(time3);
  }

  //4行人紅燈車行黃燈
  if (currentMillis >= time4) {
    FastLED.clear();
    //行人紅燈1
    for (int i = 0; i < NUM_LEDS; i++) {
      led1s[i] = CRGB(0, 255, 0);
    }
    //車行黃燈4
    for (int i = 0; i < NUM_LEDS; i++) {
      led4s[i] = CRGB(190, 255, 0);
    }
    FastLED.show();
    time4 = currentMillis + cycletime;
    //Serial.print("TIME4:  ");
    //Serial.println(time4);
  }
}
