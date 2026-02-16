#include <GL/glut.h>
#include <stdio.h>

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx = x2-x1;
    int dy = y2-y1;
    int p = 2*dy - dx;
    int two_dy = 2*dy;
    int two_dy_dx = 2*(dy - dx);
    int x = x1, y = y1;

    while(x < x2)
    {
        glVertex2f(x, y);
        printf("%d %d\n", x, y);

        x++;
        if(p < 0)
        {
            p += two_dy;
        }
        else
        {
            y++;
            p += two_dy_dx;
        }
    }
}

void drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    glVertex2f(0, -10);
    glVertex2f(0, 10);

    glEnd();
}

void drawGrid()
{
    glBegin(GL_LINES);
    glColor3f(0.8, 0.8, 0.8);

    for(int i=-10;i<=10;i++)
    {
        glVertex2f(i, -10);
        glVertex2f(i, 10);

        glVertex2f(-10, i);
        glVertex2f(10, i);
    }

    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();
    drawAxis();
    drawLine(1, 2, 9, 8);

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(3);
    glBegin(GL_POINTS);

    bresenham(1, 2, 9, 8);

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Bresenham's Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}