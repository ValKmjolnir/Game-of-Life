#include <ctime>
#include <cmath>
#include <gl/glut.h>

#define windowsize 400
#define mapsize 400
bool map[mapsize][mapsize];
bool tmp[mapsize][mapsize];
int width, height;
bool check(int, int);
void init();
void calc();
void draw();
void reshape(GLsizei,GLsizei);

bool check(int x, int y)
{
	x = x < 0 ? mapsize - 1 : x;
	y = y < 0 ? mapsize - 1 : y;
	x = x >= mapsize ? 0 : x;
	y = y >= mapsize ? 0 : y;
	return map[x][y];
}
void init()
{
	std::srand(unsigned(time(NULL)));
	for (int i = 0; i < mapsize; ++i)
		for (int j = 0; j < mapsize; ++j)
			map[i][j] = (rand() % 100>65);
	return;
}
void calc()
{
	int change[8][2] = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };
	for(int i=0;i<mapsize;++i)
		for (int j = 0; j < mapsize; ++j)
		{
			int cnt = 0;
			for (int k = 0; k < 8; ++k)
				cnt += check(i + change[k][0], j + change[k][1]);
			if (cnt == 2)      tmp[i][j] = map[i][j];
			else if (cnt == 3) tmp[i][j] = true;
			else               tmp[i][j] = false;
		}
	for (int i = 0; i < mapsize; ++i)
		for (int j = 0; j < mapsize; ++j)
			map[i][j] = tmp[i][j];
	return;
}
void draw()
{
	calc();
	reshape(width, height);
	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize((double)windowsize/(double)mapsize-1);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.8, 0.9);
	for (int i = 0; i < mapsize; ++i)
		for (int j = 0; j < mapsize; ++j)
			if (map[i][j])
				glVertex2f(i-mapsize/2, j-mapsize/2);
	glEnd();
	glFlush();
}
void reshape(GLsizei w, GLsizei h)
{
	width = w;
	height = h;
	GLfloat ratio = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double left = (double)-mapsize*0.5-0.1;
	double right = (double)mapsize*0.5+0.1;
	if (ratio<=1) gluOrtho2D(left, right, left/ratio, right/ratio);
	else          gluOrtho2D(left*ratio, right*ratio, left, right);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return;
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;
	case 'b':
		init();
		break;
	}
	reshape(width, height);
	glutPostRedisplay();
	return;
}
int main()
{
	init();
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowsize, windowsize);
	width = windowsize;
	height = windowsize;
	glutCreateWindow("game of life");
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}