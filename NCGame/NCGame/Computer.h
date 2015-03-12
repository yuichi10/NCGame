//
//  Computer.h
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#ifndef __NCGame__Computer__
#define __NCGame__Computer__

#include <stdio.h>
class GameManeger;

class Computer
{
public:
    Computer();
    //borad value for place/
    const int borad_value[3][3] = {3,2,3,2,5,2,3,2,3};
    //boradStatus
    int borad_status[3][3];
    //computer's number
    int computerTurn = 0;
    //start computer thinking
    int comptuerPut();
    
    //caluculate the value
    void calValue(int* putV);
    GameManeger* game_maneger;
    
    //find continue of 2 computer num
    void findTwoLine();
    //find most big point
    int findPutPlace(int* putV);
};
#endif /* defined(__NCGame__Computer__) */
