#include "../includes/freeglut/include/GL/glut.h"

class Life {
public:
    GLfloat x{};           //Position initial position of x coordinate of enemy spaceship
    GLfloat y{};           // initial position of y  coordinate of enemy spaceship
    int alive = 1;          // this variable will whether the enemy is alive not not 0 means alive 1 means dead
    GLfloat x2{};          //this the same x2 coordinate as we have declared earlier but this one will be retrieved for collision detection
    GLfloat y2{};          //same as the above x2 t
    GLfloat w2{};          //width of the object
    GLfloat h2{};          //height of the object

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    void getCollisionInformation()   // this function send information about current position
    {
        x2 = x - 10;
        w2 = 40;
        y2 = y + 40;
        h2 = 50;
    }

    void init() {
        x = rand() % screen_width;
        y = screen_height;
        alive = 1;
    }


    void draw() const            //heart
    {
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

    }

    void move(GLfloat offset) //this function will be descended the enemy according a give speed which is offset
    {
        y = y - offset;
    }
};
