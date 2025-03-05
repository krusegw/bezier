
#include <GL/glut.h>
#include <cstdlib>


typedef GLfloat Point3[3];

Point3 lid1[4]={{0,3,0},{0.8,3,0},{0,2.7,0},{0.2,2.55,0}};
Point3 lid2[4]={{0.2,2.55,0},{0.4,2.4,0},{1.3,2.4,0},{1.3,2.25,0}};

Point3 body1[4]={{1.4,2.25,0},{1.3375,2.38125,0},{1.4375,2.38125,0},{1.5,2.25,0}};
Point3 body2[4]={{1.5,2.25,0},{1.75,1.725,0},{2,1.2,0},{2,0.75,0}};
Point3 body3[4]={{2,0.75,0},{2,0.3,0},{1.5,0.075,0},{1.5,0,0}};

GLfloat bern0 (GLfloat t)
{
	return (1-t)*(1-t)*(1-t);
}

GLfloat bern1 (GLfloat t)
{
	return 3.0*t*(1-t)*(1-t);
}

GLfloat bern2 (GLfloat t)
{
	return 3.0*t*t*(1-t);
}

GLfloat bern3 (GLfloat t)
{
	return t*t*t;
}


void myInit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	GLfloat light_diffuse[] = { 1.0 , 1.0 , 1.0 , 1.0 };
	GLfloat light_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
	GLfloat light_ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 };
	GLfloat light_position[] = { -1,1,1 , 0 };

	glLightfv(GL_LIGHT0 , GL_POSITION , light_position);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , light_diffuse);
	glLightfv(GL_LIGHT0 , GL_AMBIENT , light_ambient);
	glLightfv(GL_LIGHT0 , GL_SPECULAR , light_specular);

	glClearColor( 0.3 , 0.3 , 0.8 , 1.0 );
	//glClearColor( 0.6 , 0.6 , 0.6 , 1.0 );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5,1.5,-1.5,1.5,-10,20.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(0,0,5 , 0,0,0 , 0,1,0);
}

void display()
{
	GLint i,N=50;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0 , 0.0 , 0.0);


	GLfloat mat_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };
	GLfloat mat_diffuse[] = { 0.01 , 0.01 , 0.01 , 1.0 };
	GLfloat mat_specular[] = {0.5 , 0.5 , 0.5, 1.0 };
	GLfloat mat_shininess[] = { 32 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	mat_ambient[0]=0.329412 ; mat_ambient[1]=0.223529 ; mat_ambient[2]=0.027451;
	mat_diffuse[0]=0.780392 ; mat_diffuse[1]=0.568627 ; mat_diffuse[2]=0.113725;
	mat_specular[0]=0.992157; mat_specular[1]=0.941176; mat_specular[2]=0.807843;
	mat_shininess[0]=27.8974;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glViewport(0,0,200,200);
	glutSolidTeapot(1.0);

	glViewport(200,0,200,200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5,1.5,-1.5,1.5, 5.05 , 20 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,5 , 0,0,0 , 0,1,0);
	glutSolidTeapot(1.0);

	glViewport(400,0,200,200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5,1.5,-1.5,1.5, 5.5 , 20 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,5 , 0,0,0 , 0,1,0);
	glutSolidTeapot(1.0);

	glViewport(600,0,200,200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,4,-1,4, -10 , 20 );
	glPointSize(4.0);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
		for (i=0;i<4;i++) {
			glVertex2fv(lid1[i]);
		}
	glEnd();

	glBegin(GL_POINTS);
		for (i=0;i<4;i++) {
			glVertex2fv(lid2[i]);
		}
	glEnd();


	GLfloat t=0,deltat=1.0/(N-1);
	GLfloat x,y;

	glLineWidth(1.0);
	glPointSize(1.0);
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	t=0-deltat;
	for (i=0;i<N;i++)
	{
		t+=deltat;
		x = lid1[0][0]*bern0(t) + lid1[1][0]*bern1(t) + lid1[2][0]*bern2(t) + lid1[3][0]*bern3(t);
		y = lid1[0][1]*bern0(t) + lid1[1][1]*bern1(t) + lid1[2][1]*bern2(t) + lid1[3][1]*bern3(t);
		glVertex2f(x,y);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	t=0-deltat;
	for (i=0;i<N;i++)
	{
		t+=deltat;
		x = lid2[0][0]*bern0(t) + lid2[1][0]*bern1(t) + lid2[2][0]*bern2(t) + lid2[3][0]*bern3(t);
		y = lid2[0][1]*bern0(t) + lid2[1][1]*bern1(t) + lid2[2][1]*bern2(t) + lid2[3][1]*bern3(t);
		glVertex2f(x,y);
	}
	glEnd();

	glTranslatef(1,0,0);

	/*
	glPointSize(4.0);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
		for (i=0;i<4;i++) {
			glVertex2fv(body1[i]);
		}
	glEnd();
	glBegin(GL_POINTS);
		for (i=0;i<4;i++) {
			glVertex2fv(body2[i]);
		}
	glEnd();
	glBegin(GL_POINTS);
		for (i=0;i<4;i++) {
			glVertex2fv(body3[i]);
		}
	glEnd();
	*/

	glPointSize(1.0);
	glLineWidth(1.0);
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	t=0-deltat;
	for (i=0;i<N;i++)
	{
		t+=deltat;
		x = body1[0][0]*bern0(t) + body1[1][0]*bern1(t) + body1[2][0]*bern2(t) + body1[3][0]*bern3(t);
		y = body1[0][1]*bern0(t) + body1[1][1]*bern1(t) + body1[2][1]*bern2(t) + body1[3][1]*bern3(t);
		glVertex2f(x,y);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	t=0-deltat;
	for (i=0;i<N;i++)
	{
		t+=deltat;
		x = body2[0][0]*bern0(t) + body2[1][0]*bern1(t) + body2[2][0]*bern2(t) + body2[3][0]*bern3(t);
		y = body2[0][1]*bern0(t) + body2[1][1]*bern1(t) + body2[2][1]*bern2(t) + body2[3][1]*bern3(t);
		glVertex2f(x,y);
	}
	glEnd();	
	glBegin(GL_LINE_STRIP);
	t=0-deltat;
	for (i=0;i<N;i++)
	{
		t+=deltat;
		x = body3[0][0]*bern0(t) + body3[1][0]*bern1(t) + body3[2][0]*bern2(t) + body3[3][0]*bern3(t);
		y = body3[0][1]*bern0(t) + body3[1][1]*bern1(t) + body3[2][1]*bern2(t) + body3[3][1]*bern3(t);
		glVertex2f(x,y);
	}
	glEnd();	

	glFlush();
}

void keyboard(unsigned char key, GLint x, GLint y)
{
	
	switch (key)
	{
	case 'q':
		exit( 0 );
		break;
	}


	return;

 }


int main (int argc , char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,200);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Inside the Teapot");
	myInit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}