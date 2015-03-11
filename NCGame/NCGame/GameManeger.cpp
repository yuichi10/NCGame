//
//  GameManeger.cpp
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#include <iostream>
#include "GameManeger.h"
#include "BoradView.h"

void GameManeger::startGame()
{
    boradView = new BoradView();
    boradView->initBoradStatus();
    decideAhead();
    boradView->showBorad();
    putSection();
}

//decide who start
void GameManeger::decideAhead()
{
    int chooseTurn = 0;
    std::cout << "push number ber if ahead paly:" << AHEAD << " late play:" << LAST << std::endl;
    while (chooseTurn != AHEAD && chooseTurn != LAST){
        std::cin >> chooseTurn;
    }
    
    //decide player turn and comptuer turn
    playerTurn = chooseTurn;
    computerTurn = (playerTurn == AHEAD) ? LAST : AHEAD;
}

//put section (put piece)
void GameManeger::putSection()
{
    //it do untill finish
    while(!boradView->checkFinish()){
        if(nowPlayer == playerTurn){
            playerPut();
            nowPlayer = computerTurn;
        }else {
            playerPut();
            nowPlayer = playerTurn;
        }
        boradView->showBorad();
    }
}

//put piece by player
void GameManeger::playerPut()
{
    int putPlace = 0;
    do{
        //get the number (if put 12 -> x:1 y:2, 32 -> x:3 y:2)
        std::cout << "if put 12 -> x:1 y:2, 32 -> x:3 y:2\n";
        std::cout << "Your turn Please input(xy): ";
        std::cin >> putPlace;
    }while(!boradView->canPut(putPlace/10, putPlace%10));
    boradView->putPiece(putPlace/10, putPlace%10);
}

