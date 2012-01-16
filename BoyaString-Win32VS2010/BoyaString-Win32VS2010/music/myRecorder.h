#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>
using namespace std;

#include <music/mymidi.h>

struct monoRecord
{
	int voice;
	int interval;
	float freq;
};

class myRecorder
{
public:
	myRecorder();
	myRecorder(string filename,bool mode);	//1 for app, 0 for trunc 
											//如果只是回放请使用app
	void close();
	void pushSound(float freq,int voice);	//voice=14 编钟
	void Replay(string filename);
	void Pause();
	void Continue();
	void Stop();

private:
	DWORD start,end;
	mymidi* player;
	ofstream out;
	ifstream in;
	off_t pausePointer;	//tell the position when pause

};
