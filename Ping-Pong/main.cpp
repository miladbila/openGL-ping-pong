#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL/glut.h>
#include <iostream>

GLfloat ballRadius = 0.05f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
int refreshMillis = 16;


void display() {
	glClearColor(0, 0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();
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
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ping Pong");
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}