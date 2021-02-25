//
//  ViewController.m
//  EyerPlayer
//
//  Created by Yuqiao Miao on 2020/8/31.
//  Copyright © 2020 Yuqiao Miao. All rights reserved.
//

#import "ViewController.h"
#import "MyOpenGLView.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    MyOpenGLView * openGLView = [[MyOpenGLView alloc] init];
    openGLView.name = @"喵呜";
    NSLog(@"name: %@\n", openGLView.name);
}

@end
