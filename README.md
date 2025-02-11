Here is my Arduino code for the DCS AV-8B UFC. It displays the UFC Scratchpad data on an SSD1322 OLED, 
while the two UFC Comm Preset Displays are shown on two SSD1306 OLED screens. Additionally, 
it makes the Master Caution and Master Warning LEDs blink accordingly.

You need SSD1306 displays where the I²C address can be changed. Normally, SSD1306 displays have two standard addresses: 0x3C and 0x3D. If both displays have the same address, you can change one (e.g., via a solder pad). See the image "Change I²C Address.jpg"

SSD1322 (SPI) → show data from UFC Scratchpad Display

SSD1306 (I²C Address 0x3C)→ shows data from UFC Comm1 Preset Display

SSD1306 (I²C Address 0x3D) → shows data from UFC Comm2 Preset Display

For wiring, see the image "PIN Connection.png".
Make sure to use the latest version of DCS-BIOS Skunkworks.

The project is still a Work in Progress (WIP), meaning the 3D files for printing are not available yet. A Thingiverse link will be shared soon.

SSD1322 SPI OLED: https://www.amazon.de/OLED-Display-SSD1322-Grafik-LCD-Modul-Parallel-L%C3%B6tstift-wei%C3%9F/dp/B0DQ52MRX1?source=ps-sl-shoppingads-lpcontext&ref_=fplfs&psc=1&smid=A9KVXEOZANNPE

SSD1306 I²C OLED: https://www.amazon.de/AZDelivery-Display-Arduino-Raspberry-gratis/dp/B01L9GC470?th=1

