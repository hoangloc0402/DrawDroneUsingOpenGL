#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define DEG2RAD (3.14159f/180.0f)


void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
//Loc
void Mesh::CalculateFacesNorm() {
	float mx, my, mz;
	int numVertOnFace;
	Point3 curPoint, nextPoint;
	for (int faceCount = 0; faceCount < this->numFaces; faceCount++) {
		mx = my = mz = 0.0;
		numVertOnFace = face[faceCount].nVerts;
		for (int i = 0; i < numVertOnFace; i++) {
			curPoint = pt[face[faceCount].vert[i].vertIndex];
			nextPoint = pt[face[faceCount].vert[(i + 1) % numVertOnFace].vertIndex];
			mx += (curPoint.y - nextPoint.y) *(curPoint.z + nextPoint.z);
			my += (curPoint.z - nextPoint.z) *(curPoint.x + nextPoint.x);
			mz += (curPoint.x - nextPoint.x) *(curPoint.y + nextPoint.y);
		}
		float size = sqrt(mx * mx + my * my + mz * mz);
		mx /= size;
		my /= size;
		mz /= size;
		face[faceCount].facenorm.set(mx, my, mz);
	}

}

void Mesh::CreateEclipseCylinder(int length, int solidity, float rX, float rY) {
	numVerts = solidity * 2;
	pt = new Point3[numVerts];
	double radStep = 360*DEG2RAD / solidity;
	for (int i = 0; i < solidity; i++) {
		pt[i].x = rX*cos(radStep *i);
		pt[i].y = 0;
		pt[i].z = rY*sin(radStep*i);

		pt[i + solidity].x = pt[i].x;
		pt[i + solidity].y = length;
		pt[i + solidity].z = pt[i].z;
	}

	numFaces =  solidity;
	face = new Face[numFaces];
	for (int i = 0; i < solidity; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];

		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = (i + 1) % solidity;
		face[i].vert[2].vertIndex = (i + 1) % solidity + solidity ;
		face[i].vert[3].vertIndex = i + solidity;
	}

	CalculateFacesNorm();
}

void Mesh::CreateHoleCylinder(float height, int solidity, float radiusInside, float radiusOutside1, float radiusOutside2) {
	numVerts = solidity * 4;
	pt = new Point3[numVerts];
	double radStep = 360 * DEG2RAD / solidity;
	for (int i = 0; i < solidity; i++) {
		pt[i].x = radiusOutside1 * cos(i*radStep);
		pt[i].y = 0;
		pt[i].z = radiusOutside1 * sin(i*radStep);

		pt[i + solidity].x = radiusOutside2 * cos(i*radStep);
		pt[i + solidity].y = height;
		pt[i + solidity].z = radiusOutside2 * sin(i*radStep);

		pt[i + 3 * solidity].x = pt[i + 2 * solidity].x = radiusInside * cos(i*radStep);
		pt[i + 2 * solidity].y = 0;
		pt[i + 3 * solidity].y = height;
		pt[i + 3 * solidity].z = pt[i + 2 * solidity].z = radiusInside * sin(i*radStep);
	}

	numFaces = 4 * solidity;
	face = new Face[numFaces];

	for (int i = 0; i < solidity; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = (i + 1) % solidity;
		face[i].vert[2].vertIndex = (i + 1) % solidity + solidity;
		face[i].vert[3].vertIndex = i + solidity;

		int a, b, c;
		a = i + solidity;
		face[a].nVerts = 4;
		face[a].vert = new VertexID[4];
		face[a].vert[0].vertIndex = i + 2*solidity;
		face[a].vert[3].vertIndex = (i + 1) % solidity + 2*solidity;
		face[a].vert[2].vertIndex = (i + 1) % solidity + solidity + 2*solidity;
		face[a].vert[1].vertIndex = i + solidity + 2*solidity;

		b = i + 2 * solidity;
		face[b].nVerts = 4;
		face[b].vert = new VertexID[4];
		face[b].vert[0].vertIndex = i ;
		face[b].vert[1].vertIndex = (i + 1) % solidity;
		face[b].vert[2].vertIndex = (i + 1) % solidity + 2 * solidity;
		face[b].vert[3].vertIndex = i + 2 * solidity;

		c = i + 3 * solidity;
		face[c].nVerts = 4;
		face[c].vert = new VertexID[4];
		face[c].vert[0].vertIndex = i +  solidity;
		face[c].vert[1].vertIndex = (i + 1) % solidity +  solidity;
		face[c].vert[2].vertIndex = (i + 1) % solidity  + 3 * solidity;
		face[c].vert[3].vertIndex = i + 3 * solidity;
	}

	CalculateFacesNorm();
}

void Mesh:: CreatePanel(float length, float width, float thickness1, float thickness2) {
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(0, thickness1 / 2, 0);
	pt[1].set(length, thickness1 / 2, 0);
	pt[2].set(length, thickness2 / 2, width);
	pt[3].set(0, thickness2 / 2, width);
	pt[4].set(0, -thickness1 / 2, 0);
	pt[5].set(length, -thickness1 / 2, 0);
	pt[6].set(length, -thickness2 / 2, width);
	pt[7].set(0, -thickness2 / 2, width);

	numFaces = 6;
	face = new Face[numFaces];

	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 2;
	face[1].vert[3].vertIndex = 3;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[4];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 7;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 5;
	
	face[3].nVerts = 4;
	face[3].vert = new VertexID[4];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 4;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 1;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[4];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 2;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[4];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 6;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 3;

	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[0].vertIndex = 3;
	face[0].vert[1].vertIndex = 7;
	face[0].vert[2].vertIndex = 4;
	face[0].vert[3].vertIndex = 0;

	CalculateFacesNorm();
}

void Mesh::CreateFlag(float X2, float X3, float X4, float Z3, float Z4, float thickness1, float thickness2) {
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(0, thickness1 / 2, 0);
	pt[1].set(X2, thickness1 / 2, 0);
	pt[2].set(X4, thickness2 / 2, Z4);
	pt[3].set(X3, thickness2 / 2, Z3);
	pt[4].set(0, -thickness1 / 2, 0);
	pt[5].set(X2, -thickness1 / 2, 0);
	pt[6].set(X4, -thickness2 / 2,Z4);
	pt[7].set(X3, -thickness2 / 2, Z3);

	numFaces = 6;
	face = new Face[numFaces];

	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[3].vertIndex = 0;
	face[1].vert[2].vertIndex = 1;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[0].vertIndex = 3;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[4];
	face[2].vert[3].vertIndex = 4;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[1].vertIndex = 6;
	face[2].vert[0].vertIndex = 5;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[4];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 4;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 1;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[4];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 2;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[4];
	face[5].vert[3].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[1].vertIndex = 7;
	face[5].vert[0].vertIndex = 3;

	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[3].vertIndex = 3;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[0].vertIndex = 0;

	CalculateFacesNorm();
}

