#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	Vector3 facenorm;
	VertexID*	vert;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;

	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	
		void Draw();
		void CalculateFacesNorm();
//---------------------------------------------------------------------------------------------------------------------------------------
		//Loc
		void CreateEclipseCylinder(int length, int solidity, float rX, float rY);
		void CreateHoleCylinder(float height, int solidity, float radiusInside, float radiusOutside1, float radiusOutside2);
		void CreatePanel(float length, float width, float thickness1, float thickness2);
		void CreateFlag(float X2, float X3, float X4, float Z3, float Z4, float thickness1, float thickness2);
		void CreateStar();
//---------------------------------------------------------------------------------------------------------------------------------------
		//Hao
		void CreateCylinder(float height, int solidity, float radius);
		void CreateExpShapeCylinder(float gamma, int solidity, float width, float cyRadius, int numCycle);
		void CreateCuboid(float height1, float height2, float width1, float width2, float thickness);
		void CreateSkidHead(float length, float cyRadius, int solidity, int numCycle);
		void CreateHeliMachine(float height, float radius, int solidity, int numSlice);
		void CreateMushroomShape(float height, float bigRadius, float smallRadius, int solidity, int numSlice);
		void CreateHeliFan(float length, float width, float thickness, int numSlice);
		void CreateFanAdapter(float thickness, int numSlice, float length);

//---------------------------------------------------------------------------------------------------------------------------------------
		//Tien
		void CreateHeliFace(int numVertexEachEdge);
		void CreateHeliFaceRightSide(int numVertexEachEdge, float alpha);
		void CreateHeliFaceLeftSide(int numVertexEachEdge, float alpha);
		void CreateHeliFaceTopSide(int numVertexEachEdge, float alpha);
		void CreateHeliFaceTopSideGapRight(int numVertexEachEdge, float alpha, float alpha2);
		void CreateHeliFaceTopSideGapLeft(int numVertexEachEdge, float alpha, float alpha2);
		void CreateHeliFaceBotSide(int numVertexEachEdge, float alpha);
		void CreateHeliFaceBotSideGapRight(int numVertexEachEdge, float alpha1, float alpha2);
		void CreateHeliFaceBotSideGapLeft(int numVertexEachEdge, float alpha1, float alpha2);
		void CreateHeliRear(int numVertexEachEdge);
		void CreateWindowRight(int numVertexEachEdge, float alpha);
		void CreateWindowLeft(int numVertexEachEdge, float alpha);
		void CreateHeliRearBotSide(int numVertexEachEdge, float alpha, float alphaForY);
		void CreateHeliRearTopSide(int numVertexEachEdge, float alpha, float alphaForY);
		void CreateHeliRearTopSideLeft(int numVertexEachEdge, float alpha);

	};

#endif