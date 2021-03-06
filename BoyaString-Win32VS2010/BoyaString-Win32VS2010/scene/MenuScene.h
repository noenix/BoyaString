/**
 * Defines menu scene class.
 * @author Ye Jiabin
 */



#ifndef MENUSCENE_H_
#define MENUSCENE_H

#include <config.h>
#include <cmath>
#include <iostream>

class AbstractScene;
class AMenuController;

#include <scene/AbstractScene.h>

enum menuitem_type {
	MIT_PLAY_INS,
	MIT_LEARN_INS,
	MIT_PLAY_MUSIC,
	MIT_OPTION,
	MIT_QUIT,
	MIT_COUNT
};

#define ANI_STEP 200
#define ANI_MASK 01 /** if var & ANI_MASK current state is in mask */
#define ANI_SWITCH_TO_NEXT 02


class MenuScene : public AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	MenuScene();

	/**
	 * The display method inherited from the base class.
	 * @see AbstractScene#display
	 */
	virtual int display(); 

	/**
	 * Switches to next menu.
	 * @param isNext determines whether or not switch to next menu item
	 */
	void switchTo(bool isNext) ;

	inline int getSceneId () const
	{ return SCN_MENU; }

	/**
	 * Enters to a particular menu.
	 */
	void enter();

	void clean();

private:
	ISceneNode *menuItems[MIT_COUNT]; /* scene node for menu items */
	ISceneNode *menuTitle[MIT_COUNT]; /* scene node for menu title */

	ISceneNode *backWall, *upWall, *downWall, *leftWall, *rightWall;
	ICameraSceneNode *camera;
	ILightSceneNode *mtLight; /**< menu title scene node */
	ILightSceneNode *upLight, *downLight;
	float menuRadius;

	int currentMenu; /**< Currently selective menu. */
	int returnState;

	AMenuController *controller;
	
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
	void _animate();

	/**
	 * a private initialization method.
	 */
	void _init();
};

#endif