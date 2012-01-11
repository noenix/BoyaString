#include "Bootstrap.h"

Bootstrap::Bootstrap(){
	device = IrrlichtSystem::getInstance()->getDevice();
	/**
	 * a ugly way to initialize the scene.
	 */
	scenes[SCN_MENU] = new MenuScene(); 
}

void Bootstrap::go()  {
	cout << "hello world.\n";
	currentScene = *scenes;
	if (SCN_COUNT != 0) {
		for (int nextScene = 0; (nextScene = currentScene->display()) != SCN_COUNT;
			currentScene->clean(),currentScene = scenes[nextScene]);
		device->drop();
	}
}
