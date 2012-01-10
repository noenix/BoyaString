/**
 * The bootstap class that starts the program.
 * @author Ye Jiabin
 */

#include <iostream>
#include "config.h"



using std::cout;

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_


#include <scene/MenuScene.hpp>
//#include <util/IrrlichtSystem.hpp>

class Bootstrap {
public:
	Bootstrap() {
		device = IrrlichtSystem::getInstance()->getDevice();
		/**
		 * a ugly way to initialize the scene.
		 */
		scenes[SCN_MENU] = new MenuScene(); 
	}

	/**
	 * the method starting the program.
	 */
	void go() {
		cout << "hello world.\n";
		currentScene = *scenes;
		if (SCN_COUNT != 0) {
			for (int nextScene = 0; (nextScene = currentScene->display()) != SCN_COUNT;
				currentScene->clean(),currentScene = scenes[nextScene]);
			device->drop();
		}
	}
private:
	AbstractScene *scenes[SCN_COUNT], *currentScene;
	IrrlichtDevice *device;
};

#endif

