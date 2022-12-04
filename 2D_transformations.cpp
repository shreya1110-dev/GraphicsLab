#include<gl/glut.h>
#include<iostream>
#include<vector>

using namespace std;

void draw_object(vector<vector<double>> obj, int color) {
	if (color == 1) {
		glColor3f(120.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(0.0f, 120.0f, 0.0f);
	}
	for (int i = 0; i < obj.size(); i++) {
		glVertex2d(obj[i][0], obj[i][1]);
	}
}

vector<vector<double>> multiply(vector<vector<double>> tm, vector<vector<double>> point) {
	vector<vector<double>> res(tm.size(), vector<double>(tm[0].size(), 0));
	for (int i = 0; i < tm.size(); i++) {
		for (int j = 0; j < point[0].size(); j++) {
			for (int k = 0; k < tm[0].size(); k++) {
				res[i][j] += tm[i][k] * point[k][j];
			}
		}
	}
	return res;
}
vector<double> translate(double tx, double ty, double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{1,0,tx},
		{0,1,ty},
		{0,0,1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> rotate(double theta, double x, double y) {
	theta *= 3.14 / 180;
	vector<vector<double>> transformation_matrix = {
		{cos(theta),-sin(theta),0},
		{sin(theta),cos(theta),0},
		{0,0,1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> rotate_fixed_point(double theta, double fx, double fy, double x, double y) {
	theta *= 3.14 / 180;
	vector<vector<double>> transformation_matrix = {
		{cos(theta),-sin(theta),(1-cos(theta)*fx + fy*sin(theta))},
		{sin(theta),cos(theta),(1-cos(theta)*fy - fx*sin(theta))},
		{0,0,1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> scale_fixed_point(double sx, double sy, double xf, double yf, double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{sx, 0, xf*(1-sx)},
		{0, sy, yf*(1-sy)},
		{0,0,1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> scale(double sx, double sy, double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{sx, 0, 0},
		{0, sy, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> shearX(double shx, double shy, double yf, double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{1, shx, -shx*yf},
		{0, 1, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> shearY(double shx, double shy, double xf, double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{1, 0, 0},
		{shy, 1, -shy*xf},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> reflectX(double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{1, 0, 0},
		{0, -1, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> reflectY(double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{-1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> reflectOrig(double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{-1, 0, 0},
		{0, -1, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}

vector<double> reflectXY(double x, double y) {
	vector<vector<double>> transformation_matrix = {
		{0, 1, 0},
		{1, 0, 0},
		{0, 0, 1}
	};
	vector<vector<double>> p2;
	vector<vector<double>> p1 = {
		{x},
		{y},
		{1}
	};
	p2 = multiply(transformation_matrix, p1);
	return { p2[0][0], p2[1][0] };
}
 
void transformations() {
	int op, n, op2, ch;
	vector<vector<double>> points, obj;
	double tx, ty, x, y, theta, xf, yf, sx, sy, shx, shy;
	cout << "Enter number of points: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Enter point: ";
		cin >> x >> y;
		points.push_back({ x,y });
	}
	draw_object(points, 0);
		cout << "1. Translation\n2. Rotation\n3. Scaling\n4. Shearing\n5. Reflection\nEnter the transformation: ";
		cin >> op;
		switch (op) {
		case 1: {
			cout << "Enter tx and ty: ";
			cin >> tx >> ty;
			for (int i = 0; i < n; i++) {
				obj.push_back(translate(tx, ty, points[i][0], points[i][1]));
			}
			draw_object(obj, 1);
			break;
		}
		case 2: {
			cout << "Enter theta: ";
			cin >> theta;
			cout << "1. Rotate with respect to fixed point\n2. Rotate\nEnter option: ";
			cin >> op2;
			if (op2 == 1) {
				cout << "Enter fixed point: ";
				cin >> xf >> yf;
				for (int i = 0; i < n; i++) {
					obj.push_back(rotate_fixed_point(theta, xf, yf, points[i][0], points[i][1]));
				}
			}
			else {
				for (int i = 0; i < n; i++) {
					obj.push_back(rotate(theta, points[i][0], points[i][1]));
				}
			}
			draw_object(obj, 1);
			break;
		}
		case 3: {
			cout << "Enter sx and sy: ";
			cin >> sx >> sy;
			cout << "1. Scale with respect to fixed point\n2. Scale\nEnter option: ";
			cin >> op2;
			if (op2 == 1) {
				cout << "Enter fixed point: ";
				cin >> xf >> yf;
				for (int i = 0; i < n; i++) {
					obj.push_back(scale_fixed_point(sx, sy, xf, yf, points[i][0], points[i][1]));
				}
			}
			else {
				for (int i = 0; i < n; i++) {
					obj.push_back(scale(sx, sy, points[i][0], points[i][1]));
				}
			}
			draw_object(obj, 1);
			break;
		}
		case 4: {
			cout << "Enter shx and shy: ";
			cin >> shx >> shy;
			cout << "1. Shear with respect to X-axis\n2. Shear with respect to Y-axis\nEnter option: ";
			cin >> op2;
			if (op2 == 1) {
				cout << "Enter yref: ";
				cin >> yf;
				for (int i = 0; i < n; i++) {
					obj.push_back(shearX(shx, shy, yf, points[i][0], points[i][1]));
				}
			}
			else {
				cout << "Enter xref: ";
				cin >> xf;
				for (int i = 0; i < n; i++) {
					obj.push_back(shearY(shx, shy, xf, points[i][0], points[i][1]));
				}
			}
			draw_object(obj, 1);
			break;
		}
		case 5: {
			cout << "1. X-axis\n2. Y-axis\n3. XY plane\n4. Origin\nEnter option: ";
			cin >> op2;
			if (op2 == 1) {
				for (int i = 0; i < n; i++) {
					obj.push_back(reflectX(points[i][0], points[i][1]));
				}
			}
			else if (op2 == 2) {
				for (int i = 0; i < n; i++) {
					obj.push_back(reflectY(points[i][0], points[i][1]));
				}
			}
			else if (op2 == 3) {
				for (int i = 0; i < n; i++) {
					obj.push_back(reflectXY(points[i][0], points[i][1]));
				}
			}
			else if (op2 == 4) {
				for (int i = 0; i < n; i++) {
					obj.push_back(reflectOrig(points[i][0], points[i][1]));
				}
			}
			draw_object(obj, 1);
			break;
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	transformations();
	glEnd();
	glFlush();
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(120.0f, 0.0f, 0.0f);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("2D Transformations");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 1;
}
