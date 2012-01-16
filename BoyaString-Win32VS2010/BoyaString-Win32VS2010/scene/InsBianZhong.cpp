#include <scene/InsBianZhong.h>
#include <scene/InstrumentScene.h>
#include <music/mymidi.h>

#include <iostream>
#include <cmath>

#define MAX_STRENGTH 20.0f
#define BZ_PERIOD 12 /*< steps per period **/

const InsBianZhong::bz_info InsBianZhong::bzInfos[BZ_COUNT] = {
	{71}, {69}, {67}, {64}, {62}, {60}
};

InsBianZhong::InsBianZhong(InstrumentScene *s) :
	AbstractInstrument(s)
{
	soundSrc = 0;
	for (int i=0; i<BZ_COUNT; ++i) {
		playState[i].keyOn = playState[i].sideOn = false;
		playState[i].remain = 0;
	}
}

void InsBianZhong::init() {
	ISceneManager *smgr = scene->smgr;
	IVideoDriver *driver = scene->driver;
	u32 w = scene->sSize.Width, h = scene->sSize.Height;
	if (soundSrc == 0) {
		soundSrc = mymidi::getInstance();
	}
	if (!soundSrc->isOpen()) {
		std::cerr << "Can not open MIDI device.\n";
		//TODO throws an error here
	}

	IMesh *meshBZ = smgr->getMesh("res/instrument/zhong.obj");
	float yDiff = 7.5f;

	for (int i=0; i<BZ_COUNT; ++i) {
		bianZhong[i] = smgr->addMeshSceneNode(meshBZ);
		if (bianZhong[i] == 0) {
			break; //TODO Throw some exception here
		}
		bianZhong[i]->setPosition(vector3df(_getPositionX(i), (BZ_COUNT-1-i)*yDiff, 0));
		bianZhong[i]->setScale(vector3df(8.0f+i, 8.0f+i, 8.0f+i));
	}

	hammer = smgr->addMeshSceneNode(smgr->getMesh("res/instrument/chui.obj"));
	hammer->setScale(vector3df(25.0f, 25.0f, 25.0f));
	hammer->setRotation(vector3df(-90.0f, 0, 0));
	hammer->setMaterialFlag(video::EMF_LIGHTING, false);
	hammer->setPosition(vector3df(_getPositionX(BZ_COUNT >> 1), 0, -80.0f));

	light = smgr->addLightSceneNode(0, vector3df(-static_cast<float>(w >> 1), static_cast<float>(h >> 1), -150));
	smgr->addLightSceneNode(0, vector3df(static_cast<float>(w >> 1), static_cast<float>(h >> 1), -150));
	light->setRadius(1000.0);
}

void InsBianZhong::render()
{
	for (int i=0; i<BZ_COUNT; ++i) {
		if (playState[i].keyOn) {
			--playState[i].remain;

			int periodRemain = playState[i].remain/BZ_PERIOD + 1;
			int stepInPeriod = (BZ_PERIOD >> 1) - playState[i].remain % BZ_PERIOD;

			float degDiff =  std::asinf(static_cast<float>(stepInPeriod /static_cast<float>(BZ_PERIOD >> 1)));

			std::cout << "Rotation of " << i << " is " <<
				2.0f * degDiff / PI * 90.0f * periodRemain/MAX_STRENGTH << '\n';

			bianZhong[i]->setRotation(vector3df( 
				2.0f * degDiff / PI * 90.0f * periodRemain/MAX_STRENGTH,
				0, 0));

			if (playState[i].remain <= 0) {
				playState[i].keyOn = false;
			}
		}
	}
}

void InsBianZhong::setHammerPosition(const vector3df& position) {
	this->hammer->setPosition(position);
}

void InsBianZhong::play(void *note) 
{
	/* calculates the bianzhong index */
	u32 w = static_cast<u32>(scene->sSize.Width*.8);
	float tempIdx = (hammer->getPosition().X + static_cast<float>(w >> 1))/static_cast<float>(w)*BZ_COUNT;
	if (tempIdx < 0) { /* sanity check */
		tempIdx = 0.0f;
	}
	int realIdx = static_cast<int>(tempIdx);
	if (!playState[realIdx].keyOn) {
		/* according to the strength of hitting */
		soundSrc->playNote(bzInfos[realIdx].frontKey);

		playState[realIdx].remain = 10*BZ_PERIOD;
		playState[realIdx].keyOn = true;
	}
}

float InsBianZhong::_getPositionX(int idx) {
	/* margin 10% */
	u32 w = static_cast<u32>(scene->sSize.Width*.8);
	return -static_cast<float>(w >> 1) + static_cast<float>((.5f+idx)*w)/BZ_COUNT;
}

InsBianZhong::~InsBianZhong(void)
{
}
