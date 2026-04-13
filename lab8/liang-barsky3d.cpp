#include <stdio.h>
#include <GL/glut.h>

float xmin=1, xmax=7, ymin=1, ymax=7, zmin=1, zmax=7;
float x1, yy1, z1, x2, y2, z2;

void init()
{
    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void drawCube()
{
    glColor3f(1,0,0);
    glutWireCube(6);
}

void drawLine()
{
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(x1,yy1,z1);
    glVertex3f(x2,y2,z2);
    glEnd();
}

void liangBarsky3D()
{
    float dx = x2 - x1;
    float dy = y2 - yy1;
    float dz = z2 - z1;

    float p[6] = {-dx, dx, -dy, dy, -dz, dz};
    float q[6] = {
        x1 - xmin, xmax - x1,
        yy1 - ymin, ymax - yy1,
        z1 - zmin, zmax - z1
    };

    float t1 = 0, t2 = 1;

    for(int i=0;i<6;i++)
    {
        if(p[i] == 0)
        {
            if(q[i] < 0)
                return;
        }
        else
        {
            float t = q[i] / p[i];

            if(p[i] < 0)
            {
                if(t > t1) t1 = t;
            }
            else
            {
                if(t < t2) t2 = t;
            }
        }
    }

    if(t1 > t2) return;

    float x1c = x1 + t1*dx;
    float y1c = yy1 + t1*dy;
    float z1c = z1 + t1*dz;

    float x2c = x1 + t2*dx;
    float y2c = yy1 + t2*dy;
    float z2c = z1 + t2*dz;

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(x1c,y1c,z1c);
    glVertex3f(x2c,y2c,z2c);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-5,-5,-20);

    drawCube();
    drawLine();
    liangBarsky3D();

    glFlush();
}

void menu()
{
    printf("Enter xmin ymin zmin xmax ymax zmax: ");
    scanf("%f %f %f %f %f %f",&xmin,&ymin,&zmin,&xmax,&ymax,&zmax);

    printf("Enter x1 y1 z1 x2 y2 z2: ");
    scanf("%f %f %f %f %f %f",&x1,&yy1,&z1,&x2,&y2,&z2);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutCreateWindow("3D Liang-Barsky Clipping");

    menu();
    init();

    glutDisplayFunc(display);
    glutMainLoop();
}