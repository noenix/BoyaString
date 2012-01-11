/**
 * @author Ye Jiabin
 */

#ifndef IRRLICHTSYSTEM_H_
#define IRRLICHTSYSTEM_H_

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#define DEFAULT_SCREEN_WIDTH 960
#define DEFAULT_SCREEN_HEIGHT 540

/**
 * The system is implemented in singleton pattern.
 */
class IrrlichtSystem {
public:
	/**
	 * Gets the only instance of irrlicht system.
	 * @return the only instance of irrlicht system.
	 */
	static IrrlichtSystem* getInstance() {
		if (instance == 0) {
			instance = new IrrlichtSystem;
		}
		return instance;
	}

	/**
	 * Gets the irrlicht device.
	 * @return the irrlicht device instance.
	 */
	IrrlichtDevice* getDevice() const {
		return device;
	}

	/**
	 * Gets the controller factory instance.
	 * Currently, different controller kit is determined by pre-defined marco for
	 * easily debugging.
	 * @return the controller factory instance
	 */
	//IControllerFactory* getControllerFactory() const {
	//	return cf;
	//}
private:
	IrrlichtSystem() {
		device = createDevice(video::EDT_DIRECT3D9, 
			core::dimension2du(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT));
		device->setWindowCaption(L"≤Æ—¿÷Æœ“");
#ifdef USE_KINECT
#else 
		//cf = new MouseControllerFactory();
#endif
	}

	~IrrlichtSystem() {}

	IrrlichtDevice *device; /**< Irrlicht device */
	//IControllerFactory *cf;
	static IrrlichtSystem *instance;
};

IrrlichtSystem *IrrlichtSystem::instance = 0;

#endif
