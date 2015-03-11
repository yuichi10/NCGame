//
//  BoradView.h
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#ifndef __NCGame__BoradView__
#define __NCGame__BoradView__

#include <stdio.h>
#include <string>
class GameManeger;

class BoradView
{
    
public:
    BoradView();
    ~BoradView();
    //Borad size
    static const int BORADSIZE = 5;
    //Borad around
    static const int WALL = 99;
    //Nothing there
    static const int SPACE = 0;
    //game maneger
    GameManeger* game_maneger;
    //the status of Borad
    int BoradStatus[BORADSIZE][BORADSIZE];
    
    //AHEAD player's symbol
    std::string AHEAD_VIEW = "●";
    //LAST player's symbol
    std::string LAST_VIEW = "☓";
    
    //initialisation of borad status
    void initBoradStatus();
    //write the borad
    void showBorad();
   
    
    //can put the piece
    bool canPut(int x, int y);
    //put piece
    void putPiece(int x, int y);
    //checkFinish
    bool checkFinish();
    
};

#endif /* defined(__NCGame__BoradView__) */
