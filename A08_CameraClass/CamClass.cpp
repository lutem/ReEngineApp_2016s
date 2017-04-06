/*#include "RE\ReEngAppClass.h"

using namespace glm;

class CameraClass
{
private:

	// camera instance pointer
	static CameraClass* cInstance;

	// vectors and mat4s
	static vector3 camPos;
	static vector3 up;
	static vector3 targetPos;
	static mat4 viewMat;
	static mat4 projMat;

	// constructor
	CameraClass() {
		cInstance = nullptr;
	}

	// releases instance
	void release() {
		if (cInstance != nullptr) {
			delete cInstance;
		}

	}

	// creates instance and points to it
	static void init() {
		cInstance = new CameraClass();
		camPos = vector3(0.0f, 0.0f, 0.0f);
		up = vector3(0.0f, 1.0f, 0.0f);
		targetPos = vector3(1.0f, 0.0f, 0.0f);
		viewMat = IDENTITY_M4;
		projMat = perspective(45.0f, 1280.0f/720.0f, 0.001f, 1000.0f);
	}

	// destructor
	~CameraClass() {
		release();
	}

public:
	// gets camera pointer
	static CameraClass* GetInstance() {
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



	// returns view matrix
	matrix4 getViewMat(void) {
		return viewMat;
	}
	// get projection matrices
	matrix4 getProjMat(bool bOrtho) {
		if (bOrtho) {
			return projMat;
		}
		else {
			return projMat;
		}
	}
	
	// set camera position
	void SetPosition(vector3 newPos) {
		camPos = newPos;
		viewMat = lookAt(camPos, targetPos, up);
	}
	// set what camera is pointing at
	void SetTarget(vector3 targPos) {
		targetPos = targPos;
		viewMat = lookAt(camPos, targetPos, up);
	}
	// set up vector
	void SetUp(vector3 v3Up) {
		up = v3Up;
		viewMat = lookAt(camPos, targetPos, up);
	}

	// movement functions
	void MoveForwBack(float dist) {
		camPos += (viewMat * dist);
		viewMat = lookAt(camPos, targetPos, up);
	}
	void MoveUpDown(float dist) {
		camPos += (up * dist);
		viewMat = lookAt(camPos, targetPos, up);
	}
	void MoveLeftRight(float dist) {
		camPos += (cross((vec3)viewMat, up) / dot(up,up)) * dist;
		viewMat = lookAt(camPos, targetPos, up);
	}

	// orientation changes
	void ChangePitch(float degree) {
		quat q1 = quat(0.0f, vector3(1.0f, 0.0f, 0.0f));
		quat q2 = quat(degree, vector3(1.0f, 0.0f, 0.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
	void ChangeYaw(float degree) {
		quat q1 = quat(0.0f, vector3(0.0f, 1.0f, 0.0f));
		quat q2 = quat(degree, vector3(0.0f, 1.0f, 0.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
	void ChangeRoll(float degree) {
		quat q1 = quat(0.0f, vector3(0.0f, 0.0f, 1.0f));
		quat q2 = quat(degree, vector3(0.0f, 0.0f, 1.0f));
		quat q3 = mix(q1, q2, 1.0f);
		viewMat *= toMat4(q3);
	}
};*/