#include <stdio.h>
#include <math.h>
using namespace std;

#include <music/mymidi.h>

mymidi *mymidi::instance = 0;

#define MIDIMSG(status,channel,data1,data2) ( (DWORD)((status<<4) | channel | (data1<<8) | (data2<<16)) )
double iRound (double n, int d)
{
  return (floor((n)*pow(10.0,(d))+0.5)/pow(10.0,(d)));
}


double iAbs (double a)
{
  if (a < 0)  return -a;
  return  a;
}

mymidi *mymidi::getInstance() {
	if (instance == 0) {
		instance = new mymidi();
	}
	return instance;
}

mymidi::mymidi()
{
	if (midiOutOpen(&hMidiOut,(UINT)-1,0,0,CALLBACK_NULL) == MMSYSERR_NOERROR) {
		opened = true;
	} else {
		opened = false; //TODO may throw exception here
	}
	Vol=127;
	Voice=14;

	Dura=1100;
}

mymidi::mymidi(int voice,int vol)
{
	Vol=vol;
midiOutOpen(&hMidiOut,(UINT)-1,0,0,CALLBACK_NULL);
	Voice=voice;
	Dura=1100;
}

int mymidi::playNote(int note)
{
	if (midiOutShortMsg(hMidiOut,(256*Voice)+192) != MMSYSERR_NOERROR) {
		return -1; //TODO exception handling
	}
	if (midiOutShortMsg(hMidiOut,(Vol*256+note)*256+144) != MMSYSERR_NOERROR) {
		return -1;
	}
	return 0;
}

int mymidi::playSound(float Freq)
{
	
	int Note = 0;
    int Phrase = 0;
	BYTE note=0x4c,velocity=0x40;

	//HMIDIOUT hMidi;
	//stop();
	//HMIDIOUT hMidiOut;
    
	midiOutShortMsg(hMidiOut,(256*Voice)+192);
	Note = (int)iRound((log(Freq)-log(440.0))/log(2.0)*12+69,0);
    Phrase = (Vol*256+Note)*256+144;
    midiOutShortMsg(hMidiOut,Phrase);
	 
	/*   midiOutShortMsg(hMidiOut,MIDIMSG(0x9,0x0,note,0));
	  midiOutShortMsg(hMidiOut,MIDIMSG(0x9,0x0,note,velocity));
    midiOutShortMsg(hMidi,(256*14)+192);
    // convert frequency to midi note
    Note = (int)iRound((log(150.0)-log(440.0))/log(2.0)*12+69,0);
    Phrase = (127*256+Note)*256+144;
    midiOutShortMsg(hMidi,Phrase);
    Sleep((int)(1100*(1/1+0.0001)));
    Phrase = (127*256+Note)*256+128;
    midiOutShortMsg(hMidi,Phrase);
	*/
   
	return 0;


}


int mymidi::playSound(float Freq,int type)
{
	
	int Note = 0;
    int Phrase = 0;
	BYTE note=0x4c,velocity=0x40;

	HMIDIOUT hMidi;
	//stop();
	//HMIDIOUT hMidiOut;
    
	midiOutShortMsg(hMidiOut,(256*type)+192);
	Note = (int)iRound((log(Freq)-log(440.0))/log(2.0)*12+69,0);
    Phrase = (Vol*256+Note)*256+144;
    midiOutShortMsg(hMidiOut,Phrase);
	 
	/*   midiOutShortMsg(hMidiOut,MIDIMSG(0x9,0x0,note,0));
	  midiOutShortMsg(hMidiOut,MIDIMSG(0x9,0x0,note,velocity));
    midiOutShortMsg(hMidi,(256*14)+192);
    // convert frequency to midi note
    Note = (int)iRound((log(150.0)-log(440.0))/log(2.0)*12+69,0);
    Phrase = (127*256+Note)*256+144;
    midiOutShortMsg(hMidi,Phrase);
    Sleep((int)(1100*(1/1+0.0001)));
    Phrase = (127*256+Note)*256+128;
    midiOutShortMsg(hMidi,Phrase);
	*/
   
	return 0;


}

int mymidi::stop()
{
	BYTE note=0x3C,velocity=0x40;
	midiOutShortMsg(hMidiOut,MIDIMSG(0x9,0x0,note,0));
	
	 return 0;
}

mymidi::~mymidi()
{
	 midiOutClose(hMidiOut);
}

int mymidi::forceStop()
{
	 midiOutClose(hMidiOut);
	 midiOutOpen(&hMidiOut,(UINT)-1,0,0,CALLBACK_NULL);
	 return 1;
}

void mymidi::closeDev()
{
	 if (midiOutClose(hMidiOut)== MMSYSERR_NOERROR) {
		 opened = false;
	 }
}

void mymidi::openDev()
{
	if (midiOutOpen(&hMidiOut,(UINT)-1,0,0,CALLBACK_NULL) == MMSYSERR_NOERROR) {
		opened = true;
	}
}
