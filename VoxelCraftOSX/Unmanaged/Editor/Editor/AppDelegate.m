//
//  AppDelegate.m
//  Editor
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Alec Thilenius. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    m_application = new VCApplication();
    m_application->Initialize();
    
    //[self.window makeKeyWindow];
    [self.window makeMainWindow];
    
    //glfwGetCocoaWindow();
    
//    MyTestViewController* test = [[MyTestViewController alloc] init];
//    [self.window.contentView addSubview:test.view];
//    
//    printf("View 1 frame: %f, %f | %f, %f", test.view.frame.origin.x, test.view.frame.origin.y, test.view.frame.size.width, test.view.frame.size.height);
//    
//    MyTestViewController* test2 = [[MyTestViewController alloc] init];
//    [self.window.contentView addSubview:test2.view];
//    test2.view.frame = NSMakeRect(0, 61, 144, 61);
}

-(IBAction) ButtonClickHanlder: (id) sender
{
    printf("Click!");
    m_application->Step();
}

@end