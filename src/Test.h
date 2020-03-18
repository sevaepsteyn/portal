/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"

class Test {

    public:

    void setup();
    void update();
    void draw();
    void interpolateByPct(float myPct);

    ofPoint pos;
    ofPoint posa;
    ofPoint	posb;
    float pct;	// what pct are we between "a" and "b"
};
