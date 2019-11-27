//
//  main.cpp
//  Computer_Graphics
//
//  Created by 이지훈
//  Copyright © 2019 이지훈. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "Bullet.h"
#include "Player.h"
#include "Item.h"
#include "Meteor.h"
#include "Enum.h"

//Max Value For Bullet and Meteor
#define MAX_NUM_BULLET 100
#define MAX_NUM_METEOR 100

using namespace std;

//Window Vars
GLint windowSizeX = 700;
GLint windowSizeY = 700;

//Menu Vars
GLint playMenuID;
GLint pauseMenuID;

//Bullet Count
GLint countBullet = 0;

//Meteor Count
GLint countMeteor = 0;

//Player Vars
GLdouble playerSize = 0.005;

//State
GLboolean pauseState = false;
GLboolean playState = true;

//Enum Vars
KEY tempKey;
KEY keyPressed;
DISABLE disableState;

//Global Objects
Bullet bullet[MAX_NUM_BULLET];
Player player;
Meteor meteor[MAX_NUM_METEOR];
Item item;

void CheckPlayerBoundary();
void CheckCollision(Meteor *meteor1);
void CheckItemCollision(Item *item1);

//Player Drawing
void DrawPlayer(Player *player1){
    glPushMatrix();

    //Which Key Pressed
    switch(keyPressed){
        case LEFT:
            if(disableState != MOVE_LEFT)
                player1->x -= player1->dx;
            break;
        case RIGHT:
            if(disableState != MOVE_RIGHT)
                player1->x += player1->dx;
            break;
        case TOP:
            if(disableState != MOVE_TOP)
                player1->y += player1->dy;
            break;
        case DOWN:
            if(disableState != MOVE_DOWN)
                player1->y -= player1->dy;
            break;
        case STOP:
            break;
        default:
            break;

    }
    
    //Check If Player Is Out Of Bounds
    CheckPlayerBoundary();
    
    //Drawing Player
    glBegin(GL_TRIANGLE_FAN);
    
    //Top Point
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f( player1->x + playerSize * 0, player1->y + playerSize * 12);
    player1->PointX1 = player1->x + playerSize * 0;
    player1->PointY1 = player1->y + playerSize * 12;

    //Left Point
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f( player1->x - playerSize * 8, player1->y - playerSize * 8);
    player1->PointX2 = player1->x - playerSize * 8;
    player1->PointY2 = player1->y - playerSize * 8;

    //Middle Point
    glColor3f(0.0, 1.0, 1.0);
    glVertex2f( player1->x - playerSize  * 0, player1->y - playerSize * 0);

    //Right Point
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f( player1->x + playerSize * 8, player1->y - playerSize * 8);
    player1->PointX3 = player1->x + playerSize * 8;
    player1->PointY3 = player1->y - playerSize * 8;

    glEnd();
}

//Bullet Drawing
void DrawBullet (Bullet *bullet1) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    bullet1->y += bullet1->dy;
    glTranslatef(bullet1->x, bullet1->y, 0);
    glutSolidSphere(bullet1->size, 15, 15);
    glPopMatrix();
    if(bullet1->y >= 0.98){
        bullet1->InitBullet();
    }
}



//Meteor Drawing
void DrawMeteor(Meteor *meteor1){
    glColor3f(0.58, 0.29, 0.0);
    glPushMatrix();
    meteor1->y -= meteor1->dy;
    glTranslatef(meteor1->x, meteor1->y, 0);
    glutSolidSphere(meteor1->size, 16, 16);
    glPopMatrix();
    if(meteor1->y <= -0.98){
        meteor1->InitMeteor();
    }
    CheckCollision(meteor1);
}

//Life Count Drawing
void DrawLife(){
    GLdouble x = -0.90;
    GLdouble y = -0.90;
    for(int i = 0; i < player.life; i++){
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(x + playerSize * 0, y + playerSize * 12);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(x - playerSize * 8, y - playerSize * 8);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(x - playerSize  * 0, y - playerSize * 0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x + playerSize * 8, y - playerSize * 8);
        glEnd();
        x += 0.1;
    }
}

//Item Drawing
void DrawItem(Item *item1){
    glColor3f(0.99, 0.84, 0.0);
    glPushMatrix();
    glTranslatef(item1->x, item1->y, 0);
    glutSolidSphere(item1->size, 15, 15);
    glPopMatrix();
    CheckItemCollision(item1);
}

