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

using namespace std;
void drawBall() {
	glPushMatrix();
	glTranslatef(ballX, ballY, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	switch (ballColor)
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
	}	for (int i = 0; i <= 32; ++i) {
		float angle = i * 2.0f * PI / 32;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();
	glPopMatrix();
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
	glVertex2f(0.01, -0.2);
	glVertex2f(0.01, 0.2);
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
	glVertex2f(0.01, -0.2);
	glVertex2f(0.01, 0.2);
	glEnd();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawBall();
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

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
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

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
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