#include "IGestureStrategy.h"

IGestureStrategy::IGestureStrategy()
{}

IGestureStrategy::~IGestureStrategy()
{}

int MenuGestureStrategy::setPosition(const Vector4 position[])
{
	currentTime+=intervalTime;
	if(!llr.empty())
		if((position[NUI_SKELETON_POSITION_HAND_LEFT].x-llr.back().x<0)||abs(position[NUI_SKELETON_POSITION_HAND_LEFT].y-llr.back().y)>SwipeMaximalHeight)
			llr.clear();
	if(!lrl.empty())
		if((position[NUI_SKELETON_POSITION_HAND_LEFT].x-lrl.back().x>0)||abs(position[NUI_SKELETON_POSITION_HAND_LEFT].y-lrl.back().y)>SwipeMaximalHeight)
			lrl.clear();
	if(!rlr.empty())
		if((position[NUI_SKELETON_POSITION_HAND_RIGHT].x-rlr.back().x<0)||abs(position[NUI_SKELETON_POSITION_HAND_RIGHT].y-rlr.back().y)>SwipeMaximalHeight)
			rlr.clear();
	if(!rrl.empty())
		if((position[NUI_SKELETON_POSITION_HAND_RIGHT].x-rrl.back().x>0)||abs(position[NUI_SKELETON_POSITION_HAND_RIGHT].y-rrl.back().y)>SwipeMaximalHeight)
			rrl.clear();
	llr.push_back(position[NUI_SKELETON_POSITION_HAND_LEFT]);
	lrl.push_back(position[NUI_SKELETON_POSITION_HAND_LEFT]);
	rlr.push_back(position[NUI_SKELETON_POSITION_HAND_RIGHT]);
	rrl.push_back(position[NUI_SKELETON_POSITION_HAND_RIGHT]);
	if(isGesture(llr,true,false))
		return LEFT_HAND_L_TO_R;
	if(isGesture(rrl,false,false))
		return RIGHT_HAND_R_TO_L;
	isGesture(rlr,false,true);
	isGesture(lrl,true,true);
	if((lastLeftHandTime==currentTime)&&(lastLeftHandTime==lastRightHandTime))
		return LEFT_HAND_R_TO_L_AND_RIGHT_HAND_L_TO_R_AND_OPEN_DOOR;
	if((lastLeftHandTime==currentTime)&&(currentTime-lastRightHandTime<OpenDoorDelta))
		return LEFT_HAND_R_TO_L_AND_OPEN_DOOR;
	if((lastRightHandTime==currentTime)&&(currentTime-lastLeftHandTime<OpenDoorDelta))
		return RIGHT_HAND_L_TO_R_AND_OPEN_DOOR;
	if(lastLeftHandTime==currentTime)
		return LEFT_HAND_R_TO_L;
	if(lastRightHandTime==currentTime)
		return RIGHT_HAND_L_TO_R;
	return NONE;
}

bool MenuGestureStrategy::isGesture(list<Vector4>& l,bool leftHand,bool updateLastTime)
{
	int time=(l.size()-1)*intervalTime;
	FLOAT length=abs(l.back().x-l.front().x);
	if((time>SwipeMininalDuration)&&(time<SwipeMaximalDuration)&&(length>SwipeMinimalLength))
	{
		if(updateLastTime)
			if(leftHand)
				lastLeftHandTime=currentTime;
			else
				lastRightHandTime=currentTime;
		return true;
	}
	else
		return false;
}

int InstrumentGestureStrategy::setPosition(const Vector4 position[])
{
	/*if(!l.empty())
		if(position[NUI_SKELETON_POSITION_HAND_LEFT].y-l.back().y>0||
			position[NUI_SKELETON_POSITION_HAND_LEFT].z-l.back().z>0||
			abs(position[NUI_SKELETON_POSITION_HAND_LEFT].x-l.back().x)>KnockMaximalPlaneDelta)
			l.clear();
	if(!r.empty())
		if(position[NUI_SKELETON_POSITION_HAND_RIGHT].y-r.back().y>0||
			position[NUI_SKELETON_POSITION_HAND_RIGHT].z-r.back().z>0||
			abs(position[NUI_SKELETON_POSITION_HAND_RIGHT].x-r.back().x)>KnockMaximalPlaneDelta)
			r.clear();
	l.push_back(position[NUI_SKELETON_POSITION_HAND_LEFT]);
	r.push_back(position[NUI_SKELETON_POSITION_HAND_RIGHT]);
	gestureType returnValue=NONE;
	if(isGesture(l))
		returnValue=KNOCK_LEFT;
	if(isGesture(r))
		if(returnValue==KNOCK_LEFT)
			return KNOCK_LEFT_RIGHT;
		else
			return KNOCK_RIGHT;
	else
		return returnValue;*/
	return 1;
}

bool InstrumentGestureStrategy::isGesture(list<Vector4>& positionList)
{
	int time=(positionList.size()-1)*intervalTime;
	FLOAT length=abs(positionList.back().y-positionList.front().y);
	if((time>KnockMininalDuration)&&(time<KnockMaximalDuration)&&(length>KnockMinimalLength))	
	{
		//positionList.clear();
		return true;
	}
	else
		return false;
}
