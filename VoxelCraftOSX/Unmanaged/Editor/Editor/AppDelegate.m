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
    VCApplication* application = new VCApplication();
    application->Initialize();
    application->Run();
    
    //double time = VCTime::CurrentTime();
}

@end