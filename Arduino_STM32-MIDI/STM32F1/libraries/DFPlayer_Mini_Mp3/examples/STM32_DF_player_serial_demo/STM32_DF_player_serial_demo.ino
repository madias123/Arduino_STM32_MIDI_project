/*
DF-Player mini example by Matthias Diro
Easy wiring: Serial1: DF-Player, Serial commands via USB-Serial ("Serial")

Returned data of feedback from module
Module returns ACK 7E FF 06 41 00 00 00 xx xx EF
In order to enhance stability between data communication, the function of a feedback from module is added.
Once there is a feedback to MCU from the module, it means the module has successfully received the command
that MCU sent out. 0x41 is the returned command by module.
*/

static const char* errortext[] = {"Module busy", "Currently sleep mode", "Serial receiving error",
                                  "Checksum incorrect", "Specified track is out of current track scope", "Specified track is not found", "Inter-cut error", "SD card reading failed", "Entered into sleep mode"
                                 };

#include <SerialCommand.h>
#define arduinoLED 33   // maple mini LED on board

SerialCommand sCmd;     //  SerialCommand object
#include <DFPlayer_Mini_Mp3.h>
long time = millis();
byte track = 1;
byte folder = 1;
byte intercut = 1;
byte vol = 15;
byte inc_message[16]; // incoming message buffer
byte inc_counter = 0;
byte setdev=2;
boolean inc_flag = 0; // flag for incoming messages
boolean inc_busy = 0;
boolean DAC_state = 0;
boolean sleep_state = 0;
boolean pauseflip =0;
//
void setup () {
  pinMode(arduinoLED, OUTPUT);      // Configure the onboard LED for output
  digitalWrite(arduinoLED, LOW);    // default to LED off
  Serial1.begin (9600);
  mp3_set_serial (Serial1);	//set Serial for DFPlayer-mini mp3 module
  mp3_reset();
  mp3_set_volume (vol);

  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("r", m_reset);
  sCmd.addCommand("p", m_play);
  sCmd.addCommand("pp", m_pause);
  sCmd.addCommand("s", m_stop);
  sCmd.addCommand("set", m_setdev);
  sCmd.addCommand("v", m_vol); // 1 arg (vol)
  sCmd.addCommand("c",    m_choose);  // 2 arg (folder,track) choose folder / track
  sCmd.addCommand("gs",    m_getstate);  // get state
  sCmd.addCommand("fo",    m_getfolders);  // 1 arg (folder) get totaly files in folder
  sCmd.addCommand("i", i_play); // intercut 1 arg (track)
  sCmd.addCommand("dac", m_dac); // intercut 1 arg (track)
  sCmd.addCommand("sleep", m_sleep); // intercut 1 arg (track)
  sCmd.addCommand("?",    consoleprint);  // print commands
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  Serial.begin(9600);
  delay(2000);
  consoleprint();
}


//
void loop () {
  sCmd.readSerial();     //  process serial commands
  getserial();
  delay(10);

}

void getserial() {
  if (Serial1.available() ) { // getting incoming message
    byte inChar = Serial1.read();
    if (inChar == 0x7e)
    {
      inc_flag = 1;
      inc_message[0] = inChar;
      inc_counter = 1;
      delay(100);
      while (Serial1.available())

      {
        inc_message[inc_counter] = Serial1.read();
        //   Serial.println(inc_message[inc_counter]);
        inc_counter++;
        //delay(10);
      }
    }
  }


  if (inc_flag == 1)
  {

    Serial.println(F("*****incoming Message: ******"));
    for (byte i = 0; i < inc_counter; i++) {
      Serial.print(inc_message[i], HEX);
      Serial.print (" ");
    }
    Serial.println();
    Serial.println(F("******END incoming***********"));
    proc_message();
    inc_flag = 0;

  }
}

