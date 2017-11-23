//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

double rotateX = 0;
double rotateY = 0;
double rotateZ = 0;
double Angle = 0;

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		rotateX += 5; break;
	case GLUT_KEY_DOWN:
		rotateX -= 5; break;
	case GLUT_KEY_RIGHT:
		rotateY += 5; break;
	case GLUT_KEY_LEFT:
		rotateY -= 5; break;
	case GLUT_KEY_PAGE_UP:
		rotateZ += 5; break;
	case GLUT_KEY_PAGE_DOWN:
		rotateZ -= 5; break;
	}
	glutPostRedisplay();
}

void DisplayCube()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glRotatef(rotateZ, 0.0, 0.0, 1.0);
	glutWireCube(1);
	glFlush();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void DisplayRectangle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glutSolidTetrahedron();
	glutSwapBuffers();
}

void DisplayOctahedron()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glutSolidOctahedron();
	glutSwapBuffers();
}

void DisplayColoredRectangle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotateZ, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5f, -0.5f);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5f, 0.5f);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5f, 0.5f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void DisplayRamdomlyColoredTetrahedron()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotateZ, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glColor3ub(rand() % 255, 0.0, 0.0);
	glVertex2f(-0.5f, -0.5f);
	glColor3ub(0.0, rand() % 255, 0.0);
	glVertex2f(-0.5f, 0.5f);
	glColor3ub(0.0, 0.0, rand() % 255);
	glVertex2f(0.5f, 0.5f);
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	glVertex2f(0.5f, -0.5f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}


void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		DisplayRamdomlyColoredTetrahedron();
}

void Display3()
{
	Angle += 0.05f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glRotatef(rotateZ, 0.0, 0.0, 1.0);
	glRotatef(Angle, 0.0, 1.0, 0.0);
	glutWireSphere(50.0f, 10, 10);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello, GL");

	//glutIdleFunc(Idle);
	glutDisplayFunc(DisplayCube);
	
	//glutReshapeFunc(Reshape);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseClick);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}