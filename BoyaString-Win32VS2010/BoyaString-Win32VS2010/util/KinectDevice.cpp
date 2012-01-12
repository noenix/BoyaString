#include <util/KinectDevice.h>

#include <iostream>

KinectDevice *KinectDevice::instance = 0;
HANDLE KinectDevice::threadHandler = 0;
DWORD KinectDevice::threadRet = 0;
bool KinectDevice::isRun = 0;

KinectDevice::KinectDevice(void)
{
	this->isRun = false;
}

KinectDevice *KinectDevice::getInstance() {
	if (instance == 0) {
		instance = new KinectDevice();
	}
	return instance;
}

KinectDevice::~KinectDevice(void)
{
	close();
}

DWORD WINAPI KinectDevice::_startKinect(LPVOID param)
{
	while(1) {
		Sleep(500);
		std::cout << "aaaaa.\n";
	}
	return 0;
}

bool KinectDevice::start()
{
	if (isRun) {
		return false;
	} else {
		threadHandler = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            _startKinect,       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            &threadRet);   // returns the thread identifier 
		
		if (threadHandler == NULL) {
			return false;
		}
	}
	return true;
}

void KinectDevice::close()
{
	if (isRun) {
		isRun = false;
		CloseHandle(threadHandler);
	}
}
