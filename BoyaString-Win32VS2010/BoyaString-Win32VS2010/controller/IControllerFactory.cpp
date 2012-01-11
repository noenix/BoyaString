#include <controller/IControllerFactory.h>


AMenuController* MouseControllerFactory::getMenuController(MenuScene *scene) {
		 return new MouseMenuController(0);
}