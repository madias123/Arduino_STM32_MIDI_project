Written by Michael Neiderhauser.  October 10, 2012

This Library is not optomized and its use is "as-is", and is released under the LGPL License.  Please make suggestions and report bugs on GitHub.
The Library currently does not support sequential write (with the exclusion of the page read and page write functions).

This Library was only tested on Arduino IDE v1.0.1

Page writes are done in a 16 byte burst mode to account for the beffer set by the Wire Library.

To use:
Connect pin #1 of the EEPROM to VCC or GND (VSS) (See Data Sheet) (A0)
Connect pin #2 of the EEPROM to VCC or GND (VSS) (See Data Sheet) (A1)
Connect pin #3 of the EEPROM to VCC or GND (VSS) (See Data Sheet) (A2)
Connect pin #4 of the EEPROM to GND (VSS)
Connect pin #5 of the EEPROM to Analog 4 (i2c data)
Connect pin #6 of the EEPROM to Analog 5 (i2c clock)
Connect pin #7 of the EEPROM to VCC, GND (VSS), or Digital I/O pin for control (See Data Sheet) (WP)
Connect pin #8 of the EEPROM to VCC

Check the datasheet for more info on 24LC256: http://ww1.microchip.com/downloads/en/DeviceDoc/21203R.pdf
Check the datasheet for more info on 24LC512: http://ww1.microchip.com/downloads/en/DeviceDoc/21754M.pdf