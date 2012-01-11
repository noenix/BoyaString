/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */

#ifndef ICONTROLLERFACTORY_H_
#define ICONTROLLERFACTORY_H_

#include <controller/AMenuController.h>

//#include <controller/AMenuController.h>

class IControllerFactory {
public:
	virtual AMenuController* getMenuController(MenuScene *scene) = 0;
};

class MouseControllerFactory : public IControllerFactory {
public:
	  AMenuController* getMenuController(MenuScene *scene);
};




#endif
