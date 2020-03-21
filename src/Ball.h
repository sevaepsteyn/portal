/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"

// ball park X to be window width
#define MIN_Z -ofGetWindowWidth()
#define MAX_Z ofGetWindowWidth()

class Ball {

    public:

        void setup( int, int, int, int, int, int );
        void update();
        void draw();

        int translateX, translateY;
        int sizeX, sizeY;
        int totalX, totalY;

        ofPoint screenCenter;
        ofPoint corners[8];
        float maxDistance;

        int x, y, z;
        float distance;

        ofSoundPlayer sound;
        float volume;
};
