//
//  Box.h
//  EyerPlayer
//
//  Created by lichi on 2021/2/26.
//  Copyright © 2021 Yuqiao Miao. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Box : NSObject
{
    int width;
    int height;
}

-(int) getWidth;

-(int) setW:(int) w setH:(int) h;

@end

NS_ASSUME_NONNULL_END
