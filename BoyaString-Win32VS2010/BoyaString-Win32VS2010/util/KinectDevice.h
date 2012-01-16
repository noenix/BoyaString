
#ifndef KINECTDEVICE_H_
#define KINECTDEVICE_H_

#include <windows.h>

class IGestureStrategy;
class AbstractScene;

/**
 * A kinect device handler ,
 * implemented in singleton design pattern.
 */
class KinectDevice
{
public:
	static KinectDevice * getInstance();

	/**
	 * Closes the kinect device and terminates
	 * newly-created thread.
	 */
	void close();

	/**
	 * Gets the currently calculated gesture.
	 */
	inline int getGesture() const
	{ return gesture; }

	/**
	 * Changes the current gesture strategy.
	 */
	void changeStrategy(IGestureStrategy *s);

	void setScene(AbstractScene *s);

	/**
	 * Creates a new thread and open the kinect device.
	 * @retrun false if the device cannot open, otherwise true
	 */
	bool start();
private:
	static DWORD WINAPI _startKinect(LPVOID param);

	static bool isRun; /**< Determines whether or not the device is run */
	static HANDLE threadHandler;
	static DWORD threadRet; /**< Thread return values. */

	static IGestureStrategy *strategy; /**< The gesture strategy used in the program. */
	static int gesture;

	static AbstractScene *scene;
	static KinectDevice *instance;
	KinectDevice(void);
	virtual ~KinectDevice(void);
};

#endif
