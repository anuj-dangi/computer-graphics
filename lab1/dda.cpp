#include <GL/glut.h>
#include <cmath>

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

void drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGridAxis();

    drawLine(1, 3, 8, 9);

    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(3.0);
    ddaLine(1, 3, 8, 9);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
