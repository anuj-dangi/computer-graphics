#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>

using namespace std;

float x[4], y[4];

void drawGridAxis()
{
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);

    for(int i=0;i<=15;i++)
    {
        glVertex2f(i, 0);
        glVertex2f(i, 15);

        glVertex2f(0, i);
        glVertex2f(15, i);
    }

    glEnd();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 15, 0, 15);
}

void drawLines()
{
    glColor3f(0, 1, 0);
    glLineWidth(2);
    glBegin(GL_LINES);

    glVertex2f(x[0], y[0]);
    glVertex2f(x[1], y[1]);

    glVertex2f(x[1], y[1]);
    glVertex2f(x[2], y[2]);

    glVertex2f(x[2], y[2]);
    glVertex2f(x[3], y[3]);

    glEnd();
}

void drawDots()
{
    glColor3f(1, 0, 0);
    glPointSize(4);
    glBegin(GL_POINTS);

    for(int i=0;i<4;i++)
    {
        glVertex2f(x[i], y[i]);
    }

    glEnd();
}

float bernsteinPolynomial(int n, int i, float t)
{
    float b = (tgamma(n+1)/(tgamma(i+1)*(tgamma(n-i+1))))*pow(t, i)*pow(1-t, n-i);

    return b;
}

void bezierCurve()
{
    float t = 0;

    float a[11] = {0} , b[11] = {0};

    for(int i=0;i<=10;i++)
    {

        for(int j=0;j<4;j++)
        {
            a[i] += bernsteinPolynomial(3, j, t)*x[j];
            b[i] += bernsteinPolynomial(3, j, t)*y[j];
        }

        t += 0.1;
    }

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glLineWidth(2);

    for(int i=0;i<10;i++)
    {
        glVertex2f(a[i], b[i]);
        glVertex2f(a[i+1], b[i+1]);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    drawLines();

    drawDots();

    bezierCurve();

    glFlush();
}

void menu()
{
    printf("Enter value of x[0] y[0] x[1] [y1] x[2] y[2] x[3] y[3]: ");
    for(int i=0;i<4;i++)
    {
        scanf("%f %f", &x[i], &y[i]);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("Bezier Curve");

    menu();

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}