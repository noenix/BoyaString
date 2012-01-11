/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */
#include <scene/MenuScene.hpp>

#ifndef AMENUCONTROLLER_H_
#define AMENUCONTROLLER_H_

/**
 * Abstract menu controller.
 */
class AMenuController : public IEventReceiver{
public:
	AMenuController(MenuScene *scene) {
		this->scene = scene;
	}

	/**
	 * Makes this controller as event listener.
	 */
	virtual void dominate() {
		
		//this->scene->getDevice();
		//->setEventReceiver(this);
	}
protected:
	MenuScene *scene;
};

/**
 * The menu controller for mouse.
 */
class MouseMenuController : public AMenuController {
public:
	MouseMenuController(MenuScene *scene):AMenuController(scene) {
	}

	/**
	 * Implements the base class.
	 * @param event event object passed into method
	 * @return false why 'false' is returned.
	 */
	virtual bool OnEvent(const SEvent& event) {
		if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
			switch(event.KeyInput.Key) {
			case KEY_LEFT:
				scene->switchTo(false);
				break;
			case KEY_RIGHT:
				scene->switchTo(true);
				break;
			default:
				break;
			}
		}
	}
};



#endif
