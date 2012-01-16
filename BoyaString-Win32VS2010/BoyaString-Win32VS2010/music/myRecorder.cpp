#pragma comment(lib, "winmm.lib")
#include <fstream>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

#include <music/myRecorder.h>

myRecorder::myRecorder()
{
	start=timeGetTime();

	
	out.open("record.nex",ios::app|ios::binary|ios::out);
}

myRecorder::myRecorder(string filename,bool mode)
{
	start=timeGetTime();
	if(mode==1)
		out.open(filename.c_str(),ios::app|ios::binary|ios::out);
	else
		out.open(filename.c_str(),ios::trunc|ios::binary|ios::out);
}

void myRecorder::pushSound(float freq,int voice)
{

		end=timeGetTime();

	monoRecord record;

	record.interval=end-start;
	start=timeGetTime();
	record.freq=freq;
	record.voice=voice;
	out.write(reinterpret_cast<char*>(&record),sizeof(monoRecord));

	
}

void myRecorder::Replay(string filename)
{
	
	in.open(filename.c_str(),ios::binary);
	char* tmp=(char*)malloc(sizeof(monoRecord));
	player= mymidi::getInstance();
	player->setVolume(127);

	while(!in.eof())
	{
		in.read(tmp,sizeof(monoRecord));
		player->setVolume(127);
		monoRecord* record=reinterpret_cast<monoRecord*>(tmp);
		Sleep(record->interval);
		player->playSound(record->freq,record->voice);
	}
}

void myRecorder::close()
{
	out.close();
	in.close();
}

void myRecorder::Pause()
{
	pausePointer=in.tellg();
	player->forceStop();
}

void myRecorder::Continue()
{
	in.seekg(pausePointer,ios::beg);
	
	char* tmp=(char*)malloc(sizeof(monoRecord));
	player->setVolume(127);
	while(!in.eof())
	{
		in.read(tmp,sizeof(monoRecord));
		player->setVolume(127);
		monoRecord* record=reinterpret_cast<monoRecord*>(tmp);
		Sleep(record->interval);
		player->playSound(record->freq);
	}
}