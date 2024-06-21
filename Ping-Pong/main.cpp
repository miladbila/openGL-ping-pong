#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL/glut.h>
#include <iostream>

const float PI = 3.14159265f;

GLfloat ballRadius = 0.05f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
GLfloat ballX = 0.1f;
GLfloat ballY = 0.0f;
GLfloat ySpeed = 0.01f;
GLfloat xSpeed = 0.02f;
GLfloat player1Y = 0.0f;
GLfloat player2Y = 0.0f;
int refreshMillis = 16;

bool player1up = false;
bool player1down = false;
bool player2up = false;
bool player2down = false;

int player1Color = 0;
int player2Color = 0;
int ballColor = 0;

int player1Score = 0;
int player2Score = 0;

int trail = 5;

int ballMode = 1;

using namespace std;

void drawTriangle() {
	for (size_t i = 0; i < trail; i++)
	{
		glPushMatrix();
		glTranslatef(ballX - (i * xSpeed), ballY - (i * ySpeed), 0.0f);
		switch (ballColor)
		{
		case 1:
			glColor4f(0.0f, 0.0f, 1.0f, 1.0 / (i + 1));
			break;
		case 2:
			glColor4f(1.0f, 0.0f, 0.0f, 1.0 / (i + 1));
			break;
		default:
			glColor4f(1.0f, 1.0f, 1.0f, 1.0 / (i + 1));
			break;
		}
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.1, 0);
		glVertex2f(0.05, 0.08);
		glEnd();
		glPopMatrix();
	}
}

void drawRectangle() {
	for (size_t i = 0; i < trail; i++)
	{
		glPushMatrix();
		glTranslatef(ballX - (i * xSpeed), ballY - (i * ySpeed), 0.0f);
		switch (ballColor)
		{
		case 1:
			glColor4f(0.0f, 0.0f, 1.0f, 1.0 / (i + 1));
			break;
		case 2:
			glColor4f(1.0f, 0.0f, 0.0f, 1.0 / (i + 1));
			break;
		default:
			glColor4f(1.0f, 1.0f, 1.0f, 1.0 / (i + 1));
			break;
		}
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0.1, 0);
		glVertex2f(0.1, 0.1);
		glVertex2f(0, 0.1);
		glEnd();
		glPopMatrix();
	}
}

void drawBall() {
	for (size_t i = 0; i < trail; i++) {
		glPushMatrix();
		glTranslatef(ballX - (i * xSpeed), ballY - (i * ySpeed), 0.0f);
		switch (ballColor)
		{
		case 1:
			glColor4f(0.0f, 0.0f, 1.0f, 1.0 / (i + 1));
			break;
		case 2:
			glColor4f(1.0f, 0.0f, 0.0f, 1.0 / (i + 1));
			break;
		default:
			glColor4f(1.0f, 1.0f, 1.0f, 1.0 / (i + 1));
			break;
		}
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i <= 32; ++i) {
			float angle = i * 2.0f * PI / 32;
			glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
		}
		glEnd();
		glPopMatrix();
	}
}

void player1() {
	glPushMatrix();
	glTranslatef(clipAreaXLeft, player1Y, 0.0f);
	glBegin(GL_QUADS);
	switch (player1Color)
	{
	case 1:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case 2:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	default:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}
	glVertex2f(0, 0.2);
	glVertex2f(0, -0.2);
	glVertex2f(0.02, -0.2);
	glVertex2f(0.02, 0.2);
	glEnd();
	glPopMatrix();
}

