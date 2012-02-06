/**
 * Defines abstract scene class.
 * @author Ye Jiabin
 */

#ifndef ABSTRACTSCENE_H_
#define ABSTRACTSCENE_H_

#include <config.h>

#include <irrlicht.h>
//#include <controller/IControllerFactory.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	AbstractScene();

	/**
	 * Gets irrlicht devices.
	 * @return the device instance.
	 */
	inline virtual IrrlichtDevice* getDevice() const 
	{ return device; }
	
	/**
	 * Gets the scene id according to the enum type.
	 * @return the scene id.
	 */
	virtual int getSceneId() const = 0;

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

	/**
	 * Gets the screen size.
	 * @return the screen size.
	 */
	inline core::dimension2du getSize() const 
	{ return sSize; }

protected:
	IrrlichtDevice *device;
	ISceneManager *smgr;
	IVideoDriver *driver;
	core::dimension2du sSize; /**< Screen width and height */
};

//#include <controller/IControllerFactory.hpp>

//#include <scene/MenuScene.h>

#endif
