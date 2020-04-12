/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"

class Rose {

    public:
    
        void setup( ofPoint _origin, ofPoint _petal, ofColor _color, float _pct, ofPoint _amp, bool _inverse, float _increment);
        void update();
        void draw();

        void interpolateByPct();
        
        ofPoint origin;
        ofPoint petal;
        
        float angle, angleadder;
        float ampA, ampB, ampA_max, ampB_max;
        float radian, x, p, y, theta;
        float radius;
        
        ofColor pink, blue, color;
        
        float pct, increment, ampA_increment, ampB_increment;
        
        bool inverse;
    
};
