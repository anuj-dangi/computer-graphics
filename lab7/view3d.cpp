    #include <GL/glut.h>
    #include <stdio.h>
    #include <math.h>

    #define PI 3.14

    float xmin, ymin, zmin, xmax, ymax, zmax;
    float umin, vmin, wmin, umax, vmax, wmax;


    float cube[8][3] = {
    {-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
    {-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}
    };

    float t[8][3];

    void copyCube()
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<3;j++)
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


    void drawCube(float v[8][3], float c[3])
    {
        glColor3f(c[0], c[1], c[2]);
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


    void viewport()
    {
        float sx = (umax-umin)/(xmax-xmin);
        float sy = (vmax-vmin)/(ymax-ymin);
        float sz = (wmax-wmin)/(zmax-zmin);

        for(int i=0;i<8;i++)
        {
            t[i][0] = umin + sx*(cube[i][0]-xmin);
            t[i][1] = vmin + sy*(cube[i][1]-ymin);
            t[i][2] = wmin + sz*(cube[i][2]-zmin);
        }

        

        float c[] = {1, 0, 0};

        drawCube(t, c);
    }

    void menu()
    {
        printf("Enter value of xmin ymin zmin xmax ymax zmax : ");
        scanf("%f %f %f %f %f %f", &xmin, &ymin, &zmin, &xmax, &ymax, &zmax);


        printf("Enter value of umin vmin wmin umax vmax wmax: ");
        scanf("%f %f %f %f %f %f", &umin, &vmin, &wmin, &umax, &vmax, &wmax);

    }


    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        glTranslatef(0, 0, -8);

        drawGridAxis();

        glColor3f(0, 0, 1);

        glBegin(GL_LINES);


        glVertex3f(xmin,ymin,zmin); glVertex3f(xmax,ymin,zmin);
        glVertex3f(xmax,ymin,zmin); glVertex3f(xmax,ymax,zmin);
        glVertex3f(xmax,ymax,zmin); glVertex3f(xmin,ymax,zmin);
        glVertex3f(xmin,ymax,zmin); glVertex3f(xmin,ymin,zmin);

        glVertex3f(xmin,ymin,zmax); glVertex3f(xmax,ymin,zmax);
        glVertex3f(xmax,ymin,zmax); glVertex3f(xmax,ymax,zmax);
        glVertex3f(xmax,ymax,zmax); glVertex3f(xmin,ymax,zmax);
        glVertex3f(xmin,ymax,zmax); glVertex3f(xmin,ymin,zmax);

        glVertex3f(xmin,ymin,zmin); glVertex3f(xmin,ymin,zmax);
        glVertex3f(xmax,ymin,zmin); glVertex3f(xmax,ymin,zmax);
        glVertex3f(xmax,ymax,zmin); glVertex3f(xmax,ymax,zmax);
        glVertex3f(xmin,ymax,zmin); glVertex3f(xmin,ymax,zmax);

        glEnd();

        glBegin(GL_LINES);


        glVertex3f(umin,vmin,wmin); glVertex3f(umax,vmin,wmin);
        glVertex3f(umax,vmin,wmin); glVertex3f(umax,vmax,wmin);
        glVertex3f(umax,vmax,wmin); glVertex3f(umin,vmax,wmin);
        glVertex3f(umin,vmax,wmin); glVertex3f(umin,vmin,wmin);


        glVertex3f(umin,vmin,wmax); glVertex3f(umax,vmin,wmax);
        glVertex3f(umax,vmin,wmax); glVertex3f(umax,vmax,wmax);
        glVertex3f(umax,vmax,wmax); glVertex3f(umin,vmax,wmax);
        glVertex3f(umin,vmax,wmax); glVertex3f(umin,vmin,wmax);


        glVertex3f(umin,vmin,wmin); glVertex3f(umin,vmin,wmax);
        glVertex3f(umax,vmin,wmin); glVertex3f(umax,vmin,wmax);
        glVertex3f(umax,vmax,wmin); glVertex3f(umax,vmax,wmax);
        glVertex3f(umin,vmax,wmin); glVertex3f(umin,vmax,wmax);

        glEnd();

        float c[] = {0, 1, 0};
        drawCube(cube, c);

        viewport();

        glFlush();
    }

    int main(int argc, char **argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(700, 700);

        glutCreateWindow("3D Viewport");

        init();

        menu();

        glutDisplayFunc(display);

        glutMainLoop();
    }