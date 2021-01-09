#include <ctime>
#include <cmath>
#include <gl/glut.h>

#define windowsize 400
#define mapsize 100
bool map[mapsize][mapsize];
int width, height;
int antx, anty;
int heading;
void init();
void calc();
void draw();
void reshape(GLsizei, GLsizei);

void init()
{
	heading = 0;
	antx = mapsize / 2;
	anty = mapsize / 2;
	width = windowsize;
	height = windowsize;
	std::srand(unsigned(time(NULL)));
	for (int i = 0; i < mapsize; ++i)
		for (int j = 0; j < mapsize; ++j)
			map[i][j] = (rand() % 100 > 85);
	return;
}
void calc()
{
	if (map[antx][anty])
	{
		map[antx][anty] = false;
		heading = (heading + 1) % 4;
	}
	else
	{
		map[antx][anty] = true;
		heading = (heading + 3) % 4;
	}
	switch (heading)
	{
		case 0:--antx; break;
		case 1:--anty; break;
		case 2:++antx; break;
		case 3:++anty; break;
	}
	if (antx < 0)
		antx = mapsize - 1;
	else if (antx >= mapsize)
		antx = 0;
	if (anty < 0)
		anty = mapsize - 1;
	else if (anty >= mapsize)
		anty = 0;
	return;
}
void draw()
{
	calc();
	reshape(width, height);
	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.8, 0.9);
	for (int i = 0; i < mapsize; ++i)
		for (int j = 0; j < mapsize; ++j)
			if (map[i][j])
				glVertex2f(i - mapsize / 2, j - mapsize / 2);
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
	double left = (double)-mapsize * 0.5 - 0.1;
	double right = (double)mapsize*0.5 + 0.1;
	if (ratio <= 1) gluOrtho2D(left, right, left / ratio, right / ratio);
	else          gluOrtho2D(left*ratio, right*ratio, left, right);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return;
}
int main()
{
	init();
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowsize, windowsize);
	glutCreateWindow("lanton\'s ant");
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
