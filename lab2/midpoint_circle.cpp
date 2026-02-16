#include <iostream>
#include <GL/glut.h>
using namespace std;

void drawGridAxis()
{
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);

    for(int i=-10;i<=10;i++)
    {
        glVertex2f(i, -10);
        glVertex2f(i, 10);

        glVertex2f(-10, i);
        glVertex2f(10, i);
    }

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);

    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    glVertex2f(0, -10);
    glVertex2f(0, 10);

    glEnd();
}

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
    glColor3f(0, 0, 1);
    glPointSize(3);
    gluOrtho2D(-10, 10, -10, 10);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    glColor3f(1.0, 0.0, 0.0);

    midpoint(7);

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