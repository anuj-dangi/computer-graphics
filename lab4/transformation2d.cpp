#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int choice;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

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

void drawPixel(float x, float y) {
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void ddaLine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
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

void drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}

void translation(int x1, int y1, int x2, int y2, int tx, int ty)
{
    ddaLine(x1, y1, x2, y2);

    ddaLine(x1+tx, y1+ty, x2+tx, y2+ty);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    drawLine(x1, y1, x2, y2);
    drawLine(x1+tx, y1+ty, x2+tx, y2+ty);
}

void rotation(int x1, int y1, int x2, int y2, float angle)
{
    ddaLine(x1, y1, x2, y2);
    

    float xt = cos(angle)*x2 - y2*sin(angle);
    float yt = x2*sin(angle) - y2*cos(angle);

    ddaLine(x1, y1, xt, yt);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    drawLine(x1, y1, x2, y2);
    drawLine(x1, y1, xt, yt);
}

void reflection(int x1, int y1, int x2, int y2)
{
    ddaLine(x1, y1, x2, y2);
    
    int tx1 = -x1;
    int tx2 = -x2;

    ddaLine(tx1, y1, tx2, y2);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    drawLine(x1, y1, x2, y2);
    drawLine(tx1, y1, tx2, y2);
}

void scaling(int x1, int y1, int x2, int y2, int tx, int ty)
{
    int x[] = {0, -4, 4};
    int y[] = {4, 0, 0};

    drawLine(x, y, 3);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    
    int xt[] = {0*tx, -4*tx, 4*tx};
    int yt[] = {4*ty, 0*ty, 0*ty};

    drawLine(xt, yt, 3);
}

void shearing(int x1, int y1, int x2, int y2, float shx)
{
    ddaLine(x1, y1, x2, y2);

    ddaLine(x1+(shx*y1), y1, x2+(shx*y2), y2);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    drawLine(x1, y1, x2, y2);
    drawLine(x1+(shx*y1), y1, x2+(shx*y2), y2);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    switch(choice)
    {
        case 1: translation(1, 3, 7, 5, 2, 4);
                break;
        case 2: rotation(1, 3, 7, 5, 3.14/2);
                break;
        case 3: reflection(1, 3, 7, 5);
                break;
        case 4: scaling(1, 3, 7, 5, 2, 2);
                break;
        case 5: shearing(1, 3, 7, 5, -1.5);
                break;
        default: printf("Wrong input, try again!\n");
                break;
    }

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("2D Transformation");

    printf("1. Translation.\n2. Rotation.\n3. Reflection.\n4. Scaling.\n5. Shearing.\nEnter your Choice: ");
    scanf("%d", &choice);

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}