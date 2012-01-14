#include "Bootstrap.h"

#include <scene/MenuScene.h>
#include <scene/InstrumentScene.h>

Bootstrap::Bootstrap(){
	device = IrrlichtSystem::getInstance()->getDevice();
	/**
	 * a ugly way to initialize the scene.
	 */
	scenes[SCN_MENU] = new MenuScene(); 
	scenes[SCN_INSTRUMENT] = new InstrumentScene(); 
}

void Bootstrap::go()  {
	cout << "hello world.\n";
	currentScene = *scenes;
	if (SCN_COUNT != 0) {
		for (int nextScene = 0; (nextScene = currentScene->display()) != SCN_COUNT;
			currentScene->clean(),currentScene = scenes[nextScene]) {
				IrrlichtSystem::getInstance()->showLoadingImg(true);
				IrrlichtSystem::getInstance()->getDevice()->getGUIEnvironment()->drawAll();
		}
		device->drop();
	}
}
