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
    static const int WINVALUE  = 80;
    static const int LOSEVALUE = 50;
    static const int WINDOUBLE = 30;
    static const int LOSEDOUBLE = 1;
    //borad value for place
    int borad_value[3][3] = {3,2,3,2,6,2,3,2,3};

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
    
    //if start from not middle flag
    bool startFromDiagonal = false;
    
    //start computer thinking
    int comptuerPut();
    void thinkNext(int turn, int* nBorad, int* fBorad);
    bool thinkNext2(int turn, int* nBorad, int*fBorad, int x, int y);
    
    //caluculate the value
    void calValue();
    GameManeger* game_maneger;
    
    //find continue of 2 computer num
    void findTwoLine(int turn, int* boradStatus, int* putValue);
    //find most big point
    int findPutPlace(int* putValue);
    //copy borad status
    void copyBoradStatus(int* nBorad, int* fBorad);
    //find double two line
    bool findDoubleTwoline(int turn, int* borad);
    //find max value
    int findMaxValue(int* putValue);
    //ajust borad value
    void ajustBoradValue();
    //exception(when computer start and put 11(00) && player put 33(22) it is not good to put 22(11))
    void exceptionOfPiece();
};
#endif /* defined(__NCGame__Computer__) */
