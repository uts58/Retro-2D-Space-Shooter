#include "../includes/freeglut/include/GL/glut.h"

class MyShip {
public:
    GLfloat x;       //x and y coordinates
    GLfloat y;
    int shoot;
    int alive;    // checks whether alive of not
    GLfloat x1{};
    GLfloat y1{};
    GLfloat w1{};
    GLfloat h1{};


    void Reset() //resets the ship object
    {
        shoot = 0;
        alive = 1;
    }

    void information_for_collision() // info about collision
    {
        x1 = x - 10;
        y1 = 0;
        w1 = 50;
        h1 = 60;
    }

    void move_left(GLfloat offset)     //moves the object left
    {
        x = x - offset;
    }

    void move_right(GLfloat offset)    //right
    {
        x = x + offset;
    }

    void DisplayShip() const {
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, 0);
        glVertex2f(x + 15, 10);
        glVertex2f(x + 15, 25);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x + 50, 0);
        glVertex2f(x + 15, 10);
        glVertex2f(x + 15, 25);
        glEnd();

        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, 0);
        glVertex2f(x - 10, 5);
        glVertex2f(x - 25, 13);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x + 50, 0);
        glVertex2f(x + 40, 5);
        glVertex2f(x + 55, 13);
        glEnd();

        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(x, 12);
        glVertex2f(x + 15, 25);
        glVertex2f(x + 15, 60);
        glEnd();

        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(x + 30, 12);
        glVertex2f(x + 15, 25);
        glVertex2f(x + 15, 60);

        glEnd();
    }
};