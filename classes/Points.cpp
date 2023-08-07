#include "../includes/freeglut/include/GL/glut.h"

class Points {
public:
    static void pointIndicator() {
        //1 point
        GLfloat x = 800;
        GLfloat y = 250;
        glColor3f(0.9, 0.91, 0.98);
        glBegin(GL_QUADS);
        glVertex2f(x, y);

        glVertex2f(x + 20, y);       //BODY
        glVertex2f(x + 20, y + 40);
        glVertex2f(x, y + 40);

        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(x - 10, y + 30);  //wing 1
        glVertex2f(x, y + 25);
        glVertex2f(x, y + 15);
        glVertex2f(x - 10, y + 20);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(x + 20, y + 20);
        glVertex2f(x + 30, y + 15);  // wing2
        glVertex2f(x + 30, y + 25);
        glVertex2f(x + 20, y + 30);
        glEnd();

        glColor3f(0, 0, 1);


        glBegin(GL_POLYGON);
        glVertex2f(x, y);

        glVertex2f(x + 10, y - 10);  // warhead
        //glVertex2f(x+10,y-10);
        glVertex2f(x + 20, y);

        glEnd();

    }

    static void point1() {

        GLfloat x = 800;
        GLfloat y = 170;
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


        glEnd();

    }

    static void point2() {
        GLfloat x = 785;
        GLfloat y = 100;

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
};