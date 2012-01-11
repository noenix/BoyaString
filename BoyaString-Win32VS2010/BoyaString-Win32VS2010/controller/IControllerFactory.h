/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */

#include <controller/AMenuController.hpp>

#ifndef ICONTROLLERFACTORY_H_
#define ICONTROLLERFACTORY_H_

class IControllerFactory {
public:
	virtual AMenuController* getMenuController(MenuScene *scene) = 0;
};

class MouseControllerFactory : IControllerFactory {
public:
	 inline AMenuController* getMenuController(MenuScene *scene) {
		 return new MouseMenuController(scene);
	 }
};


#endif
