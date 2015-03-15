//
//  Computer.cpp
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "Computer.h"
#include "GameManeger.h"

Computer::Computer()
{
    game_maneger = GameManeger::getInstance();
}

//start computer thinking
int Computer::comptuerPut()
{
    computerTurn = game_maneger->computerTurn;
    playerTurn = game_maneger->playerTurn;

    game_maneger->getBoradStatus(borad_status[0]);
    calValue();
    return findPutPlace();
}

//calculate the point (highest point is the place to put)
void Computer::calValue()
{
    //add borad value
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(game_maneger->canPut(i,j)){
                put_value[j][i] = borad_value[j][i];
            }else {
                put_value[j][i] = 0;
            }
        }
    }
    
    if(computerTurn == game_maneger->AHEAD){
        putFirstBoradValue();
        //if both of them over put_value[1][1], that is not good, so now use else if;
        if(rRandNum+put_value[0][0] > put_value[1][1]){
            if(game_maneger->canPut(0, 0)){
                put_value[0][0] += rRandNum;
            }
            if(game_maneger->canPut(2, 2)){
                put_value[2][2] = 4;
            }
        }else if(lRandNum+put_value[0][2] > put_value[1][1]){
            if(game_maneger->canPut(2, 0)){
                put_value[0][2] += lRandNum;
            }
            if(game_maneger->canPut(0, 2)){
                put_value[2][0] = 4;
            }
        }
    }
    //find the place which can win
    findTwoLine();
    //if next put do not have relationship with win or lose
    if(findMaxValue() < LOSEVALUE){
        thinkNext(computerTurn, nBorad_status[0], borad_status[0]);
    }
}

void Computer::putFirstBoradValue()
{
    if(game_maneger->turnCount == 1){
        srand((unsigned)time(NULL));
        rRandNum = rand() % 4;
        lRandNum = rand() % 4;
    }
}


//find the most biggest value and return xy (2,3)->23 
int Computer::findPutPlace()
{
    int max = -99;
    int x = 0;
    int y = 0;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
           /* if(max < *(putV+j*3+i) && game_maneger->canPut(i, j)){
                max = *(putV+j*3+i);
                x = i;
                y = j;
            }*/
            if(max < put_value[j][i] && game_maneger->canPut(i, j)){
                max = put_value[j][i];
                x = i;
                y = j;
            }
        }
    }
    return (x*10+y);
}

int Computer::findMaxValue()
{
    int max = -99;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(max < put_value[i][j] && game_maneger->canPut(j, i)){
                max = put_value[i][j];
            }
        }
    }
    return max;
}

void Computer::findTwoLine()
{
    /*
     three_line
     0:width 1      3:height 1    6:cross right
     1:width 2      4:height 2    7:cross left
     2:width 3      5:height 6
    */
    int three_line[8] = {0};
    //threeline[][0]->put the place to put  threeline[][1]->the amount of borad status
    //if count==2 && [][1] == 2 -> there is 1 double count==2 && [][1]==4 there are 2 double
    int three_line_place[8][2] = {0};
    //width and height
    for (int i = 0; i < game_maneger->BORADSIZE; i++) {
        int count_w = 0;
        int space_w = 0;
        int count_h = 0;
        int space_h = 0;
        //add value of borad status
        for (int j = 0;j < game_maneger->BORADSIZE; j++) {
            if(borad_status[i][j] != game_maneger->SPACE){
                count_w += 1;
                three_line_place[i][1] += borad_status[i][j];
            }else if(borad_status[i][j] == game_maneger->SPACE){
                space_w = j*10+i;
            }
            if(borad_status[j][i] != game_maneger->SPACE){
                count_h += 1;
                three_line_place[i+3][1] += borad_status[j][i];
            }else if(borad_status[j][i] == game_maneger->SPACE){
                space_h = i*10+j;
            }
        }
        // if the line have more than 2 piece
        if(count_w > 1){
            three_line_place[i][0] = space_w;
        }else {
            three_line_place[i][0] = 0;
        }
        if(count_h > 1){
            three_line_place[i+3][0] = space_h;
        }else {
            three_line_place[i+3][0] = 0;
        }
    }
    //if the line have more than 2 piece and if the 2 piece are same
    for(int i = 0;i < 6;i++){
        if(three_line_place[i][0] != 0 && three_line_place[i][1] == computerTurn*2){
            int x = three_line_place[i][0] / 10;
            int y = three_line_place[i][0] % 10;
            put_value[y][x] += WINVALUE;
        }else if(three_line_place[i][0] != 0 && three_line_place[i][1] == playerTurn*2){
            int x = three_line_place[i][0] / 10;
            int y = three_line_place[i][0] % 10;
            put_value[y][x] += LOSEVALUE;
        }
    }
    
    //cross line
    three_line[6] = borad_status[0][0]*borad_status[1][1]*borad_status[2][2];
    three_line[7] = borad_status[0][2]*borad_status[1][1]*borad_status[2][0];
    //right cross
    if(borad_status[0][0] == borad_status[1][1]){
        if(borad_status[0][0] == computerTurn){
            put_value[2][2] += WINVALUE;
        }else if(borad_status[0][0] == playerTurn){
            put_value[2][2] += LOSEVALUE;
        }
    }else if(borad_status[2][2] == borad_status[1][1]){
        if(borad_status[1][1] == computerTurn){
            put_value[0][0] += WINVALUE;
        }else if(borad_status[1][1] == playerTurn){
            put_value[0][0] += LOSEVALUE;
        }
    }else if(borad_status[0][0] == borad_status[2][2]){
        if(borad_status[0][0] == computerTurn){
            put_value[1][1] += WINVALUE;
        }else if(borad_status[0][0] == playerTurn){
            put_value[1][1] += LOSEVALUE;
        }
    }
    
    //left cross
    if(borad_status[0][2] == borad_status[1][1]){
        if(borad_status[0][2] == computerTurn){
            put_value[2][0] += WINVALUE;
        }else if(borad_status[0][2] == playerTurn){
            put_value[2][0] += LOSEVALUE;
        }
    }else if(borad_status[2][0] == borad_status[1][1]){
        if(borad_status[1][1] == computerTurn){
            put_value[0][2] += WINVALUE;
        }else if(borad_status[1][1] == playerTurn){
            put_value[0][2] += LOSEVALUE;
        }
    }else if(borad_status[2][0] == borad_status[0][2]){
        if(borad_status[2][0] == computerTurn){
            put_value[1][1] += WINVALUE;
        }else if(borad_status[2][0] == playerTurn){
            put_value[1][1] += LOSEVALUE;
        }
    }
}

