/*
 *  Created by paul on 09/09/2013.
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>
//

class TXSharedObject  
{
public:
	// virtual used to allow derived classes, esp. TXModuleBase, to overwrite
    virtual void markForDeletion() {
        markedForDeletion = true;
    }

    bool isMarkedForDeletion() {
        return markedForDeletion;
    }
    

protected:
    
	bool markedForDeletion = false;
};