void Mesh::CreateStar() {
	numVerts = 20;
	pt = new Point3[numVerts];
	pt[0].set(107, 20, 10);
	pt[1].set(130, 20, 78);
	pt[2].set(205, 20, 78);
	pt[3].set(144, 20, 122);
	pt[4].set(166, 20, 193);
	pt[5].set(108, 20, 152);
	pt[6].set(44, 20, 193);
	pt[7].set(68, 20, 123);
	pt[8].set(10, 20, 79);
	pt[9].set(84, 20, 77);

	pt[10].set(107, -20, 10);
	pt[11].set(130, -20, 78);
	pt[12].set(205, -20, 78);
	pt[13].set(144, -20, 122);
	pt[14].set(166, -20, 193);
	pt[15].set(108, -20, 152);
	pt[16].set(44, -20, 193);
	pt[17].set(68, -20, 123);
	pt[18].set(10, -20, 79);
	pt[19].set(84, -20, 77);


	numFaces = 22;
	face = new Face[numFaces];
	{
		face[0].nVerts = 5;
		face[0].vert = new VertexID[5];
		face[0].vert[4].vertIndex = 1;
		face[0].vert[3].vertIndex = 3;
		face[0].vert[2].vertIndex = 5;
		face[0].vert[1].vertIndex = 7;
		face[0].vert[0].vertIndex = 9;

		face[1].nVerts = 3;
		face[1].vert = new VertexID[3];
		face[1].vert[2].vertIndex = 0;
		face[1].vert[1].vertIndex = 1;
		face[1].vert[0].vertIndex = 9;


		face[2].nVerts = 3;
		face[2].vert = new VertexID[3];
		face[2].vert[2].vertIndex = 1;
		face[2].vert[1].vertIndex = 2;
		face[2].vert[0].vertIndex = 3;

		face[3].nVerts = 3;
		face[3].vert = new VertexID[3];
		face[3].vert[2].vertIndex = 3;
		face[3].vert[1].vertIndex = 4;
		face[3].vert[0].vertIndex = 5;

		face[4].nVerts = 3;
		face[4].vert = new VertexID[3];
		face[4].vert[2].vertIndex = 5;
		face[4].vert[1].vertIndex = 6;
		face[4].vert[0].vertIndex = 7;

		face[5].nVerts = 3;
		face[5].vert = new VertexID[3];
		face[5].vert[2].vertIndex = 7;
		face[5].vert[1].vertIndex = 8;
		face[5].vert[0].vertIndex = 9;

		face[6].nVerts = 5;
		face[6].vert = new VertexID[5];
		face[6].vert[4].vertIndex = 11;
		face[6].vert[3].vertIndex = 13;
		face[6].vert[2].vertIndex = 15;
		face[6].vert[1].vertIndex = 17;
		face[6].vert[0].vertIndex = 19;

		face[7].nVerts = 3;
		face[7].vert = new VertexID[3];
		face[7].vert[2].vertIndex = 10;
		face[7].vert[1].vertIndex = 11;
		face[7].vert[0].vertIndex = 19;


		face[8].nVerts = 3;
		face[8].vert = new VertexID[3];
		face[8].vert[2].vertIndex = 11;
		face[8].vert[1].vertIndex = 12;
		face[8].vert[0].vertIndex = 13;

		face[9].nVerts = 3;
		face[9].vert = new VertexID[3];
		face[9].vert[2].vertIndex = 13;
		face[9].vert[1].vertIndex = 14;
		face[9].vert[0].vertIndex = 15;

		face[10].nVerts = 3;
		face[10].vert = new VertexID[3];
		face[10].vert[2].vertIndex = 15;
		face[10].vert[1].vertIndex = 16;
		face[10].vert[0].vertIndex = 17;

		face[11].nVerts = 3;
		face[11].vert = new VertexID[3];
		face[11].vert[2].vertIndex = 17;
		face[11].vert[1].vertIndex = 18;
		face[11].vert[0].vertIndex = 19;
	}

	face[12].nVerts = 4;
	face[12].vert = new VertexID[4];
	face[12].vert[3].vertIndex = 0;
	face[12].vert[2].vertIndex = 1;
	face[12].vert[1].vertIndex = 11;
	face[12].vert[0].vertIndex = 10;

	face[13].nVerts = 4;
	face[13].vert = new VertexID[4];
	face[13].vert[3].vertIndex = 1;
	face[13].vert[2].vertIndex = 2;
	face[13].vert[1].vertIndex = 12;
	face[13].vert[0].vertIndex = 11;

	face[14].nVerts = 4;
	face[14].vert = new VertexID[4];
	face[14].vert[3].vertIndex = 2;
	face[14].vert[2].vertIndex = 3;
	face[14].vert[1].vertIndex = 13;
	face[14].vert[0].vertIndex = 12;

	face[15].nVerts = 4;
	face[15].vert = new VertexID[4];
	face[15].vert[3].vertIndex = 3;
	face[15].vert[2].vertIndex = 4;
	face[15].vert[1].vertIndex = 14;
	face[15].vert[0].vertIndex = 13;

	face[16].nVerts = 4;
	face[16].vert = new VertexID[4];
	face[16].vert[3].vertIndex = 4;
	face[16].vert[2].vertIndex = 5;
	face[16].vert[1].vertIndex = 15;
	face[16].vert[0].vertIndex = 14;

	face[17].nVerts = 4;
	face[17].vert = new VertexID[4];
	face[17].vert[3].vertIndex = 5;
	face[17].vert[2].vertIndex = 6;
	face[17].vert[1].vertIndex = 16;
	face[17].vert[0].vertIndex = 15;


	face[18].nVerts = 4;
	face[18].vert = new VertexID[4];
	face[18].vert[3].vertIndex = 6;
	face[18].vert[2].vertIndex = 7;
	face[18].vert[1].vertIndex = 17;
	face[18].vert[0].vertIndex = 16;

	face[19].nVerts = 4;
	face[19].vert = new VertexID[4];
	face[19].vert[3].vertIndex = 7;
	face[19].vert[2].vertIndex = 8;
	face[19].vert[1].vertIndex = 18;
	face[19].vert[0].vertIndex = 17;

	face[20].nVerts = 4;
	face[20].vert = new VertexID[4];
	face[20].vert[3].vertIndex = 8;
	face[20].vert[2].vertIndex = 9;
	face[20].vert[1].vertIndex = 19;
	face[20].vert[0].vertIndex = 18;

	face[21].nVerts = 4;
	face[21].vert = new VertexID[4];
	face[21].vert[0].vertIndex = 9;
	face[21].vert[1].vertIndex = 0;
	face[21].vert[2].vertIndex = 10;
	face[21].vert[3].vertIndex = 19;

	CalculateFacesNorm();
}

//---------------------------------------------------------------------------------------------------------------------------------------
//Hao
void Mesh::CreateCylinder(float height, int solidity, float radius) {
	Mesh::CreateHoleCylinder(height, solidity, 0.0, radius, radius);
}

