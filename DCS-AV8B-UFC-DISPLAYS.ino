#include <SPI.h>
#include <Wire.h>
#include <U8x8lib.h>
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

// **OLED Displays**
// SSD1322 (SPI) → UFC Scratchpad Display (Pin 10, 9, 8)
U8X8_SSD1322_NHD_256X64_4W_HW_SPI u8x8(10, 9, 8);

// SSD1306 (I2C) → UFC Comm1 & Comm2 Preset Displays (SCL: A5, SDA: A4)
U8X8_SSD1306_128X64_NONAME_HW_I2C oledComm1(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oledComm2(U8X8_PIN_NONE);

// **LED Konfiguration**
DcsBios::LED mcLight(0x787c, 0x0004, 10);  // UFC Comm1 LED
DcsBios::LED mwLight(0x787c, 0x0008, 11);  // UFC Comm2 LED

// **Speicher für Display-Werte**
char ufcComm1Text[3] = " ";    // 2 Zeichen + Null-Terminierung
char lastUfcComm1Text[3] = " ";

char ufcComm2Text[3] = " ";
char lastUfcComm2Text[3] = " ";

char ufcScratchpadText[13] = " ";  // 12 Zeichen + Null-Terminierung
char lastUfcScratchpadText[13] = " ";

// **Callback für UFC Comm1 Display**
void onUfcComm1DisplayChange(char* newValue) {
    if (strcmp(ufcComm1Text, newValue) != 0) {
        strncpy(ufcComm1Text, newValue, 2);
        ufcComm1Text[2] = '\0'; // Null-Terminierung
        updateComm1Display();
    }
}
DcsBios::StringBuffer<2> ufcComm1DisplayBuffer(0x7954, onUfcComm1DisplayChange);

// **Callback für UFC Comm2 Display**
void onUfcComm2DisplayChange(char* newValue) {
    if (strcmp(ufcComm2Text, newValue) != 0) {
        strncpy(ufcComm2Text, newValue, 2);
        ufcComm2Text[2] = '\0'; // Null-Terminierung
        updateComm2Display();
    }
}
DcsBios::StringBuffer<2> ufcComm2DisplayBuffer(0x7956, onUfcComm2DisplayChange);

// **Callback für UFC Scratchpad Display**
void onUfcScratchpadChange(char* newValue) {
    if (strcmp(ufcScratchpadText, newValue) != 0) {
        strncpy(ufcScratchpadText, newValue, 12);
        ufcScratchpadText[12] = '\0'; // Null-Terminierung
        updateScratchpadDisplay();
    }
}
DcsBios::StringBuffer<12> ufcScratchpadBuffer(0x7976, onUfcScratchpadChange);

// **OLED-Update für Comm1 Display**
void updateComm1Display() {
    if (strcmp(lastUfcComm1Text, ufcComm1Text) != 0) {
        strcpy(lastUfcComm1Text, ufcComm1Text);
        oledComm1.clearDisplay();
        oledComm1.setFont(u8x8_font_amstrad_cpc_2x2_f);
        oledComm1.setCursor(2, 3);
        oledComm1.print(ufcComm1Text);
    }
}

// **OLED-Update für Comm2 Display**
void updateComm2Display() {
    if (strcmp(lastUfcComm2Text, ufcComm2Text) != 0) {
        strcpy(lastUfcComm2Text, ufcComm2Text);
        oledComm2.clearDisplay();
        oledComm2.setFont(u8x8_font_amstrad_cpc_2x2_f);
        oledComm2.setCursor(2, 3);
        oledComm2.print(ufcComm2Text);
    }
}

// **OLED-Update für das Scratchpad Display**
void updateScratchpadDisplay() {
    if (strcmp(lastUfcScratchpadText, ufcScratchpadText) != 0) {
        strcpy(lastUfcScratchpadText, ufcScratchpadText);
        u8x8.clearDisplay();
        u8x8.setFont(u8x8_font_8x13B_1x2_f);
        u8x8.setCursor(0, 2);
        u8x8.print("                      "); // 22 Leerzeichen (löscht alte Zeichen)
        u8x8.setCursor(0, 2);
        u8x8.print(ufcScratchpadText);
    }
}

void setup() {
    DcsBios::setup();
    
    // **OLED Initialisierung**
    oledComm1.begin();
    oledComm2.begin();
    
    oledComm1.setFont(u8x8_font_amstrad_cpc_2x2_f);
    oledComm2.setFont(u8x8_font_amstrad_cpc_2x2_f);

    u8x8.begin();
    u8x8.setFont(u8x8_font_8x13B_1x2_f);

    // **Start-Nachrichten**
    oledComm1.setCursor(0, 1);
    oledComm1.print("COMM1 READY");

    oledComm2.setCursor(0, 1);
    oledComm2.print("COMM2 READY");

    u8x8.setCursor(0, 2);
    u8x8.print("UFC Scratchpad ready!");

    delay(2000);
    updateComm1Display();
    updateComm2Display();
    updateScratchpadDisplay();
}

void loop() {
    DcsBios::loop();
}
