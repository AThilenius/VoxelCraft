//
//  Game.h
//  Engine
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __Engine__Game__
#define __Engine__Game__

#import "PCH.h"
#import "VCApplication.h"

class VCGame : VCApplication
{
public:
    VCGame();
    ~VCGame();
    
    virtual void Initalize();
    void Run();
    
};

#endif /* defined(__Engine__Game__) */
