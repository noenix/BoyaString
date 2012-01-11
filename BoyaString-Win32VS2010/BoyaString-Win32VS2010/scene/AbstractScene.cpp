#include <scene/AbstractScene.h>
#include <util/IrrlichtSystem.h>

AbstractScene::AbstractScene() {
	device = IrrlichtSystem::getInstance()->getDevice();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	sSize = driver->getScreenSize();
}

//MouseMenuController::MouseMenuController
