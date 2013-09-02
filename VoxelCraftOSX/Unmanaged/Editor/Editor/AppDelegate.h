//
//  AppDelegate.h
//  Editor
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Alec Thilenius. All rights reserved.
//



#import <Cocoa/Cocoa.h>
#import "VCApplication.h"

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#import <glfw.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    VCApplication* m_application;
    
    IBOutlet NSButton* myButton;
}

@property (assign) IBOutlet NSWindow *window;

-(IBAction) ButtonClickHanlder: (id) sender;

@end
