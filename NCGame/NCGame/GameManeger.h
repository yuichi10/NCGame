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
    //Player's turn
    int playerTurn = 0;
    //computer's turn
    int computerTurn = 0;
    //now turn
    int nowPlayer = AHEAD;
    //Borad view class
    BoradView* boradView;
    
    //gameStart
    void startGame();
    //decide ahead
    void decideAhead();
    
    //put piece (start the game in real)
    void putSection();
    //Put piece by pleyre
    void playerPut();
    

    //initialisation the data of borad

    //check it is finish or not

    //choose the place of put
    
    //can put or not
private:
    GameManeger(){}
    
};
#endif /* defined(__NCGame__GameManeger__) */
