#include <controller/AInstrumentController.h>

#include <util/IrrlichtSystem.h>

#include <scene/InstrumentScene.h>
#include <scene/InsBianZhong.h>

#include <iostream>

AInstrumentController::AInstrumentController(InstrumentScene *scene)
	:scene(scene)
{
}

void AInstrumentController::dominate()
{
	this->scene->getDevice()->setEventReceiver(this);
}

AInstrumentController::~AInstrumentController(void)
{
}

KinectInstrumentController::KinectInstrumentController(InstrumentScene *scene)
	:AInstrumentController(scene)
{
}

bool KinectInstrumentController::OnEvent(const SEvent& event)
{
	return false;
}

MouseInstrumentController::MouseInstrumentController(InstrumentScene *scene)
	:AInstrumentController(scene)
{
	driver = IrrlichtSystem::getInstance()->getDevice()->getVideoDriver();
}

bool MouseInstrumentController::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		//TODO currently only bianzhong is available
		u32 w = driver->getScreenSize().Width, h = driver->getScreenSize().Height;
		InsBianZhong* bz = dynamic_cast<InsBianZhong*>(scene->getInstrument());

#ifdef _DEBUG

		std::cout << "Pos " << event.MouseInput.X - (w >> 1)
			<< " : " << - event.MouseInput.Y + (h >> 1) << '\n';
#endif
		bz->setHammerPosition(
			vector3df(event.MouseInput.X - static_cast<float>(w >> 1),
			- event.MouseInput.Y + static_cast<float>(h >> 1), -80.0f));
	}
	return false;
}