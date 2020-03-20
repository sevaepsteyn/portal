/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#include "Test.h"

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

        int translateX, translateY;
        int screenX, screenY;
        int totalX, totalY;

        ofPoint screenCenter;
        ofPoint corners[8];
        float maxDistance;

        ofColor bgColor;

        ofxUDPManager udpConnection;
        string message;

        string text;
        ofTrueTypeFont font;
        int textWidth, textHeight;

        int x, y, z;
        float distance;

        ofSoundPlayer sound;
        float volume;

        float pct;
        Test myRectangle;
};
