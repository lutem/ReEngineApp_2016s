#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddTri(a_vBottomLeft, a_vBottomRight, a_vTopLeft);
	/*AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);*/

	AddTri(a_vTopLeft, a_vBottomRight, a_vTopRight);
	/*AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);*/
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	vector3 base(0, 0, 0);
	vector3 peak(0, a_fHeight, 0);
	float degree = (360.0 / static_cast<float>(a_nSubdivisions)) * PI/180;

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point1(cos(degree * i) * a_fRadius, 0, sin(degree * i) * a_fRadius);
		vector3 point2(cos(degree * (i+1)) * a_fRadius, 0, sin(degree * (i+1)) * a_fRadius);

		AddTri(point1, base, point2);

		AddTri(point1, point2, peak);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	vector3 base(0, 0, 0);
	vector3 peak(0, a_fHeight, 0);
	float degree = (360.0 / static_cast<float>(a_nSubdivisions)) * PI / 180;

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point1(cos(degree * i)  * a_fRadius, 0, sin(degree * i)  * a_fRadius);
		vector3 point2(cos(degree * (i + 1))  * a_fRadius, 0, sin(degree * (i + 1))  * a_fRadius);
		vector3 point3(cos(degree * i) * a_fRadius, a_fHeight, sin(degree * i) * a_fRadius);
		vector3 point4(cos(degree * (i + 1)) * a_fRadius, a_fHeight, sin(degree * (i + 1)) * a_fRadius);

		AddTri(point1, point2, base);
		AddTri(point3, peak, point4);
		AddQuad(point3, point4, point1, point2);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	float degree = (360.0 / static_cast<float>(a_nSubdivisions)) * PI / 180;

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 innerTL(cos(degree * i) * a_fInnerRadius, a_fHeight, sin(degree * i) * a_fInnerRadius);
		vector3 innerTR(cos(degree * (i+1)) * a_fInnerRadius, a_fHeight, sin(degree * (i+1)) * a_fInnerRadius);
		vector3 innerBL(cos(degree * i) * a_fInnerRadius, 0, sin(degree * i) * a_fInnerRadius);
		vector3 innerBR(cos(degree * (i + 1)) * a_fInnerRadius, 0, sin(degree * (i + 1)) * a_fInnerRadius);

		vector3 outerTL(cos(degree * i) * a_fOuterRadius, a_fHeight, sin(degree * i) * a_fOuterRadius);
		vector3 outerTR(cos(degree * (i + 1)) * a_fOuterRadius, a_fHeight, sin(degree * (i + 1)) * a_fOuterRadius);
		vector3 outerBL(cos(degree * i) * a_fOuterRadius, 0, sin(degree * i) * a_fOuterRadius);
		vector3 outerBR(cos(degree * (i + 1)) * a_fOuterRadius, 0, sin(degree * (i + 1)) * a_fOuterRadius);


		AddQuad(outerTR, outerTL, innerTR, innerTL);
		AddQuad(innerBR, innerBL, outerBR, outerBL);
		AddQuad(outerBR, outerBL, outerTR, outerTL);
		AddQuad(innerBL, innerBR, innerTL, innerTR);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	
	// not finished, some differences between word doc and given constructor
	float degree = (360.0 / static_cast<float>(a_nSubdivisionsA)) * PI / 180;

	for (int i = 0; i < a_nSubdivisionsA; i++) {
		vector3 innerTL(cos(degree * i) * a_fInnerRadius, 0, sin(degree * i) * a_fInnerRadius);
		vector3 innerTR(cos(degree * (i + 1)) * a_fInnerRadius, 0, sin(degree * (i + 1)) * a_fInnerRadius);
		vector3 innerBL(cos(degree * i) * a_fInnerRadius, 0, sin(degree * i) * a_fInnerRadius);
		vector3 innerBR(cos(degree * (i + 1)) * a_fInnerRadius, 0, sin(degree * (i + 1)) * a_fInnerRadius);

		vector3 outerTL(cos(degree * i) * a_fOuterRadius, 0, sin(degree * i) * a_fOuterRadius);
		vector3 outerTR(cos(degree * (i + 1)) * a_fOuterRadius, 0, sin(degree * (i + 1)) * a_fOuterRadius);
		vector3 outerBL(cos(degree * i) * a_fOuterRadius, 0, sin(degree * i) * a_fOuterRadius);
		vector3 outerBR(cos(degree * (i + 1)) * a_fOuterRadius, 0, sin(degree * (i + 1)) * a_fOuterRadius);


		AddQuad(outerTR, outerTL, innerTR, innerTL);
		AddQuad(innerBR, innerBL, outerBR, outerBL);
		AddQuad(outerBR, outerBL, outerTR, outerTL);
		AddQuad(innerBL, innerBR, innerTL, innerTR);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	
	vector3 base(0, 0, 0);
	vector3 peak(0, a_fRadius * 2, 0);

	float degree = (360.0 / static_cast<float>(a_nSubdivisions)) * PI / 180;

	// height loop
	

		// needs reordering to be drawn correctly

		for (int h = 0; h < a_nSubdivisions; h++) {

			float currentH = a_fRadius + sin(degree);
			float currentR = sin(acos(currentH - a_fRadius));

			vector3 point1(cos(degree * h) * currentR, currentH, sin(degree * h) * currentR);
			vector3 point2(cos(degree * (h + 1)) * currentR, currentH, sin(degree * (h + 1)) * currentR);

			currentH = a_fRadius + sin(PI - degree);

			vector3 point3(cos(degree * h) * currentR, currentH, sin(degree * h) * currentR);
			vector3 point4(cos(degree * (h + 1)) * currentR, currentH, sin(degree * (h + 1)) * currentR);

			AddTri(point1, peak, point2);
			AddTri(base, point3, point4);

			for (int i = 1; i < a_nSubdivisions - 1; i++) {
				currentH = a_fRadius + sin(degree * i);
				int nextH = a_fRadius + sin(degree * (i + 1));
				currentR = sin(acos(currentH - a_fRadius));
				int nextR = sin(acos(nextH - a_fRadius));
				
				vector3 point5(cos(degree * h) * currentR, currentH, sin(degree * h) * currentR);
				vector3 point6(cos(degree * (h + 1)) * currentR, currentH, sin(degree * (h + 1)) * currentR);
				vector3 point7(cos(degree * h) * nextR, nextH, sin(degree * h) * nextR);
				vector3 point8(cos(degree * (h + 1)) * nextR, nextH, sin(degree * (h + 1)) * nextR);
				
				AddQuad(point5, point6, point7, point8);
			}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}