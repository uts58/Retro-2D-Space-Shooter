#include "../includes/freeglut/include/GL/glut.h"
#include "MyShip.cpp"

class Bullet {
public:
    GLfloat x{};
    GLfloat y{};
    int firing;

    Bullet() {
        firing = 0;
    }

    void getPosition(MyShip ship)   // takes the position of ship
    {
        x = ship.x + 15;
        y = 35;
    }

    void fire() {
        firing = 1;
    }

    void draw() const             //draws the bullet
    {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 10);
        glEnd();
    }

    void move(GLfloat offset)   //ascends the bullet
    {
        y = y + offset;
    }

    void ReInit()         //initialize
    {
        firing = 0;
    }
};