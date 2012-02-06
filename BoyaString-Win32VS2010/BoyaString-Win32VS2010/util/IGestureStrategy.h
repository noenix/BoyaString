
#ifndef IGESTURESTRATEGY_H_
#define IGESTURESTRATEGY_H_

#include <windows.h>
#include <MSR_NuiApi.h>
#include <list>
#include <math.h>
using namespace std;

#define SwipeMaximalHeight 0.1
#define SwipeMinimalLength 0.2
#define SwipeMininalDuration 250 
#define SwipeMaximalDuration 1500
#define KnockMaximalPlaneDelta 0.1
#define KnockMinimalLength 0.2
#define KnockMininalDuration 250 
#define KnockMaximalDuration 1500
#define OpenDoorDelta 150

enum gestureType
{
	NONE = 0,
	LEFT_HAND_L_TO_R,
	LEFT_HAND_R_TO_L,
	LEFT_HAND_R_TO_L_AND_OPEN_DOOR,
	RIGHT_HAND_L_TO_R,
	RIGHT_HAND_R_TO_L,
	RIGHT_HAND_L_TO_R_AND_OPEN_DOOR,
	LEFT_HAND_R_TO_L_AND_RIGHT_HAND_L_TO_R_AND_OPEN_DOOR,
	KNOCK_LEFT,//knock with the left hand 
	KNOCK_RIGHT,//knock with the right hand 
	KNOCK_LEFT_RIGHT,//knock with the left and right hand at the same time 
	TYPE_NUMBER
};

class IGestureStrategy
{
public:
	IGestureStrategy(void);

	/**
	 * Called by KinectDevice#start
	 * Sets the position of a certain skeleton node.
	 * @param position the position (X, Y, Z, W) value of the skeleton node
	 * @param skeleton the marco value is defined in MSR_NuiSkeletion.h
	 * @return a certain gesture type defined enumaration type 
	 */
	virtual int setPosition(const Vector4 position[]) = 0;

	virtual ~IGestureStrategy(void);
};

class MenuGestureStrategy: public IGestureStrategy
{
private:
	int intervalTime;
	int lastLeftHandTime;
	int lastRightHandTime;
	int currentTime;
	std::list<Vector4> llr;
	std::list<Vector4> lrl;
	std::list<Vector4> rlr;
	std::list<Vector4> rrl;
public:
	MenuGestureStrategy(void){lastLeftHandTime=(lastRightHandTime=-2000);currentTime=0;};
	void setInterval(int time){intervalTime=time;};
	int setPosition(const Vector4 position[]);
	bool isGesture(std::list<Vector4>& l,bool leftHand,bool updateLastTime);
	~MenuGestureStrategy(void){};
};

class InstrumentGestureStrategy: public IGestureStrategy
{
private:
	int intervalTime;
	std::list<Vector4> l;
	std::list<Vector4> r;
public:
	InstrumentGestureStrategy(void){};
	void setInterval(int time){intervalTime=time;};
	int setPosition(const Vector4 position[]);
	bool isGesture(std::list<Vector4>& positionList);
	~InstrumentGestureStrategy(void){};
};

#endif
