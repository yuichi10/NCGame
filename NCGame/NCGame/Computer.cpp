//
//  Computer.cpp
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#include <iostream>
#include "Computer.h"
#include "GameManeger.h"

Computer::Computer()
{
    game_maneger = GameManeger::getInstance();
    computerTurn = game_maneger->computerTurn;
}

int Computer::comptuerPut()
{
    //computer's thikning value of the place
    int put_value[3][3] = {0};
    game_maneger->getBoradStatus(borad_status[0]);
    calValue(put_value[0]);
    return findPutPlace(put_value[0]);
}

void Computer::calValue(int* putV)
{
    //add borad value
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(game_maneger->canPut(i,j)){
                *(putV+j*3+i) = borad_value[j][i];
            }
        }
    }
    //find the place which can win
    findTwoLine();
}


//find the most biggest value and return xy (2,3)->23 
int Computer::findPutPlace(int* putV)
{
    int max = -1;
    int x = 0;
    int y = 0;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(max < *(putV+j*3+i) && game_maneger->canPut(i, j)){
                max = *(putV+j*3+i);
                x = i;
                y = j;
            }
        }
    }
    return (x*10+y);
}

void Computer::findTwoLine()
{
    const int win_value  = 30;
    const int lose_value = 20;
    /*
     three_line
     0:width 1      3:height 1    6:cross right
     1:width 2      4:height 2    7:cross left
     2:width 3      5:height 6
     
     
     */
    int three_line[8] = {0};
    int three_line_place[8][2] = {0};
    //width and height
    for (int i = 0; i < 3; i++) {
        int count_w = 0;
        int space_w = 0;
        int count_h = 0;
        int space_h = 0;
        for (int j = 0;j < 3; j++) {
            if(borad_status[i][j] != game_maneger->SPACE){
                count_w += 1;
                three_line_place[i][1] += borad_status[i][j];
            }else {
                space_w = j*10+i;
            }
            if(borad_status[j][i] != game_maneger->SPACE){
                count_h += 1;
                three_line_place[i+3][1] += borad_status[j][i];
            }else {
                space_h = i*10+j;
            }
        }
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
    for(int i = 0;i < 6;i++){
        std::cout << three_line_place[i][0] << std::endl;
    }
    
    //cross line
    three_line[6] = borad_status[0][0]*borad_status[1][1]*borad_status[2][2];
    three_line[7] = borad_status[0][2]*borad_status[1][1]*borad_status[2][0];
    
}