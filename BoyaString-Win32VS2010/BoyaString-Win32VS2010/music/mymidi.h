#pragma comment(lib, "winmm.lib")
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

#define SNDQUE 10000

class mymidi
{
public:
	
	static mymidi *getInstance();

	//播放声音
	//para: Freq=音调
	int playSound(float Freq); 
	int playNote(int note);
	int playSound(float Freq,int type); //type 乐器类型..
	int stop();
	//调节音量
	void setVolume(int vol){if(vol<128&&vol>0)Vol=vol; else Vol=127;}
	void setVoice(int voice){Voice=voice;}
	int getVoice()	{	return Voice;}
	int forceStop();
	void closeDev();	//just close midi device and release resource
	void openDev();		//reopen the midi device
	inline bool isOpen() const 
	{ return opened; }
private:
	static mymidi *instance;

	mymidi();
	mymidi(int voice,int vol );
	virtual ~mymidi();

	bool opened;
	int Vol;
	int Voice;
	int Dura;

	HMIDIOUT hMidiOut;
};