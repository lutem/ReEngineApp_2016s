#include "RE\ReEngAppClass.h"

using namespace glm;

class CameraClass
{
private:

	// camera instance pointer
	static CameraClass* cInstance;

	// constructor
	CameraClass() {
		cInstance = nullptr;
		init();
	}

	// releases instance
	void release() {
		if (cInstance != nullptr) {
			delete cInstance;
		}

	}

	// creates instance and points to it
	void init() {
		cInstance = new CameraClass();
	}

	// destructor
	~CameraClass() {
		release();
	}

public:
	// gets camera pointer
	CameraClass* GetInstance() {

		// makes camera if it doesn't exist
		if (cInstance = nullptr) {
			init();
		}
		
		// returns instance
		return cInstance;
	}

	// calls release();
	void ReleaseInstance() {
		release();
	}



	/*
	USAGE: Gets the View matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 getViewMat(void);
	/*
	USAGE: Gets the Projection matrix from the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT:
	*/
	matrix4 getProjMat(bool bOrtho);
	
	/*
	USAGE: Sets the camera at the specified position of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetPosition(vector3 newPos);
	/*
	USAGE: Sets the Target of the camera specified by index at the specified position
	ARGUMENTS:
	vector3 a_vTarget ->
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void SetTarget(vector3 targetPos);


	/*
	USAGE:  Sets the Upward vector of the camera
	ARGUMENTS: input
	OUTPUT: ---
	*/
	void SetUp(vector3 v3Up);


	

	/*
	USAGE:	Translates the camera forward or backward of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveForBack(float dist);
	/*
	USAGE:	Translates the camera Upward or downward of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveUpDown(float dist);
	/*
	USAGE:	Translates the camera right or left of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void MoveLeftRight(float dist);
	/*
	USAGE:	Rotates the camera Pitch of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangePitch(float degree);
	/*
	USAGE:	Rotates the camera Yaw of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangeYaw(float degree);
	/*
	USAGE: Rotates the camera Roll of the camera specified by index, if -1 it will use the active camera
	ARGUMENTS:
	int a_nIndex = -1 -> Index of the camera, -1 will use the active camera's index
	OUTPUT: ---
	*/
	void ChangeRoll(float degree);
	


};