/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */

#ifndef AMENUCONTROLLER_H_
#define AMENUCONTROLLER_H_

#include <irrlicht.h>
//#include <scene/AbstractScene.h>
//#include <scene/MenuScene.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AbstractScene;
class MenuScene;

/**
 * Abstract menu controller.
 */
class AMenuController : public IEventReceiver{
public:
	AMenuController(MenuScene *scene);

	/**
	 * Makes this controller as event listener.
	 */
	virtual void dominate();

protected:
	MenuScene *scene;
};

/**
 * The menu controller for mouse.
 */
class MouseMenuController : public AMenuController {
public:
	MouseMenuController(MenuScene *scene);

	/**
	 * Implements the base class.
	 * @param event event object passed into method
	 * @return false why 'false' is returned.
	 */
	virtual bool OnEvent(const SEvent& event);
};

class KinectMenuController : public AMenuController {
public:
	KinectMenuController(MenuScene *scene);

	/**
	 * Implements the base class.
	 * @param event event object passed into method
	 * @return false why 'false' is returned.
	 */
	virtual bool OnEvent(const SEvent& event);

	void dominate();
};

#endif
