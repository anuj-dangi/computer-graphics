#include <GL/glut.h>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);

}

void display()
{

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("3D Transformation");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
}