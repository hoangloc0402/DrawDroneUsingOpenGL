
		#pragma region Define
#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "glut.h"
#include "MaterialColor.h"

#define DEG2RAD (3.14159f/180.0f)

using namespace std;

GLfloat angle;
int		screenWidth = 800;
int		screenHeight = 800;
int smallBladeSpeed = 0; //Tốc độ quạt, ấn "+" "-" để thay đổi

int o_x, o_y;
float eyeX, eyeY, eyeZ;
float alpha = 45;
float beta = 45;
float deltaAngle = 5;
float dR = 0.2;
float Radius = 4;

Point3 L;
float theta, upTheta;
float thetaAngle = 15.0;
int upThetaState = 0;


//Vẽ trục toạ độ
void drawAxis() {
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(40, 0, 0);
	setMaterial(blackplastic);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 40, 0);
	setMaterial(emerald);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 40);
	glEnd();
}

//Các hàm callback
#pragma region Callback Func
void processTimer(int value) {
	angle += (GLfloat)value / 5;
	if (angle > 360.0f) angle -= 360.0f;
	glutTimerFunc(5, processTimer, value);
	glutPostRedisplay();
}

void onKeyboardDown(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		smallBladeSpeed += 2;
		break;
	case '-':
		smallBladeSpeed -= 2;
		break;
	case '5':
		L.z += 0.1*cos(theta*DEG2RAD);
		L.x += 0.1*sin(theta*DEG2RAD);
		upThetaState = -1;
		break;
	case '2':
		L.z -= 0.1*cos(theta*DEG2RAD);
		L.x -= 0.1*sin(theta*DEG2RAD);
		upThetaState = 1;
		break;
	case '1':
		theta += 1;
		break;
	case '3':
		theta -= 1;
		break;
	case '4':
		L.y += 0.1;
		upThetaState = 1;
		break;
	case '6':
		L.y -= 0.1;
		upThetaState = -1;
		break;

	default:
		upTheta = 0;
		break;
	}

	if (smallBladeSpeed > 20) smallBladeSpeed = 20;
	else if (smallBladeSpeed < 0) smallBladeSpeed = 0;
	glutPostRedisplay();
}

void onKeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case '5':
		upThetaState = 0;
		break;
	case '2':
		upThetaState = 0;
		break;
		break;
	case '4':
		upThetaState = 0;
		break;
	case '6':
		upThetaState = 0;
		break;
	default:
		upTheta = 0;
		break;
	}

	if (smallBladeSpeed > 20) smallBladeSpeed = 20;
	else if (smallBladeSpeed < 0) smallBladeSpeed = 0;
	if (upTheta > thetaAngle) upTheta = thetaAngle;
	else if (upTheta < -thetaAngle) upTheta = -thetaAngle;
	glutPostRedisplay();
}

void onSpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		beta -= deltaAngle;
		break;
	case GLUT_KEY_DOWN:
		beta += deltaAngle;
		break;
	case GLUT_KEY_LEFT:
		alpha -= deltaAngle;
		break;
	case GLUT_KEY_RIGHT:
		alpha += deltaAngle;
		break;
	case GLUT_KEY_PAGE_UP:		
		Radius -= dR;
		break;
	case GLUT_KEY_PAGE_DOWN:	
		Radius += dR;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void onReshape(int w, int h) {
	int size = min(w, h);
	glViewport(0, 0, size, size);
}

void onMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		o_x = x;
		o_y = y;
	}
}

void onMotion(int x, int y) {
	alpha += (x - o_x) / 2;
	beta += (y - o_y) / 2;
	o_x = x;
	o_y = y;
	glutPostRedisplay();
}

#pragma endregion

#pragma region drawTailFunc

void drawCameraLens() {
	Mesh camLens;
	camLens.DrawCameraLens();
	camLens.CalculateFacesNorm();
	setMaterial(whiteplastic);
	camLens.Draw();
}

void drawTailFanBlade(float angle) {
	glPushMatrix(); {
		Mesh blade;
		glRotatef(angle, 0, 1, 0);
		glTranslated(0, 0.12, 0);
		glRotatef(-45, 1, 0, 0);
		glTranslated(0, 0, -0.1);
		setMaterial(silver);
		blade.CreatePanel(0.45, 0.15, 0.015, 0.02);
		blade.Draw();
	}
	glPopMatrix();
}

void drawTailSwing() {
	Mesh swingPart1, swingPart2;
	swingPart1.CreatePanel(0.5, 0.15, 0.06, 0.02);
	swingPart2.CreatePanel(0.3, 0.15, 0.04, 0.02);
	glPushMatrix(); {
		swingPart1.Draw();
		glTranslatef(0.45, 0, 0);
		glTranslatef(-0.05, -0.1, 0);
		glRotatef(45, 0, 0, 1);
		swingPart2.Draw();
	}
	glPopMatrix();
}

void drawTailFanBox() {
	Mesh tailFanPivot;
	Mesh tailFanBox1, tailFanBox2, tailFanBox3;
	tailFanPivot.CreateHoleCylinder(0.2, 360, 0, 0.15, 0.15);
	tailFanBox1.CreateHoleCylinder(0.2, 360, 0.5, 0.7, 0.6);
	tailFanBox2.CreateHoleCylinder(0.1, 360, 0.5, 0.7, 0.7);
	tailFanBox3.CreateHoleCylinder(0.2, 360, 0.5, 0.6, 0.7);
	glPushMatrix(); {
		glTranslatef(0, 0.05, 0);
		tailFanBox1.Draw();
		glTranslatef(0, -0.1, 0);
		tailFanBox2.Draw();

		glTranslatef(0, -0.2, 0);
		tailFanBox3.Draw();

		glTranslatef(0, 0.15, 0);
		tailFanPivot.Draw();

		glRotatef(-smallBladeSpeed*angle/2, 0 ,1, 0);
		for (int i = 0; i < 360; i += 45)
			drawTailFanBlade(i);
	}
	glPopMatrix();
}

