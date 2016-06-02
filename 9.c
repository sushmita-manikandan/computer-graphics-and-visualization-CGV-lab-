#include<stdio.h>
#include<GL/glut.h>

float x1,y1,x2,y2,x3,y3,x4,y4;

void edgedetect(int x1,int y1,int x2,int y2,int *le,int *re)
{
	int i;
	float mx,temp,x;
	if((y2-y1)<0)
	{
		temp=x1;
		x1=x2;
		x2=temp;
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if((y2-y1)!=0)
	{
		mx=(x2-x1)/(y2-y1);
	}
	else
		mx=x2-x1;
	x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<le[i])
			le[i]=x;
		if(x>re[i])
			re[i]=x;
		x+=mx;
	}
}

void draw_pixel(int x, int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void scanfill()
{
	int le[500],re[500],i,j;

	for(i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x1,y1,le,re);
	for(j=0;j<500;j++)
	{
		if(le[j]<=re[j])
		{
			for(i=le[j];i<=re[j];i++)
			{
				draw_pixel(i,j);
			}
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	/*glBegin(GL_LINE_LOOP);
	    glVertex2f(x1,y1);
	    glVertex2f(x2,y2);
	    glVertex2f(x3,y3);
	    glVertex2f(x4,y4);
	glEnd();*/
	scanfill();
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv)
{
	printf("Enter the coordinates of the polygons\n");
	scanf("%f%f%f%f%f%f%f%f",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("9.c");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
   return 0;
}
