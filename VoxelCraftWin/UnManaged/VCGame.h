//
//  Game.h
//  Engine
//
//  Created by Alec Thilenius on 9/1/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#ifndef __Engine__Game__
#define __Engine__Game__

#include "PCH.h"
#include "VCApplication.h"

class VCGame : public VCApplication
{
public:
    VCGame();
    ~VCGame();
    
    virtual void Initalize();
    void Run();
    
private:
    double m_lastDeltaTime;
    
};

#endif /* defined(__Engine__Game__) */
