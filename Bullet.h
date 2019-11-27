//
//  Bullet.h
//  Computer_Graphics
//
//  Created by 이지훈
//  Copyright © 2019 이지훈. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

class Bullet{
public:
    //Bullet Variables
    GLboolean active = false;
    GLdouble x, y;
    GLdouble dy = 0.015; //Y Axis Speed
    GLdouble size = 0.01;
    
    //Bullet Constructor
    Bullet(){};
    
    //Bullet Destructor
    ~Bullet(){};
    
    
    //Initializing Bullet
    void InitBullet(){
        this->active = false;
        this->dy = 0.015;
        this->size = 0.01;
        this->x = 0.0;
        this->y = 0.0;
    }
};

#endif
