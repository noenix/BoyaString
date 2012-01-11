#include <controller/AMenuController.h>

#include <scene/AbstractScene.h>
#include <scene/MenuScene.h>

AMenuController::AMenuController(MenuScene *scene):IEventReceiver() {
	this->scene = scene;
}

MouseMenuController::MouseMenuController(MenuScene *scene):AMenuController(scene){}

bool MouseMenuController::OnEvent(const SEvent& event) {
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
	return false;
}