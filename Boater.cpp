
#include <cstdlib>
#include <cmath>
#include <iostream>


#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <GL/freeglut_ext.h>
#  include <GL/freeglut_std.h>
#  include <GL/glut.h>
#pragma comment(lib, "glew32.lib") 
#endif
#define PI 3.14159265358979324
using namespace std;

void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c); //Can't get it to work *****
}  

// Control points for Bezier surface.
static float controlPoints[6][4][3] =
{
	//{{Left } ,{height left},{height right} , {right}}
	{ { 0.0, 2.75, -5.0 },{ 0.0, 0.0, -1.0 },{ 0.0, 0.0, -1.0 },{ 0.0, 2.75, -5.0 } },
	{ { 0.5, 2.75, -3.0 },{ 0.25,0.0, -1.0 },{ -0.25, 0.0, -1.0 },{ -0.5, 2.75, -3.0 } },
	{ { 0.5, 2.75, -1.0 },{ 0.25,0.0, -1.0 },{ -0.25, 0.0, -1.0 },{ -0.5, 2.75, -1.0 } },
	{ { 0.5, 2.75, 1.0 },{ 0.25, 0.0, 1.0 },{ -0.25, 0.0, 1.0 },{ -0.5, 2.75, 1.0 } },
	{ { 0.5, 2.75, 3.0 },{ 0.25, 0.0, 1.0 },{ -0.25, 0.0, 1.0 },{ -0.5, 2.75, 3.0 } },
	{ { 0.0, 2.75, 5.0 },{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, 1.0 },{ 0.0, 2.75, 5.0 } }
};

double eyeX=0.0, eyeY=10.0, eyeZ=-15.0, pointX=0.0, pointY=0.0, pointZ=15.0, vectorX=1.0, vectorY=0.0, vectorZ=100.0;
//angle of rotation
float Xpos = 0, yPos = 0, zPos = 0, xRot = 0, yRot = 0, angle = 0.0;
float xAxis = 0, yAxis = 0, zAxis = 0;

void enable(void) {
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

void drawScene(void)
{
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(eyeX, eyeY, eyeZ, pointX, pointY, pointZ, vectorX, vectorY, vectorZ);
	//(eyeX, eyeY, eyeZ, pointX, pointY, pointZ, vectorX, vectorY, vectorZ)
	
	// Make a mesh approximation of the Bezier surfacee.
	glPushMatrix();
	glTranslatef(xAxis, yAxis, zAxis);
	glMapGrid2f(20, 1.0, 0.0, 20, 0.0, 1.0); // IMPORTANT: The direction of the sample grid is
									 // reversed along the u-direction to get the right
											 // normal directions (compare bezierCanoe.cpp).									
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	// A lot of lines
	glLineWidth(5.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-5, 0.0, 5.0);
	glVertex3f(-5, 0, -5);
	glLineWidth(5.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(5, 0.0, 5.0);
	glVertex3f(5, 0, -5);
	glEnd();
	glLineWidth(2.5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(5, 0.0, 0.0);
	glVertex3f(-5, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-5, 0.0, -5.0);
	glVertex3f(-5, 0, 50.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(5, 0.0, -5.0);
	glVertex3f(5, 0, 60.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(5, 0.0, 60.0);
	glVertex3f(-50, 0, 60.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-5, 0.0, 50.0);
	glVertex3f(-40, 0, 50.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-40, 0.0, 50.0);
	glVertex3f(-40, 0, -20.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-50, 0.0, 60.0);
	glVertex3f(-50, 0, -30.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-50, 0.0, -30.0);
	glVertex3f(5, 0, -30.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-40, 0.0, -20.0);
	glVertex3f(-5, 0, -20.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-5, 0.0, -20.0);
	glVertex3f(-5, 0, 5.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(5, 0.0, -30.0);
	glVertex3f(5, 0, 5.0);
	glEnd();
	//End of A lot of Lines
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.7, 1.0);
	glVertex3f(-100.0, 0.0, -100.0);
	glVertex3f(-100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, -100.0);
	glEnd();
	glFlush();
}

void camera(void) {
	glRotatef(xRot, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
	glRotatef(yRot, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-Xpos, -yPos, -zPos); //translate the screen to the position of our camera
}

void display(void) {
	glClearColor(1.0, 1.0, 0.6, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color buffer and the depth buffer
	glLoadIdentity();
	camera();
	enable();
	drawScene(); 
	glutSwapBuffers(); //swap the buffers
	angle++; //increase the angle
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

	void keyboard(unsigned char key, int x, int y) {
		if (key == 27)
		{
			exit(0);
		}
		//Camera Control Start
		if (key == 'q')
		{
			xRot += 1;
			if (xRot > 360) xRot -= 360;
		}
			if (key == 'z')
			{
			xRot -= 1;
			if (xRot < -360) xRot += 360;
		}
		if (key=='i')
		{
			OutputDebugStringW(L"My output string.");
			float xrotrad, yrotrad;
			yrotrad = (yRot / 180 * 3.141592654f);
			xrotrad = (xRot / 180 * 3.141592654f);
			Xpos += float(sin(yrotrad));
			zPos -= float(cos(yrotrad));
			yPos -= float(sin(xrotrad));
			

			glutPostRedisplay();
		}
		if (key == 'k')
		{
			float xrotrad, yrotrad;
			yrotrad = (yRot / 180 * 3.141592654f);
			xrotrad = (xRot / 180 * 3.141592654f);
			Xpos -= float(sin(yrotrad));
			zPos += float(cos(yrotrad));
			yPos += float(sin(xrotrad));


			glutPostRedisplay();
		}
		if (key == 'j')
		{
			yRot -= 1;
			if (yRot > 360) yRot -= 360;
		}

		if (key == 'l')
		{
			yRot += 1;
			if (yRot < -360)yRot += 360;
		}
		//Camera Control End
		if (key == 27) //Esc for stop
		{
			exit(0);
		}
	//Boat Control start
		if (key == 'w')
		{
				OutputDebugStringW(L"My output string.");
				zAxis += 1;

				glutPostRedisplay();
			
		}
		if (key == 's')
		{
			OutputDebugStringW(L"My output string.");
			zAxis -= 1;

			glutPostRedisplay();

		}
		if (key == 'd')
		{
			OutputDebugStringW(L"My output string.");
			

			xAxis -= 1;

			glutPostRedisplay();

		}
		if (key == 'a')
		{
			OutputDebugStringW(L"My output string.");
			xAxis += 1;

			glutPostRedisplay();

		}
		//Boat Control Finish
	}
	void printInteraction(void)
	{
		cout << "Interaction:" << endl;
		cout << "Press the W,S,A,D keys to move Canoe" << endl
			<< "Press the I,K,J,L  keys to move the camera." << endl
			<< "Press Q and Z to rotate the camera." << endl
			<< "Easy to learn,hard to master Camera system ,you need to rotate in order to navigate" << endl;
	}

void setup(void)
{
	glClearColor(1.0, 1.0, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

							 //Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	camera();
	
	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.5, 3.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.    
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

														 // Material property vectors.
	float matAmbAndDif1[] = { 0.9, 0.0, 0.0, 1.0 };
	float matAmbAndDif2[] = { 0.0, 0.9, 0.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints[0][0]); // Specify the Bezier surface.
	glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

	glEnable(GL_AUTO_NORMAL); // Enable automatic normal calculation. 

}

int main(int argc, char **argv)
{
	printInteraction();
	OutputDebugStringW(L"Taste the rainbow.");
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Main.cpp");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glewExperimental = GL_TRUE;
	glewInit();
	setup();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}