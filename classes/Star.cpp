#include "../includes/freeglut/include/GL/glut.h"

class Star {
public:
    float x; // x and y coordinates of the star
    float y;

    void move() // since stars will be falling, y has to be decreased
    {
        y = y - 2;
    }

    void show() const // draws the star
    {
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(1);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        // glFlush();
    }
};
