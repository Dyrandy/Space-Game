//
//  Item.h
//  Computer_Graphics
//
//  Created by 이지훈
//  Copyright © 2019 이지훈. All rights reserved.
//

#ifndef Item_h
#define Item_h

class Item{
public:
    //Item Variables
    GLdouble x = 0.0, y = 0.0;
    GLdouble size = 0.06;
    GLboolean active = false;
    
    //Item Constructor
    Item(){};
    
    //Item Destructor
    ~Item(){};
    
    //Initializing Item
    void InitItem(){
        this->x = 0.0;
        this->y = 0.0;
        this->size = 0.06;
        this->active = false;
    }
};

#endif
