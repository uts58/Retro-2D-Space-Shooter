#pragma once
#include "../includes/freeglut/include/GL/glut.h"

class GameObject {
public:
    GLfloat x;
    GLfloat y;
    int alive;
    GLfloat x2;
    GLfloat y2;
    GLfloat w2;
    GLfloat h2;

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    virtual void getCollisionInformation() = 0;   // this function sends information about current position

    void init() {
        x = rand() % screen_width;
        y = screen_height;
        alive = 1;
    }

    virtual void draw() const = 0;  // this function will be implemented by the child classes

    virtual void drawWithBoundingBox() const = 0; // this function will be implemented by the child classes

    void move(GLfloat offset) {
        y = y - offset;
    }
};
