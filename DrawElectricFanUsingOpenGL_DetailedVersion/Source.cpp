
		#pragma region Define

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "glut.h"
#define DEG2RAD (3.14159f/180.0f)
using namespace std;

GLfloat angle;
int		screenWidth = 800;
int		screenHeight = 800;
const int circleCount = 100; //Số lượng vòng tròn trong lưới quạt
int fanSpeed = 0; //Tốc độ quạt, ấn "+" "-" để thay đổi
float orthorScaler = 3; //Tham số để scale to nhỏ, tuỳ chỉnh bằng pageup và pagedown
bool swing = false; //Thay đổi chế độ swing của quạt, ấn "s" để thay đổi
bool displayBody = false; //Biến xác định có hiển thị thân quạt hay không, ấn "b" để thay đổi
bool displayEngine = false; //Biến xác định có hiển thị động cơ hay không, ấn "e" để thay đổi
bool displayDome = false; //Biến xác định có hiển thị lưới quạt hay không, ấn "d" để thay đổi
bool displayFanBlade = false; //Biến xác định có hiển thị cánh quạt hay không, ấn "f" để thay đổi
					   //Các tham số điều chỉnh góc nhìn khi click kéo chuột
int o_x, o_y;
float eyeX, eyeY, eyeZ;
float centerX, centerY, centerZ;
float upX, upY, upZ;
float alpha = 45;
float beta = 45;
float deltaAngle = 5;
float dR = 0.2;
float Radius = 4;

enum material {
	brass, bronze, polishedbronze, chrome, copper, polishedcopper, gold, pollishedgold, tin, silver, polishedsilver,
	emerald, jade, obsidian, perl, ruby, turquoise, blackplastic, cyanplastic, greenplastic, redplastic, whiteplastic,
	yellowplastic, blackrubber, cyanrubber, greenrubber, redrubber, whiterubber, yellowrubber
};

#pragma endregion


