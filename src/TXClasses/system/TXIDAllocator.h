/*
 *  Created by paul on 09/09/2013.
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#pragma once

//#import <Foundation/Foundation.h>

#include "ofMain.h"

class TXIDAllocator  
{
public:
    
    const int startID = 1;
    const int maxID = 100000000;
    
	// constructor
	TXIDAllocator () {
        nextID.set("nextID",startID,startID,maxID);
        parameters.add(nextID);
    };
    
	// methods
    
    // increments nextID
    int getNextID() {
        int holdID = nextID;
        nextID++;
        return holdID;
    };
    
    // doesn't increment nextID
    int  getNextIDWithoutChange() {
        return nextID;
    }
    
    void setNextID(int newID) {
        nextID = newID;
    };
    
    void reset() {
        nextID.set("nextID",startID,startID,maxID);
    }
    
    
//    // archive methods
//    NSMutableDictionary * getDictionary() {
//        NSMutableDictionary * dictionary;
//        dictionary = [NSMutableDictionary dictionary];
//        NSNumber * holdNum;
//        //add data
//        holdNum = [NSNumber numberWithInt:nextID];
//        [dictionary setObject: holdNum forKey: @"nextID"];
//        return dictionary;
//    }
//    
//    void setFromDictionary(NSMutableDictionary * dictionaryArg) {
//        NSNumber * holdNum;
//        //get data
//        holdNum = [dictionaryArg objectForKey: @"nextID"];
//        if (holdNum != nil) {
//            nextID = [holdNum intValue];
//        };
//    }
    
	// properties
protected:
    ofParameter<int> nextID;
    ofParameterGroup parameters;
};

