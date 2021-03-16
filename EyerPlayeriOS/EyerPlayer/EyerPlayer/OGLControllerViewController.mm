//
//  OGLControllerViewController.m
//  EyerPlayer
//
//  Created by lichi on 2021/3/16.
//

#import "OGLControllerViewController.h"
#import <OpenGLES/EAGLIOSurface.h>
#import <GLKit/GLKit.h>

#include "Test.hpp"

@interface OGLControllerViewController ()

@end

@implementation OGLControllerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor redColor];
    
    NSLog(@"OGLControllerViewController viewDidLoad\n");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    
    int width = self.view.frame.size.width;
    int height = self.view.frame.size.height;
    
    RedknotTest test;
    
    NSLog(@"width: %d, height: %d\n", width, height);
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    btn.frame = CGRectMake(100, 100, 100, 100);
    btn.backgroundColor = [UIColor blueColor];
    
    [btn setTitle:@"按钮" forState:UIControlStateNormal];
    [btn setTitle:@"按钮按下" forState:UIControlStateHighlighted];
    
    [btn setTitleColor: [UIColor redColor ] forState:UIControlStateNormal];
    [btn setTitleColor: [UIColor grayColor] forState:UIControlStateHighlighted];
    
    [self.view addSubview:btn];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
