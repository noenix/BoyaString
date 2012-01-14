#include <util/KinectDevice.h>
#include <util/IrrlichtSystem.h>

#include <iostream>
#include <MSR_NuiApi.h>

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

	IVideoDriver *driver =
		IrrlichtSystem::getInstance()->getDevice()->getVideoDriver();
	
	/**
	 * Assets that kinect is able to open after successfully
	 * tested some tiny seconds ago.
	 */
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON );
	
	while(1) {
		Sleep(500);
		
		;
		std::cout << "aaaaa.\n";
	}
	NuiShutdown();
	return 0;
}

bool KinectDevice::start()
{
	if (isRun) {
		return false;
	} else {
		/* test device open */
		if (NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON ) != S_OK) {
			return false;
		}
		NuiShutdown();

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
