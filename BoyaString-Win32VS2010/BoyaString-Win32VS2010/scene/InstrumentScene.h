/**
 * Instrument scene
 * @author Ye Jiabin
 */
#ifndef INSTRUMENTSCENE_H_
#define INSTRUMENTSCENE_H_

#include <scene/AbstractScene.h>

class AbstractInstrument;
class AInstrumentController;
class InsBianZhong;

class InstrumentScene : public AbstractScene {
public:
	/**
	 * Default constructor.
	 */
	InstrumentScene();

	/**
	 * The display method inherited from the base class.
	 * @see AbstractScene#display
	 */
	virtual int display(); 

	inline AbstractInstrument *getInstrument() const
	{ return instrument; }

	inline int getSceneId () const
	{ return SCN_INSTRUMENT; }
	
	/**
	 * The clean method inherited from the base class.
	 * @see AbstractScene#clean
	 */
	virtual void clean(); 

	friend class InsBianZhong;
	
private:
	ICameraSceneNode *camera; /**< The default camera node */

	AbstractInstrument *instrument;

	AInstrumentController *controller;

	ISceneNode *pauseButton;

	/**
	 * constances. 
	 */
	static const float pauseButtonSize;

	/**
	 * Intialize the scene.
	 */
	void _init();

};

#endif
