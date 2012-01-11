/**
 * Defines menu scene class.
 * @author Ye Jiabin
 */

#include <config.h>
#include <scene/AbstractScene.hpp>

#include <cmath>
#include <iostream>

#ifndef MENUSCENE_H_
#define MENUSCENE_H


enum menuitem_type {
	MIT_PLAY_INS,
	MIT_LEARN_INS,
	MIT_PLAY_MUSIC,
	MIT_OPTION,
	MIT_QUIT,
	MIT_COUNT
};

#define ANI_STEP 100
#define ANI_MASK 01 /** if var & ANI_MASK current state is in mask */
#define ANI_SWITCH_TO_NEXT 02


class MenuScene : public AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	MenuScene() : AbstractScene() {
		aniHandler.animationState = 0;
		aniHandler.animationStep = 0;
		currentMenu = 0;
	}

	/**
	 * The display method inherited from the base class.
	 * @see AbstractScene#display
	 */
	virtual int display() {
		_init();
		/**
		 * actually, not forever and nothing will last 
		 * forever even love.
		 */
		for ever {
			while (device->run()) {
				driver->beginScene(true, true, video::SColor(255,0,0,0));

				_animate();

				smgr->drawAll();
				driver->endScene();
			}
		}
		return SCN_COUNT;
	}

	/**
	 * switch to next menu.
	 * @param isNext determines whether or not switch to next menu item
	 */
	void switchTo(bool isNext) {
		if (!(ANI_MASK & aniHandler.animationState)) {
			aniHandler.animationState |= ANI_MASK;
			if (isNext) {
				aniHandler.animationState |= ANI_SWITCH_TO_NEXT;
			} else {
				aniHandler.animationState &= ~ANI_SWITCH_TO_NEXT;
			}
		}
	}

	virtual void clean() {
		return;
	}

private:
	IMeshSceneNode *menuItems[MIT_COUNT];
	ICameraSceneNode *camera;
	ILightSceneNode *gLight, *selectLight;
	float menuRadius;

	int currentMenu; /**< Currently selective menu. */
	
	struct animationHandler {
		u32 animationState; /**< The animation state of the scene @see ANI_MASK */
		u32 animationStep; /**< The animation step of scene */
		union increment {
			f32 radius;
		} inc; /**< Increment pixel of each step */
	} aniHandler;

	/**
	 * animation for menu state switching.
	 */
	void _animate() {
		if (ANI_MASK & aniHandler.animationState) {
			++aniHandler.animationStep;
			for (int i=0, j=currentMenu; i<MIT_COUNT; ++i, ++j) {
				float sign = ANI_SWITCH_TO_NEXT ? 1.0f : -1.0f;
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

	/**
	 * a private initialization method.
	 */
	void _init() {
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
};

#endif