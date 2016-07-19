//
//  lgl_min_sysex.h
//  LibMaple4Midi
//
//  Created by Donald D Davis on 4/11/13.
//  Copyright (c) 2013 Suspect Devices. All rights reserved.
//
#ifndef __LGL_MIN_SYSEX_H__
#define __LGL_MIN_SYSEX_H__ 1


#include "MidiSpecs.h"
//#include "LGL.h"



// eventually all of this should be in a place for settings which can be written to flash.
extern volatile uint8 myMidiChannel;
extern volatile uint8 myMidiDevice;
extern volatile uint8 myMidiCable;
extern volatile uint8 myMidiID[];
//extern volatile uint8 sysexBuffer[MAX_SYSEX_SIZE];

void LglSysexHandler(uint32 *midiBufferRx,uint32 *rx_offset,uint32 *n_unread_bytes);

#endif