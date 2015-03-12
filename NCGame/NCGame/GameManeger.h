//
//  GameManeger.h
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#ifndef __NCGame__GameManeger__
#define __NCGame__GameManeger__

#include <stdio.h>
#include "BoradView.h"
#include "Computer.h"

class GameManeger
{
public:
    static GameManeger* getInstance(){
        static GameManeger gameManeger;
        return &gameManeger;
    }
    //AHEAD player's peace
    static const int AHEAD = 1;
    //Last player's peace
    static const int LAST = 2;
    //if draw
    static const int DRAW = 3;
    //number space
    int SPACE = 0;
    //number borad
    int BORADSIZE = 5;
    //wall number
    int WALL = 99;
    //Player's turn
    int playerTurn = 0;
    //computer's turn
    int computerTurn = 0;
    //now turn
    int nowPlayer = AHEAD;
    //who is winner
    void getWinner(int win);
    //Borad view class
    BoradView* boradView;
    //Computer class
    Computer* computer;
    
    //gameStart
    void startGame();
    //decide ahead
    void decideAhead();
    
    //put piece (start the game in real)
    void putSection();
    //Put piece by pleyre
    void playerPut();
    //research the place is available
    bool canPut(int x,int y);
    //computer put
    void computerPut();
    //get borad Status
    void getBoradStatus(int* bd);
    //initialisation the data of borad

    //check it is finish or not

    //choose the place of put
    
    //can put or not
private:
    GameManeger(){}
    //winner
    int winner = 0;
    
};
#endif /* defined(__NCGame__GameManeger__) */
