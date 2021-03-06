/**
 * The abstracy instrument controller for our program.
 * @author Ye Jiabin
 */

#ifndef AINSTRUMENTCONTROLLER_H_
#define AINSTRUMENTCONTROLLER_H_

#include <irrlicht.h>
//#include <scene/AbstractScene.h>
//#include <scene/MenuScene.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
 
class InstrumentScene;

class AInstrumentController : public IEventReceiver
{
public:
	AInstrumentController(InstrumentScene *scene);

	/**
	 * Makes this controller as event listener.
	 */
	virtual void dominate();

	virtual ~AInstrumentController(void);
protected:
	InstrumentScene *scene;
};

class KinectInstrumentController : public AInstrumentController
{
public:
	KinectInstrumentController(InstrumentScene *scene);

	/**
	 * Implements the base class.
	 * @param event event object passed into method
	 * @return false why 'false' is returned.
	 */
	virtual bool OnEvent(const SEvent& event);

	void dominate();
};

class MouseInstrumentController : public AInstrumentController
{
public:
	MouseInstrumentController(InstrumentScene *scene);

	/**
	 * Implements the base class.
	 * @param event event object passed into method
	 * @return false why 'false' is returned.
	 */
	virtual bool OnEvent(const SEvent& event);
private:
	IVideoDriver *driver;
};

#endif
