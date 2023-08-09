#include "../includes/freeglut/include/GL/glut.h"

class MyShip {
public:
    GLfloat x{};       //x and y coordinates
    GLfloat y{};
    int shoot{};
    int alive{};    // checks whether alive of not
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
        x -= offset;
    }

    void move_right(GLfloat offset)    //right
    {
        x += offset;
    }

    void DisplayShip() const {
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, 0);
        glVertex2f(x + 15, 10);
        glVertex2f(x + 15, 35);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x + 50, 0);
        glVertex2f(x + 15, 10);
        glVertex2f(x + 15, 35);
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
//        drawBoundingBox();
//        drawMouseBoundingBox();
    }

    static void DisplayHealth(GLfloat health) {
        health = health * 10;
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(110, 1070);
        glVertex2f(110 + health, 1070);
        glVertex2f(110 + health, 1050);
        glVertex2f(110, 1050);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(110, 1070);
        glVertex2f(110 + 200, 1070);
        glVertex2f(110 + 200, 1050);
        glVertex2f(110, 1050);
        glEnd();

        glFlush();
    }

    void drawBoundingBox() {
        x1 = x - 10;
        y1 = 0;
        w1 = 50;
        w1 = 60;
        glColor3f(0, 1, 0); // Set color to green, or any color you prefer for the bounding box

        glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x1 + w1, y1);
        glVertex2f(x1 + w1, y1 + w1);
        glVertex2f(x1, y1 + w1);
        glEnd();
    }

    void drawMouseBoundingBox() const {
        float w = 50;
        float h = 60;
        glColor3f(0, 1, 0); // Set color to green, or any color you prefer for the bounding box

        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
        glEnd();
    }
};