/* vim: set tabstop=4 shiftwidth=4 expandtab: */

#include "Rose.h"

void Rose::setup(ofPoint _origin, ofPoint _petal, ofColor _color, float _pct, ofPoint _amp, bool _inverse, float _increment){

    // center of rose
    origin.set(_origin);
    petal.set(_petal);
    
    ampA = _amp.x;
    ampB = _amp.y;
    ampA_max = _amp.x;
    ampB_max = _amp.y;
    radius = 1;
    
    angle = radian = x = y = 0.0f;
    angleadder = .1;
    
    inverse = _inverse;
    
    // colors
    color.set(_color);
    pink.set(255,0,255, 30);
    blue.set(0,255,255, 30);
    pct = _pct;
    pct = pct / 255;
    increment = .01f;
    ampA_increment = ampB_increment = _increment;
    
    // size of the rose : ampA and ampB
    // if a<b => 2 sets of petals, petals meet at origin, smaller set of length b-a, larger set of length b+a
    // if a>b => 2 sets of petals, petals do not meet origin, smaller set of length a-b, larger set of length a+b
    // if a=b length of petals is 2a

    
    // Max theta to view whole graph
    if (petal.x/petal.y != 1) {
        theta = 2 * petal.y * 180;
    } else{
        theta = 360;
    }
}

void Rose::update(){
    if( inverse ){
        if (angle<=360) {
            angle += angleadder;
        } else {
            angle = 0;
        }
    } else{
        if (angle>=0) {
            angle -= angleadder;
        } else {
            angle = 360;
        }
    }
    
   // radius += increment;
    
    pct += increment;
    if (pct > 1) {
        pct = 1;
        increment *= -1;
    }
    if (pct < 0) {
        pct = 0;
        increment *= -1;
    }
    
    ampA += ampA_increment;
    if (ampA > ampA_max){
        ampA = ampA_max;
        ampA_increment *= -1;
    }
    if (ampA < 0){
        ampA = 0;
        ampA_increment *= -1;
    }
    
//    ampB += ampB_increment;
//    if(ampB > ampB_max){
//        ampB = ampB_max;
//        ampB_increment *= -1;
//    }
//    if(ampB < 0){
//        ampB = 0;
//        ampB_increment *= -1;
//    }
    
    interpolateByPct();
    
   //cout << ampA << ", " << ampB << endl;
}

void Rose::draw(){
    
    ofSetColor(color);

    for (int i=0; i<theta; i+=5) {
        radian = PI/180 * ((angle + i)); // convert degrees to radians
        p = ampA + ampB * cos(petal.x / petal.y * radian); // calculate polar coordinates
        x = origin.x + p * cos(radian); // convert to Cartesian 'x'
        y = origin.y + p * sin(radian); // convert to Cartesian 'y'
        
        // set radius based on position along the x axis
        // to do - set by polar coordinates
        
        radius = ofMap(p, 0, ofGetWidth()/2, 2, 7);
//        float temp_x;
//        temp_x = x;
//        if( temp_x > ofGetWidth()/2 ){
//            radius = ofMap(temp_x, ofGetWidth()/2, ofGetWidth(), 0, 10);
//        }
//        if( temp_x < ofGetWidth()/2 ){
//            radius = ofMap(temp_x, 0, ofGetWidth()/2, 10, 0);
//        }
        
        // current x in relation to its maximum and minimum
        ofDrawCircle(x, y, radius); // draw
    }
}

void Rose::interpolateByPct(){
    color.r = (1-pct) * pink.r + pct * blue.r;
    color.g = (1-pct) * pink.g + pct * blue.g;
    
}
