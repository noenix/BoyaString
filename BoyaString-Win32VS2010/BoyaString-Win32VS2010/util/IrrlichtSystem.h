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

class IControllerFactory;

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
	 * Controlls the loading image.
	 * @param isShow true if show the loading image,
	 *        otherwise hide
	 */
	void showLoadingImg(bool isShow);

	/**
	 * Gets the controller factory instance.
	 * Currently, different controller kit is determined by pre-defined marco for
	 * easily debugging.
	 * @return the controller factory instance
	 */
	IControllerFactory* getControllerFactory() const;
private:
	IrrlichtSystem();

	~IrrlichtSystem();

	IGUIImage *loadingImg, *bgImg;

	IrrlichtDevice *device; /**< Irrlicht device */
	IControllerFactory *cf; /**< The abstract controller factory */
	static IrrlichtSystem *instance;
};


#endif
