#include <util/KinectDevice.h>
#include <util/IrrlichtSystem.h>

#include <iostream>
#include <MSR_NuiApi.h>
#include <util/IGestureStrategy.h>
#include <scene/AbstractScene.h>
#include <scene/MenuScene.h>
#include <scene/InstrumentScene.h>
#include <scene/InsBianZhong.h>

#define KINECT_MAX_X 2.2f
#define KINECT_MAX_Y 1.6f

KinectDevice *KinectDevice::instance = 0;
HANDLE KinectDevice::threadHandler = 0;
DWORD KinectDevice::threadRet = 0;
bool KinectDevice::isRun = 0;
IGestureStrategy *KinectDevice::strategy = 0;
int	KinectDevice::gesture = -1;
AbstractScene *KinectDevice::scene = 0;

KinectDevice::KinectDevice(void)
{
	this->isRun = false;
}

void KinectDevice::changeStrategy(IGestureStrategy *s) {
	this->strategy = s;
}

void KinectDevice::setScene(AbstractScene *s) {
	this->scene = s;
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
	NUI_SKELETON_FRAME localSkeletonFrame;
	/**
	 * Assets that kinect is able to open after successfully
	 * tested some tiny seconds ago.
	 */
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON );
	
	
	while(1) {
		NuiSkeletonGetNextFrame(static_cast<DWORD>(200), &localSkeletonFrame);
		if (strategy) {
			int i=0;
			for (; i<NUI_SKELETON_COUNT; i++) {
				if (localSkeletonFrame.SkeletonData[i].dwTrackingID != 0) {
					Vector4 rightPos = localSkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
					gesture = strategy->setPosition(localSkeletonFrame.SkeletonData[i].SkeletonPositions);
					if (gesture != NONE && scene != 0) {
						//TODO The following code block should be optimized!
						switch (scene->getSceneId()) {
						case SCN_MENU:

							switch (gesture) {
							case LEFT_HAND_R_TO_L_AND_RIGHT_HAND_L_TO_R_AND_OPEN_DOOR:
								dynamic_cast<MenuScene*>(scene)->enter();
								break;
							case RIGHT_HAND_L_TO_R:
								dynamic_cast<MenuScene*>(scene)->switchTo(true);
								break;
							case RIGHT_HAND_R_TO_L:
								dynamic_cast<MenuScene*>(scene)->switchTo(false);
								break;
						
							default:
								break;
							}

							break;
						case SCN_INSTRUMENT:
							//TODO not yet implemented
							//TODO currently only bianzhong is available
							{
								AbstractInstrument *instrument = dynamic_cast<InstrumentScene*>(scene)->getInstrument();
								core::dimension2du size = scene->getSize();
								f32 rW = static_cast<float>(size.Width)/KINECT_MAX_X;
								f32 rH = static_cast<float>(size.Height)/KINECT_MAX_Y;
								dynamic_cast<InsBianZhong*>(instrument)
									->setHammerPosition(vector3df(
									(rightPos.x+KINECT_MAX_X)*rW*1.35 - static_cast<float>(size.Width)*1.25 ,
							
									(rightPos.y+KINECT_MAX_Y)*rH - static_cast<float>(size.Height)*1.5,
									-20));
								std::cout << "fuck " << dynamic_cast<InsBianZhong*>(instrument)->getHammer()->getPosition().X << '\n';
								switch (gesture) {
								case KNOCK_RIGHT:
									dynamic_cast<InsBianZhong*>(instrument)->play(NULL);
									break;
								default:
									break;
								}
							}
							break;
						default:
							break;
						}
					}
					break;
				}
			}
			if (i >= NUI_SKELETON_COUNT) {
				gesture = -1;
				//TODO throw exception no body tracked
			}
		}
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
