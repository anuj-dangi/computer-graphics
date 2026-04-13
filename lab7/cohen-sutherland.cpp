#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float xmin = 1, xmax = 7, ymin = 1, ymax = 7;
float x1, yy1, x2, y2;

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8


int computeCode(float x, float y)
{
    int code = INSIDE;

    if(x < xmin) code |= LEFT;
    else if(x > xmax) code |= RIGHT;

    if(y < ymin) code |= BOTTOM;
    else if(y > ymax) code |= TOP;

    return code;
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 40, 0, 40);
}

void drawGridAxis()
{
    int gridNo = 40;
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);

    for(int i=0;i<=gridNo;i++)
    {
        glVertex2f(i, 0);
        glVertex2f(i, gridNo);

        glVertex2f(0, i);
        glVertex2f(gridNo, i);
    }

    glEnd();
}

void drawSquare()
{
    glColor3f(1, 0, 0);
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

void drawLine()
{
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(x1, yy1);
    glVertex2f(x2, y2);
    glEnd();
}

void cohenSutherland()
{
    float x1c = x1, y1c = yy1;
    float x2c = x2, y2c = y2;

    int code1 = computeCode(x1c, y1c);
    int code2 = computeCode(x2c, y2c);

    int accept = 0;

    while(true)
    {

        if((code1 | code2) == 0)
        {
            accept = 1;
            break;
        }
        else if(code1 & code2)
        {
            break;
        }
        else
        {
            float x, y;
            int code_out = code1 ? code1 : code2;

            if(code_out & TOP)
            {
                x = x1c + (x2c - x1c) * (ymax - y1c) / (y2c - y1c);
                y = ymax;
            }
            else if(code_out & BOTTOM)
            {
                x = x1c + (x2c - x1c) * (ymin - y1c) / (y2c - y1c);
                y = ymin;
            }
            else if(code_out & RIGHT)
            {
                y = y1c + (y2c - y1c) * (xmax - x1c) / (x2c - x1c);
                x = xmax;
            }
            else if(code_out & LEFT)
            {
                y = y1c + (y2c - y1c) * (xmin - x1c) / (x2c - x1c);
                x = xmin;
            }

            if(code_out == code1)
            {
                x1c = x;
                y1c = y;
                code1 = computeCode(x1c, y1c);
            }
            else
            {
                x2c = x;
                y2c = y;
                code2 = computeCode(x2c, y2c);
            }
        }
    }

    if(accept)
    {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(x1c, y1c);
        glVertex2f(x2c, y2c);
        glEnd();
    }
}

void menu()
{
    printf("Enter value of xmin ymin xmax ymax: ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter value of x1 y1 x2 y2: ");
    scanf("%f %f %f %f", &x1, &yy1, &x2, &y2);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);

    drawGridAxis();
    drawSquare();
    drawLine();

    cohenSutherland();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("Cohen-Sutherland Line Clipping");

    menu();
    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}