#include "../includes/freeglut/include/GL/glut.h"

class Star {
public:

    int screen_width = 1920;
    int screen_height = 1080;

    float x = rand() % screen_width;
    float y = rand() % screen_height;


    void move(GLfloat falling_speed) // since stars will be falling, y has to be decreased
    {
        y = y - falling_speed;
    }

    void show() const // draws the star
    {
        glPointSize(1);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
};
