#ifndef INSBIANZHONG_H_
#define INSBIANZHONG_H_

#include <scene/AbstractInstrument.h>

class InsBianZhong :
	public AbstractInstrument
{
public:
	InsBianZhong(InstrumentScene *s);

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

};

#endif
