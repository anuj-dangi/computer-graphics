//have to include GL/glut library to use opengl glut

#include <GL/glut.h>

void display();

void reshape(int, int);

//to change default settings under gl(drawing)
void init();

//glut functions will start with glut prefix

int main(int argc, char** argv)
{
    //to initialize glut takes int* argc && char** argv as parameters
    glutInit(&argc, argv);

    //colour display type mode e.g. single colour or rgb
    glutInitDisplayMode(GLUT_RGB);

    //inital poition and size of the graphical window
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    //to creat the window
    glutCreateWindow("Window 1");

    //to apply the changed default settings
    init();

    //what actually have to do in the window 
    //callback function that will be called after grahical window is created
    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    //to make the window presisent or stay alive
    glutMainLoop();

}

void init()
{
    //first three value are rgb values and last is alpha(dont know what is this).
    //this red and green to 1 and blue to 0 will make the window in yellow colour
    //default colour was black
    glClearColor(0.0, 0.0, 1.0, 1.0);
}

void display()
{
    //before drawing clear the area or window
    //clear the buffer in which we store the window data for each pixel
    glClear(GL_COLOR_BUFFER_BIT);

    //reset coordinate system -> dont know much?
    glLoadIdentity();

    //we only cleared the buffer not the actual window
    //to update the buffer changes(diplay) in window we have to call glFlush()
    glFlush();

    //order -> reset the buffer, draw, display
}

void reshape(int w, int h)
{

}