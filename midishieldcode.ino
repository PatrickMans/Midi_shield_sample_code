//////////////////////////
// MIDI sample code  
// 
// using Arduino to handle midi messages
//
//
//  (c) Patrick Mans 2019
//////////////////////////

//////////////////////////
// MIDI MESAGES 
// midi.org/techspecs/
//////////////////////////
// STATUS BYTES
// 0x8n == noteOn
// 0x9n == noteOff
// 0xAn == afterTouch
// 0xBn == controlChange
// 0xCn == programChange
// 
// n == channel number (1-F)
//////////////////////////
//DATA BYTE 1
// note# == (0-127)
// or
// control# == (0-119)
//////////////////////////
// DATA BYTE 2
// velocity == (0-127)
// or
// controlVal == (0-127)
//////////////////////////

//     Includes 
//#######################################################
#include <MIDI.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MIDI_CREATE_DEFAULT_INSTANCE();

//     Var declarations 
//#######################################################
const int buttonPin1 = 3;     // the number of the pushbutton pin
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 6;

//     Midi callback routines 
//#######################################################
// Change the routines to the desired action.. 
//

// sends CC value 
void SendCC(byte CHAN, byte NR, byte VAL) {
  MIDI.sendControlChange(NR, VAL, CHAN);
  }

// Sends progchange command
void SendPP(byte CHAN, byte PRG) {
  MIDI.sendProgramChange(PRG, CHAN);
  }

// Sends NoteOn command 
void SendNoteOn(byte CHAN, byte NOTE, byte VEL) {
  MIDI.sendNoteOn(NOTE, VEL, CHAN);
  }

// Sends NoteOff command
void SendNoteOff(byte CHAN, byte NOTE, byte VEL) {
  MIDI.sendNoteOff(NOTE, VEL, CHAN);
}

// Sends Sysex message 
void SendSysEx(byte ARRAY, byte SIZE) {
  MIDI.sendSysEx(SIZE, ARRAY, true);
}

// Write text on the top line of the display
void WriteLCD(String TEXT) {
String CLRSTRING = "                     ";

lcd.setCursor(0,0);
lcd.print(CLRSTRING);
lcd.setCursor(0,0);
lcd.print(TEXT);  
}

//     Setup Routine
//#######################################################
void setup() {
    
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    lcd.begin(16, 1); 
    lcd.print("Midi Sample Code");
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    pinMode(buttonPin4, INPUT);
    
    MIDI.setHandleControlChange(SendCC);
    MIDI.setHandleProgramChange(SendPP);
    MIDI.setHandleNoteOn(SendNoteOn);
    MIDI.setHandleNoteOff(SendNoteOff);
    MIDI.setHandleSystemExclusive(SendSysEx);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    
    }

void loop() {
  // put your code here.
  // Midi messages are handled via the callback routines in the setup
  
 }
