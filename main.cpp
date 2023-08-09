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
#include "classes/Points.cpp"


using namespace std;
using namespace irrklang;

int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);

#define n 1000
int gameState = 0;
GLfloat Health = 20;
int NOB;                //Number of Bullets
const int NOF = 5;              //Number of enemies per frame
const int NOL = 1;            //NUmber of health per frame
GLfloat enemySpeed = 5;   // speed at which enemy will fall
int sco = 0;
int highScoreForNormal = 0;
int highScoreForSpeed = 0;
GLfloat bulletSpeed = 25;  //this value will be added to the y of bullet
bool isSpeedMode;
int speedScore;
GLfloat falling_speed; //star falling speed for different modes

/////////////////////////////////////////////////////////////////////
GLfloat twicePi = 2.0f * 3.1416;
struct Color {
    GLfloat r, g, b;
};
const Color YELLOW = {245.0 / 255, 249.0 / 255, 0};
const Color RED = {244.0 / 255, 2.0 / 255, 2.0 / 255};
const Color ORANGE1 = {244.0 / 255, 152.0 / 255, 66.0 / 255};
const Color ORANGE2 = {244.0 / 255, 107.0 / 255, 65.0 / 255};
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
ISoundEngine *engine = createIrrKlangDevice();
Bullet bullet[n];       //instance of bullet object
Star star[n];        //star
MyShip ship;
Enemy enemy[NOF];            //enemy initialization
EnemyV2 enemyV2[NOF];        //enemy initialization
Life life[NOL];            //life
/////////////////////////////////////////////////////////////////////

string convertInt(int number) {
    return to_string(number);
}

void drawText(const string &text, GLfloat x, GLfloat y) {
    glRasterPos2f(x, y);
    for (const char i: text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int) i);
    }
}


void ShowStars(bool moveStars) {
    //renders the start;
    for (auto &i: star) {
        if (i.y >= 0) {
            i.show();    //render each object
            if (moveStars)
                i.move(falling_speed);    //moves starts
        } else {
            i.y = 1080;     //initial y position 500
            i.x = rand() % 1920; //initial x position
        }
    }
}

void FireBulletsIfShot() {
    if (ship.shoot)                 //when ship.ship=1
    {
        bullet[NOB - 1].fire();       //sets firing of bullet into 1
        bullet[NOB - 1].getPosition(ship); //collects the current x position of ship
        ship.shoot = 0;         //sets the shoot variable of ship into 0
    }
}

void DrawShip() {
    if (ship.alive) {
        ship.DisplayShip();
    }
    FireBulletsIfShot();
}


void DrawBullet() {
    for (auto &b: bullet) {
        if (b.firing) {
            b.draw();
            b.move(bulletSpeed);
        }

        if (b.y > 1080) {
            b.ReInit();
        }
    }
    // The logic for NOB seems a bit unclear; if it's a constant, it shouldn't be modified.
    // Otherwise, reconsider how it's being used.
}

//////////Draw enemies///////////////////////////////////
template<typename T>
void drawAndMoveEntities(T &entities) {
    for (auto &i: entities) {
        if (i.alive) {
            i.draw();
            i.move(enemySpeed);

            if (i.y - 10 < 0 || i.alive == 0) {
                i.init();
            }
        } else if (i.alive == 0) {
            i.init();
        }
    }
}

void DrawEnemy() {
    drawAndMoveEntities(enemy);
    drawAndMoveEntities(enemyV2);
    drawAndMoveEntities(life);
}
/////////////////////////////////////////////////////////////////


/////////Destroy animation//////////
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, Color color, GLfloat triangleAmount = 20) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle

    for (int i = 0; i <= triangleAmount; i++) {
        GLfloat angle = i * twicePi / triangleAmount;
        GLfloat xPosition = x + (radius * cos(angle));
        GLfloat yPosition = y + (radius * sin(angle));
        glVertex2f(xPosition, yPosition);
    }

    glEnd();
}

void DestroyAnimation(GLfloat x, GLfloat y, GLfloat radius) {
    drawFilledCircle(x, y, radius + 3, YELLOW);
    drawFilledCircle(x + 10, y + 10, radius - 5, RED);
    drawFilledCircle(x - 10, y + 10, radius - 3, ORANGE1);
    drawFilledCircle(x - 10, y - 10, radius, RED);
    drawFilledCircle(x + 10, y - 10, radius - 2, ORANGE2);
}

///////////////////////////////////////////////