void Mesh::CreateExpShapeCylinder(float gamma, int solidity, float width, float cyRadius, int numCycle) {
	numVerts = solidity * numCycle;
	numFaces = solidity * (numCycle - 1);
	pt = new Point3[numVerts];
	float deltaL = 15.0f / (numCycle - 1.0f);
	float radStep = 360.0f*DEG2RAD / solidity;
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numCycle; j++) {
			float temp;
			pt[i + solidity * j].y = temp = cyRadius * cos(i*radStep) + deltaL * j;
			pt[i + solidity * j].x = log((temp - cyRadius * cos(i*radStep) - 1) / ((2 + cyRadius * cos(i*radStep))*0.1f));
			pt[i + solidity * j].z = cyRadius * sin(i*radStep);
		}
	}

	face = new Face[numFaces];
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numCycle - 1; j++) {
			int faceNum = i + solidity * j;
			face[faceNum].nVerts = 4;
			face[faceNum].vert = new VertexID[4];
			face[faceNum].vert[3].vertIndex = i + solidity * j;
			face[faceNum].vert[2].vertIndex = (i + 1) % solidity + solidity * j;
			face[faceNum].vert[1].vertIndex = (i + 1) % solidity + solidity * (j + 1);
			face[faceNum].vert[0].vertIndex = i + solidity * (j + 1);
		}
	}

	CalculateFacesNorm();
}

void Mesh::CreateCuboid(float height1, float height2, float width1, float width2, float thickness) {
	numVerts = 8;
	numFaces = 6;
	pt = new Point3[numVerts];

	pt[0].x = width1 / 2;
	pt[0].y = thickness / 2;
	pt[0].z = height1 / 2;
	pt[1].x = width1 / 2;
	pt[1].y = thickness / 2;
	pt[1].z = -height1 / 2;
	pt[2].x = -width1 / 2;
	pt[2].y = thickness / 2;
	pt[2].z = -height1 / 2;
	pt[3].x = -width1 / 2;
	pt[3].y = thickness / 2;
	pt[3].z = height1 / 2;
	pt[4].x = width2 / 2;
	pt[4].y = -thickness / 2;
	pt[4].z = height2 / 2;
	pt[5].x = width2 / 2;
	pt[5].y = -thickness / 2;
	pt[5].z = -height2 / 2;
	pt[6].x = -width2 / 2;
	pt[6].y = -thickness / 2;
	pt[6].z = -height2 / 2;
	pt[7].x = -width2 / 2;
	pt[7].y = -thickness / 2;
	pt[7].z = height2 / 2;

	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[3].vertIndex = 0;
	face[0].vert[2].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[0].vertIndex = 3;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[3].vertIndex = 7;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[0].vertIndex = 4;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[4];
	face[2].vert[3].vertIndex = 0;
	face[2].vert[2].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[0].vertIndex = 1;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[4];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 5;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 2;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[4];
	face[4].vert[3].vertIndex = 2;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[1].vertIndex = 7;
	face[4].vert[0].vertIndex = 3;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[4];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 4;

	CalculateFacesNorm();
}

void Mesh::CreateSkidHead(float height, float cyRadius, int solidity, int numCycle) {
	numVerts = solidity * numCycle;
	numFaces = solidity * (numCycle - 1);
	pt = new Point3[numVerts];
	float deltaL = 5.0f / (numCycle - 1.0f);
	float radStep = 360.0f*DEG2RAD / solidity;
	float deltaR = cyRadius / (numCycle - 1.0f);
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numCycle; j++) {
			float temp;
			pt[i + solidity * j].y = temp = deltaR * j*cos(i*radStep) + deltaL * j;
			pt[i + solidity * j].x = sqrt(temp / (deltaR*j*cos(i*radStep) + 1));
			pt[i + solidity * j].z = deltaR * j * sin(i*radStep);
		}
	}

	face = new Face[numFaces];
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numCycle - 1; j++) {
			int faceNum = i + solidity * j;
			face[faceNum].nVerts = 4;
			face[faceNum].vert = new VertexID[4];
			face[faceNum].vert[3].vertIndex = i + solidity * j;
			face[faceNum].vert[2].vertIndex = (i + 1) % solidity + solidity * j;
			face[faceNum].vert[1].vertIndex = (i + 1) % solidity + solidity * (j + 1);
			face[faceNum].vert[0].vertIndex = i + solidity * (j + 1);
		}
	}

	CalculateFacesNorm();
}

void Mesh::CreateHeliMachine(float height, float radius, int solidity, int numSlice) {
	numVerts = solidity * numSlice;
	numFaces = solidity * (numSlice - 1);
	float radStep = 30.0f*DEG2RAD / (solidity - 2);
	float deltaH = height / (numSlice - 1);
	pt = new Point3[numVerts];
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numSlice; j++) {
			radStep = (30.0f - j * 0.1)*DEG2RAD / (solidity - 2);
			if (i == solidity - 1) {
				pt[i + solidity * j].y = deltaH * j;
				pt[i + solidity * j].x = pow(pt[i + solidity * j].y, 2);
				pt[i + solidity * j].z = 0;
			}
			else {
				pt[i + solidity * j].x = (radius - 0.0003*j*j)*cos((radStep*i - (30.0f - j * 0.1) * DEG2RAD / 2));
				pt[i + solidity * j].y = deltaH * j;
				pt[i + solidity * j].z = (radius - 0.0003*j*j)*sin((radStep*i - (30.0f - j * 0.1) * DEG2RAD / 2));
			}
		}
	}

	face = new Face[numFaces];

	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numSlice - 1; j++) {
			int faceNum = i + solidity * j;
			face[faceNum].nVerts = 4;
			face[faceNum].vert = new VertexID[4];
			face[faceNum].vert[0].vertIndex = i + solidity * j;
			face[faceNum].vert[1].vertIndex = (i + 1) % solidity + solidity * j;
			face[faceNum].vert[2].vertIndex = (i + 1) % solidity + solidity * (j + 1);
			face[faceNum].vert[3].vertIndex = i + solidity * (j + 1);
		}
	}

	face[numFaces - 1].nVerts = solidity;
	face[numFaces - 1].vert = new VertexID[solidity];
	face[numFaces - 2].nVerts = solidity;
	face[numFaces - 2].vert = new VertexID[solidity];
	for (int i = 0; i < solidity; i++) {
		face[numFaces - 1].vert[solidity - 1 - i].vertIndex = i;
		face[numFaces - 2].vert[i].vertIndex = i + solidity * (numSlice - 1);
	}
	CalculateFacesNorm();
}