//Bullet Count Drawing
void DrawBulletCount(){
    GLdouble y = -0.90;
    GLdouble x = 0.90;
    for(int i = 0; i < player.bulletCount; i++){
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glutSolidSphere(0.01, 16, 16);
        glPopMatrix();
        x -= 0.05;
    }
}

//Display Function
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Draw Player
    DrawPlayer(&player);
    
    //Draw For Each Active Bullets
    for(int i = 0; i < MAX_NUM_BULLET; i++){
        if(bullet[i].active == true){
            DrawBullet(&bullet[i]);
        }
    }
    
    //Draw For Each Active Meteors
    for(int i = 0; i < MAX_NUM_METEOR; i++){
        if(meteor[i].active == true){
            DrawMeteor(&meteor[i]);
        }
    }
    
    //Draw Item
    if(item.active == true){
        DrawItem(&item);
    }
    
    //Draw Bullet Count
    if(player.bulletCount > 0){
        DrawBulletCount();
    }
    
    //Draw Life
    DrawLife();
    glFlush();
    glutSwapBuffers();
}

//Pause Function
void Pause(){
    for(int i = 0; i < MAX_NUM_BULLET; i++){
        bullet[i].dy = 0.0;
        meteor[i].dy = 0.0;
    }
    tempKey = keyPressed;
    keyPressed = STOP;
}

//Resume Function
void Resume(){
    for(int i = 0; i < MAX_NUM_BULLET; i++){
        bullet[i].dy = 0.015;
        meteor[i].dy = 0.009;
    }
    keyPressed = tempKey;
}

//Restart Game Function
void ReStart(){
    player.InitPlayer();
    item.InitItem();
    for(int i = 0; i < MAX_NUM_BULLET; i++){
        bullet[i].InitBullet();
        meteor[i].InitMeteor();
    }
    keyPressed = NOTHING;
    pauseState = false;
}

