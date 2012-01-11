/**
 * Defines abstract scene class.
 * @author Ye Jiabin
 */

#ifndef ABSTRACTSCENE_H_
#define ABSTRACTSCENE_H_

#include <config.h>
#include <util/IrrlichtSystem.hpp>


class AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	AbstractScene() {
		device = IrrlichtSystem::getInstance()->getDevice();
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();

		sSize = driver->getScreenSize();
	}

	/**
	 * Gets irrlicht devices.
	 * @return the device instance.
	 */
	//virtual IrrlichtDevice *getDevice() const 
	//{ return device; }

	/**
	 * display the scene, called by Bootstrap class.
	 * @return the next scene index for switching,
	 *         SCENE_COUNT if the programs ends
	 */
	virtual int display() = 0;

	/**
	 * clean the garbage of the scene.
	 */
	virtual void clean() = 0;

protected:
	IrrlichtDevice *device;
	ISceneManager *smgr;
	IVideoDriver *driver;
	core::dimension2du sSize; /**< Screen width and height */
};

//#include <controller/IControllerFactory.hpp>

#endif
