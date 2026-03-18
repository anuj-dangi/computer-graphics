#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

int choice;

float cube[8][3] = {
{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}
};

float t[8][3];

void copyCube()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<3;j++)
            t[i][j] = cube[i][j];
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
    glVertex3fv(v[0]); glVertex3fv(v[4]);
    glVertex3fv(v[1]); glVertex3fv(v[5]);
    glVertex3fv(v[2]); glVertex3fv(v[6]);
    glVertex3fv(v[3]); glVertex3fv(v[7]);
    glEnd();
}

void parallelProjection()
{
    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0];
        t[i][1] = cube[i][1];
        t[i][2] = 0;
    }
}

void perspectiveProjection()
{
    float d = 2;

    for(int i=0;i<8;i++)
    {
        t[i][0] = (cube[i][0]*d)/(cube[i][2]+d);
        t[i][1] = (cube[i][1]*d)/(cube[i][2]+d);
        t[i][2] = cube[i][2];
    }
}

void obliqueProjection()
{
    float d = 2;
    int deg;
    printf("angle: ");
    scanf("%d", &deg);
    
    float angle = deg*3.14/180;

    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0] + d*cube[i][2]*cos(angle);
        t[i][1] = cube[i][1] + d*cube[i][2]*sin(angle);
        t[i][2] = 0;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0,0,-6);

    glColor3f(1,1,1);
    drawCube(cube);

    glColor3f(1,0,0);
    drawCube(t);

    glFlush();
}

void isometricProjection()
{
    for(int i=0;i<8;i++)
    {
        t[i][0] = cube[i][0] - cube[i][2];
        t[i][1] = cube[i][1] + ((cube[i][0] + cube[i][2])/(float)2);
        t[i][2] = 0;
    }
}

void menu()
{
    copyCube();

    cout<<"1. Parallel Projection\n";
    cout<<"2. Perspective Projection\n";
    cout<<"3. Oblique Projection\n";
    cout<<"4. Isometric Projection\n";
    cout<<"Enter choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1: parallelProjection();
                break;

        case 2: perspectiveProjection();
                break;
        case 3: obliqueProjection();
                break;
        case 4: isometricProjection();
                break;

        default: cout<<"Wrong choice\n";
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60,1,1,100);

    glMatrixMode(GL_MODELVIEW);

    copyCube();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(700,700);
    glutCreateWindow("Projection in Computer Graphics");

    init();

    glutDisplayFunc(display);

    menu();

    glutMainLoop();
}