#include <iostream>
#include <GL/glut.h>
using namespace std;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void plotCircle(int x, int y)
{
    drawPixel(x, y);
    drawPixel(-x, -y);
    drawPixel(x, -y);
    drawPixel(-x, y);

    drawPixel(y, x);
    drawPixel(-y, -x);
    drawPixel(y, -x);
    drawPixel(-y, x);
}

void midpoint(int r)
{
    int x = 0;
    int y = r;
    int p = 1-r;

    while(x < y)
    {
        plotCircle(x, y);

        if(p<0)
            p = p + (2*x) + 3;
        else
        {
            p = p + 2*(x-y) + 5;
            y--;
        }

        x++;
    }
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glColor3f(1, 0, 0);
    glPointSize(2);
    gluOrtho2D(-200, 200, -200, 200);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    midpoint(150);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);

    glutCreateWindow("midpoint circle algo");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}