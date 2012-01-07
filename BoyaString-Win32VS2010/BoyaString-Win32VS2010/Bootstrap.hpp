/**
 * The bootstap class that starts the program.
 * @author Ye Jiabin
 */

#include <iostream>
#include "scene\AbstractScene.hpp"
#include "util\IrrlichtSystem.hpp"

using std::cout;

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_

enum boya_scene {
	SCN_MENU,
	//TODO adds it later
	//SCN_INSTRUMENT,
	//SCN_THEATRE,
	SCN_COUNT
};

class Bootstrap {
public:
	Bootstrap() {
		device = IrrlichtSystem::getInstance()->getDevice();
	}

	/**
	 * the method starting the program.
	 */
	void go() {
		cout << "hello world.\n";
		while (device->run()) {
			device->getVideoDriver()->beginScene(true, true, video::SColor(255,0,0,0));
			device->getSceneManager()->drawAll();
            device->getVideoDriver()->endScene();
		}
		device->drop();
	}
private:
	AbstractScene *scenes[SCN_COUNT];
	IrrlichtDevice *device;
};

#endif

