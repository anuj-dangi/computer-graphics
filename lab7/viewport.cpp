#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float xmin, xmax, ymin, ymax;
float umin, umax, vmin, vmax;
float x, y, u, v;

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 300, -10, 300);
}

void drawGridAxis()
{
    int gridNo = 300;
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);

    for(int i=0;i<=gridNo;i = i + 10)
    {
        glVertex2f(i, 0);
        glVertex2f(i, gridNo);

        glVertex2f(0, i);
        glVertex2f(gridNo, i);
    }

    glEnd();
}

void drawSquare(float amin, float bmin, float amax, float bmax, float *c)
{
    glColor3f(c[0], c[1], c[2]);
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(amin, bmin);
    glVertex2f(amax, bmin);
    glVertex2f(amax, bmax);
    glVertex2f(amin, bmax);

    glEnd();

}

void viewport(float *p)
{
    float sx = (umax-umin)/(xmax-xmin);
    float sy = (vmax-vmin)/(ymax-ymin);

    float xu1 = umin + sx*(p[0]-xmin);
    float yv1 = vmin + sy*(p[1]-ymin);

    float xu2 = umin + sx*(p[2]-xmin);
    float yv2 = vmin + sy*(p[3]-ymin);

    float c[] = {0, 1, 0};

    drawSquare(xu1, yv1, xu2, yv2, c);
}

void menu()
{
    printf("Enter value of xmin & ymin: ");
    scanf("%f %f", &xmin, &ymin);
    printf("Enter value of xmax & ymax: ");
    scanf("%f %f", &xmax, &ymax);

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);

    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);

    glEnd();

    printf("Enter value of umin vmin umax vmax: ");
    scanf("%f %f %f %f", &umin, &vmin, &umax, &vmax);

    glBegin(GL_LINE_LOOP);

    glVertex2f(umin, vmin);
    glVertex2f(umax, vmin);
    glVertex2f(umax, vmax);
    glVertex2f(umin, vmax);

    glEnd();

}

void display()
{
    float p[] = {40, 60, 80, 100};
    float c[] = {1, 0, 0};
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);

    drawGridAxis();

    menu();
    drawSquare(p[0], p[1], p[2], p[3], c);
    
    viewport(p);
    

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("Window to Viewport");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}