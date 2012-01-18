#include <scene/InstrumentScene.h>

#include <iostream>
#include <util/IrrlichtSystem.h>
#include <scene/AbstractInstrument.h>
#include <scene/InsBianZhong.h>
#include <controller/IControllerFactory.h>

const float InstrumentScene::pauseButtonSize = 60.0f;

InstrumentScene::InstrumentScene():AbstractScene() {
	instrument = 0;
	controller = 0;
	pauseButton = 0;
}

int InstrumentScene::display() {

	_init();

	//for ever {
		while (device->run()) {
			driver->beginScene(true, true, video::SColor(255,0,0,0));

			instrument->render();

			smgr->drawAll();
			driver->endScene();
		}
	//}
	return 0;
}

void InstrumentScene::clean() {

}

void InstrumentScene::_init() {
	if (!controller) {
		controller = IrrlichtSystem::getInstance()
			->getControllerFactory()->getInstrumentController(this);
	}
	controller->dominate();

	instrument = new InsBianZhong(this);
	instrument->init();

	pauseButton = smgr->addCubeSceneNode(pauseButtonSize);
	pauseButton->setMaterialTexture(0, driver->getTexture("res/pause_button.png"));
	pauseButton->setMaterialFlag(video::EMF_LIGHTING, false);
	pauseButton->setPosition(vector3df(-static_cast<float>((this->sSize.Width>>1) - pauseButtonSize),
		-static_cast<float>((this->sSize.Height>>1) - pauseButtonSize), 0));
	pauseButton->addAnimator(smgr->createRotationAnimator(vector3df(0, .5f, .0f)));

	/* Intializes the camera */
	camera = smgr->addCameraSceneNode(0, core::vector3df(0, 0,
		-static_cast<float>(this->sSize.Height >> 1)*1.33333333f ));
	camera->setAspectRatio(static_cast<float>(16.0/9.0));

	IrrlichtSystem::getInstance()->showLoadingImg(false);
	/* Layouts the instrument */ 
	/*
	ISceneNode *cube = smgr->addCubeSceneNode(75);
	cube->setMaterialTexture(0, driver->getTexture("res/pixel_yellow.png"));
	cube->setMaterialFlag(video::EMF_LIGHTING, false);
	*/
}