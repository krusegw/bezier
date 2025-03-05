
/*  
In this lab we will create a 3D Bezier Curve, using a 2d Mesh.  We
also investigate shading effect.

1.  Run the code, and use the x, y, and z buttons to rotate the mesh.

2.  Try changing GL_LINE parameter in the glEvalMesh2 call to GL_POINT
and then GL_FILL.  What looks "wrong" when the GL_FILL is used?

3.  Uncomment the calls setting up and enabling the lighting, and make sure
the parameter in the glEvalMesh2 call is GL_FILL.  Does the object look better?

4.  Finally, try commenting out the call enabling auto normalization.  Any 
changes?

*/
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#define WINDOWSIZE 500

GLfloat xRot=0.0 , yRot=0.0, zRot=0.0;

GLfloat ctrlpoints[4][4][3] = {
	{ {-1.5,-1.5, 4.0} , {-0.5,-1.5, 2.0} , {0.5,-1.5,-1.0} , {1.5,-1.5, 2.0} },
	{ {-1.5,-0.5, 1.0} , {-0.5,-0.5, 3.0} , {0.5,-0.5, 0.0} , {1.5,-0.5,-1.0} },
	{ {-1.5, 0.5, 4.0} , {-0.5, 0.5, 0.0} , {0.5, 0.5, 3.0} , {1.5, 0.5, 4.0} },
	{ {-1.5, 1.5,-2.0} , {-0.5, 1.5,-2.0} , {0.5, 1.5, 0.0} , {1.5, 1.5,-1.0} }
};

void myInit()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);

	glMap2f(GL_MAP2_VERTEX_3 , 0 , 1 , 3 , 4, 0, 1, 12 , 4, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20 , 0,1,20,0,1);

	GLfloat light_ambient[] = {0.2 , 0.2 , 0.2 , 1.0};
	GLfloat light_position[] = {0.0 , 0.0 , 2.0 , 1.0};
	GLfloat mat_diffuse[] = {0.6 , 0.6 , 0.6 , 1.0};
	GLfloat mat_specular[] = {1.0 , 1.0 , 1.0 , 1.0};
	GLfloat mat_shininess[] = {50.0};

	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0 , GL_AMBIENT , light_ambient);
	glLightfv(GL_LIGHT0 , GL_POSITION , light_position);

	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , mat_shininess);
	*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5,5,-5,5,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	return;
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot , 1 , 0 , 0);
	glRotatef(yRot , 0 , 1 , 0);
	glRotatef(zRot , 0 , 0 , 1);


	glEvalMesh2(GL_LINE,0,20,0,20);

	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(4,0,0);
		glVertex3f(0,0,0);
		glVertex3f(0,4,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,4);
	glEnd();

	glPopMatrix();



	glFlush();

	return;
}



void keyboard (unsigned char key, GLint x, GLint y)
{
	switch (key) {
	case 'x' :
		xRot-= 5.0f;
		break;
	case 'X':
		xRot += 5.0f;
		break;
	case 'y':
		yRot -= 5.0f;
		break;
	case 'Y':
		yRot += 5.0f;
		break;
	case 'z':
		zRot -= 5.0f;
		break;
	case 'Z':
		zRot += 5.0f;
		break;
	case 'r':
		xRot=0.0,yRot=0.0,zRot=0.0;
		break;
	case 'q':
		exit( 0 );
		break;
	}

	glutPostRedisplay();

	return;
}



int main( int argc , char **argv )
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOWSIZE,WINDOWSIZE);
    glutInitWindowPosition(0,0);
    glutCreateWindow("BezierSurfaces");
    
	myInit();
	
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
    glutMainLoop();
	
	return 0;
}