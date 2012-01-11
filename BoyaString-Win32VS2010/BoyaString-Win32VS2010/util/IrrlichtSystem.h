/**
 * @author Ye Jiabin
 */

#ifndef IRRLICHTSYSTEM_H_
#define IRRLICHTSYSTEM_H_

#include <irrlicht.h>
#include <controller/IControllerFactory.h>

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
	static IrrlichtSystem* getInstance();

	/**
	 * Gets the irrlicht device.
	 * @return the irrlicht device instance.
	 */
	inline IrrlichtDevice* getDevice() const {
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
	IrrlichtSystem();

	~IrrlichtSystem();

	IrrlichtDevice *device; /**< Irrlicht device */
	//IControllerFactory *cf;
	static IrrlichtSystem *instance;
};


#endif
