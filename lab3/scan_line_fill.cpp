#include <GL/glut.h>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLoadIdentity();
    
}

void scanFill(int x[], int y[], int edges)
{

}

void display()
{
    glMatrixMode(GL_PROJECTION);
    glDraw
    glBegin(GL_POINTS);

    int x[] = {100, 200, 300};
    int y[] = {100, 300, 200};
    int edges = 3;

    scanFill(x, y, edges);

    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Scan Line Polygon Fill");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}