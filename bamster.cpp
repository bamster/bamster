#include <iostream>
#include <X11/Xlib.h>
#include <GL/glut.h>

const unsigned int elapsedUSecs = 40;

using std::cout;
GLsizei wh = 250 ;
GLsizei ww = 250 ;
//dot.cpp
// initial height of window
// initial width of window
void Displaydot ( void );
void MyInit
( );

unsigned int counter = 0;

void Displaydot ( void ) {
glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
glBegin(GL_POINTS);
// render with points
glVertex2i(counter%100,210); //display a point
counter++;
glEnd();
glFlush();
}


void MyInit ( void ) {
cout << glGetString(GL_VERSION) <<"\n";
cout << glGetString(GL_VENDOR) <<"\n";
glClearColor ( 1.0, 1.0, 1.0, 0.0 ); //white background
glColor3f(0.0f, 1.0f,0.0f);
// green drawing colour
glPointSize(10.0);
// 10 pixel dot!
glMatrixMode ( GL_PROJECTION );
glLoadIdentity ( );
gluOrtho2D ( 0.0, (GLdouble)ww, 0.0, (GLdouble)wh ); //Display area
}

static void timerCallback (int value) 
{ 
	glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
	glBegin(GL_POINTS);
	// render with points
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex2i(counter%100,210); //display a point
	interface.plot();
	map.plot();
	player.plot();
	counter++;
	glEnd();
	glFlush();
    /* Do timer processing */
    /* maybe glutPostRedisplay(), if necessary */
    /* call back again after elapsedUSecs have passed */
    glutTimerFunc (elapsedUSecs, timerCallback, value); 
}

int main(int argc, char **argv) {
glutInit( &argc, argv );
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
glutInitWindowSize
( ww, wh );
// window size
glutInitWindowPosition
( 180, 90 ); // & position on screen
glutCreateWindow
( "Display a Dot" );
MyInit ( );
glutDisplayFunc ( Displaydot );
glutTimerFunc ( 40,timerCallback,1 ) ;
glutMainLoop ( );
return 0;
}

