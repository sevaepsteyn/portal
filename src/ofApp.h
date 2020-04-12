/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define OSC_PORT 7777
#define BG_COLOR_ADDRESS "/color"

#include "PortalSettings.h"
#include "Ball.h"
#include "Clock.h"
#include "Rose.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        PortalSettings portal;

/*
        int translateX, translateY;
        int sizeX, sizeY;
        int totalX, totalY;
        int borderX, shiftX;
        string portalId, mapId;
*/

        ofColor bgColor;

        ofxOscReceiver osc;

        Clock clock;

        Ball ball;

        Rose rose;

};
