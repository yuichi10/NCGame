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
    //get instance of GameManeger
    game_maneger = GameManeger::getInstance();
}

//start computer thinking
int Computer::comptuerPut()
{
    computerTurn = game_maneger->computerTurn;
    playerTurn = game_maneger->playerTurn;
    
    //get now status of borad
    game_maneger->getBoradStatus(borad_status[0]);
    //ajust borad value
    ajustBoradValue();
    //started to calculate of now borad value
    calValue();
    //return place to put
    return findPutPlace(put_value[0]);
}

void Computer::ajustBoradValue()
{
    int rRandNum = 0;
    int lRandNum = 0;
    int _rRandNum = 0;
    int _lRandNum = 0;
     
    if(computerTurn == game_maneger->AHEAD && game_maneger->turnCount == 1){
        srand((unsigned)time(NULL));
        //get rundom num to start without middle
          rRandNum = rand() % 5;
          lRandNum = rand() % 5;
        //if both of them over put_value[1][1], that is not good, so now use else if;
        if(borad_value[0][0] + rRandNum > borad_value[1][1]){
            borad_value[0][0] += rRandNum;
            borad_value[2][2] = borad_value[1][1] - 1;
            startFromDiagonal = true;
        }else if(borad_value[0][2] + lRandNum > borad_value[1][1]){
            borad_value[0][2] += lRandNum;
            borad_value[2][0] = borad_value[1][1] - 1;
            startFromDiagonal = true;
        }else{
            //if not start by diagonal, try to change diagonal value
            rRandNum = rand() % 3;
            lRandNum = rand() % 3;
            _rRandNum = rand() % 3;
            _lRandNum = rand() % 3;
            borad_value[0][0] += rRandNum;
            borad_value[0][2] += lRandNum;
            borad_value[2][0] += _lRandNum;
            borad_value[2][2] += _rRandNum;
            startFromDiagonal = false;
        }
    }else if(computerTurn == game_maneger->LAST && game_maneger->turnCount == 2){
        //if not start by diagonal, try to change diagonal value
        rRandNum = rand() % 3;
        lRandNum = rand() % 3;
        _rRandNum = rand() % 3;
        _lRandNum = rand() % 3;
        borad_value[0][0] += rRandNum;
        borad_value[0][2] += lRandNum;
        borad_value[2][0] += _lRandNum;
        borad_value[2][2] += _rRandNum;
        startFromDiagonal = false;
    }
}

//calculate the point (highest point is the place to put)
void Computer::calValue()
{
    //if start from diagonal, in turn 3 computer should have to ajust borad value
    if(startFromDiagonal){
        exceptionOfPiece();
    }
    //add borad value to put value
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(game_maneger->canPut(i,j)){
                put_value[j][i] = borad_value[j][i];
            }else {
                put_value[j][i] = 0;
            }
        }
    }
    
    //find the place which can win and lose
    findTwoLine(computerTurn,borad_status[0],put_value[0]);
    //if next put do not have relationship with win or lose
    if(findMaxValue(put_value[0]) < LOSEVALUE){
        thinkNext(computerTurn, nBorad_status[0], borad_status[0]);
    }
}

void Computer::exceptionOfPiece()
{
    //computer start first and in turn 3 && player do not put middle, need ajust borad value
    if(game_maneger->turnCount == 3 && borad_status[1][1] == game_maneger->SPACE){
        if(borad_value[0][0] > borad_value[1][1]){
            if(borad_status[2][2] == playerTurn){
                borad_value[0][2] = borad_value[1][1] + 2;
            }else if(borad_status[0][2] == playerTurn){
                borad_value[2][0] = borad_value[1][1] + 1;
            }else if(borad_status[2][0] == playerTurn){
                borad_value[0][2] = borad_value[1][1] + 1;
            }
        }else if(borad_value[0][2] > borad_value[1][1]){
            if(borad_status[2][0] == playerTurn){
                borad_value[0][0] = borad_value[1][1] + 2;
            }else if(borad_status[0][0] == playerTurn){
                borad_value[2][2] = borad_value[1][1] + 1;
            }else if(borad_status[2][2] == playerTurn){
                borad_value[0][0] = borad_value[1][1] + 1;
            }
        }
    }

}


