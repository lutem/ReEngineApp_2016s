#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	DrawTri(4, vector3(0.0f, 1.0f, 0.0f), vector3(-1.0f, 0.0f, 0.0f), vector3(1.0f, 0.0f,0.0f));

	//Creating the Mesh points
	/*m_pMesh->AddVertexPosition(vector3(-1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3( 1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);*/

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::DrawTri(int iter, vector3 p1, vector3 p2, vector3 p3) {
	iter--;
	vector3 c12, c13, c23;
	c12 = vector3((p1.x + p2.x / 2), (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
	c13 = vector3((p1.x + p3.x / 2), (p1.y + p3.y) / 2, (p1.z + p3.z) / 2);
	c23 = vector3((p2.x + p3.x / 2), (p2.y + p3.y) / 2, (p2.z + p3.z) / 2);
	
	if (iter != 1) {
		DrawTri(iter, p1, c12, c13);
		DrawTri(iter, c12, p2, c23);
		DrawTri(iter, c13, c23, p3);
	}
	else {
		m_pMesh->AddVertexPosition(p1);
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(c12);
		m_pMesh->AddVertexColor(REBLUE);
		m_pMesh->AddVertexPosition(c13);
		m_pMesh->AddVertexColor(REGREEN);
		m_pMesh->AddVertexPosition(c12);
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(p2);
		m_pMesh->AddVertexColor(REBLUE);
		m_pMesh->AddVertexPosition(c23);
		m_pMesh->AddVertexColor(REGREEN);
		m_pMesh->AddVertexPosition(c13);
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(c23);
		m_pMesh->AddVertexColor(REBLUE);
		m_pMesh->AddVertexPosition(p3);
		m_pMesh->AddVertexColor(REGREEN);
	}

}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)											   //clear the screen
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}