#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<GL/glut.h>

#define outcode int

double xmin,xmax,ymin,ymax;
double xvmin,xvmax,yvmin,yvmax;
double x0,y0,x1,y1;
double x2,y2,x3,y3;
double x4,y4,x5,y5;
double x6,y6,x7,y7;

const int RIGHT=8;
const int LEFT=2;
const int TOP=4;
const int BOTTOM=1;

outcode computeoutcode(double x,double y)
{
	outcode code=0;
	if(y>ymax)
		code|=TOP;
	else if(y<ymin)
		code|=BOTTOM;
	if(x>xmax)
		code|=RIGHT;
	else if(x<xmin)
		code|=LEFT;
      return code;
}

void cohensutherland(int x0, int y0, int x1, int y1)
{
	outcode outcode0,outcode1,outcodeout;
	bool done=false, accept=false;
	
	outcode0=computeoutcode(x0,y0);
	outcode1=computeoutcode(x1,y1);
	
   do{
	
	if(!(outcode0|outcode1))
	{
		done=true;
		accept=true;
	}
	else if(outcode0&outcode1)
		done=true;
	else
	{
		double x,y;
	   	outcodeout=outcode0?outcode0:outcode1;
		
		if(outcodeout&TOP)
		{
			x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
			y=ymax;
		}	
		else if(outcodeout&BOTTOM)
		{
			x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
			y=ymin;
		}
		else if(outcodeout&RIGHT)
		{
			y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
			x=xmax;
		}
		else 
		{
			y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
			x=xmin;
		}
		if(outcodeout==outcode0)
		{
			x0=x;
			y0=y;
			outcode0=computeoutcode(x0,y0);
		}
		else
		{
			x1=x;
			y1=y;
			outcode1=computeoutcode(x1,y1);
		}
	}
   }while(!done);
	
   if(accept)
   {
	double sx=(xvmax-xvmin)/(xmax-xmin);
	double sy=(yvmax-yvmin)/(ymax-ymin);
	double vx0=xvmin+(x0-xmin)*sx;
	double vy0=yvmin+(y0-ymin)*sy;
	double vx1=xvmin+(x1-xmin)*sx;
	double vy1=yvmin+(y1-ymin)*sy;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	  glVertex2f(xvmin,yvmin);
	  glVertex2f(xvmax,yvmin);
	  glVertex2f(xvmax,yvmax);
	  glVertex2f(xvmin,yvmax);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	  glVertex2d(vx0,vy0);
	  glVertex2d(vx1,vy1);
	glEnd();
   }
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	  glVertex2f(xmin,ymin);
	  glVertex2f(xmax,ymin);
	  glVertex2f(xmax,ymax);
	  glVertex2f(xmin,ymax);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	  glVertex2d(x0,y0);
	  glVertex2d(x1,y1);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	  glVertex2d(x2,y2);
	  glVertex2d(x3,y3);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	  glVertex2d(x4,y4);
	  glVertex2d(x5,y5);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	  glVertex2d(x6,y6);
	  glVertex2d(x7,y7);
	glEnd();
	cohensutherland(x0,y0,x1,y1);
	cohensutherland(x2,y2,x3,y3);
	cohensutherland(x4,y4,x5,y5);
	cohensutherland(x6,y6,x7,y7);
     glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	gluOrtho2D(0,500,0,500);
}

void main(int argc, char ** argv)
{
	printf("Enter the coordinates of the window and viewport\n");
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&xmin,&ymin,&xmax,&ymax,&xvmin,&yvmin,&xvmax,&yvmax);
	printf("Enter the line1 corrdinates\n");
	scanf("%lf%lf%lf%lf",&x0,&y0,&x1,&y1);
	printf("Enter the line2 corrdinates\n");
	scanf("%lf%lf%lf%lf",&x2,&y2,&x3,&y3);
	printf("Enter the line3 corrdinates\n");
	scanf("%lf%lf%lf%lf",&x4,&y4,&x5,&y5);
	printf("Enter the line4 corrdinates\n");
	scanf("%lf%lf%lf%lf",&x6,&y6,&x7,&y7);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("5.c");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
