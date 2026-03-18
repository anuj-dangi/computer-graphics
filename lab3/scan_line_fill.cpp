#include <GL/glut.h>
#include <algorithm>
using namespace std;

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}

void scanFill(int x[], int y[], int edges)
{
    int ymin = y[0], ymax = y[0];

    for(int i=1;i<edges;i++)
    {
        ymin = min(ymin,y[i]);
        ymax = max(ymax,y[i]);
    }

    for(int scan=ymin; scan<=ymax; scan++)
    {
        int interX[10];
        int count = 0;

        for(int i=0;i<edges;i++)
        {
            int x1 = x[i];
            int y1 = y[i];
            int x2 = x[(i+1)%edges];
            int y2 = y[(i+1)%edges];

            if(y1==y2) continue;

            if(scan >= std::min(y1,y2) && scan < std::max(y1,y2))
            {
                int xi = x1 + (scan-y1)*(x2-x1)/(y2-y1);
                interX[count++] = xi;
            }
        }

        std::sort(interX, interX+count);

        for(int i=0;i<count;i+=2)
        {
            for(int j=interX[i]; j<=interX[i+1]; j++)
            {
                glVertex2i(j,scan);
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    glBegin(GL_POINTS);

    int x[] = {100,200,300};
    int y[] = {100,300,200};
    int edges = 3;

    scanFill(x,y,edges);

    glEnd();

    glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Scan Line Polygon Fill");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}