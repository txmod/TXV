/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModSource.h"

// properties

// constructor
TXModSource::TXModSource (string nameArg, float valueArg){
    setup (nameArg, valueArg);
};

// methods
void TXModSource::setup (string nameArg, float valueArg) {
    name = nameArg;
	value = valueArg;
};

string TXModSource::getName() {
    return name;
}

void TXModSource::setName(string nameArg){
    name = nameArg;
};

float TXModSource::getValue() {
    return value;
}

void TXModSource::setValue (float valueArg) {
    value = ofClamp(valueArg, 0.0, 1.0);
};


