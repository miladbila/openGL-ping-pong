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
int refreshMillis = 16;

void drawBall() {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i <= 32; ++i) {
		float angle = i * 2.0f * PI / 32;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}

	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(ballX, ballY, 0.0f);
	drawBall();
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

		ballX = ballXMax;
		xSpeed = -xSpeed;

	}
	else if ((ballX < ballXMin)) {

		ballX = ballXMin;
		xSpeed = -xSpeed;
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

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ping Pong");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}