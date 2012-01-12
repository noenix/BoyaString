#include <util/IrrlichtSystem.h>

#include <controller/IControllerFactory.h>

IrrlichtSystem *IrrlichtSystem::instance = 0;

IrrlichtSystem* IrrlichtSystem::getInstance() {
	if (instance == 0) {
		instance = new IrrlichtSystem;
	}
	return instance;
}

IControllerFactory* IrrlichtSystem::getControllerFactory() const {
	return cf;
}

IrrlichtSystem::IrrlichtSystem() {
	device = createDevice(video::EDT_DIRECT3D9, 
			core::dimension2du(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), 32);
	
		device->setWindowCaption(L"≤Æ—¿÷Æœ“");
#ifdef USE_KINECT
		cf = new KinectControllerFactory();
#else 
		cf = new MouseControllerFactory();
#endif
}

IrrlichtSystem::~IrrlichtSystem() {}
