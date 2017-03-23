#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	float fTimer = dTotalTime;

	// rotation
	m_m4Steve = glm::rotate(m_m4Steve, -fTimer * 72, vector3(0.0f, 0.0f, 1.0f));

	// translation
	vector3 translation;
	float fPercentage = MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);

	vector3 p1 = vector3(0.0f, 0.0f, 0.0f);
	vector3 p2 = vector3(5.0f, 0.0f, 0.0f);

	int direction = (int)floor(fPercentage);

	switch (direction % 2) {
	case 0:
		translation = glm::lerp(p1, p2, fPercentage - floor(fPercentage));
		break;
	case 1:
		translation = glm::lerp(p2, p1, fPercentage - floor(fPercentage));
		break;
	}
	// apply translation
	m_m4Steve = m_m4Steve * glm::translate(translation);




#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
