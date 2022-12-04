#include<gl/glut.h>
#include<iostream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

void drawCube(vector<vector<double>> cube) {
	
	glBegin(GL_QUADS);
	glColor3f(120.0f, 0.0f, 0.0f);
	//front
	glVertex3d(cube[0][0], cube[0][1], cube[0][2]);
	glVertex3d(cube[1][0], cube[1][1], cube[1][2]);
	glVertex3d(cube[4][0], cube[4][1], cube[4][2]);
	glVertex3d(cube[7][0], cube[7][1], cube[7][2]);

	// back
	glVertex3d(cube[2][0], cube[2][1], cube[2][2]);
	glVertex3d(cube[3][0], cube[3][1], cube[3][2]);
	glVertex3d(cube[6][0], cube[6][1], cube[6][2]);
	glVertex3d(cube[5][0], cube[5][1], cube[5][2]);

	// left
	glColor3f(0.0f, 120.0f, 0.0f);
	glVertex3d(cube[2][0], cube[2][1], cube[2][2]);
	glVertex3d(cube[0][0], cube[0][1], cube[0][2]);
	glVertex3d(cube[7][0], cube[7][1], cube[7][2]);
	glVertex3d(cube[5][0], cube[5][1], cube[5][2]);

	// right
	glVertex3d(cube[3][0], cube[3][1], cube[3][2]);
	glVertex3d(cube[1][0], cube[1][1], cube[1][2]);
	glVertex3d(cube[4][0], cube[4][1], cube[4][2]);
	glVertex3d(cube[6][0], cube[6][1], cube[6][2]);

	// top
	glColor3f(0.0f, 0.0f, 120.0f);
	glVertex3d(cube[5][0], cube[5][1], cube[5][2]);
	glVertex3d(cube[6][0], cube[6][1], cube[6][2]);
	glVertex3d(cube[4][0], cube[4][1], cube[4][2]);
	glVertex3d(cube[7][0], cube[7][1], cube[7][2]);

	// bottom
	glVertex3d(cube[2][0], cube[2][1], cube[2][2]);
	glVertex3d(cube[3][0], cube[3][1], cube[3][2]);
	glVertex3d(cube[1][0], cube[1][1], cube[1][2]);
	glVertex3d(cube[0][0], cube[0][1], cube[0][2]);

	glEnd();
}

vector<vector<double>> multiply(vector<vector<double>> tm, vector<vector<double>> p) {
	vector<vector<double>> res(tm.size(), vector<double>(p[0].size(), 0));
	for (int i = 0; i < tm.size(); i++) {
		for (int j = 0; j < p[0].size(); j++) {
			for (int k = 0; k < tm[0].size(); k++) {
				res[i][j] += tm[i][k] * p[k][j];
			}
		}
	}
	return res;
}

vector<double> translate(double tx, double ty, double tz, vector<double> side) {
	vector<vector<double>> transformation_matrix = {
		{1, 0, 0, tx},
		{0, 1, 0, ty},
		{0, 0, 1, tz},
		{0, 0, 0, 1}
	};
	vector<vector<double>> p = {
		{side[0]},
		{side[1]},
		{side[2]},
		{1}
	};
	vector<vector<double>> p2;
	p2 = multiply(transformation_matrix, p);
	return { p2[0][0], p2[1][0], p2[2][0] };
}

vector<double> scale(double sx, double sy, double sz, vector<double> side) {
	vector<vector<double>> transformation_matrix = {
		{sx, 0, 0, 0},
		{0, sy, 0, 0},
		{0, 0, sz, 0},
		{0, 0, 0, 1}
	};
	vector<vector<double>> p = {
		{side[0]},
		{side[1]},
		{side[2]},
		{1}
	};
	vector<vector<double>> p2;
	p2 = multiply(transformation_matrix, p);
	return { p2[0][0], p2[1][0], p2[2][0] };
}

vector<double> rotateZ(double theta, vector<double> side) {
	theta *= 3.14 / 180;
	vector<vector<double>> transformation_matrix = {
		{cos(theta), -sin(theta), 0, 0},
		{sin(theta), cos(theta), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	vector<vector<double>> p = {
		{side[0]},
		{side[1]},
		{side[2]},
		{1}
	};
	vector<vector<double>> p2;
	p2 = multiply(transformation_matrix, p);
	return { p2[0][0], p2[1][0], p2[2][0] };
}

vector<double> rotateX(double theta, vector<double> side) {
	theta *= 3.14 / 180;
	vector<vector<double>> transformation_matrix = {
		{1, 0, 0, 0},
		{0, cos(theta), -sin(theta), 0},
		{0, sin(theta), cos(theta), 0},
		{0, 0, 0, 1}
	};
	vector<vector<double>> p = {
		{side[0]},
		{side[1]},
		{side[2]},
		{1}
	};
	vector<vector<double>> p2;
	p2 = multiply(transformation_matrix, p);
	return { p2[0][0], p2[1][0], p2[2][0] };
}

vector<double> rotateY(double theta, vector<double> side) {
	theta *= 3.14 / 180;
	vector<vector<double>> transformation_matrix = {
		{cos(theta), 0, sin(theta), 0},
		{0, 1, 0, 0},
		{-sin(theta), 0, cos(theta), 0},
		{0, 0, 0, 1}
	};
	vector<vector<double>> p = {
		{side[0]},
		{side[1]},
		{side[2]},
		{1}
	};
	vector<vector<double>> p2;
	p2 = multiply(transformation_matrix, p);
	return { p2[0][0], p2[1][0], p2[2][0] };
}

void transform(vector<vector<double>> cube) {
	int op;
	double tx, ty, tz, theta, op2, sx, sy, sz;
	cout << "1. Translation\n2. Rotation\n3. Scaling\n4. Enter option: ";
	cin >> op;
	vector<vector<double>> res;
	switch (op) {
		case 1: {
			cout << "Enter tx, ty, tz: ";
			cin >> tx >> ty >> tz;
			for (int i = 0; i < cube.size(); i++) {
				res.push_back(translate(tx, ty, tz, cube[i]));
			}
			drawCube(res);
			break;
		}
		case 2: {
			cout << "Enter theta: ";
			cin >> theta;
			cout << "Enter 1. X-axis\n2. Y-axis\n3. Z-axis: ";
			cin >> op2;
			if (op2 == 1) {
				for (int i = 0; i < cube.size(); i++) {
					res.push_back(rotateX(theta, cube[i]));
				}
			}
			else if (op2 == 2) {
				for (int i = 0; i < cube.size(); i++) {
					res.push_back(rotateY(theta, cube[i]));
				}
			}
			else if (op2 == 3) {
				for (int i = 0; i < cube.size(); i++) {
					res.push_back(rotateZ(theta, cube[i]));
				}
			}
			drawCube(res);
			break;
		}
		case 3: {
			cout << "Enter sx, sy, sz: ";
			cin >> sx >> sy >> sz;
			for (int i = 0; i < cube.size(); i++) {
				res.push_back(scale(sx, sy, sz, cube[i]));
			}
			drawCube(res);
			break;
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(10, 5, 10,   //Camera_x,Camera_y,Camera_z
		0, 0, 0,     //loot at point
		0, 1, 0);
	vector<vector<double>> cube = { {50,50,50}, {100,50,50}, {50,50,0}, {100,50,0}, {100,100,50}, {50,100,0}, {100,100,0}, {50,100,50} }; \
	drawCube(cube);
	transform(cube);
	glFlush();
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(120.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500.0, 500.0, -500.0, 500.0, 500.0, -500.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3D Transformations");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
