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
	BZ_C4,
	BZ_D4,
	BZ_E4,
	BZ_G4,
	BZ_A4,
	BZ_B4,
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
	 * Sets hammer position.
	 */
	void setHammerPosition(const vector3df& position);

	/**
	 * Implements base class method.
	 * @see AbstractInstrument#play
	 */
	void play(void *note);

	virtual ~InsBianZhong(void);
private:
	IMeshSceneNode *bianZhong[BZ_COUNT]; /**< A set of bianzhongs. */
	IMeshSceneNode *hammer; /**< The hammer to beat bianzhong. */
	ILightSceneNode *light;

	/**
	 * Gets the specific x-coordinate of a bianzhong.
	 * @param idx the index of a bianzhong.
	 * @return the x-corrdinate.
	 */
	float _getPositionX(int idx);
};

#endif
