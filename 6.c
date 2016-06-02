#include<GL/glut.h>
#include<stdio.h>

int xc,yc,r;
int x1,y1,x0,y0;

void draw_pixel(GLint cx, GLint cy)
{
	glColor3f(1.0,0.0,0.0);	
	glBegin(GL_POINTS);
		glVertex2i(cx,cy);
	glEnd();
}

void plotpixel(GLint h, GLint k, GLint x, GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}

void circ_draw(int h, int k, int r)
{
	int d=1-r, x=0,y=r;
	while(y>x)
	{
		plotpixel(h,k,x,y);

		if(d<0)
			d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		x++;
	}
	plotpixel(h,k,x,y);
}		

void cylinder_draw(int xc,int yc,int r)
{
	int i, n=50;
	
	for(i=0;i<50;i+=3)
	{
		circ_draw(xc,yc+i,r);
	}
}

void paralellopiped(int x0, int y0, int x1, int y1)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	  glVertex2i(x0,y0);
	  glVertex2i(x1,y0);
	  glVertex2i(x1,y1);
	  glVertex2i(x0,y1);
	glEnd();
}
	
void draw_parallelopiped()
{
	int i,n=50;
	for(i=0;i<n;i+=2)
	{
		paralellopiped(x0+i,y0+i,x1+i,y1+i);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	cylinder_draw(xc,yc,r);
	draw_parallelopiped();
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	gluOrtho2D(0,400,0,300);
}
int main(int argc, char **argv)
{
	printf("Enter the values of xc,yc and radius r\n");
	scanf("%d%d%d",&xc,&yc,&r);
	printf("Enter the starting point for the parallelopiped\n");
	scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(0,0);
	glutCreateWindow("6.c");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
  return 0;
}
