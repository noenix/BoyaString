/**
 * The bootstap class that starts the program.
 * @author Ye Jiabin
 */



#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_

#include <iostream>
#include "config.h"

using std::cout;

#include <scene/AbstractScene.h>
#include <scene/MenuScene.h>
#include <util/IrrlichtSystem.h>
//#include <controller/IControllerFactory.h>

class Bootstrap {
public:
	Bootstrap() ;

	/**
	 * the method starting the program.
	 */
	void go();
private:
	AbstractScene *scenes[SCN_COUNT], *currentScene;
	IrrlichtDevice *device;
};

#endif

