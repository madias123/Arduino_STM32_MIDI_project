# Arduino_STM32_MIDI_project
USB_MIDI HID - very experimental!
First upload of a super rough conversation of libmaple_midi -> https://github.com/feurig/libmaplemidi-cma
Beware: Serial.USB is gone with this branch (for now)
Setup is easy (if you have installed the original Arduino_STM32 -->https://github.com/rogerclarkmelbourne/Arduino_STM32
Just copy the repro into your Arduino/hardware folder
From Arduino IDE (1.6++) choose "MIDI leaflabs maple mini Rev 2 to flash"
Choose the sketch from "usb-midi-test-WORKING" 
After uploading your maple should be apear as MIDI device