void Mesh::CreateMushroomShape(float height, float bigRadius, float smallRadius, int solidity, int numSlice) {
	numVerts = solidity * numSlice;
	numFaces = solidity * (numSlice - 1) + 2;
	float radStep = 360.0f*DEG2RAD / solidity;
	float deltaH = height / (numSlice - 1);
	float deltaR = (bigRadius - smallRadius) / (numSlice - 1);
	pt = new Point3[numVerts];
	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numSlice; j++) {
			pt[i + solidity * j].x = (bigRadius - 0.2*pow(deltaR*j, 2))*cos((radStep*i - (30.0f - j * 0.1) * DEG2RAD / 2));
			pt[i + solidity * j].y = deltaH * j;
			pt[i + solidity * j].z = (bigRadius - 0.2*pow(deltaR*j, 2))*sin((radStep*i - (30.0f - j * 0.1) * DEG2RAD / 2));
		}
	}

	face = new Face[numFaces];

	for (int i = 0; i < solidity; i++) {
		for (int j = 0; j < numSlice - 1; j++) {
			int faceNum = i + solidity * j;
			face[faceNum].nVerts = 4;
			face[faceNum].vert = new VertexID[4];
			face[faceNum].vert[0].vertIndex = i + solidity * j;
			face[faceNum].vert[1].vertIndex = (i + 1) % solidity + solidity * j;
			face[faceNum].vert[2].vertIndex = (i + 1) % solidity + solidity * (j + 1);
			face[faceNum].vert[3].vertIndex = i + solidity * (j + 1);
		}
	}

	face[numFaces - 1].nVerts = solidity;
	face[numFaces - 1].vert = new VertexID[solidity];
	face[numFaces - 2].nVerts = solidity;
	face[numFaces - 2].vert = new VertexID[solidity];
	for (int i = 0; i < solidity; i++) {
		face[numFaces - 1].vert[solidity - 1 - i].vertIndex = i;
		face[numFaces - 2].vert[i].vertIndex = i + solidity * (numSlice - 1);
	}
	CalculateFacesNorm();
}

void Mesh::CreateHeliFan(float length, float width, float thickness, int numSlice) {
	numVerts = numSlice * 4;
	numFaces = (numSlice - 1) * 4;
	pt = new Point3[numVerts];
	float paraLength = width;
	float deltaL = paraLength / (numSlice - 2);
	for (int i = 0; i < numSlice - 1; i++) {
		float temp;
		pt[i].y = temp = deltaL * i;
		pt[i].x = temp * temp;
		pt[i].z = thickness / 2;

		pt[i + numSlice].y = temp = deltaL * i;
		pt[i + numSlice].x = temp * temp;
		pt[i + numSlice].z = -thickness / 2;

		pt[i + numSlice * 2].y = 0;
		pt[i + numSlice * 2].x = temp * temp;
		pt[i + numSlice * 2].z = thickness / 2;

		pt[i + numSlice * 3].y = 0;
		pt[i + numSlice * 3].x = temp * temp;
		pt[i + numSlice * 3].z = -thickness / 2;
	}

	pt[numSlice - 1].x = length;
	pt[numSlice - 1].y = paraLength;
	pt[numSlice - 1].z = thickness / 2;

	pt[numSlice - 1 + numSlice].x = length;
	pt[numSlice - 1 + numSlice].y = paraLength;
	pt[numSlice - 1 + numSlice].z = -thickness / 2;

	pt[numSlice - 1 + numSlice * 2].x = length;
	pt[numSlice - 1 + numSlice * 2].y = 0;
	pt[numSlice - 1 + numSlice * 2].z = thickness / 2;

	pt[numSlice - 1 + numSlice * 3].x = length;
	pt[numSlice - 1 + numSlice * 3].y = 0;
	pt[numSlice - 1 + numSlice * 3].z = -thickness / 2;

	face = new Face[numFaces];

	for (int i = 0; i < numSlice - 1; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i + numSlice * 2;
		face[i].vert[2].vertIndex = i + 1 + numSlice * 2;
		face[i].vert[3].vertIndex = i + 1;

		face[i + (numSlice - 1)].nVerts = 4;
		face[i + (numSlice - 1)].vert = new VertexID[4];
		face[i + (numSlice - 1)].vert[0].vertIndex = i;
		face[i + (numSlice - 1)].vert[1].vertIndex = i + 1;
		face[i + (numSlice - 1)].vert[2].vertIndex = i + numSlice + 1;
		face[i + (numSlice - 1)].vert[3].vertIndex = i + numSlice;

		face[i + (numSlice - 1) * 2].nVerts = 4;
		face[i + (numSlice - 1) * 2].vert = new VertexID[4];
		face[i + (numSlice - 1) * 2].vert[0].vertIndex = i + numSlice;
		face[i + (numSlice - 1) * 2].vert[1].vertIndex = i + 1 + numSlice;
		face[i + (numSlice - 1) * 2].vert[2].vertIndex = i + numSlice * 3 + 1;
		face[i + (numSlice - 1) * 2].vert[3].vertIndex = i + numSlice * 3;

		face[i + (numSlice - 1) * 3].nVerts = 4;
		face[i + (numSlice - 1) * 3].vert = new VertexID[4];
		face[i + (numSlice - 1) * 3].vert[0].vertIndex = i + numSlice * 2;
		face[i + (numSlice - 1) * 3].vert[1].vertIndex = i + numSlice * 3;
		face[i + (numSlice - 1) * 3].vert[2].vertIndex = i + numSlice * 3 + 1;
		face[i + (numSlice - 1) * 3].vert[3].vertIndex = i + numSlice * 2 + 1;
	}

	CalculateFacesNorm();
}

void Mesh::CreateFanAdapter(float thickness, int numSlice, float length) {
	numVerts = numSlice * 4;
	numFaces = (numSlice - 1) * 4;
	pt = new Point3[numVerts];
	float deltaL = length / (numSlice - 1);
	for (int i = 0; i < numSlice; i++) {
		float temp;
		pt[i].y = temp = deltaL * i;
		pt[i].x = length - 2 * temp*temp;
		pt[i].z = thickness / 2;

		pt[i + numSlice].y = deltaL * i;
		pt[i + numSlice].x = length - 2 * temp*temp;
		pt[i + numSlice].z = -thickness / 2;

		pt[i + numSlice * 2].y = temp = -deltaL * i;
		pt[i + numSlice * 2].x = length - 2 * temp*temp;
		pt[i + numSlice * 2].z = thickness / 2;

		pt[i + numSlice * 3].y = -deltaL * i;
		pt[i + numSlice * 3].x = length - 2 * temp*temp;
		pt[i + numSlice * 3].z = -thickness / 2;
	}
	face = new Face[numFaces];

	for (int i = 0; i < numSlice - 1; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i + numSlice * 2;
		face[i].vert[2].vertIndex = i + 1 + numSlice * 2;
		face[i].vert[3].vertIndex = i + 1;

		face[i + (numSlice - 1)].nVerts = 4;
		face[i + (numSlice - 1)].vert = new VertexID[4];
		face[i + (numSlice - 1)].vert[0].vertIndex = i;
		face[i + (numSlice - 1)].vert[1].vertIndex = i + 1;
		face[i + (numSlice - 1)].vert[2].vertIndex = i + numSlice + 1;
		face[i + (numSlice - 1)].vert[3].vertIndex = i + numSlice;

		face[i + (numSlice - 1) * 2].nVerts = 4;
		face[i + (numSlice - 1) * 2].vert = new VertexID[4];
		face[i + (numSlice - 1) * 2].vert[0].vertIndex = i + numSlice;
		face[i + (numSlice - 1) * 2].vert[1].vertIndex = i + 1 + numSlice;
		face[i + (numSlice - 1) * 2].vert[2].vertIndex = i + numSlice * 3 + 1;
		face[i + (numSlice - 1) * 2].vert[3].vertIndex = i + numSlice * 3;

		face[i + (numSlice - 1) * 3].nVerts = 4;
		face[i + (numSlice - 1) * 3].vert = new VertexID[4];
		face[i + (numSlice - 1) * 3].vert[0].vertIndex = i + numSlice * 2;
		face[i + (numSlice - 1) * 3].vert[1].vertIndex = i + numSlice * 3;
		face[i + (numSlice - 1) * 3].vert[2].vertIndex = i + numSlice * 3 + 1;
		face[i + (numSlice - 1) * 3].vert[3].vertIndex = i + numSlice * 2 + 1;
	}

	CalculateFacesNorm();
}

