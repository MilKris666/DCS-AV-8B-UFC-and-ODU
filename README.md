Here is my Arduino code for the DCS AV-8B UFC. It displays the UFC Scratchpad data on an SSD1322 OLED,
while the two UFC Comm Preset Displays are shown on two SSD1306 OLED screens. Additionally,
it makes the Master Caution and Master Warning LEDs blink accordingly.

SSD1322 (SPI) → show data from UFC Scratchpad Display
SSD1306 (I²C) → shows data from UFC Comm1 Preset Display und UFC Comm2 Preset Display

You need SSD1306 displays where the I²C address can be changed. Normally, SSD1306 displays have two standard addresses: 0x3C and 0x3D.
If both displays have the same address, you can change one (e.g., via a solder pad). 

Make sure to use the latest version of DCS-BIOS Skunkworks.

The project is still a Work in Progress (WIP), meaning the 3D files for printing are not available yet. A Thingiverse link will be shared soon.


