/***********************************************/
Commands
/***********************************************/

Command Function Description Remarks
0x01 Play Next
0x02 Play Previous
0x03 Specify playback of a track 1-3000
0x04 Increase volume
0x05 Decrease volume
0x06 Specify volume Volume level:0-30
0x07 Specify EQ(0/1/2/3/4/5) 0:Normal/1:Pop/2:Rock/3:Jazz/4:Classic/5:
Bass
0x08 Specify single repeat playback Tracks 0001-3000
0x09 Specify playback of a device(0/1) 0:USB/1:SD // Specify playback source(0/1/2/3/4): U/TF/AUX/SLEEP/FLASH
0x0A Set Sleep
0x0B N/A(Reserved Normal working)
0x0C Reset
0x0D Play
0x0E Pause
0x0F Specify playback a track in a folder Folders 01-99
0x10 Audio amplification setting MSB=1:amplifying on, LSB:set gain 0-31
0x11 Set all repeat playback 1:start all repeat playback; 0:stop playback
0x12 Specify playback of folder named “MP3”
0x13 Inter cut an advertisement
0x14 Specify playback a track in a folder that supports 3000 tracks Supports 15 folders only(01-15)
0x15 Stop playing inter-cut advertisement and go back to play the music interrupted
0x16 Stop
0x17 Specify repeat playback of a folder
0x18 Set random playback
0x19 Set repeat playback of current track
0x1A Set DAC

/***********************************************/
Query Commands
/***********************************************/

Command Function Description Remarks
0x3C N/A(Reserved)
0x3D N/A(Reserved)
0x3E N/A(Reserved)
0x3F Query current online storage device
0x40 Module returns an error data with this command
0x41 Module reports a feedback with this command // "debug mode"
0x42 Query current status
0x43 Query current volume
0x44 Query current EQ
0x45 Query the current playback mode
0x46 Query the current software version
0x47 Query total file numbers of USB flash disk
0x48 Query total file numbers of micro SD Card
0x49 Query the total number of flash files
0x4A N/A(Reserved)
0x4B Query current track of USB flash disk
0x4C Query current track of micro SD Card
0x4D Queries the current track of Flash
0x4E Query total file numbers of a folder
0x4F Query total folder numbers of the storage device

/*****************************************************/
EXAMPLES Examples of Sending Serial Commands
/*****************************************************/

Commands Description Serial Commands
[with checksum]			[without checksum] 		Notes

Play Next 
7E FF 06 01 00 00 00 FE FA EF 		7E FF 06 01 00 00 00 EF

Play Previous 
7E FF 06 02 00 00 00 FE F9 EF 		7E FF 06 02 00 00 00 EF

Specify playback of a track under the root directory
7E FF 06 03 00 00 01 FE F7 EF 		7E FF 06 03 00 00 01 EF 	Specify playback of the 1st track
7E FF 06 03 00 00 02 FE F6 EF 		7E FF 06 03 00 00 02 EF 	Specify playback of the 2nd track
7E FF 06 03 00 00 0A FE EE EF 		7E FF 06 03 00 00 0A EF 	Specify playback of the 10th track

Specify volume 
7E FF 06 06 00 00 1E FE D7 EF 		7E FF 06 06 00 00 1E EF 	Specified volume is level 30

Specify EQ 
7E FF 06 07 00 00 01 FE F3 EF 		7E FF 06 07 00 00 01 EF 	Specified EQ mode is POP

Specify single repeat playback
7E FF 06 08 00 00 01 FE F2 EF 		7E FF 06 08 00 00 01 EF 	Repeatedly play the 1st track
7E FF 06 08 00 00 02 FE F1 EF 		7E FF 06 08 00 00 02 EF 	Repeatedly play the 2nd track
7E FF 06 08 00 00 0A FE E9 EF 		7E FF 06 08 00 00 0A EF 	Repeatedly play the 10th track

Specify playback of a device
7E FF 06 09 00 00 01 FE F1 EF 		7E FF 06 09 00 00 01 EF 	Specified device is USB flash disk
7E FF 06 09 00 00 02 FE F0 EF 		7E FF 06 09 00 00 02 EF 	Specified device is micro SD

Set sleep mode 
7E FF 06 0A 00 00 00 FE F1 EF 		7E FF 06 0A 00 00 00 EF

Reset 
7E FF 06 0C 00 00 00 FE EF EF 		7E FF 06 0C 00 00 00 EF

Play 
7E FF 06 0D 00 00 00 FE EE EF 		7E FF 06 0D 00 00 00 EF

Pause 
7E FF 06 0E 00 00 00 FE ED EF 		7E FF 06 0E 00 00 00 EF

Specify playback of a folder
7E FF 06 0F 00 01 01 FE EA EF 		7E FF 06 0F 00 01 01 EF 	Specify track "001" in the folder “01”
7E FF 06 0F 00 01 02 FE E9 EF 		7E FF 06 0F 00 01 02 EF 	Specify track "002" in the folder “01”

