#include<GL/glut.h>
#include<iostream>

using namespace std;

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(45);
	glBegin(GL_QUAD_STRIP);
	glVertex2d(150, 100);
	glVertex2d(250, 100);
	glVertex2d(250, 200);
	glVertex2d(150, 200);
	glVertex2d(300, 300);
	glVertex2d(400, 300);
	glEnd();
	glBegin(GL_LINES);
	glPointSize(2);
	glVertex2d(32.0, 45.0);
	glVertex2d(45.0, 56.0);
	glEnd();
	glFlush();
}

void myInit() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glColor3f(240.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Ex1");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 1;
}
