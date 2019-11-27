//
//  Meteor.h
//  Computer_Graphics
//
//  Created by 이지훈
//  Copyright © 2019 이지훈. All rights reserved.
//

#ifndef Meteor_h
#define Meteor_h

class Meteor{
public:
    //Meteor Variables
    GLdouble x = 0.0, y = 1.0;
    GLdouble dy = 0.009; //Y Axis Speed
    GLdouble size = 0.1;
    GLboolean active = false;
    
    
    //Meteor Constructor
    Meteor(){};
    
    //Meteor Destructor
    ~Meteor(){};
    
    //Initializing Meteor
    void InitMeteor(){
        this->x = 0.0;
        this->y = 1.0;
        this->dy = 0.009;
        this->size = 0.1;
        this->active = false;
    }
};

#endif
