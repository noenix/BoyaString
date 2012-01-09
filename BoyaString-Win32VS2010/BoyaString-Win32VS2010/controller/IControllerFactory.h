/**
 * The abstracy controller for our program.
 * @author Ye Jiabin
 */

#ifndef ICONTROLLERFACTORY_H_
#define ICONTROLLERFACTORY_H_

#include <scene/MenuScene.hpp>
#include "AMenuController.hpp"

class IControllerFactory {
public:
	virtual AMenuController* getMenuController(MenuScene *scene) = 0;
};

class MouseControllerFactory : IControllerFactor {
public:
	 AMenuController* getMenuController(MenuScene *scene) {

	 }
};

#endif
