#include <util/IrrlichtSystem.h>

#include <controller/IControllerFactory.h>

IrrlichtSystem *IrrlichtSystem::instance = 0;

IrrlichtSystem* IrrlichtSystem::getInstance() {
	if (instance == 0) {
		instance = new IrrlichtSystem;
	}
	return instance;
}

IControllerFactory* IrrlichtSystem::getControllerFactory() const {
	return cf;
}

IrrlichtSystem::IrrlichtSystem() {
	device = createDevice(video::EDT_DIRECT3D9, 
			core::dimension2du(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), 32);
	device->setWindowCaption(L"²®ÑÀÖ®ÏÒ");

	u32 w = device->getVideoDriver()->getScreenSize().Width,
		h = device->getVideoDriver()->getScreenSize().Height;

	bgImg = device->getGUIEnvironment()->addImage(rect<s32>(0, 0, w, h));
	bgImg->setImage(device->getVideoDriver()->getTexture("res/pixel_white.png"));
	bgImg->setScaleImage(true);

	ITexture *loadingTexture = device->getVideoDriver()->getTexture("res/loading.png");
	loadingImg = device->getGUIEnvironment()->addImage(
		loadingTexture,vector2d<s32>((w - loadingTexture->getSize().Width) >> 1,
		(h - loadingTexture->getSize().Height) >> 1));

	
	this->showLoadingImg(false);

		
#ifdef USE_KINECT
		cf = new KinectControllerFactory();
#else 
		cf = new MouseControllerFactory();
#endif
}

IrrlichtSystem::~IrrlichtSystem() {}

void IrrlichtSystem::showLoadingImg(bool isShow)
{
	loadingImg->setVisible(isShow);
	bgImg->setVisible(isShow);
}
