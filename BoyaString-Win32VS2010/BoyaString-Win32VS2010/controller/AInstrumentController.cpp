#include <controller/AInstrumentController.h>

#include <scene/InstrumentScene.h>

AInstrumentController::AInstrumentController(InstrumentScene *scene)
	:scene(scene)
{
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
}

bool MouseInstrumentController::OnEvent(const SEvent& event) {
	return false;
}