//find the most biggest value and return xy (2,3)->23 
int Computer::findPutPlace(int* putValue)
{
    int max = -99;
    int x = 0;
    int y = 0;
    //put piece which have most biggest value in put_value
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(max < *(putValue+game_maneger->BORADSIZE*j+i) && game_maneger->canPut(i, j)){
                max = *(putValue+game_maneger->BORADSIZE*j+i);
                x = i;
                y = j;
            }
        }
    }
    return (x*10+y);
}

//return most biggest value
int Computer::findMaxValue(int* putValue)
{
    int max = -99;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(max < *(putValue+game_maneger->BORADSIZE*i+j) && game_maneger->canPut(j, i)){
                max = *(putValue+game_maneger->BORADSIZE*i+j);
            }
        }
    }
    return max;
}

//try to find two line of computer and player. if find put extra value to put_value
void Computer::findTwoLine(int turn, int* boradStatus, int* putValue)
{
    /*
     three_line
     0:width 1      3:height 1    6:cross right
     1:width 2      4:height 2    7:cross left
     2:width 3      5:height 6
    */
    int oTurn = (turn == computerTurn) ? playerTurn : computerTurn;
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
            if(*(boradStatus+game_maneger->BORADSIZE*i+j) != game_maneger->SPACE){
                count_w += 1;
                three_line_place[i][1] += *(boradStatus+game_maneger->BORADSIZE*i+j);
            }else if(*(boradStatus+game_maneger->BORADSIZE*i+j) == game_maneger->SPACE){
                space_w = j*10+i;
            }
            if(*(boradStatus+game_maneger->BORADSIZE*j+i) != game_maneger->SPACE){
                count_h += 1;
                three_line_place[i+3][1] += *(boradStatus+game_maneger->BORADSIZE*j+i);
            }else if(*(boradStatus+game_maneger->BORADSIZE*j+i) == game_maneger->SPACE){
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
        if(three_line_place[i][0] != 0 && three_line_place[i][1] == turn*2){
            int x = three_line_place[i][0] / 10;
            int y = three_line_place[i][0] % 10;
            *(putValue+game_maneger->BORADSIZE*y+x) += WINVALUE;
        }else if(three_line_place[i][0] != 0 && three_line_place[i][1] == oTurn*2){
            int x = three_line_place[i][0] / 10;
            int y = three_line_place[i][0] % 10;
            *(putValue+game_maneger->BORADSIZE*y+x) += LOSEVALUE;
        }
    }
    
    
    int* bs00 = (boradStatus);
    int* bs11 = (boradStatus+game_maneger->BORADSIZE*1+1);
    int* bs22 = (boradStatus+game_maneger->BORADSIZE*2+2);
    int* bs02 = (boradStatus+game_maneger->BORADSIZE*0+2);
    int* bs20 = (boradStatus+game_maneger->BORADSIZE*2+0);
    //cross line
    three_line[6] = (*bs00)*(*bs11)*(*bs22);
    three_line[7] = (*bs02)*(*bs11)*(*bs20);
    //right cross
    if(*bs00 == *bs11 && *bs22 == game_maneger->SPACE){
        if(*bs00 == turn){
            *(putValue+game_maneger->BORADSIZE*2+2) += WINVALUE;
        }else if(*bs00 == playerTurn){
            *(putValue+game_maneger->BORADSIZE*2+2) += LOSEVALUE;
        }
    }else if(*bs22 == *bs11 && *bs00 == game_maneger->SPACE){
        if(*bs11 == turn){
            *(putValue) += WINVALUE;
        }else if(*bs11 == oTurn){
            *(putValue) += LOSEVALUE;
        }
    }else if(*bs00 == *bs22 && *bs11 == game_maneger->SPACE){
        if(*bs00 == turn){
            *(putValue+game_maneger->BORADSIZE*1+1) += WINVALUE;
        }else if(*bs00 == oTurn){
            *(putValue+game_maneger->BORADSIZE*1+1) += LOSEVALUE;
        }
    }
    
    //left cross
    if(*bs02 == *bs11 && *bs20 == game_maneger->SPACE){
        if(*bs02 == turn){
            *(putValue+game_maneger->BORADSIZE*2+0) += WINVALUE;
        }else if(*bs02 == oTurn){
            *(putValue+game_maneger->BORADSIZE*2+0) += LOSEVALUE;
        }
    }else if(*bs20 == *bs11 && *bs02 == game_maneger->SPACE){
        if(borad_status[1][1] == turn){
            *(putValue+game_maneger->BORADSIZE*0+2) += WINVALUE;
        }else if(*bs11 == oTurn){
            *(putValue+game_maneger->BORADSIZE*0+2) += LOSEVALUE;
        }
    }else if(*bs20 == *bs02 && *bs11 == game_maneger->SPACE){
        if(*bs20 == turn){
            *(putValue+game_maneger->BORADSIZE*1+1) += WINVALUE;
        }else if(*bs20 == oTurn){
            *(putValue+game_maneger->BORADSIZE*1+1) += LOSEVALUE;
        }
    }
}

