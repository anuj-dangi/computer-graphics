#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float xmin = 1, xmax = 7, ymin = 1, ymax = 7;
float x1, yy1, x2, y2;

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

void liangBarsky()
{
    float dx = x2-x1;
    float dy = y2-yy1;

    float p[] = {-dx, dx, -dy, dy};

    float q[] = {x1 - xmin, xmax - x1, yy1 - ymin, ymax - yy1};

    float t1 = 0;
    float t2 = 1;

    for(int i=0;i<4;i++)
    {
        if(p[i] == 0)
        {
            if(q[i] < 0)
            {
                return; 
            }
        }
        else
        {
            float t = q[i]/(float)p[i];

            if(p[i] < 0)
            {
                if(t > t1)
                {
                    t1 = t;
                }
            }
            else
            {
                if(t < t2)
                {
                    t2 = t;
                }
            }
        }
    }

    if(t1 > t2)
        return; 
    
    float x1c = x1 + t1*dx;
    float y1c = yy1 + t1*dy;
    float x2c = x1 + t2*dx;
    float y2c = yy1 + t2*dy;

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);

    glVertex2f(x1c, y1c);
    glVertex2f(x2c, y2c);

    glEnd();
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

    liangBarsky();
    

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("Line Barsky Clipping");

    menu();

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}