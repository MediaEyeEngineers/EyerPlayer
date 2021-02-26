//
//  ViewController.m
//  EyerPlayer
//
//  Created by Yuqiao Miao on 2020/8/31.
//  Copyright © 2020 Yuqiao Miao. All rights reserved.
//

#import "ViewController.h"
#import "MyOpenGLView.h"
#import "Box.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    CGRect frame = CGRectMake(300, 300, 300, 50);
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    button.frame = frame;
    [button setTitle:@"新添加的动态按钮" forState: UIControlStateNormal];
    button.backgroundColor = [UIColor clearColor];
    button.tag = 2000;
    // [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
    /*
    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    GLKView * glkView = (GLKView *)self.view;
    glkView.context = context;
    
    glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    */
}

@end
