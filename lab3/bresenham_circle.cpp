#include <GL/glut.h>

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

void display();
void init();
void bresenhamCircle(int, int, int);
void plotCirclePoints(int, int, int, int);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 200);

    glutCreateWindow("Bresenham's Circle algorithm");
    
    init();

    glutDisplayFunc(display);
    glutMainLoop();

	return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(4.0);
    
    glBegin(GL_POINTS);
    bresenhamCircle(0, 0, 5);
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

void bresenhamCircle(int h, int k, int r)
{
    int x = 0, y = r;
    int d = 3 - 2*r;

    plotCirclePoints(h, k, x, y);

    while(x <= y)
    {
        x++;

        if(d < 0)
        {
            d = d+4*x+6;
        }
        else
        {
            d = d+4*(x-y)+10;
            y--;
        }

        plotCirclePoints(h, k, x, y);
    }
}

void plotCirclePoints(int h, int k, int x, int y)
{
    glVertex2f(h+x, k+y);
    glVertex2f(h+x, k-y);
    glVertex2f(h-x, k+y);
    glVertex2f(h-x, k-y);

    glVertex2f(h+y, k+x);
    glVertex2f(h+y, k-x);
    glVertex2f(h-y, k+x);
    glVertex2f(h-y, k-x);
}
