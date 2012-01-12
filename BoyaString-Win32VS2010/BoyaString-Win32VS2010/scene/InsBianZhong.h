#ifndef INSBIANZHONG_H_
#define INSBIANZHONG_H_

#include <scene/AbstractInstrument.h>
#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum bianZhongType {
	BZ_COUNT
};

class InsBianZhong :
	public AbstractInstrument
{
public:
	InsBianZhong(InstrumentScene *s);

	void init();

	/**
	 * Implements base class method.
	 * @see AbstractInstrument#render
	 */
	virtual void render();

	/**
	 * Implements base class method.
	 * @see AbstractInstrument#play
	 */
	void play(void *note);

	virtual ~InsBianZhong(void);
private:
	ISceneNode *bianZhong;
};

#endif
