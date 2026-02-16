#include <GL/glut.h>
#include <stdio.h>

float fillColor[3] = {1.0, 0.0, 0.0};
float boundaryColor[3] = {0.0, 1.0, 0.0};

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

void drawGridAxis()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7, 0.7, 0.7);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(int i=-10;i<=10;i++)
    {
        glVertex2f(i, -10);
        glVertex2f(i, 10);

        glVertex2f(-10, i);
        glVertex2f(10, i);
    }

    glEnd();

    glLineWidth(2);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);
    

    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    glVertex2f(0, -10);
    glVertex2f(0, 10);

    glEnd();
}

void drawLine(int x[], int y[], int noEdges)
{
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<noEdges;i++)
    {
        glVertex2f(x[i%noEdges], y[i%noEdges]);
        glVertex2f(x[(i+1)%noEdges], y[(i+1)%noEdges]);
    }
    glEnd();
}

void getPixel(int x, int y, float *color)
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

void setPixel(int x, int y)
{
    float wx = (x / 25.0) - 10;
    float wy = (y / 25.0) - 10;

    glBegin(GL_POINTS);
    glVertex2f(wx, wy);
    glEnd();
    glFlush();
}


void boundaryFill(int x, int y)
{
    float pixel[3];

    getPixel(x, y, pixel);

    if( (pixel[0] != boundaryColor[0] || pixel[1] != boundaryColor[1] || pixel[2] != boundaryColor[2]) && (
        pixel[0] != fillColor[0] || pixel[1] != fillColor[1] || pixel[2] != fillColor[2]
    ))
    {
        glColor3fv(fillColor);
        setPixel(x,y);

        boundaryFill(x+1,y);
        boundaryFill(x-1,y);
        boundaryFill(x,y+1);
        boundaryFill(x,y-1);
    }


}

void display()
{
    drawGridAxis();

    int x[] = {0, -4, 4};
    int y[] = {4, 0, 0};

    drawLine(x, y, 3);

    int seedX = (0+10)*25;
    int seedY = (2+10)*25;

    boundaryFill(seedX, seedY);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Boundary Fill Algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}