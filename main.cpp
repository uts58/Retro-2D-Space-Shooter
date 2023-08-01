#include <cstdlib>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include "includes/irrKlang/include/irrKlang.h"
#include "includes/freeglut/include/GL/glut.h"

#include "classes/Star.cpp"
#include "classes/Bullet.cpp"
#include "classes/Enemy.cpp"
#include "classes/Enemyv2.cpp"
#include "classes/Life.cpp"


using namespace std;
using namespace irrklang;

int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);

const int arraySize = 1920;

#define n 1000
int counter = 0;
int gameState = 0;
GLfloat Health = 20;
int c = 0;
int NOB;                //Number of Bullets
int NOF = 5;              //Number of enemies per frame
int NOL = 2;            //NUmber of health per frame
int enemyX[arraySize];       //Generates Random X positions for X
GLfloat enemySpeed = 5;   // speed at which enemy will fall
int sco = 0;
int highScoreForNormal = 0;
int highScoreForSpeed = 0;
GLfloat bulletSpeed = 25;  //this value will be added to the y of bullet
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

void drawText(const string &text, GLfloat x, GLfloat y) //draw text
{
    glRasterPos2f(x, y);
    for (char i: text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int) i);
    }
}

Bullet b[n];       //instance of bullet object
Star s[n];        //star
MyShip ship;
Enemy e[5];            //enemy initialization
EnemyV2 e2[5];        //enemy initialization
Life l[2];            //life

void ShowStars(int x)  //renders the start;
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

void DrawShip()       //renders the ship object
{
    if (ship.alive) //as long as the ship is alive
    {
        ship.DisplayShip(); //it will render the ship object
    }
    FireBulletsIfShot(); //if ship.shot is 1 it sets the bullet ready to shot
}

/////////////////////////////////////////////Move Object with mouse////////////////////////////////////////
void move(int x, int y)  //takes the current position of mouse and sets the ship according to that
{
    ship.x = x;
    glutPostRedisplay();
}

void DrawBullet()    //renders bullet
{
    int i;
    for (i = 0; i < NOB; i++) {
        if (b[i].firing) {
            b[i].draw(); //renders
            b[i].move(bulletSpeed); //move
        }
        if (b[i].y > 1080) {
            b[i].ReInit();  //resets the bullet object when it goes beyond the screen

        }
    }
    if (NOB > 50)  // number of bullets can never go beyond 30
    {
        NOB = 0;
    }
}