////////////////////////Collision detection of enemy with space ship/////////////////////////////////////
template<typename T>
void checkCollisionWithEntity(T *entities, int size, int healthDelta) {
    ship.information_for_collision();

    for (int i = 0; i < size; i++) {
        entities[i].getCollisionInformation();

        if ((ship.x1 < (entities[i].x2 + entities[i].w2)) &&
            (entities[i].x2 < ship.x1 + ship.w1) &&
            (ship.y1 + ship.h1 == entities[i].y2 - entities[i].h2)) {

            Health += healthDelta;
        }
    }
}

void CollisionShip() {
    checkCollisionWithEntity(enemy, NOF, -5);
    checkCollisionWithEntity(enemyV2, NOF, -5);
    checkCollisionWithEntity(life, NOL, (Health < 20) ? 5 : 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Collision detection for bullet and enemy//////////////////////
template<typename T>
void checkBulletCollisionWithEntity(T *entities, int entityCount, int bulletCount, int scoreIncrement,
                                    const char *soundFile) {
    for (int i = 0; i < bulletCount; i++) {
        for (int j = 0; j < entityCount; j++) {
            entities[j].getCollisionInformation();

            if ((entities[j].x2 <= bullet[i].x) &&
                (bullet[i].x <= (entities[j].x2 + entities[j].w2)) &&
                (entities[j].alive) &&
                (entities[j].y2 <= bullet[i].y + 20) &&
                (bullet[i].y < 1080)) {

                DestroyAnimation(bullet[i].x, bullet[i].y, 20);
                entities[j].alive = 0;
                bullet[i].firing = 0;
                bullet[i].x = 0;
                bullet[i].y = 0;
                sco += scoreIncrement;
                engine->play2D(soundFile);
            }
        }
    }
}

void BulletsVsEnemyCollisionTest() {
    checkBulletCollisionWithEntity(enemy, NOF, NOB, 1, "explosion1.wav");
    checkBulletCollisionWithEntity(enemyV2, NOF, NOB, 2, "explosion2.mp3");
    checkBulletCollisionWithEntity(life, NOL, NOB, 1, "life.wav");
}
/////////////////////////////////////////////////////////////////////////////////


void Reinitialization() {
    ship.Reset();
    NOB = 0;
    Health = 20;
    for (auto & i : enemy) {
        i.init();
    }
}

/////////////////////////////////////////Keyboard/////////////////////////////////////////

void SpeedyModeCallBack(int value) {
    Reinitialization();
    speedScore = sco;
    sco = 0;
    gameState = 2;
    ship.alive = 0;
}

// This function can be used in both 'slow' and 'speedy' modes to avoid repetition.
void setGameModeAttributes(GLfloat eSpeed, GLfloat fallSpeed, bool speedMode) {
    enemySpeed = eSpeed;
    falling_speed = fallSpeed;
    isSpeedMode = speedMode;
    if (speedMode) {
        glutTimerFunc(10000, SpeedyModeCallBack, 0);
    }
}

void GameMode(const string &mode) {
    if (mode == "slow") {
        setGameModeAttributes(0.1, 0.5, false);
    } else if (mode == "speedy") {
        setGameModeAttributes(1, 1, true);
    }
}

///////////////////////////////////////////////////////////////////////////////////
void shootIfShipAlive() {
    if (ship.alive) {
        ship.shoot = 1;
        NOB++;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'f':
            shootIfShipAlive();
            break;
        case 'l':
            ship.x += 10;
            break;
        case 'j':
            ship.x -= 10;
            break;
        case 'r':
            if (!ship.alive) {
                Reinitialization();
                gameState = 1;
                GameMode(isSpeedMode ? "speedy" : "slow");
                sco = 0;
            }
            break;
        case 27:  // Escape key
            gameState = 0;
            break;
    }
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x > 850 && x < 1100 && y > 620 && y < 670) {
            exit(0);
        } else if (x > 900 && x < 1050) {
            gameState = 1;
            if (y > 560 && y < 600) {
                GameMode("speedy");
            } else if (y > 500 && y < 540) {
                GameMode("slow");
            }
            Reinitialization();
        }
    }
}

void MouseDummy(int button, int state, int x, int y) {}

void MouseForGame(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shootIfShipAlive();
    }
}

/////////////////////////////////////////////Move Object with mouse////////////////////////////////////////
void MoveShipWithMouse(int x, int y) {
    //takes the current position of mouse and sets the ship according to that
    ship.x = x;
    ship.y = y;
    glutPostRedisplay();
}

///////////////////// MENU///////////////////////////////
// Helper function to draw rectangle wrappers
void drawWrapper(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glVertex2f(x1, y1);
    glEnd();
}

