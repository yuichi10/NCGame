//
//  main.cpp
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#include <iostream>
#include "GameManeger.h"
int main(int argc, const char * argv[]) {
    GameManeger* game_maneger = GameManeger::getInstance();
    game_maneger->startGame();
}