//computer think next borad status
void Computer::thinkNext(int turn, int* nBorad, int* fBorad)
{
    for(int i=0;i<3;i++){
        for(int j=0;j < 3;j++){
            copyBoradStatus(nBorad, fBorad);
            if(put_value[i][j] > 0){
                *(nBorad+i*game_maneger->BORADSIZE+j) = turn;
                if(findDoubleTwoline(turn, nBorad)){
                    put_value[i][j] += WINDOUBLE;
                }
            }
        }
    }
    //if max value < WINDOUBLE
    if(findMaxValue() < WINDOUBLE){
        int oTurn = (turn == computerTurn) ? playerTurn : computerTurn;
        for(int i=0;i<3;i++){
            for(int j=0;j < 3;j++){
                //put the piece to next borad
                if(put_value[i][j] > 0){
                    copyBoradStatus(nBorad, fBorad);
                    *(nBorad+i*game_maneger->BORADSIZE+j) = turn;
                    for(int k=0; k < game_maneger->BORADSIZE;k++){
                        for(int l=0; l < game_maneger->BORADSIZE;l++){
                            copyBoradStatus(nnBorad_status[0], nBorad);
                            //put the piece to next's next borad
                            if(put_value[k][l] > 0 && (k != i && l != j)){
                                nnBorad_status[k][l] = oTurn;
                                //if player can make the double two line the piece value be 1
                                if(findDoubleTwoline(oTurn, nnBorad_status[0])){
                                    if(oTurn == playerTurn){
                                        put_value[i][j] = LOSEDOUBLE;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


//copy one borad status to another one
void Computer::copyBoradStatus(int* nBorad, int* fBorad){
    for(int i=0;i < game_maneger->BORADSIZE;i++){
        for(int j=0;j < game_maneger->BORADSIZE;j++){
            *(nBorad+i*game_maneger->BORADSIZE+j) = *(fBorad+i*game_maneger->BORADSIZE+j);
        }
    }
}

//try to find double two line
bool Computer::findDoubleTwoline(int turn,int* borad)
{
    int two_line_count = 0;
    for(int i=0; i < game_maneger->BORADSIZE; i++){
        int count_turns_pieceH = 0;
        int count_turns_pieceW = 0;
        int count_zero_pieceH = 0;
        int count_zero_pieceW = 0;
        for(int j=0;j < game_maneger->BORADSIZE;j++){
            if(*(borad+i*game_maneger->BORADSIZE+j) == turn){
                count_turns_pieceW += 1;
            }else if(*(borad+i*game_maneger->BORADSIZE+j) == game_maneger->SPACE){
                count_zero_pieceW += 1;
            }
            
            if(*(borad+j*game_maneger->BORADSIZE+i) == turn){
                count_turns_pieceH += 1;
            }else if(*(borad+j*game_maneger->BORADSIZE+i) == game_maneger->SPACE){
                count_zero_pieceH = 1;
            }
        }
        if(count_turns_pieceH == 2 && count_zero_pieceH == 1){
            two_line_count += 1;
        }
        if(count_turns_pieceW == 2 && count_zero_pieceW == 1){
            two_line_count += 1;
        }
        if(two_line_count >= 2){
            return true;
        }
    }
    return false;
}
