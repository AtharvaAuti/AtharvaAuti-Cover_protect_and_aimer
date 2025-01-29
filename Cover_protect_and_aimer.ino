#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     9
#define TFT_RST    10
#define TFT_DC     8
#define TFT_MOSI   11
#define TFT_SCLK   13
#define TFT_VCC    3.3
#define TFT_BL     3.3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define OV7670_VSYNC 2
#define OV7670_PCLK 12
#define OV7670_SIOD A4
#define OV7670_SIOC A5
#define OV7670_D0 A0
#define OV7670_D1 A1
#define OV7670_D2 A2
#define OV7670_D3 A3
#define OV7670_D4 4
#define OV7670_D5 5
#define OV7670_D6 6
#define OV7670_D7 7
#define OV7670_XCLK 3
#define OV7670_RESET 3.3
#define OV7670_PWDN 0

void setup() {
    Serial.begin(115200);
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    pinMode(OV7670_VSYNC, INPUT);
    pinMode(OV7670_PCLK, INPUT);
    pinMode(OV7670_D0, INPUT);
    pinMode(OV7670_D1, INPUT);
    pinMode(OV7670_D2, INPUT);
    pinMode(OV7670_D3, INPUT);
    pinMode(OV7670_D4, INPUT);
    pinMode(OV7670_D5, INPUT);
    pinMode(OV7670_D6, INPUT);
    pinMode(OV7670_D7, INPUT);
    pinMode(OV7670_XCLK, OUTPUT);
    pinMode(OV7670_RESET, OUTPUT);
    pinMode(OV7670_PWDN, OUTPUT);
    digitalWrite(OV7670_XCLK, HIGH);
    digitalWrite(OV7670_RESET, HIGH);
    digitalWrite(OV7670_PWDN, LOW);
}

void loop() {
    if (digitalRead(OV7670_VSYNC) == LOW) {
        tft.fillScreen(ST7735_BLACK);
        for (int y = 0; y < 128; y++) {
            for (int x = 0; x < 128; x++) {
                while (digitalRead(OV7670_PCLK) == LOW);
                int pixelHigh = (analogRead(OV7670_D4) << 4) | analogRead(OV7670_D0);
                while (digitalRead(OV7670_PCLK) == HIGH);
                while (digitalRead(OV7670_PCLK) == LOW);
                int pixelLow = (analogRead(OV7670_D4) << 4) | analogRead(OV7670_D0);
                while (digitalRead(OV7670_PCLK) == HIGH);
                uint16_t color = (pixelHigh << 8) | pixelLow;
                tft.drawPixel(x, y, color);
            }
        }
    }
}