void proc_message() { // processing incoming message

  if (inc_message[3] == 0x40) { // error occurs
    Serial.print("Error: ");
    Serial.println(errortext[inc_message[6] - 1]);
  }
  if (inc_message[3] == 0x3A && inc_message[6] == 2) { // sd card plugged in
    Serial.print("SD card plugged in!");
  }
  if (inc_message[3] == 0x3B && inc_message[6] == 2) { // sd card plugged out
    Serial.print("SD card plugged out!");
  }

  if (inc_message[3] == 0x3d) { // track finished
    Serial.print("Track finished playing: ");
  }
  if (inc_message[3] == 0x3f && inc_message[6] == 2) { // sd card online (startup)
    Serial.print("SD card online");
  }

  if (inc_message[3] == 0x4e) { // query nr/tracks in folder
    if ( inc_message[6] != 0) { // check if folder not empty (error msg = 7E FF 06 40 00 00 06 FE B5 EF)
      Serial.print(" tracks: ");
      Serial.println(inc_message[6]);

    }
    else
      Serial.println("Folder is empty! ");
  }
} // end void proc_message

void consoleprint() {
  Serial.println();
  Serial.println(F("******* MP3 console ************"));
  Serial.println(F("*  r = reset                   *"));
  Serial.println(F("*  p = play                    *"));
  Serial.println(F("*  s = stop                    *"));
  Serial.println(F("* set = set dev 2 USB 4 SLEEP  *"));
  Serial.println(F("* pp = pause                   *"));
  Serial.println(F("*  v = vol (0 to 30            *"));
  Serial.println(F("*  c = folder / track          *"));
  Serial.println(F("* gs = get state               *"));
  Serial.println(F("* fo = get nr/tracks in folder *"));
  Serial.println(F("*  i = play intercut / track   *"));
  Serial.println(F("*  dac = dac on/off            *"));
  Serial.println(F("*  sleep = sleep on/off        *"));
  Serial.println(F("*  ? = print commands          *"));
  Serial.println(F("********************************"));
}
void m_getstate() {
  Serial.println("Status: ");
  mp3_get_state ();
}
void m_reset() {
  Serial.println("Reset! ");
  mp3_reset ();
}
void m_play() {
  mp3_play (track, folder);
  Serial.println();
  Serial.print(F("Playing: Track: "));
  Serial.print(track);
  Serial.print(" Folder: ");
  Serial.println(folder);
}

void m_setdev() {
    char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    setdev = atoi(arg);    // Converts a char string to an integer
  mp3_set_device (setdev);
  Serial.println();
  Serial.print(F("Device: "));
  Serial.println(setdev);
  }
  else
  Serial.print(F("no dev number! "));

}

void i_play() {
    char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    intercut = atoi(arg);    // Converts a char string to an integer
  }
  mp3_play_intercut (intercut);
  Serial.println();
  Serial.print(F("Intercut:  "));
  Serial.print(intercut);

}

void m_pause() {
  pauseflip=!pauseflip;
  if (pauseflip==1)
  {
  mp3_pause ();
  Serial.println();
  Serial.println("Pausing...");
  }
  else
  {
    mp3_play ();
  Serial.println();
  Serial.println("resume...");
  
  }
}

void m_stop() {
  mp3_stop();
  Serial.println();
  Serial.println("Playback stopped");
}

void m_dac() {
  DAC_state=!DAC_state;
  mp3_DAC (DAC_state);
  Serial.println();
  Serial.print("DAC state: ");
  Serial.println(DAC_state);
}

void m_sleep() {
  sleep_state=!sleep_state;
  mp3_sleep (sleep_state);
  Serial.println();
  Serial.print("sleep state: ");
  Serial.println(sleep_state);
}

void m_choose() {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    folder = atoi(arg);    // Converts a char string to an integer
    Serial.println();
    Serial.print("Choosed and now playing: ");
    Serial.print("Folder: ");
    Serial.print(folder);
  }
  arg = sCmd.next();
  if (arg != NULL) {
    track = atoi(arg);    // Converts a char string to an integer
    Serial.print(" Track: ");
    Serial.println(track);
  }
  mp3_play (track, folder);
}

void m_vol() {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    vol = atoi(arg);    // Converts a char string to an integer
    Serial.println();
    Serial.print("Volume set to: ");
    Serial.println(vol);
  }
  mp3_set_volume(vol);
}

void m_getfolders() {
  char *arg;
  byte qfolder;
  arg = sCmd.next();
  if (arg != NULL) {
    qfolder = atoi(arg);    // Converts a char string to an integer
    Serial.println();
    Serial.print("Query number/tracks in folder: ");
    Serial.println(qfolder);
  }
  mp3_get_track_in_folders (qfolder);
}

void unrecognized(const char *command) {
  Serial.println("What?");
}


