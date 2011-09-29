// vim: set ts=4 sw=4 expandtab sts=4:
#include <iostream>
#include <X11/Xlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"


#include "keyLogger.h"
#include "game.h"

const unsigned int elapsedUSecs = 3;





int hamsterPos=0;

void handelKeypress(unsigned char key, int x, int y) {
    switch (key)
    case 27: //Escape
        exit(0);
}

using std::cout;
GLsizei wh = 130 ;
GLsizei ww = 130 ;
//dot.cpp
// initial height of window
// initial width of window
void plot ( void );
void MyInit
( );

game* theBamsterGame;

void plot ( void ) {
    glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer


    theBamsterGame->plot();

    glFlush();
}


void myInit ( void ) {
    cout << glGetString(GL_VERSION) <<"\n";
    cout << glGetString(GL_VENDOR) <<"\n";
    glClearColor ( 0.0, 0.0, 0.0, 0.0 ); //white background
    glColor3f(0.0f, 1.0f,0.0f);
    // green drawing colour
    glPointSize(10.0);
    // 10 pixel dot!
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity ( );
    gluOrtho2D ( 0.0, (GLdouble)ww, 0.0, (GLdouble)wh ); //Display area
    glEnable(GL_COLOR_MATERIAL);
}



void handleKeypress (unsigned char key, int x, int y) 

{
    switch (key) {
        case 27:
            //			cleanup();
            exit(0);
        case 32:
            pressedKeys.spaceKey= true;
            break;

    }
}

void handleKeyReleased (unsigned char key, int x, int y)
{
    switch (key) {
        case 32:
            pressedKeys.spaceKey = false;
            break;
    }

}



void timerCallback (int value) 
{

    theBamsterGame->timerCallback();
    theBamsterGame->plot();

    glFlush();


    /* Do timer processing */
    /* maybe glutPostRedisplay(), if necessary */
    /* call back again after elapsedUSecs have passed */
    glutTimerFunc (elapsedUSecs, timerCallback, value); 
}


void handleSpecialKeyReleased(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            pressedKeys.leftKey = false;
            break;
        case GLUT_KEY_RIGHT:
            pressedKeys.rightKey = false;
            break;
        case GLUT_KEY_UP:
            pressedKeys.upKey = false;
            break;
        case GLUT_KEY_DOWN:
            pressedKeys.downKey = false;
            break;
        case 32: // 32 is spacebar
            pressedKeys.spaceKey= false;
            break;
    }
}



void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            pressedKeys.leftKey = true;
            break;
        case GLUT_KEY_RIGHT:
            pressedKeys.rightKey = true;
            break;
        case GLUT_KEY_UP:
            pressedKeys.upKey = true;
            break;
        case GLUT_KEY_DOWN:
            pressedKeys.downKey = true;
            break;
    }
}



int main(int argc, char **argv) {


    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( ww, wh ); // window size
    glutInitWindowPosition ( 0, 0 ); // & position on screen
    glutCreateWindow( "It's BAMster Time!" );
    myInit ( );

    theBamsterGame = new game();
    activGame = theBamsterGame;

    glutDisplayFunc (plot );
    glutTimerFunc ( 40,timerCallback,1 ) ;
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyReleased);
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);
    glutMainLoop ( );



    return 0;
}

