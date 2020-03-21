/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"

class Clock {

    public:

    void setup();
    void update();
    void draw();

    string text;
    ofTrueTypeFont font;
    int textWidth, textHeight;
};
