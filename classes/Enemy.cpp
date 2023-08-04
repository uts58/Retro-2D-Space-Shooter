#include "../includes/freeglut/include/GL/glut.h"

class Enemy {
public:
    GLfloat x{};         // Initial position of x-coordinate of enemy spaceship
    GLfloat y{};         // Initial position of y-coordinate of enemy spaceship
    int alive{};  // This variable indicates whether the enemy is alive or not. 0 means alive, 1 means dead
    GLfloat x2{};        // x2 coordinate used for collision detection
    GLfloat y2{};        // y2 coordinate used for collision detection
    GLfloat w2{};        // Width of the object
    GLfloat h2{};        // Height of the object

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    void getCollisionInformation() {
        x2 = x - 10;
        w2 = 40;
        y2 = y;
        h2 = 50;
    }

    void init() {
        x = rand() % screen_width;
        y = screen_height;
        alive = 1;
    }

    void draw() const {
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

        drawWithBoundingBox();
    }

    void drawWithBoundingBox() const {
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

    void move(GLfloat offset) {
        y -= offset;  // Move the enemy downwards according to the given speed (offset)
    }
};