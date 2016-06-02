#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

int maxx,maxy;
int x[100],y[100];
int dx,dy;

void display()
{
	int i,j;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	for(i=0;i<maxx;i++)
		x[i]=x[0]+i*dx;
	for(j=0;j<maxy;j++)
		y[j]=y[0]+j*dy;
	for(i=0;i<maxx-1;i++)
	{
		for(j=0;j<maxy-1;j++)
		{
			glBegin(GL_LINE_LOOP);
				glVertex2i(x[i],y[j]);
				glVertex2i(x[i+1],y[j]);
				glVertex2i(x[i+1],y[j+1]);
				glVertex2i(x[i],y[j+1]);
			glEnd();
			glFlush();
		}
	}
	glFlush();
}

void myinit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv)
{
	printf("Enter maxx, maxy\n");
	scanf("%d%d",&maxx,&maxy);
	printf("Enter the value of dx and dy\n");
	scanf("%d%d",&dx,&dy);
	printf("Enter the starting point of the mesh\n");
	scanf("%d%d",&x[0],&y[0]);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("10.c");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
