/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */

#ifndef ICONTROLLERFACTORY_H_
#define ICONTROLLERFACTORY_H_

#include <controller/AMenuController.hpp>

class IControllerFactory {
public:
	virtual AMenuController* getMenuController(MenuScene *scene) = 0;
};

class MouseControllerFactory : IControllerFactory {
public:
	 AMenuController* getMenuController(MenuScene *scene) {
		 return new MouseMenuController(scene);
	 }
};


#endif
