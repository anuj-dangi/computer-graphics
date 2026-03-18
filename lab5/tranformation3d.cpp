#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14

float cube[8][3] = {
{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}
};

float t[8][3];

void copyCube()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            t[i][j] = cube[i][j];
        }
    }
}

void drawGridAxis()
{
    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);

    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    glVertex2f(0, -10);
    glVertex2f(0, 10);

    glEnd();
}


void drawCube(float v[8][3])
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(v[0]);
    glVertex3fv(v[1]);
    glVertex3fv(v[2]);
    glVertex3fv(v[3]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3fv(v[4]);
    glVertex3fv(v[5]);
    glVertex3fv(v[6]);
    glVertex3fv(v[7]);
    glEnd();

    glBegin(GL_LINES);
    glVertex3fv(v[0]);
    glVertex3fv(v[4]);
    glVertex3fv(v[1]);
    glVertex3fv(v[5]);
    glVertex3fv(v[2]);
    glVertex3fv(v[6]);
    glVertex3fv(v[3]);
    glVertex3fv(v[7]);
    glEnd();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);

    copyCube();

}

void translation()
{
    int tx, ty, tz;
    printf("tx ty tz: ");
    scanf("%d %d %d", &tx, &ty, &tz);

    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0] + tx;
        t[i][1] = cube[i][1] + ty;
        t[i][2] = cube[i][2] + tz;  
    }
}

void rotation()
{
    int degree;

    printf("angle: ");
    scanf("%d", &degree);

    float angle = (degree*PI)/((float)180.0);

    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0]*cos(angle) - cube[i][0]*sin(angle);
        t[i][1] = cube[i][0]*sin(angle) + cube[i][1]*cos(angle);
        t[i][2] = cube[i][2];
    }
}

//about XY plane
void reflection()
{
    for(int i=0;i<8;i++)
    {
        t[i][0]=cube[i][0];
        t[i][1]=cube[i][1];
        t[i][2]=-cube[i][2];
    }
}

void shearing()
{
    float shx, shy;
    printf("Enter shx shy: ");
    scanf("%f %f", &shx, &shy);

    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0] + shx*cube[i][1];
        t[i][1] = cube[i][1] + shy*cube[i][0];
        t[i][2] = cube[i][2];
    }
}

void scaling()
{
    float sx, sy, sz;
    printf("Enter sx sy sz: ");
    scanf("%f %f %f", &sx, &sy, &sz);

    for(int i=0;i<8;i++)
    {
        t[i][0]=cube[i][0]*sx;
        t[i][1]=cube[i][1]*sy;
        t[i][2]=cube[i][2]*sz;
    }
}

void menu()
{
    copyCube();

    int choice;
    printf("1. Translation.\n2. Rotation.\n3. Reflection.\n4. Shearing.\n5. Scaling.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1: translation();
                break;
        case 2: rotation();
                break;
        case 3: reflection();
                break;
        case 4: shearing();
                break;
        case 5: scaling();
                break;
        default:printf("Error, wrong input, try again!\n");
                break;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glTranslatef(0, 0, -8);

    drawGridAxis();

    glColor3f(0, 0, 0);
    drawCube(cube);

    glColor3f(1, 0, 0);
    drawCube(t);

    glFlush();

    menu();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);

    glutCreateWindow("3D Transformation");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
}