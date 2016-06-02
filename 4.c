#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define pi 3.14

GLfloat house[3][9]={{100,100,175,250,250,150,150,200,200},{100,300,400,300,100,100,150,150,100},{1,1,1,1,1,1,1,1,1}};
GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat res[3][9]={{0},{0},{0}};
GLfloat h=100.0,k=100.0,theta;

void multiply()
{
	int i,j,l;

	for(i=0;i<3;i++)
	{
		for(j=0;j<9;j++)
		{	
			res[i][j]=0;
			for(l=0;l<3;l++)
			{
				res[i][j]=res[i][j]+rot_mat[i][l]*house[l][j];
			}
		}
	}
}

void rotate()
{
	GLfloat m,n;
	m=-h*(cos(theta)-1)+k*(sin(theta));
	n=-k*(cos(theta)-1)-h*(sin(theta));

	rot_mat[0][0]=cos(theta);
	rot_mat[0][1]=-sin(theta);
	rot_mat[0][2]=m;
 	rot_mat[1][0]=sin(theta);
	rot_mat[1][1]=cos(theta);
	rot_mat[1][2]=n;
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;
	multiply();
}

void drawhouse()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(house[0][0],house[1][0]);
	 glVertex2f(house[0][1],house[1][1]);
	 glVertex2f(house[0][3],house[1][3]);
	 glVertex2f(house[0][4],house[1][4]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	 glVertex2f(house[0][1],house[1][1]);
	 glVertex2f(house[0][2],house[1][2]);
	 glVertex2f(house[0][3],house[1][3]);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(house[0][5],house[1][5]);
	 glVertex2f(house[0][6],house[1][6]);
	 glVertex2f(house[0][7],house[1][7]);
	 glVertex2f(house[0][8],house[1][8]);
	glEnd();
}

void drawrotatedhouse()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(res[0][0],res[1][0]);
	 glVertex2f(res[0][1],res[1][1]);
	 glVertex2f(res[0][3],res[1][3]);
	 glVertex2f(res[0][4],res[1][4]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	 glVertex2f(res[0][1],res[1][1]);
	 glVertex2f(res[0][2],res[1][2]);
	 glVertex2f(res[0][3],res[1][3]);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(res[0][5],res[1][5]);
	 glVertex2f(res[0][6],res[1][6]);
	 glVertex2f(res[0][7],res[1][7]);
	 glVertex2f(res[0][8],res[1][8]);
	glEnd();
}
void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	drawhouse();
	rotate();
	drawrotatedhouse();
	glFlush();
}
void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,800.0,0.0,800.0);
}
int main(int argc,char **argv)
{
	printf("Enter theta\n");
	scanf("%f",&theta);
	theta*=pi/180;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("4.c");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
  return 0;
}

