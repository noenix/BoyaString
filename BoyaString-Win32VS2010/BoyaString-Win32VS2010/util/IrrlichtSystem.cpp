#include <util/IrrlichtSystem.h>

IrrlichtSystem *IrrlichtSystem::instance = 0;

IrrlichtSystem* IrrlichtSystem::getInstance() {
	if (instance == 0) {
		instance = new IrrlichtSystem;
	}
	return instance;
}

IrrlichtSystem::IrrlichtSystem() {
	device = createDevice(video::EDT_DIRECT3D9, 
			core::dimension2du(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT));
		device->setWindowCaption(L"≤Æ—¿÷Æœ“");
#ifdef USE_KINECT
#else 
		//cf = new MouseControllerFactory();
#endif
}

IrrlichtSystem::~IrrlichtSystem() {}