Set all repeat playback 
7E FF 06 11 00 00 01 FE E9 EF 		7E FF 06 11 00 00 01 EF

Specify playback of folder named “MP3”
7E FF 06 12 00 00 01 FE E8 EF 		7E FF 06 12 00 00 01 EF 	Play track "0001" in the folder “MP3”
7E FF 06 12 00 00 02 FE E7 EF 		7E FF 06 12 00 00 02 EF 	Play track "0002" in the folder “MP3”
7E FF 06 12 00 00 FF FD EA EF 		7E FF 06 12 00 00 FF EF 	Play track "0255" in the folder “MP3”
7E FF 06 12 00 07 CF FE 13 EF 		7E FF 06 12 00 07 CF EF 	Play track "1999" in the folder “MP3”
7E FF 06 12 00 0B B8 FE 26 EF 		7E FF 06 12 00 0B B8 EF 	Play track "3000" in the folder “MP3”

Inter cut an advertisement
7E FF 06 13 00 00 01 FE E7 EF 		7E FF 06 13 00 00 01 EF 	Inter cut track "0001"in the folder “ADVERT”
7E FF 06 13 00 00 02 FE E6 EF 		7E FF 06 13 00 00 02 EF 	Inter cut track "0002"in the folder “ADVERT”
7E FF 06 13 00 00 FF FD E9 EF 		7E FF 06 13 00 00 FF EF 	Inter cut track "0255"in the folder “ADVERT”

Specify playback of a track in a folder that supports 3000 tracks
7E FF 06 14 00 10 FF FD D8 EF 		7E FF 06 14 00 10 FF EF 	Play track "0255" in the specified folder “01”
7E FF 06 14 00 17 CF FE 01 EF 		7E FF 06 14 00 17 CF EF 	Play track "1999" in the specified folder “01”
7E FF 06 14 00 C0 01 FE 26 EF 		7E FF 06 14 00 C0 01 EF 	Play track "0001" in the specified folder “12”
7E FF 06 14 00 C0 FF FD 28 EF 		7E FF 06 14 00 C0 FF EF 	Play track "0255" in the specified folder “12”
7E FF 06 14 00 C7 CF FD 51 EF 		7E FF 06 14 00 C7 CF EF 	Play track "1999" in the specified folder “12”

Stop playing inter-cut ad 
7E FF 06 15 00 00 00 FE E6 EF Go back and continue to play themusic interrupted

Stop playback 
7E FF 06 16 00 00 00 FE E5 EF 		Stop software decoding

Specify repeat playback of a folder
7E FF 06 17 00 00 02 FE E2 EF 		7E FF 06 17 00 00 02 EF Specify repeat playback of the folder “02”
7E FF 06 17 00 00 01 FE E3 EF 		7E FF 06 17 00 00 01 EF Specify repeat playback of the folder “01”

Set random playback 
7E FF 06 18 00 00 00 FE E3 EF 		7E FF 06 18 00 00 00 EF

Set single repeat playback
7E FF 06 19 00 00 00 FE E2 EF 		7E FF 06 19 00 00 00 EF Turn on single repeat playback
7E FF 06 19 00 00 01 FE E1 EF 		7E FF 06 19 00 00 01 EF Turn off single repeat playback

Set DAC 
7E FF 06 1A 00 00 00 FE E1 EF 		7E FF 06 1A 00 00 00 EF Turn on DAC
7E FF 06 1A 00 00 01 FE E0 EF 		7E FF 06 1A 00 00 01 EF Turn off DAC

Query current status 
7E FF 06 42 00 00 00 FE B9 EF 		7E FF 06 42 00 00 00 EF

Query current volume 
7E FF 06 43 00 00 00 FE B8 EF 		7E FF 06 43 00 00 00 EF

Query current EQ 
7E FF 06 44 00 00 00 FE B7 EF 		7E FF 06 44 00 00 00 EF

Query total file numbers of USB flash disk
7E FF 06 47 00 00 00 FE B4 EF 		7E FF 06 47 00 00 00 EF Total file numbers of current device

Query total file numbers of micro SD card
7E FF 06 48 00 00 00 FE B3 EF 		7E FF 06 48 00 00 00 EF Total file numbers of current device

Query current track of USB flash disk 
7E FF 06 4B 00 00 00 FE B0 EF 		7E FF 06 4B 00 00 00 EF Query the track being played

Query current track of micro SD card 
7E FF 06 4C 00 00 00 FE AF EF 		7E FF 06 4C 00 00 00 EF Query the track being played

Query total file numbers of a folder
7E FF 06 4E 00 00 01 FE AC EF 		7E FF 06 4E 00 00 01 EF Query the total file numbers of the folder “01”.
7E FF 06 4E 00 00 0B FE A2 EF 		7E FF 06 4E 00 00 0B EF Query the total file numbers of the folder “11”.