void drawTailPivot() {
	Mesh bigTailPivot, smallTailPivot;
	bigTailPivot.CreateEclipseCylinder(2.5, 360, 0.18, 0.15);
	smallTailPivot.CreateEclipseCylinder(2.5, 360, 0.1, 0.05);
	glPushMatrix(); {
	glTranslatef(0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bigTailPivot.Draw();
	glTranslatef(0, 0, -0.12);
	glRotatef(90, 0, 1, 0);
	smallTailPivot.Draw();
	}
	glPopMatrix();
}

void drawTailFlag() {
	glPushMatrix();
	Mesh tailFlag;
	Mesh star;
	tailFlag.CreateFlag(0.4, 0.25, 0.5, 0.3, 0.32, 0.07, 0.02);
	star.CreateStar();
	glPushMatrix(); {
		glScalef(-1, 1, 1);
		glRotatef(-90, 1, 0, 0);
		setMaterial(redplastic);
		tailFlag.Draw();
	}
	glPopMatrix();
	setMaterial(gold);
	glTranslatef(-0.43, 0.3, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.001, 0.0015, 0.001);
	star.Draw();
	glPopMatrix();
}

void drawHeliTail() {
	glPopMatrix(); {
		glRotatef(90, 0, 0, 1);
		drawTailFanBox();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(0, 0, -0.35);
		drawTailPivot();
	}
	glPopMatrix();

	glPushMatrix(); {
		glTranslatef(0, 0, 1.4);
		drawTailSwing();
		glScalef(-1, 1, 1);
		drawTailSwing();
		glScalef(1, 1, -1);
		drawTailSwing();
		glScalef(-1, 1, 1);
		drawTailSwing();
	}
	glPopMatrix();

	glPushMatrix(); {
		glTranslatef(0, 0.5, 0.75);
		glRotatef(-90, 0, 1, 0);
		glScalef(2, 2, 2);
		drawTailFlag();
	}
	glPopMatrix();
	
}

void setUpTheta() {
	if (upThetaState == 0) {
		if (upTheta < 0) upTheta += 0.1;
		else upTheta -= 0.1;
	}
	else if (upThetaState > 0){
		upTheta += 0.2;
	}
	else upTheta -= 0.2;

	if (upTheta > thetaAngle) upTheta = thetaAngle;
	else if (upTheta < -thetaAngle) upTheta = -thetaAngle;
}
#pragma endregion

void myDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	eyeX = Radius * cos(DEG2RAD * alpha)*cos(DEG2RAD*beta);
	eyeY = Radius * sin(DEG2RAD * beta);
	eyeZ = Radius * sin(DEG2RAD * alpha)*sin(DEG2RAD*beta);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glViewport(0, 0, screenWidth, screenHeight);
	gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);

		#pragma region Light

	GLfloat	lightDiffuse[] = { 0.6f,  0.6f,  0.6f,  1.0f };
	GLfloat	lightSpecular[] = { 0.6f,  0.6f,  0.6f,  1.0f };
	GLfloat	lightAmbient[] = { 0.4f,  0.4f,  0.4f,  1.0f };
	GLfloat light_position[] = {3.0f, 3.0f, 3.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat	lightDiffuse1[] = {0.7f,  0.7f,  0.7f,  0.2f };
	GLfloat	lightSpecular1[] = { 0.7f,  0.7f,  0.7f,  0.8f };
	GLfloat	lightAmbient1[] = { 0.4f,  0.4f,  0.4f,  0.6f };
	GLfloat light_position1[] = { 6.0f, 0.0f, 0.0f, 0.3f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	GLfloat	lightDiffuse2[] = { 0.3f,  0.3f, 0.3f,  0.5f };
	GLfloat	lightSpecular2[] = { 0.3f,  0.3f, 0.3f,  .20f };
	GLfloat	lightAmbient2[] = { 0.4f,  0.4f,  0.4f,  0.3f };
	GLfloat light_position2[] = { 0.0f, 6.0f, 0.0f, 0.8f };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);

#pragma endregion

	//drawCameraLens();
	drawAxis();

	setUpTheta();

	glTranslatef(L.x, L.y, L.z);
	glRotatef(theta, 0, 1, 0);
	glRotatef(-upTheta, 1, 0, 0);
	drawHeliTail();

	glFlush();
	glutSwapBuffers();
	//upTheta = 0;
}


int main(int argc, CHAR* argv[]) {

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Draw Electric Fan");

	glutDisplayFunc(myDisplay);
	glutTimerFunc(5, processTimer, 5);
	glutKeyboardFunc(onKeyboardDown);
	glutKeyboardUpFunc(onKeyboardUp);
	glutSpecialFunc(onSpecialKey);
	glutReshapeFunc(onReshape);
	glutMotionFunc(onMotion);
	glutMouseFunc(onMouseDown);

	L.set(0, 0, 0);
	theta = upTheta = 0;

	glutMainLoop();
	return 0;
}

