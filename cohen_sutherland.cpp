#include<gl/glut.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct point {
	int x, y;
	vector<int> region_code;
};

struct point p1, p2;

void write_point(int x, int y) {
	string pt = "(" + to_string(x) + "," + to_string(y) + ")";
	glRasterPos2i(x - 25, y - 15);
	for (int i = 0; pt[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, pt[i]);
	}
}

void points_writer(vector<int> clipping_area) {
	for (int i = 0; i < clipping_area.size(); i += 2) {
		write_point(clipping_area[i], clipping_area[i + 1]);
	}
}

void plot_area(vector<int> clipping_area) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < clipping_area.size(); i += 2) {
		glVertex2d(clipping_area[i], clipping_area[i + 1]);
	}
	glEnd();
	points_writer(clipping_area);
}

vector<int> get_region_code(struct point p, vector<int> clipping_area) {
	int xmax, xmin, ymin, ymax;
	xmin = clipping_area[0];
	xmax = clipping_area[4];
	ymin = clipping_area[1];
	ymax = clipping_area[5];
	vector<int> region_code = { 0,0,0,0 };
	if (p.x > xmax) {
		region_code[2] = 1;
	}
	if (p.x < xmin) {
		region_code[3] = 1;
	}
	if (p.y > ymax) {
		region_code[0] = 1;
	}
	if (p.y < ymin) {
		region_code[1] = 1;
	}
	return region_code;
}

int find_intersection(vector<int> region_code, vector<int>edge) {
	for (int i = 0; i < 4; i++) {
		if ((region_code[i] & edge[i]) == 1) {
			return 1;
		}
	}
	return 0;
}

void cohen_sutherland(vector<int> clipping_area, int x1, int y1, int x2, int y2) {
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
repeat:
	write_point(p1.x, p1.y);
	write_point(p2.x, p2.y);
	glBegin(GL_POINTS);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
	p1.region_code = get_region_code(p1, clipping_area);
	p2.region_code = get_region_code(p2, clipping_area);
	int flag=0;
	// critical acceptance test
	for (int i = 0; i < 4; i++) {
		if ((p1.region_code[i] | p2.region_code[i]) == 1) {
			flag = 1;
		}
	}
	if (flag == 1) {
		flag = 0;
		// critical rejection
		for (int i = 0; i < 4; i++) {
			if ((p1.region_code[i] & p2.region_code[i]) == 1) {
				flag = 1;
			}
		}
		if (flag == 1) {
			cout << "(" << p1.x << "," << p1.y << ") to (" << p2.x << "," << p2.y << ")" << " completely outside the line\n";
		}
		else {
			cout << "(" << p1.x << "," << p1.y << ") to (" << p2.x << "," << p2.y << ")" << " can be clipped\n";
			int xmax, xmin, ymin, ymax, x, y;
			float m;
			m = float(p2.y - p1.y) / float(p2.x - p1.x);
			xmin = clipping_area[0];
			xmax = clipping_area[4];
			ymin = clipping_area[1];
			ymax = clipping_area[5];
			vector<int> top = { 1,0,0,0 };
			vector<int> bottom = { 0,1,0,0 };
			vector<int> right = { 0,0,1,0 };
			vector<int> left = { 0,0,0,1 };
			if (find_intersection(p1.region_code, left)) {
				x = xmin;
				y = p1.y + m * (x - p1.x);
				p1.x = x;
				p1.y = y;
				goto repeat;
			}
			if (find_intersection(p1.region_code, right)) {
				x = xmax;
				y = p1.y + m * (x - p1.x);
				p1.x = x;
				p1.y = y;
				goto repeat;
			}
			if (find_intersection(p1.region_code, top)) {
				y = ymax;
				x = p1.x + float(y - p1.y) / m;
				p1.x = x;
				p1.y = y;
				goto repeat;
			}
			if (find_intersection(p1.region_code, bottom)) {
				y = ymin;
				x = p1.x + float(y - p1.y) / m;
				p1.x = x;
				p1.y = y;
				goto repeat;
			}
			if (find_intersection(p2.region_code, left)) {
				x = xmin;
				y = p2.y + m * (x - p2.x);
				p2.x = x;
				p2.y = y;
				goto repeat;
			}
			if (find_intersection(p2.region_code, right)) {
				x = xmax;
				y = p2.y + m * (x - p2.x);
				p2.x = x;
				p2.y = y;
				goto repeat;
			}
			if (find_intersection(p2.region_code, top)) {
				y = ymax;
				x = p2.x + float(y - p2.y) / float(m);
				p2.x = x;
				p2.y = y;
				goto repeat;
			}
			if (find_intersection(p2.region_code, bottom)) {
				y = ymin;
				x = p2.x + float(y - p2.y) / float(m);
				p2.x = x;
				p2.y = y;
				goto repeat;
			}
		}
	}
	else {
		cout << "("<<p1.x<<","<<p1.y<<") to ("<<p2.x<<","<<p2.y<<")"<<" completely inside the line\n";
	}
}

void display() {
	int x1, y1, x2, y2;
	glClear(GL_COLOR_BUFFER_BIT);
	vector<int> clipping_area = { -200,-200,200,-200,200,200,-200,200 };
	plot_area(clipping_area);
	cout << "Enter the coordinates of point A: ";
	cin >> x1 >> y1;
	cout << "Enter the coordinates of point B: ";
	cin >> x2 >> y2;
	write_point(x1, y1);
	write_point(x2, y2);
	glColor3f(120.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
	glColor3f(0.0f, 120.0f, 0.0f);
	glPointSize(5);
	cohen_sutherland(clipping_area, x1, y1, x2, y2);
	glColor3f(0.0f, 0.0f, 120.0f);
	glPointSize(1);
	glBegin(GL_LINES);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
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
	glutCreateWindow("Window to Viewport Mapping");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
