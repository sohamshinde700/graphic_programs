/*
Implement DDA and Bresenham line drawing algorithm to draw: i) Simple
Line ii) Dotted Line iii) Dashed Line iv) Solid line ;
using mouse interface Divide the screen in four quadrants with center as (0, 0). The line should work
for all the slopes positive as well as negative.
*/

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

int points[4];
int pointer = 0;
int choice = 1;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 500, 0);
}

void drawDDALine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float xinc, yinc;
    int steps;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2d(round(x), round(y));
        x = x + xinc;
        y = y + yinc;
    }
    glEnd();
}

void dotedLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float xinc, yinc;
    int steps;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        if ((int)x % 4 == 0)
        {
            glVertex2d(round(x), round(y));
        }
        x = x + xinc;
        y = y + yinc;
    }
    glEnd();
}

void dashLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float xinc, yinc;
    int steps;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        if ((int)x % 4 != 0)
        {
            glVertex2d(round(x), round(y));
        }
        x = x + xinc;
        y = y + yinc;
    }
    glEnd();
}

void drawBreLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int xinc, yinc;
    xinc = (x1 > x2) ? -1 : 1;
    yinc = (y1 > y2) ? -1 : 1;
    int x = x1, y = y1;

    if (dx == 0)
    {
        glBegin(GL_POINTS);
        for (int i = 0; i < dy; i++)
        {
            glVertex2d(x, y);
            y = y + yinc;
        }
        glEnd();
        return;
    }
    if (dy == 0)
    {
        glBegin(GL_POINTS);
        for (int i = 0; i < dx; i++)
        {
            glVertex2d(x, y);
            x = x + xinc;
        }
        glEnd();
        return;
    }
    if (dx > dy)
    {
        int p = 2 * dy - dx;
        glBegin(GL_POINTS);
        for (int i = 0; i < dx; i++)
        {
            glVertex2d(x, y);
            if (p > 0)
            {
                y = y + yinc;
                p = p + 2 * (dy - dx);
            }
            else
            {
                p = p + 2 * dy;
            }
            x = x + xinc;
        }
        glEnd();
    }
    else
    {
        int p = 2 * dx - dy;
        glBegin(GL_POINTS);
        for (int i = 0; i < dy; i++)
        {
            glVertex2d(x, y);
            if (p > 0)
            {
                x = x + xinc;
                p = p + 2 * (dx - dy);
            }
            else
            {
                p = p + 2 * dx;
            }
            y = y + yinc;
        }
        glEnd();
    }
}

void mouseFun(int a, int b, int c, int d)
{

    printf("\n %d  %d  %d  %d", a, b, c, d);
    if (a == GLUT_LEFT_BUTTON && b == GLUT_DOWN && pointer < 4)
    {
        points[pointer] = c;
        pointer++;
        points[pointer] = d;
        pointer++;
    }
    if (pointer == 4)
    {
        glColor3f(1.0, 0.0, 0.0);
        switch (choice)
        {
        case 1:
            drawBreLine(points[0], points[1], points[2], points[3]);
            break;
        case 2:
            drawDDALine(points[0], points[1], points[2], points[3]);
            break;
        case 3:
            dotedLine(points[0], points[1], points[2], points[3]);
            break;
        case 4:
            dashLine(points[0], points[1], points[2], points[3]);
            break;

        default:
            break;
        }
        glutSwapBuffers();
        pointer = 0;
    }
}
void keyboardFun(unsigned char key, int x, int y)
{
    printf("%c", key);
    if (key = '1')
    {
        choice = 1;
        glutMouseFunc(mouseFun);
    }
    else if (key = '1')
    {
        choice = 2;
        glutMouseFunc(mouseFun);
    }
    else if (key = '1')
    {
        choice = 3;
        glutMouseFunc(mouseFun);
    }
    else if (key = '1')
    {
        choice = 4;
        glutMouseFunc(mouseFun);
    }
}
void drawFunction()
{
    glutKeyboardFunc(keyboardFun);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Assignment no 2");
    init();
    glutDisplayFunc(drawFunction);
    glutMainLoop();
    return 0;
}
