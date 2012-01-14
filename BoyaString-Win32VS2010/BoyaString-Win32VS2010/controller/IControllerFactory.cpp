#include <controller/IControllerFactory.h>


AMenuController* MouseControllerFactory::getMenuController(MenuScene *scene) {
		 return new MouseMenuController(scene);
}

AMenuController* KinectControllerFactory::getMenuController(MenuScene *scene) {
		 return new KinectMenuController(scene);
}

AInstrumentController* MouseControllerFactory::getInstrumentController(InstrumentScene *scene)
{
	return new MouseInstrumentController(scene);
}

AInstrumentController* KinectControllerFactory::getInstrumentController(InstrumentScene *scene)
{
	return new KinectInstrumentController(scene);
}