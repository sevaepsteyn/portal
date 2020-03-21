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

        translateX = ofToInt( ofGetEnv("TRANSLATE_X") );
        translateY = ofToInt( ofGetEnv("TRANSLATE_Y") );

        sizeX = ofToInt( ofGetEnv("SIZE_X") );
        sizeY = ofToInt( ofGetEnv("SIZE_Y") );

        totalX = ofToInt( ofGetEnv("TOTAL_X") );
        totalY = ofToInt( ofGetEnv("TOTAL_Y") );

        shiftX = ofToInt( ofGetEnv("SHIFT_X") );
        borderX = ofToInt( ofGetEnv("BORDER_X") );
        translateX += shiftX + borderX;

        portalId = ofGetEnv("PORTAL_ID");
        mapId = ofGetEnv("MAP_ID");

        ofLogNotice() << "My location, x: " << translateX << ", y: " << translateY;

        ofSetWindowShape( sizeX, sizeY );
        ofSetWindowPosition( shiftX, 0 );

    } else {

        translateX = 0;
        translateY = 0;

        sizeX = ofGetWindowWidth();
        sizeY = ofGetWindowHeight();

        totalX = ofGetWindowWidth();
        totalY = ofGetWindowHeight();

        shiftX = 0;
        borderX = 0;

        portalId = "n/a";
        mapId = "n/a";

        ofLogNotice() << "No portal info received from env";
    }

    bgColor = ofColor::black;
    ofSetBackgroundColor(bgColor);
 
    clock.setup();

    ball.setup( translateX, translateY, sizeX, sizeY, totalX, totalY );

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
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
    ofSetColor( bgColor.getInverted() );
        

    ofSetColor( ofColor::pink );
    ofSetCircleResolution( 64 );

    // general info
    ofDrawBitmapString( "translate x, y: " + ofToString(translateX) + ", " + ofToString(translateY), 10, 10 );
    ofDrawBitmapString( "screen width, height: " + ofToString(ofGetWindowWidth()) + ", " + ofToString(ofGetWindowHeight()), 10, 30 );
    ofDrawBitmapString( "total width, total height: " + ofToString(totalX) + ", " + ofToString(totalY), 10, 50 );
    ofDrawBitmapString( "portalId (mapId): " + portalId + " (" + mapId + ")", 10, 70 );

    ofPushMatrix();
        ofTranslate( -translateX, -translateY );
            ball.draw();
    ofPopMatrix();

    clock.draw();


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
