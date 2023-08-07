//#include "../includes/freeglut/include/GL/glut.h"
#include "GameObject.cpp"

class Life : public GameObject {
public:

    void getCollisionInformation() override {
        // this function sends information about current position
        x2 = x;      // Left edge of the heart
        w2 = 40;     // Width of the heart (from x to x + 40)
        y2 = y - 25; // Top edge of the heart (from y - 25)
        h2 = 40;     // Height of the heart (from y - 25 to y + 15)
    }


    void draw() const override {

        glColor3f(1, 0, 0);

        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 20, y - 25);
        glVertex2f(x + 20, y + 5);
        glVertex2f(x + 15, y + 15);
        glVertex2f(x + 5, y + 15);
        glVertex2f(x, y + 10);

        glEnd();

        glBegin(GL_POLYGON);

        glVertex2f(x + 20, y - 25);
        glVertex2f(x + 40, y);
        glVertex2f(x + 40, y + 10);
        glVertex2f(x + 35, y + 15);
        glVertex2f(x + 25, y + 15);
        glVertex2f(x + 20, y + 5);

        glEnd();
//        drawWithBoundingBox();
    }

    void drawWithBoundingBox() const override {
        float w = 40;     // Width of the bounding box
        float h = 40;     // Height of the bounding box
        float yTop = y - 25; // Top edge of the bounding box

        glColor3f(0, 1, 0); // Set color to green, or any color you prefer for the bounding box

        glBegin(GL_LINE_LOOP);
        glVertex2f(x, yTop);
        glVertex2f(x + w, yTop);
        glVertex2f(x + w, yTop + h);
        glVertex2f(x, yTop + h);
        glEnd();
    }
};
