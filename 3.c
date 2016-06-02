#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

GLfloat vertices[][3]={{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
GLfloat colors[][3]={{0.5,1.0,0.0},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,0.8},{0.0,0.0,0.3},{0.5,0.5,0.5},{1.0,1.0,0.0}};

void poly(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}
void colorcube()
{
	poly(0,3,2,1);
	poly(2,3,7,6);
	poly(0,1,5,4);
	poly(1,5,6,2);
	poly(4,5,6,7);
	poly(0,4,7,3);
}

static GLfloat theta[]={0,0,0};
static int axis=2;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glLoadIdentity();
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
	colorcube();
	glFlush();
	glutSwapBuffers();
}

void spincube()
{
	theta[axis]+=2.0;
	if(theta[axis]>360.0)
		theta[axis]-=360.0;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)	axis=0;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)	axis=1;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)	axis=2;
	spincube();
}	

void myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	{
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	}
	else
		glOrtho(-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3.c");
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spincube);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
