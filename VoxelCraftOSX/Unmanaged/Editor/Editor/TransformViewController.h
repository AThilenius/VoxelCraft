//
//  TransformViewController.h
//  Editor
//
//  Created by Alec Thilenius on 9/6/13.
//  Copyright (c) 2013 Alec Thilenius. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface TransformViewController : NSViewController
{
    IBOutlet NSTextField* PositionXField;
    IBOutlet NSTextField* PositionYField;
    IBOutlet NSTextField* PositionZField;
    
    IBOutlet NSTextField* RotationXField;
    IBOutlet NSTextField* RotationYField;
    IBOutlet NSTextField* RotationZField;
    
    IBOutlet NSTextField* ScaleXField;
    IBOutlet NSTextField* ScaleYField;
    IBOutlet NSTextField* ScaleZField;
}

@end
