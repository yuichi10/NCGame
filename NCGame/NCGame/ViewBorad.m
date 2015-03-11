//
//  ViewBorad.m
//  NCGame
//
//  Created by YuichiSawada on 11/03/2015.
//  Copyright (c) 2015 YuichiSawada. All rights reserved.
//

#import "ViewBorad.h"

@implementation ViewBorad
{
    int BoradBig;
    int BoradStatus[4][4];
}

-(void) setValue
{
    BoradBig = 4;
}

-(void) initBoradStatus
{
    int i,j;
    for(i=0;i < BoradBig;i++){
        for(j=0;j < BoradBig;j++){
            BoradStatus[i][j] = 0;
        }
    }
}

-(void)viewBorad
{
    
}


@end
