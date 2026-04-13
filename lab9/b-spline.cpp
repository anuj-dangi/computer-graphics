#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int knotSize;
float knot[8];
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


float basicFunction(int n, int i, int k, float t)
{
    if(k == 0)
    {
        if(knot[i] <= t && t < knot[i+1])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    float term1 = 0, term2 = 0;

    if(knot[i+k] - knot[i] != 0)
        term1 = (t - knot[i]) / (knot[i+k] - knot[i]) * basicFunction(n, i, k-1, t);

    if(knot[i+k+1] - knot[i+1] != 0)
        term2 = (knot[i+k+1] - t) / (knot[i+k+1] - knot[i+1]) * basicFunction(n, i+1, k-1, t);

    return term1 + term2;
}

void bSpline()
{

    float a[100] = {0} , b[100] = {0};

    for(int i=0;i<100;i++)
    {
        float t = knot[3] + i*(knot[4]-knot[3])/100.0;

        for(int j=0;j<4;j++)
        {
            a[i] += basicFunction(3, j, 3, t)*x[j];
            b[i] += basicFunction(3, j, 3, t)*y[j];
        }

        
    }

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glLineWidth(2);

    for(int i=0;i<99;i++)
    {
        glVertex2f(a[i], b[i]);
        glVertex2f(a[i+1], b[i+1]);
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


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    drawLines();

    drawDots();

    bSpline();

    glFlush();
}

void menu()
{
    printf("Enter value of x[0] y[0] x[1] [y1] x[2] y[2] x[3] y[3]: ");
    for(int i=0;i<4;i++)
    {
        scanf("%f %f", &x[i], &y[i]);
    }

    printf("Enter knot 0 1 2 3 4 5 6 7: ");
    for(int i=0;i<8;i++)  
    {
        scanf("%f", &knot[i]);
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