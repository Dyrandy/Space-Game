//
//  Player.h
//  Computer_Graphics
//
//  Created by 이지훈
//  Copyright © 2019 이지훈. All rights reserved.
//

#ifndef Player_h
#define Player_h

class Player{
public:
    //Player Variables
    int life = 3;
    unsigned int bulletCount = 0;
    GLdouble x = 0.01;
    GLdouble y = 0.01;
    GLdouble dx = 0.01;
    GLdouble dy = 0.01;
    
    //Three Major Points Used For Collision
    GLdouble PointX1, PointX2, PointX3;
    GLdouble PointY1, PointY2, PointY3;
    
    //Player Constructor
    Player(){};
    
    //Player Destructor
    ~Player(){};
    
    //Initializing Player
    void InitPlayer(){
        this->life = 3;
        this->x = 0.01;
        this->y = 0.01;
        this->PointX1 = 0.0;
        this->PointX2 = 0.0;
        this->PointX3 = 0.0;
        this->PointY1 = 0.0;
        this->PointY2 = 0.0;
        this->PointY3 = 0.0;
        this->bulletCount = 0;
    }
};

#endif
