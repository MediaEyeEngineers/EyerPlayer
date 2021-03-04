//
//  Box.m
//  EyerPlayer
//
//  Created by lichi on 2021/2/26.
//  Copyright © 2021 Yuqiao Miao. All rights reserved.
//

#import "Box.h"

@implementation Box

-(id)init {
    self = [super init];
    width = 200;
    height = 300;
    return self;
}

-(int) getWidth
{
    return width;
}

-(int) setW:(int) w setH:(int) h
{
    width = w;
    height = h;
    return 0;
}

@end
