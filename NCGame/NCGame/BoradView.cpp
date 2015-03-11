//
//  ;
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//


#include <iostream>
#include <string>
#include "BoradView.h"
#include "GameManeger.h"

BoradView::BoradView()
{
    game_maneger = GameManeger::getInstance();
}

//initialisation of BoradStatus
void BoradView::initBoradStatus()
{
    int i,j = 0;
    for(i=0;i<BORADSIZE;i++){
        for(j=0;j<BORADSIZE;j++){
            if(i == 0 || i == 4 || j == 0 || j == 4){
                BoradStatus[i][j] = WALL;
            }else{
                BoradStatus[i][j] = SPACE;
            }
        }
    }
}

//show the borad
void BoradView::showBorad()
{
    int i,j = 0;
    std::cout << "     1   2   3  " << "\n";
    for(i = 1;i < BORADSIZE-1;i++){
        std::cout << "   -------------" << "\n";
        for(j = 1; j< BORADSIZE-1; j++){
            if(j == 1){
                std::cout << " " << i << " ";
            }
            if(BoradStatus[i][j] == SPACE){
                std::cout << "|   ";
            }else if(BoradStatus[i][j] == game_maneger->AHEAD){
                std::cout << "| " << AHEAD_VIEW << " ";
            }else if(BoradStatus[i][j] == game_maneger->LAST){
                std::cout << "| " << LAST_VIEW << " ";
            }
            /*it happen err, i do not why
            switch (BoradStatus[i][j]) {
                case SPACE:
                    std::cout << "|   ";
                    break;
                case game_maneger->AHEAD:
                    std::cout << "| " << AHEAD_VIEW << " ";
                    break;
                case game_maneger->LAST:
                    std::cout << "| " << LAST_VIEW << " ";
                    break;
                default:
                    break;
            }
             */
        }
        std::cout << "|\n";
        if(i == BORADSIZE-2){
            std::cout << "   -------------\n";
        }
    }
}

bool BoradView::canPut(int x, int y)
{
    if(x <= 3 && x >=1 && y <= 3 && y >= 1){
        if(BoradStatus[y][x] == SPACE){
            return true;
        }
    }
    return false;
}

bool BoradView::checkFinish()
{
    return false;
}

void BoradView::putPiece(int x, int y){
    BoradStatus[y][x] = game_maneger->nowPlayer;
}


//