/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofApp.h"

void ofApp::setup(){

    ofSetFrameRate( 60 );
    ofSetWindowTitle( "Mars Portal" );
    ofSetVerticalSync( true );
    ofEnableAntiAliasing();
    ofSetLogLevel( OF_LOG_VERBOSE );

/*
#if OF_VERSION_MINOR >= 11
    if ( ofGetScreenWidth() >= 2560 ) {
        ofxGuiEnableHiResDisplay();
    }
#endif
*/

    osc.setup(OSC_PORT);
    
    if( (ofGetEnv("PORTAL").length() != 0) ){


        portal.translateX = ofToInt( ofGetEnv("TRANSLATE_X") );
        portal.translateY = ofToInt( ofGetEnv("TRANSLATE_Y") );

        portal.sizeX = ofToInt( ofGetEnv("SIZE_X") );
        portal.sizeY = ofToInt( ofGetEnv("SIZE_Y") );

        portal.totalX = ofToInt( ofGetEnv("TOTAL_X") );
        portal.totalY = ofToInt( ofGetEnv("TOTAL_Y") );

        portal.shiftX = ofToInt( ofGetEnv("SHIFT_X") );
        portal.borderX = ofToInt( ofGetEnv("BORDER_X") );
        if( portal.shiftX != 0 ) {
            portal.translateX += portal.shiftX + portal.borderX;
        }

        portal.portalId = ofGetEnv("PORTAL_ID");
        portal.mapId = ofGetEnv("MAP_ID");

        ofLog() << "Side" + ofGetEnv("SIDE");
        if ( ofToString(ofGetEnv("SIDE")).compare("NORTH") ) {
            portal.side = 0;
        } else {
            portal.side = 1;
        }

        ofLogNotice() << "My location, x: " << portal.translateX << ", y: " << portal.translateY;


    } else {

        portal.translateX = 0;
        portal.translateY = 0;

        portal.sizeX = ofGetWindowWidth();
        portal.sizeY = ofGetWindowHeight();

        portal.totalX = portal.sizeX;
        portal.totalY = portal.sizeY;

        portal.shiftX = 0;
        portal.borderX = 0;

        portal.portalId = "n/a";
        portal.mapId = "n/a";

        ofLogNotice() << "No portal info received from env";
    }

    ofSetWindowShape( portal.sizeX, portal.sizeY );
    ofSetWindowPosition( portal.shiftX, 0 );

    bgColor = ofColor::black;
    ofSetBackgroundColor(bgColor);
 
    clock.setup();

    ball.setup( portal );

/*
    rose.setup(
        ofPoint(ofGetWidth()/2, ofGetHeight()/2),
        ofPoint(ofRandom(0,9),ofRandom(0,9)),
        ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)),
        ofRandom(0.1,1),
        ofPoint(ofRandom(150,300),ofRandom(150,300)),
        ofRandom(0,1),
        ofRandom(1.0,2.0)
    );
*/

}

void ofApp::update(){
    
    while (osc.hasWaitingMessages()) {
      ofxOscMessage m;
      osc.getNextMessage(m);
        
        if(m.getAddress() == BG_COLOR_ADDRESS) {
            if( m.getNumArgs() == 3) {
                bgColor = ofColor(m.getArgAsInt(0), m.getArgAsInt(1), m.getArgAsInt(2) );
            }
        }
    }

    clock.update();

    ball.update();

    //rose.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
    ofSetColor( bgColor.getInverted() );
        

    ofSetColor( ofColor::pink );
    ofSetCircleResolution( 64 );

    // general info
    ofDrawBitmapString( "translate x, y: " + ofToString(portal.translateX) + ", " + ofToString(portal.translateY), 10, 10 );
    ofDrawBitmapString( "screen width, height: " + ofToString(ofGetWindowWidth()) + ", " + ofToString(ofGetWindowHeight()), 10, 30 );
    ofDrawBitmapString( "total width, total height: " + ofToString(portal.totalX) + ", " + ofToString(portal.totalY), 10, 50 );
    ofDrawBitmapString( "portalId (mapId): " + portal.portalId + " (" + portal.mapId + ")", 10, 70 );
    ofDrawBitmapString( "side: " + ofToString(portal.side), 10, 90 );

    // draw translated to the portal
    ofPushMatrix();
        ofTranslate( -portal.translateX, -portal.translateY );
            ball.draw();
    ofPopMatrix();

    // draw to my screen only
    clock.draw();

    //rose.draw();


}

void ofApp::keyPressed(int key){

    switch ( key ) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        case 'p':
        case 'P':
        case OF_KEY_RETURN:
            ofSaveScreen( "screenshot-" + ofToString( ofGetUnixTime() ) + ".png");
            break;
        case 'q':
        case 'Q':
            ofExit();
            break;
        case '?':
            ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();
            break;
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 
}