void player2() {
	glPushMatrix();
	glTranslatef(clipAreaXRight - 0.01, player2Y, 0.0f);
	glBegin(GL_QUADS);
	switch (player2Color)
	{
	case 1:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case 2:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	default:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}	glVertex2f(0, 0.2);
	glVertex2f(0, -0.2);
	glVertex2f(0.02, -0.2);
	glVertex2f(0.02, 0.2);
	glEnd();
	glPopMatrix();
}

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	char s[10];
	glColor3f(1.0, 1.0, 1.0);
	sprintf_s(s, "%ld", player1Score);
	renderBitmapString(-0.5, 0.8, GLUT_BITMAP_TIMES_ROMAN_24, s);
	glColor3f(1.0, 1.0, 1.0);
	sprintf_s(s, "%ld", player2Score);
	renderBitmapString(0.5, 0.8, GLUT_BITMAP_TIMES_ROMAN_24, s);
	switch (ballMode)
	{
	case 1:
		drawBall();
		break;
	case 2:
		drawTriangle();
		break;
	case 3:
		drawRectangle();
		break;
	}
	player1();
	player2();
	glutSwapBuffers();
	if (ballY > ballYMax) {
		ballY = ballYMax;
		ySpeed = -ySpeed;
	}
	else if (ballY < ballYMin) {
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}
	else {
		ballY += ySpeed;
	}
	if ((ballX > ballXMax)) {
		if (ballY > player2Y + 0.2 || ballY < player2Y - 0.2)
		{
			ballX = 0;
			ballY = 0;
			player1Color = 1;
			player2Color = 2;
			player1Score++;
		}
		else
		{
			ballX = ballXMax;
			xSpeed = -xSpeed;
			ballColor = player2Color;
		}
	}
	else if ((ballX < ballXMin)) {
		if (ballY > player1Y + 0.2 || ballY < player1Y - 0.2)
		{
			ballX = 0;
			ballY = 0;
			player2Color = 1;
			player1Color = 2;
			player2Score++;
		}
		else
		{
			ballX = ballXMin;
			xSpeed = -xSpeed;
			ballColor = player1Color;
		}
	}
	else {
		ballX += xSpeed;
	}
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else
	{
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	clipAreaXLeft += 0.05;
	clipAreaXRight -= 0.05;
	clipAreaYBottom += 0.05;
	clipAreaYTop -= 0.3;
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w') {
		player1up = true;
	}
	else if (key == 's')
	{
		player1down = true;
	}

	if (key == 'o') {
		player2up = true;
	}
	else if (key == 'l')
	{
		player2down = true;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	if (key == 'w') {
		player1up = false;
	}
	else if (key == 's')
	{
		player1down = false;
	}

	if (key == 'o') {
		player2up = false;
	}
	else if (key == 'l')
	{
		player2down = false;
	}
}

void idle() {
	if (player1up)
	{
		if (player1Y + 0.2 < clipAreaYTop) {
			player1Y += 0.0000005;
		}
	}
	if (player1down)
	{
		if (player1Y - 0.2 > clipAreaYBottom) {
			player1Y -= 0.0000005;
		}
	}
	if (player2up)
	{
		if (player2Y + 0.2 < clipAreaYTop) {
			player2Y += 0.0000005;
		}
	}
	if (player2down)
	{
		if (player2Y - 0.2 > clipAreaYBottom) {
			player2Y -= 0.0000005;
		}
	}
}

void menu(int item)
{
	switch (item)
	{
	case 1:
		xSpeed *= 2;
		ySpeed *= 2;
		break;
	case 2:
		xSpeed /= 2;
		ySpeed /= 2;
		break;
	case 3:
		if (trail == 1)
		{
			trail = 6;
		}
		else
		{
			trail = 1;
		}
		break;
	case 4:
		exit(0);
		break;
	case 5:
		ballMode = 1;
		break;
	case 6:
		ballMode = 2;
		break;
	case 7:
		ballMode = 3;
		break;
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int subMenu = glutCreateMenu(menu);
	glutAddMenuEntry("circle", 5);
	glutAddMenuEntry("triangle", 6);
	glutAddMenuEntry("rectangle", 7);

	glutCreateMenu(menu);
	glutAddSubMenu("Change ball", subMenu);
	glutAddMenuEntry("speed up", 1);
	glutAddMenuEntry("speed down", 2);
	glutAddMenuEntry("trail", 3);
	glutAddMenuEntry("Exit", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA);
	glEnable(GL_BLEND);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ping Pong");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}