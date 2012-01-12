
#ifndef IGESTURESTRATEGY_H_
#define IGESTURESTRATEGY_H_

#include <MSR_NuiApi.h>

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
	virtual int setPosition(const Vector4& position, int skeleton) =0;

	virtual ~IGestureStrategy(void);
};

#endif
