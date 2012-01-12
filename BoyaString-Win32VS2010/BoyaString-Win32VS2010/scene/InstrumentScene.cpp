#include <scene/InstrumentScene.h>

#include <iostream>

InstrumentScene::InstrumentScene():AbstractScene() {
}

int InstrumentScene::display() {

	_init();

	//for ever {
		while (device->run()) {
			driver->beginScene(true, true, video::SColor(255,0,0,0));

			smgr->drawAll();
			driver->endScene();
		}
	//}
	return 0;
}

void InstrumentScene::clean() {

}

void InstrumentScene::_init() {

	/* Intializes the camera */
	camera = smgr->addCameraSceneNode(0, core::vector3df(0, 0,
		-static_cast<float>(this->sSize.Height >> 1)*1.33333333f ));
	camera->setAspectRatio(static_cast<float>(16.0/9.0));

	/* Layouts the instrument */ 
	ISceneNode *cube = smgr->addCubeSceneNode(75);
	cube->setMaterialTexture(0, driver->getTexture("res/pixel_yellow.png"));
	cube->setMaterialFlag(video::EMF_LIGHTING, false);
}