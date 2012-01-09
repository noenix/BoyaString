/**
 * Defines menu scene class.
 * @author Ye Jiabin
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H

#include <config.h>
#include <scene/AbstractScene.hpp>

class MenuScene : public AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	MenuScene() : AbstractScene() {
	}

	/**
	 * The display method inherited from the base class.
	 * @see AbstractScene#display
	 */
	virtual int display() {
		/**
		 * actually, not forever and nothing will last 
		 * forever even love.
		 */
		for ever {
			while (device->run()) {
				driver->beginScene(true, true, video::SColor(255,0,0,0));

				smgr->drawAll();
				driver->endScene();
			}
		}
		return SCN_COUNT;
	}

	virtual void clean() {
		return;
	}
};

#endif