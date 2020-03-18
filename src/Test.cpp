/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "Test.h"

void Test::setup(){
}

void Test::update(){
}

void Test::draw(){
    ofSetColor(ofColor::red);
    ofDrawCircle(pos, 100);
}

void Test::interpolateByPct(float myPct){
    pos.x = (1-pct) * posa.x + (pct) * posb.x;
    pos.y = (1-pct) * posa.y + (pct) * posb.y;
}
