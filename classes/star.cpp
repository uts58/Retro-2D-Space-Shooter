#include "../includes/freeglut/include/GL/glut.h"

class star                      //start object we have made start with glpoints
{
public:

    float x;                //x and y coordinates of start
    float y;

    void move()              // since stars will be falling y has to be decreased
    {
        y = y - 2;
    }

    void show() const     // draws the start
    {
        //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glPointSize(1);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        //glFlush();
    }

};