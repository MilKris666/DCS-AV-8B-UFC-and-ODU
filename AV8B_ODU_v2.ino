#include <SPI.h>
#include <Wire.h>
#include <U8x8lib.h>
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

// TCA9548A Adresse (Standard: 0x70)
#define TCA9548A_ADDR 0x70

// Funktion, um einen bestimmten Kanal am TCA9548A auszuwählen
void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);  // Kanal auswählen: Kanal 0 -> 0x01, Kanal 1 -> 0x02, etc.
  Wire.endTransmission();
}

// SSD1306-Displays (alle haben intern die Adresse 0x3C)
U8X8_SSD1306_128X64_NONAME_HW_I2C oledOdu1(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oledOdu2(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oledOdu3(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oledOdu4(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oledOdu5(U8X8_PIN_NONE);

// Textpuffer für die ODU-Displays (4 Zeichen + Nullterminator)
char odu1Text[5] = "    ";
char lastOdu1Text[5] = "    ";
char odu2Text[5] = "    ";
char lastOdu2Text[5] = "    ";
char odu3Text[5] = "    ";
char lastOdu3Text[5] = "    ";
char odu4Text[5] = "    ";
char lastOdu4Text[5] = "    ";
char odu5Text[5] = "    ";
char lastOdu5Text[5] = "    ";

// Hilfsfunktion zur Zentrierung des Textes (optional)
int getCenteredPosition(int displayWidth, int textLength, int charWidth) {
    return (displayWidth - (textLength * charWidth)) / (2 * charWidth);
}

// --- Callback-Funktionen für DCS‑Bios ---
// Diese Funktionen aktualisieren die jeweiligen Puffer und rufen dann das Update der Displays auf.

void onOdu1DisplayChange(char* newValue) {
    memset(odu1Text, 0, sizeof(odu1Text));
    strncpy(odu1Text, newValue, 4);
    if (strcmp(lastOdu1Text, odu1Text) != 0) {
        strcpy(lastOdu1Text, odu1Text);
        updateOdu1Display();
    }
}

void onOdu2DisplayChange(char* newValue) {
    memset(odu2Text, 0, sizeof(odu2Text));
    strncpy(odu2Text, newValue, 4);
    if (strcmp(lastOdu2Text, odu2Text) != 0) {
        strcpy(lastOdu2Text, odu2Text);
        updateOdu2Display();
    }
}

void onOdu3DisplayChange(char* newValue) {
    memset(odu3Text, 0, sizeof(odu3Text));
    strncpy(odu3Text, newValue, 4);
    if (strcmp(lastOdu3Text, odu3Text) != 0) {
        strcpy(lastOdu3Text, odu3Text);
        updateOdu3Display();
    }
}

void onOdu4DisplayChange(char* newValue) {
    memset(odu4Text, 0, sizeof(odu4Text));
    strncpy(odu4Text, newValue, 4);
    if (strcmp(lastOdu4Text, odu4Text) != 0) {
        strcpy(lastOdu4Text, odu4Text);
        updateOdu4Display();
    }
}

void onOdu5DisplayChange(char* newValue) {
    memset(odu5Text, 0, sizeof(odu5Text));
    strncpy(odu5Text, newValue, 4);
    if (strcmp(lastOdu5Text, odu5Text) != 0) {
        strcpy(lastOdu5Text, odu5Text);
        updateOdu5Display();
    }
}

// DCS‑Bios StringBuffer für die einzelnen ODU-Displays
DcsBios::StringBuffer<4> odu1DisplayBuffer(0x795a, onOdu1DisplayChange);
DcsBios::StringBuffer<4> odu2DisplayBuffer(0x7960, onOdu2DisplayChange);
DcsBios::StringBuffer<4> odu3DisplayBuffer(0x7966, onOdu3DisplayChange);
DcsBios::StringBuffer<4> odu4DisplayBuffer(0x796c, onOdu4DisplayChange);
DcsBios::StringBuffer<4> odu5DisplayBuffer(0x7972, onOdu5DisplayChange);

// --- Update-Funktionen für die einzelnen ODU-Displays ---
// Vor jedem Zugriff wird der entsprechende TCA-Kanal ausgewählt.

void updateOdu1Display() {
    tcaSelect(0); // Kanal 0 für Display 1
    oledOdu1.clear();
    oledOdu1.setFont(u8x8_font_inb33_3x6_r);
    int cursorPos = getCenteredPosition(16, strlen(odu1Text), 2);
    oledOdu1.setCursor(cursorPos + 0, 2);
    oledOdu1.print(odu1Text);
    oledOdu1.refreshDisplay();
}

void updateOdu2Display() {
    tcaSelect(1); // Kanal 1 für Display 2
    oledOdu2.clear();
    oledOdu2.setFont(u8x8_font_inb33_3x6_r);
    int cursorPos = getCenteredPosition(16, strlen(odu2Text), 2);
    oledOdu2.setCursor(cursorPos + 0, 2);
    oledOdu2.print(odu2Text);
    oledOdu2.refreshDisplay();
}

void updateOdu3Display() {
    tcaSelect(2); // Kanal 2 für Display 3
    oledOdu3.clear();
    oledOdu3.setFont(u8x8_font_inb33_3x6_r);
    int cursorPos = getCenteredPosition(16, strlen(odu3Text), 2);
    oledOdu3.setCursor(cursorPos + 0, 2);
    oledOdu3.print(odu3Text);
    oledOdu3.refreshDisplay();
}

void updateOdu4Display() {
    tcaSelect(3); // Kanal 3 für Display 4
    oledOdu4.clear();
    oledOdu4.setFont(u8x8_font_inb33_3x6_r);
    int cursorPos = getCenteredPosition(16, strlen(odu4Text), 2);
    oledOdu4.setCursor(cursorPos + 0, 2);
    oledOdu4.print(odu4Text);
    oledOdu4.refreshDisplay();
}

void updateOdu5Display() {
    tcaSelect(4); // Kanal 4 für Display 5
    oledOdu5.clear();
    oledOdu5.setFont(u8x8_font_inb33_3x6_r);
    int cursorPos = getCenteredPosition(16, strlen(odu5Text), 2);
    oledOdu5.setCursor(cursorPos + 0, 2);
    oledOdu5.print(odu5Text);
    oledOdu5.refreshDisplay();
}

void setup() {
    DcsBios::setup();
    Wire.begin();

    // Initialisierung der Displays über die jeweiligen TCA-Kanäle

    // Display 1 (Kanal 0)
    tcaSelect(0);
    oledOdu1.setI2CAddress(0x3C << 1);
    oledOdu1.begin();
    oledOdu1.setFont(u8x8_font_inb33_3x6_r);
    oledOdu1.clear();
    oledOdu1.setCursor(0, 2);
    oledOdu1.print("ODU1");
    oledOdu1.refreshDisplay();

    // Display 2 (Kanal 1)
    tcaSelect(1);
    oledOdu2.setI2CAddress(0x3C << 1);
    oledOdu2.begin();
    oledOdu2.setFont(u8x8_font_inb33_3x6_r);
    oledOdu2.clear();
    oledOdu2.setCursor(0, 2);
    oledOdu2.print("ODU2");
    oledOdu2.refreshDisplay();

    // Display 3 (Kanal 2)
    tcaSelect(2);
    oledOdu3.setI2CAddress(0x3C << 1);
    oledOdu3.begin();
    oledOdu3.setFont(u8x8_font_inb33_3x6_r);
    oledOdu3.clear();
    oledOdu3.setCursor(0, 2);
    oledOdu3.print("ODU3");
    oledOdu3.refreshDisplay();

    // Display 4 (Kanal 3)
    tcaSelect(3);
    oledOdu4.setI2CAddress(0x3C << 1);
    oledOdu4.begin();
    oledOdu4.setFont(u8x8_font_inb33_3x6_r);
    oledOdu4.clear();
    oledOdu4.setCursor(0, 2);
    oledOdu4.print("ODU4");
    oledOdu4.refreshDisplay();

    // Display 5 (Kanal 4)
    tcaSelect(4);
    oledOdu5.setI2CAddress(0x3C << 1);
    oledOdu5.begin();
    oledOdu5.setFont(u8x8_font_inb33_3x6_r);
    oledOdu5.clear();
    oledOdu5.setCursor(0, 2);
    oledOdu5.print("ODU5");
    oledOdu5.refreshDisplay();

    delay(2000);

    // Initiale Updates (optional)
    updateOdu1Display();
    updateOdu2Display();
    updateOdu3Display();
    updateOdu4Display();
    updateOdu5Display();
}

void loop() {
    DcsBios::loop();
}
