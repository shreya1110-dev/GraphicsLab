#include<gl/glut.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

void writepoint(int x, int y) {
	string pt = "(" + to_string(x) + "," + to_string(y) + ")";
	glRasterPos2i(x - 25, y - 15);
	for (int k = 0; pt[k] != '\0'; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, pt[k]);
	}
}
void writepoints(vector<int> area) {
	for (int i = 0; i < area.size(); i = i + 2) {
		writepoint(area[i], area[i + 1]);
	}
}

void plot(vector<int> area) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < area.size(); i = i + 2) {
		glVertex2d(area[i], area[i + 1]);
	}
	glEnd();
	writepoints(area);
}

vector<int> window_viewport_mapping(vector<int> window, vector<int> viewport, vector<int> window_object) {
	int xwmin, ywmin, xwmax, ywmax, xvmin, yvmin, xvmax, yvmax;
	double sx, sy, xv, yv;
	vector<int> viewport_object;
	xwmin = window[0];
	xwmax = window[4];
	ywmin = window[1];
	ywmax = window[5];
	xvmin = viewport[0];
	xvmax = viewport[4];
	yvmin = viewport[1];
	yvmax = viewport[5];
	sx = float(xvmax - xvmin) / float(xwmax - xwmin);
	sy = float(yvmax - yvmin) / float(ywmax - ywmin);
	for (int i = 0; i < window_object.size(); i = i + 2) {
		viewport_object.push_back(xvmin + (window_object[i] - xwmin) * sx);
		viewport_object.push_back(yvmin + (window_object[i + 1] - ywmin) * sy);
	}
	return viewport_object;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	vector<int> window = { -300,-100,-100,-100,-100,100,-300,100 };
	vector<int> viewport = { 0,-70,200,-70,200,70,0,70 };
	vector<int> window_object = { -250,-75,-150,-75,-150,75,-250,75 };
	vector<int> viewport_object;
	glColor3f(120.0f, 0.0f, 0.0f);
	plot(window);
	plot(viewport);
	glColor3f(0.0f, 120.0f, 0.0f);
	plot(window_object);
	viewport_object = window_viewport_mapping(window, viewport, window_object);
	plot(viewport_object);
	glEnd();
	glFlush();
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(120.0f, 0.0f, 0.0f);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Window to Viewoport Mapping");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
