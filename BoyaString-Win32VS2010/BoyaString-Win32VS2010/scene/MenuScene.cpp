#include <scene/MenuScene.h>
#include <scene/AbstractScene.h>
#include <util/IrrlichtSystem.h>
#include <controller/IControllerFactory.h>
#include <controller/AMenuController.h>

MenuScene::MenuScene() : AbstractScene() {
	aniHandler.animationState = 0;
	aniHandler.animationStep = 0;
	currentMenu = 0;
	controller = 0;
}

int MenuScene::display() {
	_init();
	/**
		* actually, not forever and nothing will last 
		* forever even love.
		*/
	for ever {
		while (device->run()) {
			driver->beginScene(true, true, video::SColor(255,0,0,0));

			if (!returnState) {
				_animate();
			} else {
				break;
			}

			smgr->drawAll();
			driver->endScene();
		}
	}
	return SCN_COUNT;
}

void MenuScene::enter() {
	if (!(ANI_MASK & aniHandler.animationState)) {
		returnState = currentMenu |  0x100;
	}
}

void MenuScene::clean() {
}

void MenuScene::switchTo(bool isNext) {
	if (!(ANI_MASK & aniHandler.animationState)) {
		aniHandler.animationState |= ANI_MASK;
		if (isNext) {
			aniHandler.animationState |= ANI_SWITCH_TO_NEXT;
		} else {
			aniHandler.animationState &= ~ANI_SWITCH_TO_NEXT;
		}
	}
}

void MenuScene::_animate() {
	if (ANI_MASK & aniHandler.animationState) {
		++aniHandler.animationStep;
		for (int i=0, j=currentMenu; i<MIT_COUNT; ++i, ++j) {
			float sign = ANI_SWITCH_TO_NEXT & aniHandler.animationState ? 1.0f : -1.0f;
			float radius = (.5f - (sign*static_cast<float>(aniHandler.animationStep)/static_cast<float>(ANI_STEP)+i)
				*2.0f/MIT_COUNT)*PI;;
			menuItems[j % MIT_COUNT]->setPosition(vector3df(std::cos(radius)*menuRadius, 0,
			(1.0f-std::sinf(radius))*menuRadius));
		}
		if (aniHandler.animationStep >= ANI_STEP) {
			aniHandler.animationStep = 0;
			aniHandler.animationState &= ~ANI_MASK;
		}
	}
}

void MenuScene::_init() {

	returnState = 0;
	/* initialize the controller */
	if (!controller) {
		controller = IrrlichtSystem::getInstance()
			->getControllerFactory()->getMenuController(this);
	}
	controller->dominate();

	/* TODO temporarily adds some basic mesh */
	u32 w = this->sSize.Width, h = this->sSize.Height ; 
	menuRadius = 300.0;
	camera = smgr->addCameraSceneNode(0, core::vector3df(0, 0,
		-static_cast<float>(this->sSize.Height >> 1)*1.33333333f ));
	camera->setAspectRatio(static_cast<float>(16.0/9.0));

	//smgr->setAmbientLight(SColor(1.0, 1.0, 0.0, 0.0));
	gLight = smgr->addLightSceneNode(0, vector3df(-static_cast<float>(w >> 1), static_cast<float>(h >> 1), -100.0));
	gLight->setRadius(1200.0);
	gLight->setVisible(false);

	selectLight = smgr->addLightSceneNode(0, vector3df(0, 80, -300.0));
	selectLight->setRadius(700.0);

	
	for (int i=0; i<MIT_COUNT; ++i) {
		menuItems[i] = smgr->addCubeSceneNode(75);
		/* 10 percent for margin */
		//menuItems[i]->setPosition(vector3df(static_cast<float>(w >> 1) - (.5+i)*(w*.9/MIT_COUNT), 0, 0));
		float radius = (.5f - i*2.0f/MIT_COUNT)*PI;
		menuItems[i]->setPosition(vector3df(std::cos(radius)*menuRadius, 0,
			(1.0f-std::sinf(radius))*menuRadius));
		std::cout << menuItems[i]->getPosition().X << ' ' << menuItems[i]->getPosition().Z << '\n';
		menuItems[i]->setMaterialTexture(0, driver->getTexture("res/pixel_yellow.png"));
		//menuItems[i]->setMaterialFlag(video::EMF_LIGHTING, false);

	}
}
