#include <controller/IControllerFactory.h>


AMenuController* MouseControllerFactory::getMenuController(MenuScene *scene) {
		 return new MouseMenuController(scene);
}

AMenuController* KinectControllerFactory::getMenuController(MenuScene *scene) {
		 return new KinectMenuController(scene);
}