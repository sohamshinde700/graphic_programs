/*
Implement DDA and Bresenham line drawing algorithm to draw: i) Simple
Line ii) Dotted Line iii) Dashed Line iv) Solid line ;
using mouse interface Divide the screen in four quadrants with center as (0, 0). The line should work
for all the slopes positive as well as negative.
*/

#include<GL/freeglut.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<stdio.h>
#include<math.h>

int points[4];
int pointer = 0;

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    gluOrtho2D(0,500,500,0);
}

void drawDDALine(float x1,float y1, float x2,float y2){
    float dx=x2-x1,dy=y2-y1;
    float m = abs(dy/dx),xinc,yinc;
    int steps;
    if(abs(dx)>abs(dx)){
        steps = abs(dx);
    }
    else{
        steps = abs(dy);
    }
    xinc=dx/(float)steps;
    yinc = dy/(float)steps;
    float x = x1;
    float y=y1;
    glBegin(GL_POINTS);
    for(int i = 0;i<=steps;i++){
        glVertex2d(round(x),round(y));
        x = x+xinc;
        y = y+yinc;
    }
    glEnd();
}
void drawFunction(){
    drawDDALine(20,20,100,100);
    glFlush();
}
void mouseFun(int a ,int b ,int c ,int d){
    
    printf("\n %d  %d  %d  %d",a,b,c,d);
    if(a==GLUT_LEFT_BUTTON && b == GLUT_DOWN && pointer<4){
        points[pointer] =c;
        pointer++;
        points[pointer] = d; 
        pointer++;
    }
    if(pointer ==4){
        glColor3f(1.0,0.0,0.0);
        drawDDALine(points[0],points[1],points[2],points[3]);
        glutSwapBuffers();
        pointer=0;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Assignment no 2");
     init();
     glutMouseFunc(mouseFun);
    // glutDisplayFunc(drawFunction);
   
    glutMainLoop();
    return 0;
}