//Hàm set material
#pragma region Material
void applyMaterial(float ambient[], float diffuse[], float specular[], float shiness) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void setMaterial(material myMaterial) {
	switch (myMaterial) {
	case brass: {
		float mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
		float mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
		float mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
		float shine = 2.8974f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case bronze: {
		float mat_ambient[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
		float mat_diffuse[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
		float mat_specular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
		float shine = 2.6f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedbronze: {
		float mat_ambient[] = { 0.25f, 0.148f, 0.06475f, 1.0f };
		float mat_diffuse[] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
		float mat_specular[] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
		float shine = 7.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case chrome: {
		float mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		float mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
		float shine = 7.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case copper: {
		float mat_ambient[] = { 0.19125f, 0.0735f, 0.0225f, 1.0f };
		float mat_diffuse[] = { 0.7038f, 0.27048f, 0.0828f, 1.0f };
		float mat_specular[] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedcopper: {
		float mat_ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
		float mat_diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
		float mat_specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
		float shine = 5.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case gold: {
		float mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
		float mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
		float mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
		float shine = 5.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case pollishedgold: {
		float mat_ambient[] = { 0.24725f, 0.2245f, 0.0645f, 1.0f };
		float mat_diffuse[] = { 0.34615f, 0.3143f, 0.0903f, 1.0f };
		float mat_specular[] = { 0.797357f, 0.723991f, 0.208006f, 1.0f };
		float shine = 8.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case tin: {
		float mat_ambient[] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
		float mat_diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
		float mat_specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
		float shine = 9.84615f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case silver: {
		float mat_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
		float mat_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
		float mat_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
		float shine = 5.2f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case polishedsilver: {
		float mat_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
		float mat_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
		float mat_specular[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
		float shine = 8.6f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case emerald: {
		float mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
		float mat_diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
		float mat_specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
		float shine = 7.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case jade: {
		float mat_ambient[] = { 0.135f, 0.2225f, 0.1575f, 0.95f };
		float mat_diffuse[] = { 0.54f, 0.89f, 0.63f, 0.95f };
		float mat_specular[] = { 0.316228f, 0.316228f, 0.316228f, 0.95f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case obsidian: {
		float mat_ambient[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
		float mat_diffuse[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
		float mat_specular[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
		float shine = 3.4f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case perl: {
		float mat_ambient[] = { 0.25f, 0.20725f, 0.20725f, 0.922f };
		float mat_diffuse[] = { 1.0f, 0.829f, 0.829f, 0.922f };
		float mat_specular[] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
		float shine = 1.264f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case ruby: {
		float mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
		float mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
		float mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
		float shine = 7.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case turquoise: {
		float mat_ambient[] = { 0.1f, 0.18725f, 0.1745f, 0.8f };
		float mat_diffuse[] = { 0.396f, 0.74151f, 0.69102f, 0.8f };
		float mat_specular[] = { 0.297254f, 0.30829f, 0.306678f, 0.8f };
		float shine = 1.8f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case blackplastic: {
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case cyanplastic: {
		float mat_ambient[] = { 0.0f,0.1f,0.06f ,1.0f };
		float mat_diffuse[] = { 0.0f,0.50980392f,0.50980392f,1.0f };
		float mat_specular[] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case greenplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
		float mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case redplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.0f,0.0f,1.0f };
		float mat_specular[] = { 0.7f,0.6f,0.6f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case whiteplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.55f,0.55f,0.55f,1.0f };
		float mat_specular[] = { 0.70f,0.70f,0.70f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case yellowplastic: {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.0f,1.0f };
		float mat_specular[] = { 0.60f,0.60f,0.50f,1.0f };
		float shine = 3.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case blackrubber: {
		float mat_ambient[] = { 0.02f, 0.02f, 0.02f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case cyanrubber: {
		float mat_ambient[] = { 0.05f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.4f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.04f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case greenrubber: {
		float mat_ambient[] = { 0.0f,0.05f,0.0f,1.0f };
		float mat_diffuse[] = { 0.4f,0.5f,0.4f,1.0f };
		float mat_specular[] = { 0.04f,0.7f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case redrubber: {
		float mat_ambient[] = { 0.05f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.4f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.04f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case whiterubber: {
		float mat_ambient[] = { 0.05f,0.05f,0.05f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
		float mat_specular[] = { 0.7f,0.7f,0.7f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	case yellowrubber: {
		float mat_ambient[] = { 0.05f,0.05f,0.0f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.4f,1.0f };
		float mat_specular[] = { 0.7f,0.7f,0.04f,1.0f };
		float shine = 1.0f;
		applyMaterial(mat_ambient, mat_diffuse, mat_specular, shine);
		break;
	}
	default:
		break;
	}
}
#pragma endregion


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
	glutTimerFunc(25, processTimer, value);
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		fanSpeed += 4;
		break;
	case '-':
		fanSpeed -= 4;
		break;
	case 's':
		if (swing) swing = false;
		else swing = true;
		break;
	case 'b':
		if (displayBody) displayBody = false;
		else displayBody = true;
		break;
	case 'd':
		if (displayDome) displayDome = false;
		else displayDome = true;
		break;
	case 'f':
		if (displayFanBlade) displayFanBlade = false;
		else displayFanBlade = true;
		break;
	case 'e':
		if (displayEngine) displayEngine = false;
		else displayEngine = true;
		break;
	case 'a':
		displayBody = displayEngine = displayDome = displayFanBlade = true;
		break;
	default: break;
	}
	if (fanSpeed > 20) fanSpeed = 20;
	if (fanSpeed < 0) fanSpeed = 0;
	glutPostRedisplay();
}

void onSpecialKey(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_PAGE_UP:		// Zoom in
		orthorScaler -= 0.2;
		break;
	case GLUT_KEY_PAGE_DOWN:	// Zoom out
		orthorScaler += 0.2;
		break;
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
	default:
		break;
	}
	if (orthorScaler > 10) orthorScaler = 10;
	if (orthorScaler < 0.5) orthorScaler = 0.5;
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


void view() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glOrtho(-orthorScaler, orthorScaler, -orthorScaler, orthorScaler, -orthorScaler, orthorScaler);
}

void initOpenGL() {
	//setup projection type
	//glFrustrum: define viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-2.0,	//left
		2.0,	//right
		-2.0,	//bottom
		2.0,	//top
		2.0,	//near
		10.0	//far
	);
	//Default MatrixMode is MODELVIEW 
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void initialize() {
	eyeX = Radius * cos(DEG2RAD * alpha);
	eyeY = Radius * sin(DEG2RAD * beta);
	eyeZ = Radius * sin(DEG2RAD * alpha);
	centerX = 0;
	centerY = 0;
	centerZ = 0;
	upX = 0;
	upY = 1;
	upZ = 0;
}

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

void myDisplay() {
	initOpenGL();
	initialize();
	view();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	drawAxis();
	glViewport(0, 0, screenWidth, screenHeight);

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

	//drawCameraLens();

	drawHeliTail();

	

	glFlush();
	glutSwapBuffers();
}


int main(int argc, CHAR* argv[]) {

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Draw Electric Fan");

	glutDisplayFunc(myDisplay);
	glutTimerFunc(5, processTimer, 5);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc(onSpecialKey);
	glutReshapeFunc(onReshape);
	glutMotionFunc(onMotion);
	glutMouseFunc(onMouseDown);

	glutMainLoop();
	return 0;
}

