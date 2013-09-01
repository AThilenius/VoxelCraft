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
}

-(IBAction) ButtonClickHanlder: (id) sender
{
    printf("Click!");
    m_application->Step();
}

@end