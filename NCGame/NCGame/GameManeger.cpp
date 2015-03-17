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
#include "Computer.h"

void GameManeger::startGame()
{
    boradView = new BoradView();
    computer = new Computer();
    decideAhead();
    boradView->showBorad();
    putSection();
}

//decide who start
void GameManeger::decideAhead()
{
    //the turn player choose
    int chooseTurn = 0;
    std::cout << "push number ber if ahead paly:" << AHEAD << " late play:" << LAST << std::endl;
    while (chooseTurn != AHEAD && chooseTurn != LAST){
        std::cin >> chooseTurn;
    }
    
    //decide player turn and comptuer turn
    playerTurn = chooseTurn;
    //embeded opposit turn of player to computer
    computerTurn = (playerTurn == AHEAD) ? LAST : AHEAD;
}

//put section (put piece)
void GameManeger::putSection()
{
    //it do untill finish
    while(!checkFinish()){
        if(nowPlayer == playerTurn){
            turnCount += 1;
            playerPut();
            nowPlayer = computerTurn;
        }else {
            turnCount += 1;
            computerPut();
            nowPlayer = playerTurn;
        }
        boradView->showBorad();
    }
    
    //if finish
    if(winner == playerTurn){
        std::cout << "Player Win" << std::endl;
    }else if(winner == computerTurn){
        std::cout << "Computer Win" << std::endl;
    }else if(winner == DRAW){
        std::cout << "Draw" << std::endl;
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
    }while(!canPut(putPlace/10-1, putPlace%10-1));
    boradView->putPiece(putPlace/10-1, putPlace%10-1);
}

//give borad status(use difference address)
void GameManeger::getBoradStatus(int* bd)
{
    int* cBoardStatus = boradView->getBoradPointer();
    for(int i=0;i < BORADSIZE;i++){
        for (int j=0; j < BORADSIZE; j++) {
            *(bd+i*BORADSIZE+j) = *(cBoardStatus+i*BORADSIZE+j);
        }
    }
}

bool GameManeger::checkFinish()
{
    if(boradView->checkFinish()){
        return true;
    }else if(turnCount == 9){
        std::cout << "Draw" << std::endl;
        return true;
    }
    return false;
}

//turn of computer
void GameManeger::computerPut()
{
    int xy = computer->comptuerPut();
    boradView->putPiece(xy/10, xy%10);
}

//ask borad class can put or not
bool GameManeger::canPut(int x, int y)
{
    return boradView->canPut(x, y);
}

//decide winner
void GameManeger::getWinner(int win)
{
    winner = win;
}

