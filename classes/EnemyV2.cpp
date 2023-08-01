#include "../includes/freeglut/include/GL/glut.h"

class EnemyV2 {
public:
    GLfloat x;           //Position initial position of x coordinate of enemy spaceship
    GLfloat y;           // initial position of y  coordinate of enemy spaceship
    int alive;          // this variable will whether the enemy is alive not not 0 means alive 1 means dead
    GLfloat x2;          //this the same x2 coordinate as we have declared earlier but this one will be retrieved for collision detection
    GLfloat y2;          //same as the above x2 t
    GLfloat w2;          //width of the object
    GLfloat h2;          //height of the object

    void getCollisionInformation()   // this function send information about current position
    {
        x2 = x - 10;
        w2 = 40;
        y2 = y + 40;
        h2 = 50;
    }

    void init(int screen_width) {
        x = rand() % screen_width;
        y = 1080;
        alive = 1;
    }


    void draw() const              //this draws the enemy
    {
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

        //glVertex2f(x+10,y-10);  // warhead
        //glVertex2f(x+10,y-10);
        //glVertex2f(x+20,y);

        glEnd();

    }

    void move(GLfloat offset) {
        y = y - offset;
    }
};