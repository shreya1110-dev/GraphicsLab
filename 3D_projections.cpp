#include<gl/glut.h>
#include<iostream>
#include<vector>

using namespace std;

vector<bool> keys(256,0);
int x_angle = 0, y_angle = 0, z_angle=0;

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	int n;
	cout << "1. Parallel\n2. Perspective\nEnter type of projection: ";
	cin >> n;
	if (n == 1) {
		glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 100.0);
	}
	else {
		gluPerspective(120, (GLfloat)100/(GLfloat)100, 0.1, 100.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(0.1);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glPushMatrix();
	glRotatef(x_angle, 1, 0, 0);
	glRotatef(y_angle, 0, 1, 0);
	glColor3f(120.0f, 0.0f, 0.0f);
	glutWireTeapot(1);
	glPopMatrix();
	glFlush();
}

void keyPress(unsigned char key, int x, int y) {
	keys[key] = 1;
	if (key == 'a') {
		x_angle += 45;
	}
	else if (key == 'b') {
		y_angle += 45;
	}
	if (key == 'c') {
		x_angle -= 45;
	}
	else if (key == 'd') {
		y_angle -= 45;
	}
	else {
		cout << "Invalid";
	}
	x_angle = x_angle % 360;
	y_angle = y_angle % 360;
	display();
}

void keyDown(unsigned char key, int x, int y) {
	keys[key] = 0;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Projections");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyDown);
	init();
	glutMainLoop();
	return 1;
}