void DrawEnemy() {
    for (int i = 0; i < NOF; i++) {
        if (e[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            e[i].draw();             //render the enemy
            e[i].move(enemySpeed);  //enemies will fall at this speed
            if (e[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                e[i].init(screen_width);  //initialize
            }
        }
        if (e[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            e[i].init(screen_width);
        }
    }

    for (int i = 0; i < NOF; i++) {
        if (e2[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            e2[i].draw();             //render the enemy
            e2[i].move(enemySpeed);  //enemies will fall at this speed
            if (e2[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                e2[i].init(screen_width);  //initialize
            }
        }
        if (e2[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            e2[i].init(screen_width);
        }
    }
    for (int i = 0; i < NOL; i++) {
        if (l[i].alive)  //as long as the enemy is alive  it will be rendered
        {
            l[i].draw();             //render the each enemy
            l[i].move(enemySpeed);  //enemies will fall at this speed
            if (l[i].y - 10 < 0)  //when the y coordinate of y will be 0 new enemies will be initialized
            {
                l[i].init(screen_width);  //initialize
            }
        }
        if (l[i].alive == 0) //if the current enemy is dead it will also be initialized
        {
            l[i].init(screen_width);
        }
    }

}

/////////Destroy animation//////////
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat triangleAmount = 20) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle

    GLfloat twicePi = 2.0f * 3.1416; // Use M_PI constant from math library for better precision

    for (int i = 0; i <= triangleAmount; i++) {
        GLfloat angle = i * twicePi / triangleAmount;
        GLfloat xPosition = x + (radius * cos(angle));
        GLfloat yPosition = y + (radius * sin(angle));
        glVertex2f(xPosition, yPosition);
    }

    glEnd();
}

void DestroyAnimation(GLfloat x, GLfloat y, GLfloat radius) {    //center circle
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

///////////////////////////////////////////////
void DisplayHealth(GLfloat health) {
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
void CollisionShip() {
    for (int i = 0; i < NOF; i++) {
        e[i].getCollisionInformation();
        ship.information_for_collision();

        if ((ship.x1 < (e[i].x2 + e[i].w2)) && (e[i].x2 < ship.x1 + ship.w1) &&
            ((ship.y1 + ship.h1 == e[i].y2 - e[i].h2))) {
            Health = Health - 5;
        }
    }
    for (int i = 0; i < NOF; i++) {
        e2[i].getCollisionInformation();
        ship.information_for_collision();

        if ((ship.x1 < (e2[i].x2 + e2[i].w2)) && (e2[i].x2 < ship.x1 + ship.w1) &&
            ((ship.y1 + ship.h1 == e2[i].y2 - e2[i].h2))) {
            Health = Health - 5;
        }
    }
    for (int i = 0; i < NOL; i++) {
        l[i].getCollisionInformation();
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
            e2[j].getCollisionInformation();
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
        e[i].init(screen_width);
    }
}

/////////////////////////////////////////Keyboard/////////////////////////////////////////

void update(int value) {
    Reinitialization();
    speedScore = sco;
    sco = 0;
    NOB = 0;
    gameState = 2;
    ship.alive = 0;
}

void GameMode(const string &mode) //gamemode
{
    if (mode == "slow") {
        enemySpeed = 0.5;
        isSpeedMode = false;
    } else if (mode == "speedy") {
        enemySpeed = 5;
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

                gameState = 1;
                if (isSpeedMode) {
                    GameMode("speedy");
                    sco = 0;
                } else {
                    GameMode("slow");
                    sco = 0;
                }
            }
            break;

        case 27:
            gameState = 0;
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
            gameState = 1;
            GameMode("speedy");
            Reinitialization();
            NOB = 0;
        } else if ((x > 900) && (x < 1050) && (y > 500) && (y < 540)) {
            gameState = 1;
            GameMode("slow");
            Reinitialization();
            NOB = 0;
        }
    }
}

void MouseDummy(int button, int state, int x, int y) {}

void MouseForGame(int button, int state, int x, int y) //mouse for menu
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

void point1() {

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

void point2() {
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

void DrawMenu() //draws menu
{
    glutSetCursor(GLUT_CURSOR_INHERIT);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    ShowStars(1);
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


void OverDisplay()                //displays text when game is over
{
    glutKeyboardFunc(keyboard);
    glutMouseFunc(MouseDummy);
    glutSetCursor(GLUT_CURSOR_INHERIT);
    if (!isSpeedMode) {
        fstream myfile("highscoreNText.txt", ios_base::in);
        myfile >> highScoreForNormal;
        if (sco > highScoreForNormal) {
            fstream myfile("highscoreNText.txt", ios_base::out);
            myfile << convertInt(sco) << endl;
            myfile.close();
        } else {
            myfile.close();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        string text1 = "GAME OVER";
        string text2 = "You Scored " + convertInt(sco);
        string highscoreNText = "High Score for Normal: " + convertInt(highScoreForNormal);
        string text3 = "Press R to restart";
        ShowStars(1);
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
        myfile >> highScoreForSpeed;
        if (speedScore > highScoreForSpeed) {
            fstream myfile("highscoreSText.txt", ios_base::out);
            myfile << convertInt(speedScore) << endl;
            myfile.close();
        } else {
            myfile.close();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        string text1 = "GAME OVER";
        string text2 = "You Scored " + convertInt(speedScore);
        string highscoreSText = "High Score for Speed: " + convertInt(highScoreForSpeed);
        string text3 = "Press R to restart";
        ShowStars(1);
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
    ShowStars(0);
    glutMouseFunc(MouseForGame);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardFunc(keyboard);
    DrawShip();
    DrawEnemy();
    DrawBullet();
    ship.information_for_collision();
    BulletsVsEnemyCollisionTest();
    CollisionShip();
    DisplayHealth(Health);

    string sf = "Score :" + convertInt(sco);
    string ss = "Health :"/* + convertInt(Health)*/;
    drawText(ss, 10, 1050);
    drawText(sf, 10, 1020);
    if (Health <= 0) {
        ship.alive = 0;

        gameState = 2;
    }
    glFlush();
    glutSwapBuffers();

    glutPostRedisplay();
}


/////////////////////////////////////////////////////Main Display Function////////////////////////////////////////

void loop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (gameState) {
        case 0:
            DrawMenu();
            break;
        case 1:
            display();
            break;
        case 2:
            OverDisplay();
            break;
        default:
            DrawMenu();
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
    engine->drop();
    return 0;
}