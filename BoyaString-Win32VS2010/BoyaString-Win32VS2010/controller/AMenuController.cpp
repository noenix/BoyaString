#include <controller/AMenuController.h>

#include <iostream>

#include <scene/AbstractScene.h>
#include <scene/MenuScene.h>

#include <util/KinectDevice.h>
#include <util/IGestureStrategy.h>

AMenuController::AMenuController(MenuScene *scene):IEventReceiver() {
	this->scene = scene;
}

void AMenuController::dominate() {
	this->scene->getDevice()->setEventReceiver(this);
}

MouseMenuController::MouseMenuController(MenuScene *scene):AMenuController(scene){}

bool MouseMenuController::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		switch(event.KeyInput.Key) {
		case KEY_LEFT:
#ifdef _DEBUG
			std::cout << "LEFT.\n";
#endif
			scene->switchTo(false);
			break;
		case KEY_RIGHT:
#ifdef _DEBUG
			std::cout << "RIGHT.\n";
#endif
			scene->switchTo(true);
			break;
		case irr::KEY_RETURN:
#ifdef _DEBUG
			std::cout << "ENTER.\n";
#endif
			scene->enter();
			break;
		default:
			break;
		}
	}
	return false;
}

KinectMenuController::KinectMenuController(MenuScene *scene):AMenuController(scene){}


bool KinectMenuController::OnEvent(const SEvent& event) {
	return false;
}

void KinectMenuController::dominate() {
	MenuGestureStrategy *s = new MenuGestureStrategy();
	s->setInterval(200);
	KinectDevice::getInstance()->changeStrategy(s);
	KinectDevice::getInstance()->setScene(scene);
	KinectDevice::getInstance()->start();

	this->scene->getDevice()->setEventReceiver(this);
}
