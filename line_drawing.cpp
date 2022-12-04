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
	gluOrtho2D(0.0, 640.0, 0.0, 320.0);
}

void plot(double x, double y) {
	glVertex2d(x, y);
}

void dda(double x1, double x2, double y1, double y2) {
	double dx, dy, x, y, xinc, yinc;
	int steps;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy)) {
		steps = dx;
	}
	else {
		steps = dy;
	}
	x = x1;
	y = y1;
	xinc = dx / steps;
	yinc = dy / steps;
	plot(x, y);
	for (int i = 0; i < steps; i++) {
		x += xinc;
		y += yinc;
		plot(x, y);
	}
}

void bresenham(double x1, double x2, double y1, double y2) {
	double xinc, yinc, x, y, dx, dy, p0;
	xinc = 1;
	yinc = 1;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (x1 > x2) {
		xinc = -1;
	}
	if (y1 > y2) {
		yinc = -1;
	}
	x = x1;
	y = y1;
	plot(x, y);
	if (dx > dy) {
		for (int i = 0; i < dx; i++) {
			p0 = 2 * dy - dx;
			if (p0 < 0) {
				p0 += 2 * dy;
			}
			else {
				p0 += 2 * (dy - dx);
				y += yinc;
			}
			x += xinc;
			plot(x, y);
		}
	}
	else {
		for (int i = 0; i < dy; i++) {
			p0 = 2 * dx - dy;
			if (p0 < 0) {
				p0 += 2 * dx;
			}
			else {
				p0 += 2 * (dx - dy);
				x += xinc;
			}
			y += yinc;
			plot(x, y);
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	int op;
	double x1, x2, y1, y2;
	cout << "1. DDA\n2. Bresenham\nEnter option: ";
	cin >> op;
	cout << "Enter point A: ";
	cin >> x1 >> y1;
	cout << "Enter point B: ";
	cin >> x2 >> y2;
	if(op==1) {
		dda(x1, x2, y1, y2);
	}
	else {
		bresenham(x1, x2, y1, y2);
	}
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Line drawing");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
