#include <cstdlib>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include "includes/irrKlang/include/irrKlang.h"
#include "includes/freeglut/include/GL/glut.h"

#include "classes/star.cpp"


using namespace std;
using namespace irrklang;

#define n 1000
int counter = 0;
int gamestate = 0;
int Health = 20;
int c = 0;
int NOB;                //Number of Bullets
int NOF = 5;              //Number of enemies per frame
int NOL = 2;            //NUmber of health per frame
int enemyX[1920];       //Generates Random X positions for X
float enemyspeed = 5;   // speed at which enemy will fall
int sco = 0;
int highscoreForNormal = 0;
int highscoreForSpeed = 0;
int bulletspeed = 25;  //this value will be added to the y of bullet
bool isSpeedMode;
int speedScore;

ISoundEngine *engine = createIrrKlangDevice();

string convertInt(int number) {
    stringstream ss;

    ss << number;
    return ss.str();
}

string convertHealth(int number) {
    stringstream ss;//create a stringstream
    Health = Health - 1;
    ss << Health;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

void drawText(string text, float x, float y) //draw text
{
    glRasterPos2f(x, y);
    for (int i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int) text[i]);
    }
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.1416;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

class enemy             //enemy class
{
public:
    float x{};           //Position initial position of x coordinate of enemy spaceship
    float y{};           // initial position of y  coordinate of enemy spaceship
    int alive = 1;          // this variable will whether the enemy is alive not not 0 means alive 1 means dead
    float x2{};          //this the same x2 coordinate as we have declared earlier but this one will be retrieved for collision detection
    float y2{};          //same as the above x2 t
    float w2{};          //width of the object
    float h2{};          //height of the object
//    enemy()             // constructor for enemy
//    {
//        alive = 1;        // we will make the alive  variable 1
//    }

    void getCollisionInformation() // this function send information about current position
    {
        x2 = x - 10;
        w2 = 40;
        y2 = y + 40;
        h2 = 50;
    }

    void init() {
        x = enemyX[rand() % 1920];
        y = 1080;
        alive = 1;
    }


    void draw()              //this draws the enemy
    {
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

    void
    move(float offset) //this function will be descend the enemy according a give speed which is offset in this case
    {
        y = y - offset;
    }

};

class enemyv2             //enemy class
{
public:
    double x;           //Position initial position of x coordinate of enemy spaceship
    double y;           // initial position of y  coordinate of enemy spaceship
    int alive;          // this variable will whether the enemy is alive not not 0 means alive 1 means dead
    double x2;          //this the same x2 coordinate as we have declared earlier but this one will be retrieved for collision detection
    double y2;          //same as the above x2 t
    double w2;          //width of the object
    double h2;          //height of the object
    enemyv2()             // constructor for enemy
    {
        alive = 1;        // we will make the alive  variable 1

    }

    void getcollsioninformation()   // this function send information about current position
    {
        x2 = x - 10;
        w2 = 40;
        y2 = y + 40;
        h2 = 50;
    }

    void init() {
        x = enemyX[rand() % 1920];
        y = 1080;
        alive = 1;
    }


    void draw()              //this draws the enemy
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

    void
    move(float offset) //this function will be descend the enemy according a give speed which is offset in this case
    {
        y = y - offset;
    }
};

class life             //enemy class
{
public:
    double x;           //Position initial position of x coordinate of enemy spaceship
    double y;           // initial position of y  coordinate of enemy spaceship
    int alive;          // this variable will whether the enemy is alive not not 0 means alive 1 means dead
    double x2;          //this the same x2 coordinate as we have declared earlier but this one will be retrieved for collision detection
    double y2;          //same as the above x2 t
    double w2;          //width of the object
    double h2;          //height of the object
    life()             // constructor for enemy
    {
        alive = 1;        // we will make the alive  variable 1

    }

    void getcollsioninformation()   // this function send information about current position
    {
        x2 = x - 10;
        w2 = 40;
        y2 = y + 40;
        h2 = 50;
    }

    void init() {
        x = enemyX[rand() % 1920];
        y = 1080;
        alive = 1;
    }


    void draw()              //heart
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

    void
    move(float offset) //this function will be descend the enemy according a give speed which is offset in this case
    {
        y = y - offset;
    }
};



class myship            //class for spaceship
{
public:
    double x;       //x and y coordinates
    double y;
    int shoot;
    int alive;    // checks whether alive of not
    double x1;
    double y1;
    double w1;
    double h1;

