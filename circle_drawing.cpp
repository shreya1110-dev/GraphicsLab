#include<gl/glut.h>
#include<iostream>
#include<math.h>

using namespace std;

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(240.0f, 0.0f, 0.0f);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}

void plot(double x, double y) {
	glVertex2d(x, y);
}

void circle(double xc, double yc, double r) {
	double p0, x, y;
	p0 = 1 - r;
	x = 0;
	y = r;
	cout << x << y;
	plot(x+xc, y+yc);
	while (y > x) {
		if (p0 < 0) {
			p0 += 2 * x;
		}
		else {
			p0 += 2 * x - 2 * y + 1;
			y--;
		}
		x++;
		plot(x+xc, y+yc);
		plot(x+xc, -y+yc);
		plot(-x+xc, y+yc);
		plot(-x+xc, -y+yc);
		plot(y+yc, x+xc);
		plot(y+yc, -x+xc);
		plot(-y+yc, x+xc);
		plot(-y+yc, -x+xc);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	double xc, yc, r;
	cout << "Enter the center coordinates: ";
	cin >> xc >> yc;
	cout << "Enter radius: ";
	cin >> r;
	circle(xc, yc, r);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Circle drawing");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