void DrawMenu() //draws menu
{
    // Set OpenGL state and callbacks
    glutSetCursor(GLUT_CURSOR_INHERIT);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    // Clear and set drawing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // Draw background and other menu components
    ShowStars(false);

    drawText("2D SPACE SHOOTER", 850, 700);
    drawText("-----------------", 850, 680);
    drawText("PLAY", 940, 635);
    drawText("#  SLOW", 920, 575);
    drawText("#  SPEEDY    (10 sec)", 920, 510);
    drawText("QUIT", 940, 445);
    drawText("SLOW: Normal mode!", 800, 390);
    drawText("SPEEDY: Un-alive most enemy in 10 Second! No health penalty!", 800, 350);
    drawText("Instruction: Press 'F' to shoot, move mouse to control ship ", 800, 310);
    drawText(": +1 point", 860, 260);
    drawText(": +2 point", 860, 180);
    drawText(": +5 health", 860, 95);

    // Draw button wrappers
    drawWrapper(850, 430, 1100, 480);  // Play wrapper
    drawWrapper(900, 560, 1050, 600);  // Easy wrapper
    drawWrapper(900, 540, 1050, 500);  // Hard wrapper
    drawWrapper(850, 620, 1100, 670);  // Quit wrapper

    Points::point1();
    Points::point2();
    Points::pointIndicator();

    // Swap buffers and display
    glFlush();
    glutSwapBuffers();
}
/////////////////////////////////////////////////////////

// Helper function to read high scores from a file
int readHighScore(const string &filename) {
    fstream myfile(filename, ios_base::in);
    int score;
    myfile >> score;
    myfile.close();
    return score;
}

// Helper function to write high scores to a file
void writeHighScore(const string &filename, int score) {
    fstream myfile(filename, ios_base::out);
    myfile << convertInt(score) << endl;
    myfile.close();
}

// The refactored OverDisplay function
void OverDisplay() {
    glutKeyboardFunc(keyboard);
    glutMouseFunc(MouseDummy);
    glutSetCursor(GLUT_CURSOR_INHERIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    string text1 = "GAME OVER";
    string text3 = "Press R to restart";
    ShowStars(false);
    glColor3f(1, 0, 0);
    drawText(text1, 900, 600);

    glBegin(GL_LINE_LOOP);
    glVertex2f(840 + 50, 550);
    glVertex2f(1020 + 50, 550);
    glVertex2f(1020 + 50, 650);
    glVertex2f(840 + 50, 650);
    glEnd();

    string text2;
    string highscoreText;
    if (!isSpeedMode) {
        highScoreForNormal = readHighScore("highscoreNText.txt");
        if (sco > highScoreForNormal) {
            writeHighScore("highscoreNText.txt", sco);
            highScoreForNormal = sco;
        }
        text2 = "You Scored " + convertInt(sco);
        highscoreText = "High Score for Normal: " + convertInt(highScoreForNormal);
    } else {
        highScoreForSpeed = readHighScore("highscoreSText.txt");
        if (speedScore > highScoreForSpeed) {
            writeHighScore("highscoreSText.txt", speedScore);
            highScoreForSpeed = speedScore;
        }
        text2 = "You Scored " + convertInt(speedScore);
        highscoreText = "High Score for Speed: " + convertInt(highScoreForSpeed);
    }

    drawText(text2, 910, 510);
    drawText(highscoreText, 865, 470);
    drawText(text3, 895, 430);

    glFlush();
    glutSwapBuffers();
}


void display() {
    // Clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set Display Settings
    ShowStars(true);
    glutMouseFunc(MouseForGame);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutKeyboardFunc(keyboard);

    // Draw Game Elements
    DrawShip();
    DrawEnemy();
    DrawBullet();

    // Handle Collisions
    ship.information_for_collision();
    BulletsVsEnemyCollisionTest();
    CollisionShip();

    // Display Game Information
    MyShip::DisplayHealth(Health);
    drawText("Health :", 10, 1050);
    drawText("Score :" + convertInt(sco), 10, 1020);

    // Check Game State
    if (Health <= 0) {
        ship.alive = 0;
        gameState = 2;
    }

    // Update the display
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}



/////////////////////////////////////////////////////Main Display Function////////////////////////////////////////

void loop() {
    // OpenGL setup
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25, 1960.0, 0, 1080.0);

    // Rendering based on game state
    switch (gameState) {
        case 1:
            display();
            break;
        case 2:
            OverDisplay();
            break;
        default: // For both case 0 and any unexpected value
            DrawMenu();
            break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Space Shooter");
    glutDisplayFunc(loop);
    glutPassiveMotionFunc(MoveShipWithMouse);

    glutFullScreen();
    glLineWidth(4);
    engine->play2D("sound.mp3", true);
    glutMainLoop();
    engine->drop();
    return 0;
}