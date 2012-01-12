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
	//for ever {
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
	//}
	return returnState & ~0x100;
}

void MenuScene::enter() {
	if (!(ANI_MASK & aniHandler.animationState)) {
		int sceneId[MIT_COUNT] = {SCN_INSTRUMENT,
			SCN_INSTRUMENT,SCN_INSTRUMENT,
			SCN_INSTRUMENT,SCN_INSTRUMENT};
		returnState = sceneId[currentMenu] |  0x100;
	}
}

void MenuScene::clean() {
	smgr->clear();
	
	//smgr->drawAll();
	driver->endScene();
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

			/* change current menu value. */
			if (ANI_SWITCH_TO_NEXT & aniHandler.animationState) {
				++currentMenu;
				currentMenu = currentMenu >= MIT_COUNT ? 0 : currentMenu;
			} else {
				--currentMenu;
				currentMenu = currentMenu < 0 ? MIT_COUNT - 1 : currentMenu;
			}
#ifdef _DEBUG
			std::cout << "current menu " << currentMenu << '\n';
#endif
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

	upLight = smgr->addLightSceneNode(0, vector3df(0, 50, -30.0));
	upLight->setRadius(1500.0);

	downLight = smgr->addLightSceneNode(0, vector3df(0, -50, -30.0));
	downLight->setRadius(1500.0);

	//TODO the detailed design of the scene should be done later
/*
	ITexture *gray = driver->getTexture("res/pixel_grey.png");
	ISceneNode *backWall =
	smgr->addMeshSceneNode(
		smgr->addHillPlaneMesh("plane", dimension2d<f32>(960 ,540), dimension2d<u32>(1,1)));
	backWall->setMaterialTexture(0, gray);
	backWall->setPosition(vector3df(0, -0, 2.2*menuRadius));
	backWall->setRotation(vector3df(-90.0, 0.0, 0.0));
	//plane->setMaterialFlag(video::EMF_LIGHTING, false

	ISceneNode *upWall =
	smgr->addMeshSceneNode(
		smgr->addHillPlaneMesh("plane1", dimension2d<f32>(960 ,2.2*menuRadius), dimension2d<u32>(1,1)));
	upWall->setMaterialTexture(0,gray);
	upWall->setPosition(vector3df(0, 270, 1.1*menuRadius));
	upWall->setRotation(vector3df(180.0, 00.0, 0.0));

	ISceneNode *downWall =
	smgr->addMeshSceneNode(
		smgr->addHillPlaneMesh("plane2", dimension2d<f32>(960 ,2.2*menuRadius), dimension2d<u32>(1,1)));
	downWall->setMaterialTexture(0, gray);
	downWall->setPosition(vector3df(0, -270, 1.1*menuRadius));
	
*/
	IMesh *jzMesh = smgr->getMesh("res/juanzhou/juanzhou.obj");
	for (int i=0; i<MIT_COUNT; ++i) {
		//TODO 
		//menuItems[i] = smgr->addCubeSceneNode(75);
		menuItems[i] = smgr->addEmptySceneNode();

		//ISceneNode *cube = smgr->addCubeSceneNode(75/20.0,menuItems[i]);
		ISceneNode *leftJz, *rightJz;
		leftJz = smgr->addMeshSceneNode(jzMesh, menuItems[i]);
		leftJz->setPosition(vector3df(-.8, 00, 0));
		rightJz = smgr->addMeshSceneNode(jzMesh, menuItems[i]);
		rightJz->setPosition(vector3df(.8, 00, 0));
		menuItems[i]->setRotation(vector3df(90.0, 0.0, 0.0));
		menuItems[i]->setScale(vector3df(20.0, 20.0, 20.0));

		/* 10 percent for margin */
		//menuItems[i]->setPosition(vector3df(static_cast<float>(w >> 1) - (.5+i)*(w*.9/MIT_COUNT), 0, 0));
		float radius = (.5f - i*2.0f/MIT_COUNT)*PI;
		menuItems[i]->setPosition(vector3df(std::cos(radius)*menuRadius, 0,
			(1.0f-std::sinf(radius))*menuRadius));
		std::cout << menuItems[i]->getPosition().X << ' ' << menuItems[i]->getPosition().Z << '\n';
		
		//cube->setMaterialTexture(0, driver->getTexture("res/pixel_yellow.png"));
		//cube->setMaterialFlag(video::EMF_LIGHTING, false);

		menuItems[i]->setMaterialType(video::EMT_LIGHTMAP);

	}
}