//---------------------------------------------------------------------------------------------------------------------------------------
//Tien
void Mesh::CreateHeliFace(int numVertexEachEdge) {
	numVerts = numVertexEachEdge * numVertexEachEdge + numVertexEachEdge * 4;
	pt = new Point3[numVerts];

	//rightPt = new Point3[numVertexEachEdge];
	float offset = 0.15f;

	//float maxZ = 3.4025f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f + i * deltaX;
		for (float j = 0; j < numVertexEachEdge; j++) {
			float y = -1.0f + j * deltaY;
			float z = (x + 0.05f) * (x + 0.05f) + y * y;
			//if (i == numVertexEachEdge - 1) z = 5.0;
			pt[count].set(x, y, z);
			count++;
		}
	}

	numFaces = pow(numVertexEachEdge - 1, 2) + (numVertexEachEdge - 1) * 0;
	face = new Face[numFaces];

	int vertexCount = count;
	count = 0;

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}

}

void Mesh::CreateHeliFaceRightSide(int numVertexEachEdge, float alpha) {
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f + i * deltaX;
		float y = -1.0f;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
		//cout << count << " " << pt[count].x << " " << pt[count].y << " " << pt[count].z << endl;
	}

	float maxZ = 11.0f;
	float maxY = -1.25f;
	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float x = pt[(i - 1)*numVertexEachEdge + j].x;
			float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliFaceLeftSide(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f + i * deltaX;
		float y = 1.0f;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
		//cout << count << " " << pt[count].x << " " << pt[count].y << " " << pt[count].z << endl;
	}

	float maxZ = 11.0f;
	float maxY = 1.25f;

	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float x = pt[(i - 1)*numVertexEachEdge + j].x;
			float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = (i + 1) * numVertexEachEdge + j;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = i * numVertexEachEdge + j + 1;

			count++;
		}
	}
}

void Mesh::CreateHeliFaceTopSide(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = 1.5f;
		float y = -1.0f + i * deltaY;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
	}

	float maxZ = 11.0f;
	float maxX = 1.75f;

	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float y = pt[(i - 1)*numVertexEachEdge + j].y;
			float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
			float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	//int i = 0, j = 0;
	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliFaceTopSideGapRight(int numVertexEachEdge, float alpha, float alpha2)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = 1.75f;

	float sucker = 1.0f;

	pt[0].set(1.5, -1.0, 3.4025);

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		float z = pt[i - 1].z + alphaZ;
		float y = pt[i - 1].y;
		float alphaX = (maxX - pt[0].x) / (numVertexEachEdge - 1);
		float x = pt[i - 1].x + (sucker*alpha + 1)*alphaX;
		pt[i].set(x, y, z);
		sucker -= deltaY;
	}


	maxZ = 11.0f;
	float maxY = -1.25f;

	sucker = 1.0f;
	int k;
	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		if (i == 1) k = 1;
		float z = pt[k - 1].z + alphaZ;
		float x = pt[k - 1].x;
		float alphaY = (maxY - pt[0].y) / (numVertexEachEdge - 1);
		float y = pt[k - 1].y + (sucker*alpha2 + 1)*alphaY;
		if (i == 1) k = numVertexEachEdge;
		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	int numV = 10;

	deltaY = 2.0f / (numV - 1);

	float smallAlpha = 0.5;



	for (int i = 1; i <numVertexEachEdge; i++) {
		float maxY = pt[i + numVertexEachEdge - 1].y;
		float maxX = pt[i + numVertexEachEdge - 1].x;
		sucker = 1.0;
		float startY = pt[i].y;
		float startX = pt[i].x;
		for (int j = 0; j < numV; j++) {
			float alphaY = (maxY - pt[i].y) / (numV);
			float alphaX = (maxX - pt[i].x) / (numV);
			if (j != 0) {
				startY = pt[k - 1].y; startX = pt[k - 1].x;
			}
			float y = startY + (sucker*smallAlpha + 1)*alphaY;
			float z = pt[i].z;
			float x = startX + alphaX;
			pt[k].set(x, y, z);
			k++;
			sucker -= deltaY;
		}
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	int base = numVertexEachEdge + numVertexEachEdge - 2;
	int i = 1;
	while (i < numVertexEachEdge - 1) {
		int j = 1;
		face[count].nVerts = 4;
		face[count].vert = new VertexID[4];

		face[count].vert[0].vertIndex = i;
		face[count].vert[1].vertIndex = i + 1;
		face[count].vert[2].vertIndex = base + numV + j;
		face[count].vert[3].vertIndex = base + j;

		count++;

		while (j < numV) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = base + j;
			face[count].vert[1].vertIndex = base + numV + j;
			face[count].vert[2].vertIndex = base + numV + j + 1;
			face[count].vert[3].vertIndex = base + j + 1;



			count++;
			j++;
		}
		base += numV;
		i++;
	}
	int u = 1, v = (numVertexEachEdge - 1) * 2 + 1;
	for (int i = 0; i < numV; i++) {
		face[count].nVerts = 3;
		face[count].vert = new VertexID[3];

		face[count].vert[0].vertIndex = 0;
		face[count].vert[1].vertIndex = u;
		face[count].vert[2].vertIndex = v;
		u = v;
		v = v + 1;
		count++;
	}
}

