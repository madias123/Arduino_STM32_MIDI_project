/*******************************************************************************
 * Copyright (C) 2014 DFRobot						       *
 *									       *
 * DFPlayer_Mini_Mp3, This library provides a quite complete function for      * 
 * DFPlayer mini mp3 module.                                                   *
 * www.github.com/dfrobot/DFPlayer_Mini_Mp3 (github as default source provider)*
 *  DFRobot-A great source for opensource hardware and robot.                  *
 *                                                                             *
 * This file is part of the DFplayer_Mini_Mp3 library.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is free software: you can redistribute it and/or          *
 * modify it under the terms of the GNU Lesser General Public License as       *
 * published by the Free Software Foundation, either version 3 of              *
 * the License, or any later version.                                          *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public            *
 * License along with DFPlayer_Mini_Mp3. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                             *
 ******************************************************************************/

/*
 *	name:		DFPlayer_Mini_Mp3
 *	version:	1.0
 *	Author:		lisper <lisper.li@dfrobot.com>
 *	Date:		2014-05-22
 *	Description:	mp3 library for DFPlayer mini board
 *			note: mp3 file must put into mp3 folder in your tf card
* Edit and converted for STM32-Arduino by Matthias Diro on 2015-04-22 with additional functions, but deleted the soft-serial-stuff (not needed on STM32)
 */

//#define sdebug 1
#include <Arduino.h>
#ifdef sdebug
#pragma message("Serial CPP")
#endif
//#include  "DFPlayer_Mini_Mp3.h"

uint8_t send_buf[10] = {0x7E, 0xFF, 06, 00, 00, 00, 00, 00, 00, 0xEF};
uint8_t recv_buf[10];

static void(*send_func)() = NULL;
static HardwareSerial * _hardware_serial = NULL;
//static SoftwareSerial * _software_serial = NULL;
static boolean is_reply = false;

// *****INTERNALS*******************
byte mp3_get_message () {
    static byte counter=0;
    while (_hardware_serial ->available()) {
        recv_buf[counter]= _hardware_serial ->read ();
        counter++;
    }
    return (counter);
}
void mp3_set_reply (boolean state) {
	is_reply = state;
	send_buf[4] = is_reply;
}

static void fill_uint16_bigend (uint8_t *thebuf, uint16_t data) {
	*thebuf =	(uint8_t)(data>>8);
	*(thebuf+1) =	(uint8_t)data;
}

//calc checksum (1~6 byte)
uint16_t mp3_get_checksum (uint8_t *thebuf) {
	uint16_t sum = 0;

	for (int i=1; i<7; i++) {
		sum += thebuf[i];

	}
	return -sum;
}

//fill checksum to send_buf (7~8 byte)
void mp3_fill_checksum () {
	uint16_t checksum = mp3_get_checksum (send_buf);
	fill_uint16_bigend (send_buf+7, checksum);
}

//
void h_send_func () {
    #ifdef sdebug
    Serial.println();
    Serial.print("Send: ");
    #endif
	for (int i=0; i<10; i++) {
    #ifdef sdebug
        Serial.print(send_buf[i],HEX);
        Serial.print(" ");
    #endif
		_hardware_serial->write (send_buf[i]);
      //  int a=_hardware_serial->read ();
	}
#ifdef sdebug
    Serial.println();
#endif
}

//void mp3_set_serial (HardwareSerial *theSerial) {
void mp3_set_serial (HardwareSerial &theSerial) {
	_hardware_serial = &theSerial;
	send_func = h_send_func;
}

void mp3_send_cmd (uint8_t cmd, uint16_t arg, uint16_t arg2) {
    send_buf[3] = cmd;
   
    fill_uint16_bigend ((send_buf+5), arg);
    fill_uint16_bigend ((send_buf+4), arg2); // does this work?!?
    mp3_fill_checksum ();
    send_func ();
}

void mp3_send_cmd (uint8_t cmd, uint16_t arg) {
	send_buf[3] = cmd;
	fill_uint16_bigend ((send_buf+5), arg);
	mp3_fill_checksum ();
	send_func ();
}

//
void mp3_send_cmd (uint8_t cmd) {
	send_buf[3] = cmd;
	fill_uint16_bigend ((send_buf+5), 0);
	mp3_fill_checksum ();
	send_func ();
}

//******************COMMANDS*****************
void mp3_play_physical (uint16_t num) {
	mp3_send_cmd (0x03, num);
}

void mp3_play_physical () {
	mp3_send_cmd (0x03);
}

void mp3_next () {
	mp3_send_cmd (0x01);
}

void mp3_prev () {
	mp3_send_cmd (0x02);
}

void mp3_set_volume (uint16_t volume) {
	mp3_send_cmd (0x06, volume);//0x06 set volume 0-30
}

void mp3_set_EQ (uint16_t eq) {
	mp3_send_cmd (0x07, eq);//0x07 set EQ0/1/2/3/4/5    Normal/Pop/Rock/Jazz/Classic/Bass
}

void mp3_set_device (uint16_t device) {
	mp3_send_cmd (0x09, device);//0x09 set device 1/2/3/4/5 U/SD/AUX/SLEEP/FLASH
}

void mp3_sleep (boolean state) {
	mp3_send_cmd (0x0a,state);
}

void mp3_reset () {
	mp3_send_cmd (0x0c);
}

void mp3_play () {
	mp3_send_cmd (0x0d);
}

void mp3_pause () {
	mp3_send_cmd (0x0e);
}

void mp3_stop () {
	mp3_send_cmd (0x16);
}
void mp3_stop_intercut () {
    mp3_send_cmd (0x15);
}

void mp3_play (uint16_t num) {
	mp3_send_cmd (0x12, num);//play mp3 file in mp3 folder in your tf card
}

void mp3_play (uint16_t num, uint16_t folder) {  //*new* specify track <num> in folder <folder>
	mp3_send_cmd (0x0F, num,folder);
}

void mp3_play_intercut (uint16_t num) {
    mp3_send_cmd (0x13, num);
}


void mp3_single_loop (boolean state) {
	mp3_send_cmd (0x19, !state);
}

void mp3_single_play (uint16_t num) {
	mp3_play (num);
	delay (10);
	mp3_single_loop (true); 
	//mp3_send_cmd (0x19, !state);
}

//
void mp3_DAC (boolean state) {
	mp3_send_cmd (0x1a, !state);
}

//
void mp3_random_play () {
	mp3_send_cmd (0x18);
}

void mp3_repeat_folder (uint16_t folder){ //*new*
	mp3_send_cmd (0x17,folder);
}
//******************QUERY*****************

void mp3_get_track_in_folders (uint16_t folder) {
mp3_send_cmd (0x4e,folder);
}
void mp3_get_state () {
	mp3_send_cmd (0x42);
    /*
    byte resp=mp3_get_message ();
    if (resp>0) {
        for (byte x=0;x<=resp;x++) {
            // do something
        }
     
    }
     */
}

void mp3_get_volume () {
	mp3_send_cmd (0x43);
}

void mp3_get_u_sum () {
	mp3_send_cmd (0x47);
}

void mp3_get_tf_sum () {
	mp3_send_cmd (0x48);
}

void mp3_get_flash_sum () {
	mp3_send_cmd (0x49);
}

void mp3_get_tf_current () {
	mp3_send_cmd (0x4c);
}

void mp3_get_u_current () {
	mp3_send_cmd (0x4b);
}

void mp3_get_flash_current () {
	mp3_send_cmd (0x4d);
}



