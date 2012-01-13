#include <scene/InsBianZhong.h>
#include <scene/InstrumentScene.h>

InsBianZhong::InsBianZhong(InstrumentScene *s) :
	AbstractInstrument(s)
{
}

void InsBianZhong::init() {
	ISceneManager *smgr = scene->smgr;
	IVideoDriver *driver = scene->driver;
	u32 w = scene->sSize.Width, h = scene->sSize.Height;
	
	IMesh *meshBZ = smgr->getMesh("res/instrument/zhong.obj");
	for (int i=0; i<BZ_COUNT; ++i) {
		bianZhong[i] = smgr->addMeshSceneNode(meshBZ);
		if (bianZhong[i] == 0) {
			break; //TODO Throw some exception here
		}
		bianZhong[i]->setPosition(vector3df(-static_cast<float>(w >> 1) + static_cast<float>((.5f+i)*w)/BZ_COUNT, 0, 0));
		bianZhong[i]->setScale(vector3df(8.0f+i, 8.0f+i, 8.0f+i));
	}

	light = smgr->addLightSceneNode(0, vector3df(-static_cast<float>(w >> 1), static_cast<float>(h >> 1), -150));
	smgr->addLightSceneNode(0, vector3df(static_cast<float>(w >> 1), static_cast<float>(h >> 1), -150));
	light->setRadius(1000.0);
}

void InsBianZhong::render()
{
}

void InsBianZhong::play(void *note) 
{
}

InsBianZhong::~InsBianZhong(void)
{
}