void Mesh::CreateHeliFaceTopSideGapLeft(int numVertexEachEdge, float alpha, float alpha2)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = 1.75f;

	float sucker = 1.0f;

	pt[0].set(1.5, 1.0, 3.4025);

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		float z = pt[i - 1].z + alphaZ;
		float y = pt[i - 1].y;
		float alphaX = (maxX - pt[0].x) / (numVertexEachEdge - 1);
		float x = pt[i - 1].x + (sucker*alpha + 1)*alphaX;
		pt[i].set(x, y, z);
		sucker -= deltaY;
	}


	maxZ = 11.0f;
	float maxY = 1.25f;

	sucker = 1.0f;
	int k;
	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		if (i == 1) k = 1;
		float z = pt[k - 1].z + alphaZ;
		float x = pt[k - 1].x;
		float alphaY = (maxY - pt[0].y) / (numVertexEachEdge - 1);
		float y = pt[k - 1].y + (sucker*alpha2 + 1)*alphaY;
		if (i == 1) k = numVertexEachEdge;
		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	int numV = 10;

	deltaY = 2.0f / (numV - 1);

	float smallAlpha = 0.5;



	for (int i = 1; i <numVertexEachEdge; i++) {
		float maxY = pt[i + numVertexEachEdge - 1].y;
		float maxX = pt[i + numVertexEachEdge - 1].x;
		sucker = 1.0;
		float startY = pt[i].y;
		float startX = pt[i].x;
		for (int j = 0; j < numV; j++) {
			float alphaY = (maxY - pt[i].y) / (numV);
			float alphaX = (maxX - pt[i].x) / (numV);
			if (j != 0) {
				startY = pt[k - 1].y; startX = pt[k - 1].x;
			}
			float y = startY + (sucker*smallAlpha + 1)*alphaY;
			float z = pt[i].z;
			float x = startX + alphaX;
			pt[k].set(x, y, z);
			k++;
			sucker -= deltaY;
		}
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	int base = numVertexEachEdge + numVertexEachEdge - 2;
	int i = 1;
	while (i < numVertexEachEdge - 1) {
		int j = 1;
		face[count].nVerts = 4;
		face[count].vert = new VertexID[4];

		face[count].vert[0].vertIndex = i;
		face[count].vert[1].vertIndex = i + 1;
		face[count].vert[2].vertIndex = base + numV + j;
		face[count].vert[3].vertIndex = base + j;

		count++;

		while (j < numV) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = base + j;
			face[count].vert[1].vertIndex = base + numV + j;
			face[count].vert[2].vertIndex = base + numV + j + 1;
			face[count].vert[3].vertIndex = base + j + 1;

			count++;
			j++;
		}
		base += numV;
		i++;
	}
	int u = 1, v = (numVertexEachEdge - 1) * 2 + 1;
	for (int i = 0; i < numV; i++) {
		face[count].nVerts = 3;
		face[count].vert = new VertexID[3];

		face[count].vert[0].vertIndex = 0;
		face[count].vert[1].vertIndex = u;
		face[count].vert[2].vertIndex = v;
		u = v;
		v = v + 1;
		count++;
	}
}

void Mesh::CreateHeliFaceBotSide(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f;
		float y = -1.0f + i * deltaY;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
	}

	float maxZ = 11.0f;
	float maxX = -1.15f;

	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float y = pt[(i - 1)*numVertexEachEdge + j].y;
			float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
			float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	//int i = 0, j = 0;
	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliFaceBotSideGapRight(int numVertexEachEdge, float alpha1, float alpha2)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = -1.15f;

	float sucker = 1.0f;

	pt[0].set(-1.0, -1.0, 1.9025);

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		float z = pt[i - 1].z + alphaZ;
		float y = pt[i - 1].y;
		float alphaX = (maxX - pt[0].x) / (numVertexEachEdge - 1);
		float x = pt[i - 1].x + (sucker*alpha1 + 1)*alphaX;
		pt[i].set(x, y, z);
		sucker -= deltaY;
	}


	maxZ = 11.0f;
	float maxY = -1.25f;

	sucker = 1.0f;
	int k;
	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		if (i == 1) k = 1;
		float z = pt[k - 1].z + alphaZ;
		float x = pt[k - 1].x;
		float alphaY = (maxY - pt[0].y) / (numVertexEachEdge - 1);
		float y = pt[k - 1].y + (sucker*alpha2 + 1)*alphaY;
		if (i == 1) k = numVertexEachEdge;
		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	int numV = 10;

	deltaY = 2.0f / (numV - 1);

	float smallAlpha = 0.5;

	for (int i = 1; i <numVertexEachEdge; i++) {
		float maxY = pt[i + numVertexEachEdge - 1].y;
		float maxX = pt[i + numVertexEachEdge - 1].x;
		sucker = 1.0;
		float startY = pt[i].y;
		float startX = pt[i].x;
		for (int j = 0; j < numV; j++) {
			float alphaY = (maxY - pt[i].y) / (numV);
			float alphaX = (maxX - pt[i].x) / (numV);
			if (j != 0) {
				startY = pt[k - 1].y; startX = pt[k - 1].x;
			}
			float y = startY + (sucker*smallAlpha + 1)*alphaY;
			float z = pt[i].z;
			float x = startX + alphaX;
			pt[k].set(x, y, z);
			k++;
			sucker -= deltaY;
		}
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	int base = numVertexEachEdge + numVertexEachEdge - 2;
	int i = 1;
	while (i < numVertexEachEdge - 1) {
		int j = 1;
		face[count].nVerts = 4;
		face[count].vert = new VertexID[4];

		face[count].vert[0].vertIndex = i;
		face[count].vert[1].vertIndex = i + 1;
		face[count].vert[2].vertIndex = base + numV + j;
		face[count].vert[3].vertIndex = base + j;

		count++;

		while (j < numV) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = base + j;
			face[count].vert[1].vertIndex = base + numV + j;
			face[count].vert[2].vertIndex = base + numV + j + 1;
			face[count].vert[3].vertIndex = base + j + 1;



			count++;
			j++;
		}
		base += numV;
		i++;
	}
	int u = 1, v = (numVertexEachEdge - 1) * 2 + 1;
	for (int i = 0; i < numV; i++) {
		face[count].nVerts = 3;
		face[count].vert = new VertexID[3];

		face[count].vert[0].vertIndex = 0;
		face[count].vert[1].vertIndex = u;
		face[count].vert[2].vertIndex = v;
		u = v;
		v = v + 1;
		count++;
	}
}

void Mesh::CreateHeliFaceBotSideGapLeft(int numVertexEachEdge, float alpha1, float alpha2)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = -1.15f;

	float sucker = 1.0f;

	pt[0].set(-1.0, 1.0, 1.9025);

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		float z = pt[i - 1].z + alphaZ;
		float y = pt[i - 1].y;
		float alphaX = (maxX - pt[0].x) / (numVertexEachEdge - 1);
		float x = pt[i - 1].x + (sucker*alpha1 + 1)*alphaX;
		pt[i].set(x, y, z);
		sucker -= deltaY;
	}


	maxZ = 11.0f;
	float maxY = 1.25f;

	sucker = 1.0f;
	int k;
	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		if (i == 1) k = 1;
		float z = pt[k - 1].z + alphaZ;
		float x = pt[k - 1].x;
		float alphaY = (maxY - pt[0].y) / (numVertexEachEdge - 1);
		float y = pt[k - 1].y + (sucker*alpha2 + 1)*alphaY;
		if (i == 1) k = numVertexEachEdge;
		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	int numV = 10;

	deltaY = 2.0f / (numV - 1);

	float smallAlpha = 0.5;



	for (int i = 1; i <numVertexEachEdge; i++) {
		float maxY = pt[i + numVertexEachEdge - 1].y;
		float maxX = pt[i + numVertexEachEdge - 1].x;
		sucker = 1.0;
		float startY = pt[i].y;
		float startX = pt[i].x;
		for (int j = 0; j < numV; j++) {
			float alphaY = (maxY - pt[i].y) / (numV);
			float alphaX = (maxX - pt[i].x) / (numV);
			if (j != 0) {
				startY = pt[k - 1].y; startX = pt[k - 1].x;
			}
			float y = startY + (sucker*smallAlpha + 1)*alphaY;
			float z = pt[i].z;
			float x = startX + (sucker*smallAlpha + 1)*alphaX;
			pt[k].set(x, y, z);
			k++;
			sucker -= deltaY;
		}
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	int base = numVertexEachEdge + numVertexEachEdge - 2;
	int i = 1;
	while (i < numVertexEachEdge - 1) {
		int j = 1;
		face[count].nVerts = 4;
		face[count].vert = new VertexID[4];

		face[count].vert[0].vertIndex = i;
		face[count].vert[1].vertIndex = i + 1;
		face[count].vert[2].vertIndex = base + numV + j;
		face[count].vert[3].vertIndex = base + j;

		count++;

		while (j < numV) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = base + j;
			face[count].vert[1].vertIndex = base + numV + j;
			face[count].vert[2].vertIndex = base + numV + j + 1;
			face[count].vert[3].vertIndex = base + j + 1;

			count++;
			j++;
		}
		base += numV;
		i++;
	}
	int u = 1, v = (numVertexEachEdge - 1) * 2 + 1;
	for (int i = 0; i < numV; i++) {
		face[count].nVerts = 3;
		face[count].vert = new VertexID[3];

		face[count].vert[0].vertIndex = 0;
		face[count].vert[1].vertIndex = u;
		face[count].vert[2].vertIndex = v;
		u = v;
		v = v + 1;
		count++;
	}
}

