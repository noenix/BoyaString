#ifndef ABSTRACTINSTRUMENT_H_
#define ABSTRACTINSTRUMENT_H_

class InstrumentScene;

class AbstractInstrument
{
public:
	AbstractInstrument(InstrumentScene *s);

	/**
	 * renders the scene calls by Instrument scene.
	 */
	virtual void render() = 0;

	virtual void play(void *note) = 0;

	virtual ~AbstractInstrument(void);

protected:
	InstrumentScene *scene;
};

#endif