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
