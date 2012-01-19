#include <scene/MenuScene.h>
#include <scene/AbstractScene.h>
#include <util/IrrlichtSystem.h>
#include <controller/IControllerFactory.h>
#include <controller/AMenuController.h>

#define MTITLE_WIDTH 256.0f
#define MTITLE_HEIGHT 96.0f
#define MTITLE_XDIFF 540.0f
#define MTITLE_DEPTH 125.0f

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
			float currentStep = static_cast<float>(aniHandler.animationStep)/static_cast<float>(ANI_STEP);
			float radius = (.5f - (sign*currentStep+i)
				*2.0f/MIT_COUNT)*PI;;
			menuItems[j % MIT_COUNT]->setPosition(vector3df(std::cos(radius)*menuRadius, 0,
			(1.0f-std::sinf(radius))*menuRadius));
			menuTitle[j % MIT_COUNT]->setPosition(vector3df(
				-MTITLE_XDIFF*(i-sign*currentStep) +MTITLE_WIDTH - static_cast<float>(sSize.Width >> 1), 
				MTITLE_HEIGHT  - static_cast<float>(sSize.Height >> 1), (i-sign*currentStep)*MTITLE_DEPTH)
				);
		}
		if (aniHandler.animationStep >= ANI_STEP) {
			aniHandler.animationStep = 0;
			aniHandler.animationState &= ~ANI_MASK;

			/* change current menu value. */
			if (ANI_SWITCH_TO_NEXT & aniHandler.animationState) {
				menuTitle[currentMenu]->setPosition(vector3df(
				-MTITLE_XDIFF*(MIT_COUNT-1) +MTITLE_WIDTH - static_cast<float>(sSize.Width >> 1), 
				MTITLE_HEIGHT  - static_cast<float>(sSize.Height >> 1), (MIT_COUNT-1)*MTITLE_DEPTH)
				);
				++currentMenu;
				currentMenu = currentMenu >= MIT_COUNT ? 0 : currentMenu;
			} else {
				menuTitle[(currentMenu + MIT_COUNT -1) % MIT_COUNT]->setPosition(vector3df(
				-MTITLE_XDIFF*(0) +MTITLE_WIDTH - static_cast<float>(sSize.Width >> 1), 
				MTITLE_HEIGHT  - static_cast<float>(sSize.Height >> 1), (0)*MTITLE_DEPTH)
				);
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

	//smgr->setAmbientLight(SColor(1.0, 1.0, 0.0, 0.0))

	upLight = smgr->addLightSceneNode(0, vector3df(0, 50, -30.0));
	upLight->setRadius(1500.0);

	downLight = smgr->addLightSceneNode(0, vector3df(0, -50, -30.0));
	downLight->setRadius(1500.0);


	IMesh *jzMesh = smgr->getMesh("res/juanzhou/juanzhou.obj");
	IMesh *paperMesh = smgr->addHillPlaneMesh("paper", 
			dimension2df(1.0f, 8.0f),  dimension2du(1, 1));
	for (int i=0; i<MIT_COUNT; ++i) {
		//TODO 
		//menuItems[i] = smgr->addCubeSceneNode(75);
		menuItems[i] = smgr->addEmptySceneNode();

		//ISceneNode *cube = smgr->addCubeSceneNode(75/20.0,menuItems[i]);
		ISceneNode *leftJz, *rightJz, *paper;
		leftJz = smgr->addMeshSceneNode(jzMesh, menuItems[i]);
		leftJz->setPosition(vector3df(-.8, 00, 0));
		rightJz = smgr->addMeshSceneNode(jzMesh, menuItems[i]);
		rightJz->setPosition(vector3df(.8, 00, 0));
		paper = smgr->addMeshSceneNode(paperMesh, menuItems[i]);
		//paper->setMaterialFlag(video::EMF_LIGHTING, false);
		paper->setRotation(vector3df(-180, 0, 0));
		paper->setMaterialTexture(0, driver->getTexture("res/pixel_white.png"));

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

		//menuItems[i]->setMaterialType(video::EMT_LIGHTMAP);

		/* also set menu title */
		menuTitle[i] = smgr->addMeshSceneNode(smgr->addHillPlaneMesh("plane", dimension2df(MTITLE_WIDTH, MTITLE_HEIGHT),  dimension2du(1, 1)));
	//	menuTitle[i]->setMaterialFlag(video::EMF_LIGHTING, false);
		menuTitle[i]->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		
		std::string menuTitleFileName("res/menuTitle");
		menuTitleFileName.push_back('1' + i); //CAUTION! menu items will never exceeds NINE
		menuTitleFileName += ".png";

		menuTitle[i]->setMaterialTexture(0, driver->getTexture(menuTitleFileName.c_str()));
		//menuTitle[i]->getMaterial(0).AmbientColor = SColor(100, 255, 255, 255);
		//menuTitle[i]->setMaterialTexture(0, driver->getTexture("res/pixel_white.png"));
		menuTitle[i]->setPosition(vector3df(-MTITLE_XDIFF*i +MTITLE_WIDTH - static_cast<float>(sSize.Width >> 1), 
			 MTITLE_HEIGHT  - static_cast<float>(sSize.Height >> 1), i*MTITLE_DEPTH));
		menuTitle[i]->setRotation(vector3df(-90.0f,  0.0f, 0.f));

	}
}
