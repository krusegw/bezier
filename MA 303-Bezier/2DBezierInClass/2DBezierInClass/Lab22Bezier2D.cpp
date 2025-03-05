
/*  
In this lab we will create a 2D Bezier Curve, given four control points, using
OpenGL's 1D evaluators.

1.  Fill-in the  glMap1f  call.

2.  Fill-in the  glMapGrid1f  call.

3.  Fill-in the  glEvalMesh1  call.

4.  Compile your code, fixing any errors, and then run it.

5.  Try changing the type of the curve to GL_POINT, and only calculating the grid between 0.25 and 0.75
*/
#include <GL/glut.h>
#include <cstdlib>

#define WINDOWSIZE 500

typedef GLfloat Point3[3];

Point3 p[4]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
GLint pointCount=0;

GLint mouseX, mouseY;


void myInit()
{
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WINDOWSIZE,0,WINDOWSIZE);
	glMatrixMode(GL_MODELVIEW);
	
	return;
}


void mouse (GLint btn , GLint state , GLint x , GLint y)
{

	if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		p[pointCount][0] = x;
		p[pointCount][1] = WINDOWSIZE - y;
		pointCount++;
		glutPostRedisplay();
	}


	if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);
}


void display() {
	GLint i,j,N=100;
	GLfloat t=0,deltat=1.0/(N-1);

	// create the evaluator based on the given 4 control points
	glMap1f(  GL_MAP1_VERTEX_3, 
		0.0 ,
		1.0 , 
		3 ,
		4 , 
		&p[0][0] );
	// enable the evaluator
	glEnable(GL_MAP1_VERTEX_3);

	// render the 4 control points
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glColor3f(0.0 , 0.0 , 0.0);
	glBegin(GL_POINTS);
		for (i=0;i<pointCount;i++) {
			glVertex2fv(p[i]);
		}
	glEnd();

	// now that 4 points are clicked, render the Bezier curve they define
	if (pointCount>=4) 
	{
		pointCount=0;
		glColor3f(1.0,0.0,0.0);

		// create an evenly spaced grid of N points between 0 and 1
		glMapGrid1f( N , 0 , 1 );
		// apply this grid to all the evaluators, so all the vertices of the curve are calculated
		glEvalMesh1( GL_LINE , 0 , N );


		// alternatively to the two calls above, the evaluator could be explicitly called from each point
		/*
		glBegin(GL_LINE_STRIP);
		t=0;
		for (j=0;j<N;j++){ glEvalCoord1f( t );		t+=deltat;	}
		glEnd();
		*/
	}

	glFlush();

	return;
}



void keyboard (unsigned char key, GLint x, GLint y)
{
	if (key=='q') exit( 0 );

	if (key=='r') pointCount=0;

	glutPostRedisplay();

	return;
}



int main( int argc , char **argv )
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOWSIZE,WINDOWSIZE);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bezier Curve");
    
	myInit();
	
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
    glutMainLoop();
	
	return 0;
}