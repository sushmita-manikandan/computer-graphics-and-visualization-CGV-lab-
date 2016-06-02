#include<stdio.h>
#include<GL/glut.h>

GLfloat v[4][3]={{0,0,1},{0,0.9,-0.33},{-0.81,-0.47,-0.33},{0.81,-0.47,-0.33}};
int m;

void triangle(GLfloat *a,GLfloat *b,GLfloat *c)
{
	glBegin(GL_POLYGON);
	  glVertex3fv(a);
	  glVertex3fv(b);
	  glVertex3fv(c);
	glEnd();
}
void divide_triangle(GLfloat *a,GLfloat *b,GLfloat *c,int m)
{
	float v1[3],v2[3],v3[3];
	int j;

	for(j=0;j<3;j++)
		v1[j]=(a[j]+b[j])/2;
	for(j=0;j<3;j++)
		v2[j]=(a[j]+c[j])/2;
	for(j=0;j<3;j++)
		v3[j]=(b[j]+c[j])/2;
	
	if(m>0)
	{
		divide_triangle(a,v1,v2,m-1);
		divide_triangle(c,v2,v3,m-1);
		divide_triangle(b,v3,v1,m-1);
	}
	else
	{	
		triangle(a,b,c);
	}
}
void tetrahedron(int m)
{
	glColor3f(1.0,0.0,0.0);
	divide_triangle(v[0],v[1],v[2],m);
	glColor3f(0.0,1.0,0.0);
	divide_triangle(v[3],v[2],v[1],m);
	glColor3f(0.0,0.0,1.0);
	divide_triangle(v[0],v[3],v[1],m);
	glColor3f(0.0,0.0,0.0);
	divide_triangle(v[0],v[2],v[3],m);
}

void display()
{	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	tetrahedron(m);
	glFlush();
}

void main(int argc, char **argv)
{
	printf("Enter the m\n");
	scanf("%d",&m);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("1.c");
	glEnable(GL_DEPTH_TEST);
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glutDisplayFunc(display);
	glutMainLoop();
}
