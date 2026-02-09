#include <GL/glut.h>

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void naive(int x1, int y1, int x2, int y2)
{
    float m = (float)(y2-y1)/(x2-x1);

    for(int i=x1;i<=x2;i++)
    {
        float y = y1+ m*(i-x1);

        glVertex2f(i,y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POINTS);
    

    naive(100, 100, 400, 400);

    glEnd();
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Naive approach");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}


