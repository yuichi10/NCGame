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
    int borad_value[3][3] = {3,2,3,2,6,2,3,2,3};
    static const int WINVALUE  = 80;
    static const int LOSEVALUE = 50;
    static const int WINDOUBLE = 30;
    static const int LOSEDOUBLE = 1;

    //computer's thikning value of the place
    int put_value[3][3] = {0};
    //boradStatus
    int borad_status[3][3];
    //next borad status
    int nBorad_status[3][3];
    //next and next borad status
    int nnBorad_status[3][3];
    
    //computer's number
    int computerTurn = 0;
    //player's turn
    int playerTurn = 0;
    
    //start computer thinking
    int comptuerPut();
    void thinkNext(int turn, int* nBorad, int* fBorad);
    
    //caluculate the value
    void calValue();
    GameManeger* game_maneger;
    
    //find continue of 2 computer num
    void findTwoLine();
    //find most big point
    int findPutPlace();
    //copy borad status
    void copyBoradStatus(int* nBorad, int* fBorad);
    //find double two line
    bool findDoubleTwoline(int turn, int* borad);
    //find max value
    int findMaxValue();
    //ajust borad value
    void ajustBoradValue();
};
#endif /* defined(__NCGame__Computer__) */
