#include<iostream>
#include<gl/glut.h>

using namespace std;

float trans = 0.1;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 10.0f, 0.0f);
	glTranslatef(0.0f, -trans, 0.0f);
	glutSolidTeapot(1);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void timer(int n) {
	if (trans < 10) {
		glutPostRedisplay();
	}
	glutTimerFunc(10000/60, timer, 0);
	trans += 1;
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1.0, 0.1, 50);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0);
	//glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3D Animation");
	glutDisplayFunc(display);
	init();
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 1;
}
