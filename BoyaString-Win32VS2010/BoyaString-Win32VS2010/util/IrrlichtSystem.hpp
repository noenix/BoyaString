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

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

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
	IrrlichtDevice* getDevice() {
		return device;
	}

private:
	IrrlichtSystem() {
		device = createDevice(video::EDT_DIRECT3D9, 
			core::dimension2du(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT));
	}
	~IrrlichtSystem() {}

	IrrlichtDevice *device; /**< Irrlicht device */
	static IrrlichtSystem *instance;
};

IrrlichtSystem *IrrlichtSystem::instance = 0;

#endif
