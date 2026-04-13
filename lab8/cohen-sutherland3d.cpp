#include <GL/glut.h>
#include <stdio.h>

float xmin=1, xmax=7, ymin=1, ymax=7, zmin=1, zmax=7;
float x1=2, yy1=2, z1=0;
float x2=6, y2=5, z2=6;

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define FRONT 16
#define BACK 32

int computeCode(float x, float y, float z)
{
    int code = INSIDE;

    if(x < xmin)
    {
        code |= LEFT;
    } 
    else if(x > xmax)
    {
        code |= RIGHT;
    }

    if(y < ymin)
    {
        code |= BOTTOM;
    } 
    else if(y > ymax)
    {
        code |= TOP;
    }

    if(z < zmin)
    {
        code |= FRONT;
    } 
    else if(z > zmax)
    {
        code |= BACK;
    } 

    return code;
}

void cohenSutherland3D()
{
    float x1c=x1, y1c=yy1, z1c=z1;
    float x2c=x2, y2c=y2, z2c=z2;

    int code1 = computeCode(x1c,y1c,z1c);
    int code2 = computeCode(x2c,y2c,z2c);

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
            float x,y,z;
            int code_out = code1 ? code1 : code2;

            if(code_out & TOP)
            {
                x = x1c + (x2c-x1c)*(ymax-y1c)/(y2c-y1c);
                z = z1c + (z2c-z1c)*(ymax-y1c)/(y2c-y1c);
                y = ymax;
            }
            else if(code_out & BOTTOM)
            {
                x = x1c + (x2c-x1c)*(ymin-y1c)/(y2c-y1c);
                z = z1c + (z2c-z1c)*(ymin-y1c)/(y2c-y1c);
                y = ymin;
            }
            else if(code_out & RIGHT)
            {
                y = y1c + (y2c-y1c)*(xmax-x1c)/(x2c-x1c);
                z = z1c + (z2c-z1c)*(xmax-x1c)/(x2c-x1c);
                x = xmax;
            }
            else if(code_out & LEFT)
            {
                y = y1c + (y2c-y1c)*(xmin-x1c)/(x2c-x1c);
                z = z1c + (z2c-z1c)*(xmin-x1c)/(x2c-x1c);
                x = xmin;
            }
            else if(code_out & FRONT)
            {
                x = x1c + (x2c-x1c)*(zmin-z1c)/(z2c-z1c);
                y = y1c + (y2c-y1c)*(zmin-z1c)/(z2c-z1c);
                z = zmin;
            }
            else if(code_out & BACK)
            {
                x = x1c + (x2c-x1c)*(zmax-z1c)/(z2c-z1c);
                y = y1c + (y2c-y1c)*(zmax-z1c)/(z2c-z1c);
                z = zmax;
            }

            if(code_out == code1)
            {
                x1c=x; y1c=y; z1c=z;
                code1 = computeCode(x1c,y1c,z1c);
            }
            else
            {
                x2c=x; y2c=y; z2c=z;
                code2 = computeCode(x2c,y2c,z2c);
            }
        }
    }

    if(accept)
    {
        glColor3f(0,1,0);
        glBegin(GL_LINES);
        glVertex3f(x1c,y1c,z1c);
        glVertex3f(x2c,y2c,z2c);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-5,-5,-20);

    glColor3f(1,0,0);

    glutWireCube(6);

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(x1,yy1,z1);
    glVertex3f(x2,y2,z2);
    glEnd();

    cohenSutherland3D();

    glFlush();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60,1,1,100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutCreateWindow("3D Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}