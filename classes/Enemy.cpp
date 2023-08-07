//#include "../includes/freeglut/include/GL/glut.h"
#include "GameObject.cpp"

class Enemy : public GameObject {
public:

    void getCollisionInformation() override {
        x2 = x - 10;
        w2 = 40;
        y2 = y;
        h2 = 50;
    }


    void draw() const override {
        glColor3f(0.9, 0.91, 0.98);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 20, y);
        glVertex2f(x + 20, y + 40);
        glVertex2f(x, y + 40);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x - 10, y + 30);  // Wing 1
        glVertex2f(x, y + 25);
        glVertex2f(x, y + 15);
        glVertex2f(x - 10, y + 20);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(x + 20, y + 20);
        glVertex2f(x + 30, y + 15);  // Wing 2
        glVertex2f(x + 30, y + 25);
        glVertex2f(x + 20, y + 30);
        glEnd();

        glColor3f(0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 10, y - 10);  // Warhead
        glVertex2f(x + 20, y);
        glEnd();
//        drawWithBoundingBox();
    }

    void drawWithBoundingBox() const override {
        // Hard-coded height and width values
        const float w2 = 40;
        const float h2 = 50;

        // Adjustments for the bounding box
        float x2 = x - 10;
        float y2 = y;

        glColor3f(0, 1, 0); // Set color to green for the bounding box

        glBegin(GL_LINE_LOOP);
        glVertex2f(x2, y2);
        glVertex2f(x2 + w2, y2);
        glVertex2f(x2 + w2, y2 + h2);
        glVertex2f(x2, y2 + h2);
        glEnd();
    }
};