    myship()         //constructor
    {
        x = 250;       //initial position
        y = 40;
        shoot = 0;
        alive = 1;      //alive or not
    }

    void information_for_collision() // info about collision
    {
        x1 = x - 10;
        y1 = 0;
        w1 = 50;
        h1 = 60;
    }

    void move_left(int offset)     //moves the object left
    {
        x = x - offset;
    }

    void move_right(int offset)    //right
    {
        x = x + offset;
    }

    void displayShip() {
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

    void Constructor() //resets the ship object
    {
        x = 250;
        y = 40;
        shoot = 0;
        alive = 1;
    }
};

class bullet {
public:
    double x;
    double y;
    int firing;
    double x3;
    double y3;
    double w3;
    double h3;

    bullet() {
        firing = 0;
    }

    void getPosition(myship ship)   // takes the position of ship
    {
        x = ship.x + 15;
        y = ship.y + 35;
    }

    void fire() {
        firing = 1;
    }

    void draw()             //draws the bullet
    {
        glColor3f(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 10);
        glEnd();
    }

    void move(int offset)   //ascends the bullet
    {
        y = y + offset;
    }

    void reinit()         //initialize
    {
        firing = 0;
    }
};


bullet b[n];       //instance of bullet object
star s[n];        //star
myship ship;
enemy e[5];            //enemy initialization
enemyv2 e2[5];        //enemy initialization
life l[2];            //life

void showstars(int x)  //renders the start;
{
    int i;
    if (x == 0) {
        for (i = 0; i < n; i++) {
            if (s[i].y >= 0) {
                s[i].show();    //render each object
                s[i].move();    //moves starts
            } else {
                s[i].y = 1080;     //initial y position 500
                s[i].x = rand() % 1920; //initial x position
            }
        }
    } else if (x == 1) {
        for (i = 0; i < n; i++) {
            if (s[i].y >= 0) {
                s[i].show();    //render each object
            } else {
                s[i].y = 1080;     //initial y position 500
                s[i].x = rand() % 1920; //initial x position
            }
        }
    }

}

void FireBulletsIfShot() {
    if (ship.shoot)                 //when ship.ship=1
    {
        b[NOB - 1].fire();       //sets firing of bullet into 1
        b[NOB - 1].getPosition(ship); //collects the current x position of ship
        ship.shoot = 0;         //sets the shoot variable of ship into 0
    }
}

void drawship()       //renders the ship object
{
    if (ship.alive) //as long as the ship is alive
    {
        ship.displayShip(); //it will render the ship object
    }
    FireBulletsIfShot(); //if ship.shot is 1 it sets the bullet ready to shot
}

/////////////////////////////////////////////Move Object with mouse////////////////////////////////////////
void move(int x, int y)  //takes the current position of mouse and sets the ship according to that
{
    ship.x = x;
    glutPostRedisplay();
}

void drawbullet()    //renders bullet
{
    int i;
    for (i = 0; i < NOB; i++) {
        if (b[i].firing) {
            b[i].draw(); //renders
            b[i].move(bulletspeed); //move
        }
        if (b[i].y > 1080) {
            b[i].reinit();  //resets the bullet object when it goes beyond the screen

        }
    }
    if (NOB > 50)  // number of bullets can never go beyond 30
    {
        NOB = 0;
    }
}

void drawenemy() {
    for (int i = 0; i < NOF; i++) {
        if (e[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            e[i].draw();             //render the each enemy
            e[i].move(enemyspeed);  //enemies will fall at this speed
            if (e[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                e[i].init();  //initialize
            }
        }
        if (e[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            e[i].init();
        }
    }

    for (int i = 0; i < NOF; i++) {
        if (e2[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            e2[i].draw();             //render the each enemy
            e2[i].move(enemyspeed);  //enemies will fall at this speed
            if (e2[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                e2[i].init();  //initialize
            }
        }
        if (e2[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            e2[i].init();
        }
    }
    for (int i = 0; i < NOL; i++) {
        if (l[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            l[i].draw();             //render the each enemy
            l[i].move(enemyspeed);  //enemies will fall at this speed
            if (l[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                l[i].init();  //initialize
            }
        }
        if (l[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            l[i].init();
        }
    }

}

/////////Destroy animation//////////

void DestroyAnimation(int x, int y, int radius) {    //center cirle
    glColor3ub(245, 249, 0);
    drawFilledCircle(x, y, radius + 3);
    //side circles
    glColor3ub(244, 2, 2);
    drawFilledCircle(x + 10, y + 10, radius - 5);
    glColor3ub(244, 152, 66);
    drawFilledCircle(x - 10, y + 10, radius - 3);
    glColor3ub(244, 2, 2);
    drawFilledCircle(x - 10, y - 10, radius);
    glColor3ub(244, 107, 65);
    drawFilledCircle(x + 10, y - 10, radius - 2);
}

void displayhealth(int health) {
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
    //glutSwapBuffers();
}

////////////////////////Collision detection of enemy with space ship/////////////////////////////////////
void collisionship() {
    for (int i = 0; i < NOF; i++) {
        e[i].getCollisionInformation();
        ship.information_for_collision();

        if ((ship.x1 < (e[i].x2 + e[i].w2)) && (e[i].x2 < ship.x1 + ship.w1) &&
            ((ship.y1 + ship.h1 == e[i].y2 - e[i].h2))) {
            Health = Health - 5;
        }
    }
    for (int i = 0; i < NOF; i++) {
        e2[i].getcollsioninformation();
        ship.information_for_collision();

        if ((ship.x1 < (e2[i].x2 + e2[i].w2)) && (e2[i].x2 < ship.x1 + ship.w1) &&
            ((ship.y1 + ship.h1 == e2[i].y2 - e2[i].h2))) {
            Health = Health - 5;
        }
    }
    for (int i = 0; i < NOL; i++) {
        l[i].getcollsioninformation();
        ship.information_for_collision();

        if ((ship.x1 < (l[i].x2 + l[i].w2)) && (l[i].x2 < ship.x1 + ship.w1) &&
            ((ship.y1 + ship.h1 == l[i].y2 - l[i].h2))) {
            if (Health < 20) {
                Health = Health + 5;
            }
        }
    }
}


/////////////////////////////////////Collision detection for bullet and enemy//////////////////////
void BulletsVsEnemyCollisionTest() {
    for (int i = 0; i < NOB; i++) {
        for (int j = 0; j < NOF; j++) {
            e[j].getCollisionInformation();
            if ((e[j].x2 <= b[i].x) && (b[i].x <= (e[j].x2 + e[j].w2)) && (e[j].alive) && (e[j].y2 <= b[i].y + 20) &&
                (b[i].y < 1050)) {
                DestroyAnimation(b[i].x + 3, b[i].y + 3, 10);
                e[j].alive = 0;
                b[i].firing = 0;
                b[i].x = 0;
                b[i].y = 0;
                sco += 1;
                engine->play2D("explosion1.wav");
            }
        }
    }

    for (int i = 0; i < NOB; i++) {

        for (int j = 0; j < NOF; j++) {
            e2[j].getcollsioninformation();
            if ((e2[j].x2 <= b[i].x) && (b[i].x <= (e2[j].x2 + e2[j].w2)) && (e2[j].alive) &&
                (e2[j].y2 <= b[i].y + 20) && (b[i].y < 1050)) {
                DestroyAnimation(b[i].x, b[i].y, 10);
                e2[j].alive = 0;
                b[i].firing = 0;
                b[i].x = 0;
                b[i].y = 0;
                sco += 2;
                engine->play2D("explosion2.mp3");

            }
        }
    }
    //for (int i = 0; i < NOL; i++)
    //{

    //	for (int j = 0; j < NOL; j++) {
    //		l[j].getCollsionInformation();
    //		if ((l[j].x2 <= b[i].x) && (b[i].x <= (l[j].x2 + l[j].w2)) && (l[j].alive) && (l[j].y2 <= b[i].y + 20) && (b[i].y < 1050))
    //		{
    //			DestroyAnimation(b[i].x, b[i].y, 10);
    //			l[j].alive = 0;
    //			b[i].firing = 0;
    //			b[i].x = 0;
    //			b[i].y = 0;
    //			sco += 2;
    //			engine->play2D("explosion1.wav");

    //		}
    //	}
    //}
}


void Reinitialization() {
    ship.Constructor();
    Health = 20;
    //sco = 0;
    int i;
    NOF = 5;
    for (i = 0; i < NOF; i++) {
        e[i].init();
    }
    return;
}

/////////////////////////////////////////Keyboard/////////////////////////////////////////

void update(int value) {


    Reinitialization();
    speedScore = sco;
    sco = 0;
    NOB = 0;
    gamestate = 2;
    ship.alive = 0;

}

void gamemode(string mode) //gamemode
{
    if (mode == "slow") {
        enemyspeed = 5;
        isSpeedMode = false;
    } else if (mode == "speedy") {
        enemyspeed = 25;
        isSpeedMode = true;
        glutTimerFunc(10000, update, 0);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
        case 'F':
            if (ship.alive) {
                ship.shoot = 1;
                NOB++;
            }
            break;

        case 'L':
        case 'l':
            ship.x = ship.x + 10;
            break;

        case 'J':
        case 'j':
            ship.x = ship.x - 10;
            break;

        case 'r':
        case 'R':
            if (ship.alive == 0) {
                Reinitialization();

                gamestate = 1;
                if (isSpeedMode) {
                    gamemode("speedy");
                    sco = 0;
                } else {
                    gamemode("slow");
                    sco = 0;
                }
            }
            break;

        case 27:
            gamestate = 0;
            break;

    }
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) //mouse for menu
{

    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        if ((x > 850) && (x < 1100) && (y > 620) && (y < 670)) {
            exit(0);
        } else if ((x > 900) && (x < 1050) && (y > 560) && (y < 600)) {
            gamestate = 1;
            gamemode("speedy");
            Reinitialization();
            NOB = 0;
        } else if ((x > 900) && (x < 1050) && (y > 500) && (y < 540)) {
            gamestate = 1;
            gamemode("slow");
            Reinitialization();
            NOB = 0;
        }
    }
}

void mousedummy(int button, int state, int x, int y) {}

void mouseforgame(int button, int state, int x, int y) //mouse for menu
{

    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        if (ship.alive) {
            ship.shoot = 1;
            NOB++;
        }
    }
}

void pointIndicator() {
    //1 point
    int x = 800;
    int y = 250;
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

void point1() {

    int x = 800;
    int y = 170;
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

void point2() {
    int x = 785;
    int y = 100;

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

void drawmenu() //draws menu
{
    glutSetCursor(GLUT_CURSOR_INHERIT);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    showstars(1);
    string line = "-----------------";
    string name = "2D SPACE SHOOTER";
    string play = "PLAY";
    string slow = "#  SLOW";
    string speedy = "#  SPEEDY    (10 sec)";
    string p1 = ": +1 point";
    string p2 = ": +2 point";
    string p3 = ": +5 health";

    string note1 = "SLOW: Normal mode!";
    string note2 = "SPEEDY: Kill 'enemy all in 1 min! No health penalty!";
    string instruction = "Instruction: Press 'F' to shoot, move mouse to controll ship ";
    char quit[6] = "QUIT";
    glColor3f(1.0, 0.0, 0.0);
    drawText(line, 850, 680);
    drawText(name, 850, 700);
    drawText(play, 940, 635);
    drawText(slow, 920, 575);
    drawText(speedy, 920, 510);
    drawText(quit, 940, 445);
    drawText(note1, 800, 390);
    drawText(note2, 800, 350);
    drawText(instruction, 800, 310);
    drawText(p1, 860, 260);
    drawText(p2, 860, 180);
    drawText(p3, 860, 95);
    //play wrapper
    glBegin(GL_LINE_STRIP);
    glVertex2f(850, 430);
    glVertex2f(1100, 430);
    glVertex2f(1100, 480);
    glVertex2f(850, 480);
    glVertex2f(850, 430);
    glEnd();

    //easy wrapper
    glBegin(GL_LINE_STRIP);
    glVertex2f(900, 560);
    glVertex2f(1050, 560);
    glVertex2f(1050, 600);
    glVertex2f(900, 600);
    glVertex2f(900, 560);
    glEnd();

    //hard wrapper
    glBegin(GL_LINE_STRIP);
    glVertex2f(900, 540);
    glVertex2f(1050, 540);
    glVertex2f(1050, 500);
    glVertex2f(900, 500);
    glVertex2f(900, 540);
    glEnd();

    //quit wrapper
    glBegin(GL_LINE_STRIP);
    glVertex2f(850, 620);
    glVertex2f(1100, 620);
    glVertex2f(1100, 670);
    glVertex2f(850, 670);
    glVertex2f(850, 620);
    glEnd();

    point1();
    point2();
    pointIndicator();
    glFlush();
    glutSwapBuffers();

}


void overdisplay()                //displays text when game is over
{
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mousedummy);
    glutSetCursor(GLUT_CURSOR_INHERIT);
    if (!isSpeedMode) {
        fstream myfile("highscoreNText.txt", ios_base::in);
        myfile >> highscoreForNormal;
        if (sco > highscoreForNormal) {
            fstream myfile("highscoreNText.txt", ios_base::out);
            myfile << convertInt(sco) << endl;
            myfile.close();
        } else {
            myfile.close();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        string text1 = "GAME OVER";
        string text2 = "You Scored " + convertInt(sco);
        string highscoreNText = "High Score for Normal: " + convertInt(highscoreForNormal);
        string text3 = "Press R to restart";
        showstars(1);
        glColor3f(1, 0, 0);
        drawText(text1, 900, 600);
        glBegin(GL_LINE_LOOP);
        glVertex2f(840 + 50, 550);
        glVertex2f(1020 + 50, 550);
        glVertex2f(1020 + 50, 650);
        glVertex2f(840 + 50, 650);
        glEnd();
        drawText(text2, 910, 510);
        drawText(highscoreNText, 865, 470);
        drawText(text3, 895, 430);
        //glRasterPos2f(660, 600);
        glFlush();
        glutSwapBuffers();
    } else {
        fstream myfile("highscoreSText.txt", ios_base::in);
        myfile >> highscoreForSpeed;
        if (speedScore > highscoreForSpeed) {
            fstream myfile("highscoreSText.txt", ios_base::out);
            myfile << convertInt(speedScore) << endl;
            myfile.close();
        } else {
            myfile.close();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        string text1 = "GAME OVER";
        string text2 = "You Scored " + convertInt(speedScore);
        string highscoreSText = "High Score for Speed: " + convertInt(highscoreForSpeed);
        string text3 = "Press R to restart";
        showstars(1);
        glColor3f(1, 0, 0);
        drawText(text1, 900, 600);
        glBegin(GL_LINE_LOOP);
        glVertex2f(840 + 50, 550);
        glVertex2f(1020 + 50, 550);
        glVertex2f(1020 + 50, 650);
        glVertex2f(840 + 50, 650);
        glEnd();
        drawText(text2, 910, 510);
        drawText(highscoreSText, 865, 470);
        drawText(text3, 895, 430);
        //glRasterPos2f(660, 600);
        glFlush();
        glutSwapBuffers();
    }

}

void display() {
    start:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    showstars(0);
    glutMouseFunc(mouseforgame);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardFunc(keyboard);
    drawship();
    drawenemy();
    drawbullet();
    ship.information_for_collision();
    BulletsVsEnemyCollisionTest();
    collisionship();
    displayhealth(Health);
    char score[10] = {0};
    string sf = "Score :" + convertInt(sco);
    string ss = "Health :"/* + convertInt(Health)*/;
    drawText(ss, 10, 1050);
    drawText(sf, 10, 1020);
    if (Health <= 0) {
        ship.alive = 0;

        gamestate = 2;
    }
    glFlush();
    system("sleep 0.0001");
    glutSwapBuffers();

    glutPostRedisplay();
}





/////////////////////////////////////////////////////Main Display Function////////////////////////////////////////

void loop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (gamestate) {
        case 0:
            drawmenu();
            break;
        case 1:
            display();
            break;
        case 2:
            overdisplay();
            break;
    }
}


void myinit() {
    int i;
    int inc = 10;
    for (i = 0; i < n; i++) {
        s[i].x = rand() % 1920;
        s[i].y = rand() % 1080;
    }

    for (i = 0; i < 1920; i++) {
        enemyX[i] = inc;
        inc++;
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25, 1960.0, 0, 1080.0);
    //gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Space Shooter");
    glutDisplayFunc(loop);
    glutPassiveMotionFunc(move);

    myinit();
    glutFullScreen();
    engine->play2D("sound.mp3", true);
    glutMainLoop();
    return 0;
}