void Mesh::CreateHeliRearBotSide(int numVertexEachEdge, float alpha, float alphaForY)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = -1.15f;

	for (int j = 0; j < numVertexEachEdge; j++) {
		float z = maxZ;
		float y = -1.0 + deltaY * j;
		float x = maxX;
		pt[j].set(x, y, z);
	}

	maxZ = 14.0f;
	maxX = 0.75f;
	float maxY = 0.0f;
	float sucker = 1.0;

	/*for (int i = 1; i < numVertexEachEdge; i++) {
	float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
	for (int j = 0; j < numVertexEachEdge; j++) {
	float z = pt[(i-1)*numVertexEachEdge + j].z + alphaZ;
	float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
	float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
	float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
	float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
	pt[i*numVertexEachEdge + j].set(x, y, z);
	}
	sucker -= deltaY;
	}*/

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		for (int j = 0; j < numVertexEachEdge; j++) {
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
			float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
			float alphaY = (pt[j].y*alphaForY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliRearTopSide(int numVertexEachEdge, float alpha, float alphaForY)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = 1.75f;

	for (int j = 0; j < numVertexEachEdge; j++) {
		float z = maxZ;
		float y = -1.0 + deltaY * j;
		float x = maxX;
		pt[j].set(x, y, z);
	}

	maxZ = 14.0f;
	maxX = 1.25f;
	float maxY = 0.0f;
	float sucker = 1.0;

	/*for (int i = 1; i < numVertexEachEdge; i++) {
	float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
	for (int j = 0; j < numVertexEachEdge; j++) {
	float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
	float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
	float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
	float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
	float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
	pt[i*numVertexEachEdge + j].set(x, y, z);
	}
	sucker -= deltaY;
	}*/

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		for (int j = 0; j < numVertexEachEdge; j++) {
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
			float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
			float alphaY = (pt[j].y*alphaForY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliRearTopSideLeft(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.0f;
	float maxX = 1.75f;

	for (int j = 0; j < numVertexEachEdge; j++) {
		float z = maxZ;
		float y = -1.0 + deltaY * j;
		float x = maxX;
		pt[j].set(x, y, z);
	}

	maxZ = 18.0f;
	maxX = 0.0f;
	float maxY = 0.0f;
	float sucker = 1.0;

	for (int i = 1; i < numVertexEachEdge; i++) {
		float alphaZ = (maxZ - pt[0].z) / (numVertexEachEdge - 1);
		for (int j = 0; j < numVertexEachEdge; j++) {
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float alphaX = (maxX - pt[j].x) / (numVertexEachEdge - 1);
			float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
			float x = pt[(i - 1)*numVertexEachEdge + j].x + (sucker*alpha + 1)*alphaX;
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateHeliRear(int numVertexEachEdge) {
	numVerts = numVertexEachEdge * numVertexEachEdge * 50;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	float maxZ = 11.001f;
	float maxX = -1.15f;

	int k = 0;
	// bot
	for (int j = 0; j < numVertexEachEdge; j++) {
		float z = maxZ;
		float y = 1.0 - deltaY * j;
		float x = maxX - .025;
		pt[k].set(x, y, z);
		k++;
	}

	//bot right
	int numV = 10;

	deltaY = 2.0f / (numV - 1);

	float smallAlpha = 0.5;
	float sucker = 1.0;
	float preX = -1.15 - .025;
	float preY = -1;
	for (int j = 0; j < numV; j++) {
		float Ax = (-1.15 + 1) / numV;
		float Ay = (-1.25 - .12 + 1) / numV;
		float x = preX - Ax;
		float y = preY + (sucker*smallAlpha + 1)*Ay;
		float z = 11;

		preX = x;
		preY = y;

		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	//right

	maxZ = 11.0f;
	float maxY = -1.25 - .12;
	sucker = 1.0f;

	for (int j = 1; j < numVertexEachEdge; j++) {
		float z = 11.0;
		float x = -1.0 + deltaX * j;
		//float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
		float y = -1.25 - .12;
		pt[k].set(x, y, z);
		k++;
	}

	//righttop

	numV = 10;

	deltaY = 2.0f / (numV - 1);

	smallAlpha = 0.5;
	sucker = 1.0;
	preX = 1.5;
	preY = -1.25 - .12;
	for (int j = 1; j < numV; j++) {
		float Ax = (1.75 + .05 - 1.5) / numV;
		float Ay = (-1.0 + 1.25 + .03) / numV;
		float x = preX + Ax;
		float y = preY + (sucker*smallAlpha + 1)*Ay;
		float z = 11.0;

		preX = x;
		preY = y;

		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	/*for (int i = 1; i <numVertexEachEdge; i++) {
	float maxY = pt[i + numVertexEachEdge - 1].y;
	float maxX = pt[i + numVertexEachEdge - 1].x;
	sucker = 1.0;
	float startY = pt[i].y;
	float startX = pt[i].x;
	for (int j = 0; j < numV; j++) {
	float alphaY = (maxY - pt[i].y) / (numV);
	float alphaX = (maxX - pt[i].x) / (numV);
	if (j != 0) {
	startY = pt[k - 1].y; startX = pt[k - 1].x;
	}
	float y = startY + (sucker*smallAlpha + 1)*alphaY;
	float z = pt[i].z;
	float x = startX + alphaX;
	pt[k].set(x, y, z);
	k++;
	sucker -= deltaY;
	}
	}*/

	//top
	maxZ = 11.0f;
	maxX = 1.75f;


	for (int j = 0; j < numVertexEachEdge; j++) {
		float z = maxZ;
		float y = -1.0f + 2.0f / (numVertexEachEdge - 1) * j;
		float x = maxX + .05;
		pt[k].set(x, y, z);
		k++;
	}

	//lefttop

	numV = 10;

	deltaY = 2.0f / (numV - 1);

	smallAlpha = 0.5;
	sucker = 1.0;
	preX = 1.75 + .05;
	preY = 1.0;
	for (int j = 0; j < numV; j++) {
		float Ax = (1.5 - 1.75) / numV;
		float Ay = (1.25 + .12 - 1) / numV;
		float x = preX + Ax;
		float y = preY + (sucker*smallAlpha + 1)*Ay;
		float z = 11.0;

		preX = x;
		preY = y;

		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}

	//left 
	maxZ = 11.0f;
	maxY = 1.25f;
	sucker = 1.0f;

	for (int j = 1; j < numVertexEachEdge; j++) {
		float z = 11.0;
		float x = -1.0 + deltaX * (numVertexEachEdge - j - 1);
		//float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
		float y = 1.25 + .12;
		pt[k].set(x, y, z);
		k++;
	}

	//leftbot

	numV = 10;

	deltaY = 2.0f / (numV - 1);


	smallAlpha = 0.5;
	sucker = 1.0;
	preX = -1.0;
	preY = 1.25 + .12;
	for (int j = 0; j < numV; j++) {
		float Ax = (-1.15 - .025 + 1) / numV;
		float Ay = (-1.25 - .12 + 1) / numV;
		float x = preX + Ax;
		float y = preY + (sucker*smallAlpha + 1)*Ay;
		float z = 11.0;

		preX = x;
		preY = y;

		pt[k].set(x, y, z);
		k++;
		sucker -= deltaY;
	}
	smallAlpha = 0.7;
	numV = 120;
	deltaY = 2.0f / (numV - 1);

	for (int i = 0; i < k; i++) {
		float finishx = pt[i].x*0.3 + 0.7;
		float finishy = pt[i].y*0.3;
		float finishz = pt[i].z*1.2;
		sucker = 1.0;
		float aX = (finishx - pt[i].x) / (numV - 1);
		float aY = (finishy - pt[i].y) / (numV - 1);
		float aZ = (finishz - pt[i].z) / (numV - 1);
		float prex = pt[i].x;
		float prey = pt[i].y;
		float prez = pt[i].z;
		for (int j = 1; j < numV; j++) {
			float x = prex + aX /** (1 + sucker * smallAlpha)*/;
			float y = prey + aY /** (1 + sucker * smallAlpha)*/;
			float z = prez + aZ * (1 + sucker * smallAlpha);
			pt[j*k + i].set(x, y, z);
			prex = x;
			prey = y;
			prez = z;
			sucker -= deltaY;
		}
	}


	/*numFaces = 2;
	face = new Face[numFaces];
	face[0].nVerts = k;
	face[0].vert = new VertexID[k];
	for (int i = k - 1; i >= 0; i--)
	face[0].vert[k-i-1].vertIndex = i;

	face[1].nVerts = k;
	face[1].vert = new VertexID[k];
	for (int i = 2*k - 1; i >= k; i--)
	face[1].vert[2*k - i - 1].vertIndex = i;*/

	numFaces = k * (numV - 1) + 1;
	face = new Face[numFaces];
	count = 0;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < numV - 1; j++) {
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = j * k + i;
			face[count].vert[1].vertIndex = (j + 1) *k + i;
			face[count].vert[2].vertIndex = (j + 1) *k + (i + 1) % k;
			face[count].vert[3].vertIndex = j * k + (i + 1) % k;
			count++;
		}
	}
	face[count].nVerts = k;
	face[count].vert = new VertexID[k];
	for (int i = k - 1; i >= 0; i--) {
		face[count].vert[i].vertIndex = (numV - 1)*k + i;
	}
}

void Mesh::CreateWindowRight(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f + i * deltaX;
		float y = -1.0f;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
		//cout << count << " " << pt[count].x << " " << pt[count].y << " " << pt[count].z << endl;
	}

	float maxZ = 11.0f;
	float maxY = -1.25f;
	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float x = pt[(i - 1)*numVertexEachEdge + j].x;
			float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;

	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			if (pt[i*numVertexEachEdge + j].z > 7.0f || pt[i*numVertexEachEdge + j].x < -0.5f) continue;
			if (pt[i*numVertexEachEdge + j + 1].z > 7.0f) pt[i*numVertexEachEdge + j + 1].z = 7.0f;
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;

			count++;
		}
	}
}

void Mesh::CreateWindowLeft(int numVertexEachEdge, float alpha)
{
	numVerts = numVertexEachEdge * numVertexEachEdge;
	pt = new Point3[numVerts];

	float offset = 0.15f;

	int count = 0;
	float deltaY = 2.0f / (numVertexEachEdge - 1);
	float deltaX = 2.5f / (numVertexEachEdge - 1);

	for (int i = 0; i < numVertexEachEdge; i++) {
		float x = -1.0f + i * deltaX;
		float y = 1.0f;
		float z = (x + 0.05f) * (x + 0.05f) + y * y;
		pt[count].set(x, y, z);
		count++;
		//cout << count << " " << pt[count].x << " " << pt[count].y << " " << pt[count].z << endl;
	}

	float maxZ = 11.0f;
	float maxY = 1.25f;

	float sucker = 1.0f;

	for (int i = 1; i < numVertexEachEdge; i++) {
		for (int j = 0; j < numVertexEachEdge; j++) {
			float alphaZ = (maxZ - pt[j].z) / (numVertexEachEdge - 1);
			float z = pt[(i - 1)*numVertexEachEdge + j].z + alphaZ;
			float x = pt[(i - 1)*numVertexEachEdge + j].x;
			float alphaY = (maxY - pt[j].y) / (numVertexEachEdge - 1);
			float y = pt[(i - 1)*numVertexEachEdge + j].y + (sucker*alpha + 1)*alphaY;
			pt[i*numVertexEachEdge + j].set(x, y, z);
		}
		sucker -= deltaY;
	}

	numFaces = pow(numVertexEachEdge - 1, 2);
	face = new Face[numFaces];

	count = 0;
	for (int i = 0; i < (numVertexEachEdge - 1); i++) {
		for (int j = 0; j < (numVertexEachEdge - 1); j++) {
			if (pt[i*numVertexEachEdge + j].z > 7.0f || pt[i*numVertexEachEdge + j].x < -0.5f) continue;
			if (pt[i*numVertexEachEdge + j + 1].z > 7.0f) pt[i*numVertexEachEdge + j + 1].z = 7.0f;
			face[count].nVerts = 4;
			face[count].vert = new VertexID[4];

			face[count].vert[0].vertIndex = i * numVertexEachEdge + j;
			face[count].vert[3].vertIndex = (i + 1) * numVertexEachEdge + j;
			face[count].vert[2].vertIndex = (i + 1) * numVertexEachEdge + j + 1;
			face[count].vert[1].vertIndex = i * numVertexEachEdge + j + 1;

			count++;
		}
	}
}