//#include "../includes/freeglut/include/GL/glut.h"
#include "GameObject.cpp"

class EnemyV2 : public GameObject {
public:

    void getCollisionInformation() override {
        // this function send information about current position
        x2 = x - 10;
        w2 = 40;
        y2 = y;
        h2 = 50;
    }

    void draw() const override {
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(x - 5, y + 10);
        glVertex2f(x - 10, y + 30);
        glVertex2f(x - 10, y + 10);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x + 20, y + 10);
        glVertex2f(x + 25, y + 30);
        glVertex2f(x + 25, y + 10);
        glEnd();

        glColor3f(0, 0, 1);

        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 15, y);
        glVertex2f(x + 20, y + 10);
        glVertex2f(x + 15, y + 40);
        glVertex2f(x, y + 40);
        glVertex2f(x - 5, y + 10);
        glVertex2f(x + 10, y - 10);  // warhead
        glVertex2f(x + 10, y - 10);
        glVertex2f(x + 20, y);
        glEnd();
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