//computer think next borad status
void Computer::thinkNext(int turn, int* nBorad, int* fBorad)
{
    //try to find the place which can make double two line
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
    //if max value < WINDOUBLE consider next player's put place
    if(findMaxValue(put_value[0]) < WINDOUBLE){
        //get opposit turn
        int oTurn = (turn == computerTurn) ? playerTurn : computerTurn;
        for(int i=0;i<3;i++){
            for(int j=0;j < 3;j++){
                //put the piece to next borad
                if(put_value[i][j] > 0){
                    copyBoradStatus(nBorad, fBorad);
                    *(nBorad+i*game_maneger->BORADSIZE+j) = turn;
                    thinkNext2(oTurn, nnBorad_status[0], nBorad, j, i);
                }
            }
        }
    }
}

bool Computer::thinkNext2(int turn, int *nBorad, int *fBorad, int x, int y)
{
    int pPut_value[3][3] = {0};
    for(int i = 0;i < game_maneger->BORADSIZE; i++){
        for(int j = 0;j < game_maneger->BORADSIZE; j++){
            if(put_value[i][j] > 0){
                pPut_value[i][j] = 1;
            }
        }
    }
    findTwoLine(turn, fBorad, pPut_value[0]);
    if(findMaxValue(pPut_value[0]) < 50){
        for(int k=0; k < game_maneger->BORADSIZE;k++){
            for(int l=0; l < game_maneger->BORADSIZE;l++){
                copyBoradStatus(nBorad, fBorad);
                //put the piece to next's next borad
                if(put_value[k][l] > 0 && (k != y && l != x)){
                    nnBorad_status[k][l] = turn;
                    //if player can make the double two line the piece value be 1
                    if(findDoubleTwoline(turn, nBorad)){
                        if(turn == playerTurn){
                            put_value[y][x] = LOSEDOUBLE;
                            return true;
                        }
                    }
                }
            }
        }
    }else {
        int txy = findPutPlace(pPut_value[0]);
        int tx = txy / 10;
        int ty = txy % 10;
        copyBoradStatus(nBorad, fBorad);
        *(nBorad+game_maneger->BORADSIZE*ty+tx) = turn;
        if(findDoubleTwoline(turn, nBorad)){
            if(turn == playerTurn){
                put_value[y][x] = LOSEDOUBLE;
                return true;
            }

        }
    }
    return false;
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
    
    //right diagonal
    if((*(borad))*(*(borad+1*game_maneger->BORADSIZE+1))*(*(borad+2*game_maneger->BORADSIZE+2)) == game_maneger->SPACE){
        if(*(borad) == *(borad+1*game_maneger->BORADSIZE+1) && *(borad) == turn){
            two_line_count += 1;
        }else if(*(borad+1*game_maneger->BORADSIZE+1) == *(borad+2*game_maneger->BORADSIZE+2) &&*(borad+1*game_maneger->BORADSIZE+1) == turn){
            two_line_count += 1;
        }else if(*(borad+2*game_maneger->BORADSIZE+2) == *(borad) && *(borad+2*game_maneger->BORADSIZE+2) == turn){
            two_line_count += 1;
        }
    }
    
    //left diagonal
    if((*(borad+2))*(*(borad+1*game_maneger->BORADSIZE+1))*(*(borad+game_maneger->BORADSIZE*2)) == game_maneger->SPACE){
        if(*(borad+2) == *(borad+1*game_maneger->BORADSIZE+1) && *(borad+2) == turn){
            two_line_count += 1;
        }else if(*(borad+1*game_maneger->BORADSIZE+1) == *(borad+game_maneger->BORADSIZE*2) && *(borad+1*game_maneger->BORADSIZE+1) == turn){
            two_line_count += 1;
        }else if(*(borad+game_maneger->BORADSIZE*2) == *(borad+2) && *(borad+game_maneger->BORADSIZE*2) == turn){
            two_line_count += 1;
        }
    }

    
    //count width and height of two line
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
        //if thre is double two line
        if(two_line_count >= 2){
            return true;
        }
    }
    //if there is no double two line
    return false;
}