//Menu Function
void MyMainMenu(int entry){
    switch(entry){
        case 1:
            Pause();
            pauseState = true;
            glutSetMenu(pauseMenuID);
            break;
        case 2:
            Resume();
            pauseState = false;
            glutSetMenu(playMenuID);
            break;
        case 3:
            ReStart();
            glutSetMenu(playMenuID);
            break;
        case 0:
            player.~Player();
            item.~Item();
            for(int i = 0; i < MAX_NUM_BULLET; i++){
                bullet[i].~Bullet();
                meteor[i].~Meteor();
            }
            exit(0);
            break;
        default:
            break;
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Movement Function
void MySpecialKey(int key, int x, int y){
    if(keyPressed != STOP){
        if(key == GLUT_KEY_LEFT){
            keyPressed = LEFT;
        }
        else if(key == GLUT_KEY_RIGHT){
            keyPressed = RIGHT;
        }
        else if(key == GLUT_KEY_UP){
            keyPressed = TOP;
        }
        else if(key == GLUT_KEY_DOWN){
            keyPressed = DOWN;
        }
    }
    glutPostRedisplay();
}

//Check Collision Function
void CheckCollision(Meteor *meteor1){
    
    //Checking For Bullet and Meteor Intersection
    for(int i = 0; i < MAX_NUM_BULLET; i++){
        if(bullet[i].active == true){
            GLdouble rad1 = pow(meteor1->size + bullet[i].size, 2.0);
            GLdouble d1 = pow(meteor1->x - bullet[i].x, 2.0) + pow(meteor1->y - bullet[i].y, 2.0);
            if(rad1 >= d1){
                bullet[i].InitBullet();
                meteor1->InitMeteor();
            }
        }
    }
    
    //Checking For Player and Meteor Intersection
    GLdouble rad2 = pow(meteor1->size, 2.0);
    GLdouble d2 = pow(meteor1->x - player.PointX1, 2.0) + pow(meteor1->y - player.PointY1, 2.0);
    GLdouble d3 = pow(meteor1->x - player.PointX2, 2.0) + pow(meteor1->y - player.PointY2, 2.0);
    GLdouble d4 = pow(meteor1->x - player.PointX3, 2.0) + pow(meteor1->y - player.PointY3, 2.0);
    if(rad2 >= d2 || rad2 >= d3 || rad2 >= d4){
        player.life -= 1;
        meteor1->InitMeteor();
    }
    
}

//Check Item Collision Function
void CheckItemCollision(Item *item){
    
    //Checking For Player and Item Intersection
    GLdouble rad2 = pow(item->size, 2.0);
    GLdouble d2 = pow(item->x - player.PointX1, 2.0) + pow(item->y - player.PointY1, 2.0);
    GLdouble d3 = pow(item->x - player.PointX2, 2.0) + pow(item->y - player.PointY2, 2.0);
    GLdouble d4 = pow(item->x - player.PointX3, 2.0) + pow(item->y - player.PointY3, 2.0);
    if(rad2 >= d2 || rad2 >= d3 || rad2 >= d4){
        player.bulletCount = 20;
        item->active = false;
    }
}

//Check Player Position Function
void CheckPlayerBoundary(){
    if(player.x >= 0.96){
        disableState = MOVE_RIGHT;
    }
    else if(player.x <= -0.96){
        disableState = MOVE_LEFT;
    }
    else if(player.y >= 0.96){
        disableState = MOVE_TOP;
    }
    else if(player.y <= -0.96){
        disableState = MOVE_DOWN;
    }
    else{
        disableState = NONE;
    }
}

//Keyboard Function For Shooting
void MyKeyboard(unsigned char key, int x, int y){
    if(key == ' ' && player.bulletCount > 0 && keyPressed != STOP){
        bullet[countBullet].active = true;
        bullet[countBullet].x = player.x;
        bullet[countBullet].y = player.y;
        player.bulletCount -= 1;
        countBullet += 1;
        
        if(countBullet == MAX_NUM_BULLET){
            countBullet = 0;
        }
    }
}



//Checking If Player Died Function
void CheckDeath(){
    if(player.life <= 0){
        for(int i = 0; i < MAX_NUM_BULLET; i++){
            bullet[i].dy = 0.0;
            meteor[i].dy = 0.0;
        }
        keyPressed = STOP;
    }
}

//Timer Function
void MyTimer(int Value){
    glutSpecialFunc(MySpecialKey);
    glutKeyboardFunc(MyKeyboard);
    
    //Possibility Meteor Will Be Made
    int makeMeteor = rand() % 15;
    
    //Meteor X Axis Value
    GLdouble meteorX = rand() % 100000 / 100000.0;
    
    //Plus or Minus Value
    int plusMinusX = rand() % 2;
    int plusMinusY = rand() % 2;
    
    //Possibility Bullet Item Will Be Made
    int makeItem = rand() % 1000;
    
    //Making Item
    if(item.active == false && makeItem == 0 && player.life > 0 && pauseState == false){
        if(plusMinusX == 0)
            item.x = rand() % 100000 / 100000.0;
        else
            item.x = -(rand() % 100000 / 100000.0);
        if(plusMinusY == 0)
            item.y = rand() % 100000 / 100000.0;
        else
            item.y = -(rand() % 100000 / 100000.0);
        item.active = true;
    }
    
    //Making Meteor
    if(makeMeteor == 0 && player.life > 0 && pauseState == false){
        meteor[countMeteor].active = true;
        if(plusMinusX == 0)
            meteor[countMeteor].x = meteorX;
        else
            meteor[countMeteor].x = -meteorX;
        countMeteor += 1;
        if(countMeteor >= MAX_NUM_BULLET){
            countMeteor = 0;
        }
    }
    
    //Checking Life Of Player
    CheckDeath();
    glutPostRedisplay();
    glutTimerFunc(30, MyTimer, Value);
}

int main(int argc, char ** argv){
    srand(time_t(NULL));
    
    //Init Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowSizeX, windowSizeY);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowSizeX) / 2, ((glutGet(GLUT_SCREEN_HEIGHT) - windowSizeY)/ 2));
    glutCreateWindow("201521825이지훈_SpaceGame");
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Initiating Menus
    pauseMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Resume", 2);
    glutAddMenuEntry("Restart", 3);
    glutAddMenuEntry("Exit", 0);
    playMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Pause", 1);
    glutAddMenuEntry("Restart", 3);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    //Game
    glutTimerFunc(20, MyTimer, 1);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
