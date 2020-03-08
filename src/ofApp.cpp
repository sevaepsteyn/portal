/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofApp.h"

void ofApp::setup(){

    ofSetFrameRate( 60 );
    ofSetWindowTitle( "Brahman portal" );
    //ofEnableAntiAliasing();
    //ofSetVerticalSync( true );

    ofSetLogLevel( OF_LOG_VERBOSE );
    ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();

/*
#if OF_VERSION_MINOR >= 11
    if ( ofGetScreenWidth() >= 2560 ) {
        ofxGuiEnableHiResDisplay();
    }
#endif
*/

#define SIZE_X 160
#define BORDER_X 16
#define TOTAL_X ( 6*SIZE_X + 5*BORDER_X )
#define SIZE_Y 160
#define BORDER_Y 16
#define TOTAL_Y ( 3*SIZE_Y + 2*BORDER_Y )

    if( (ofGetEnv("PORTAL_X").length() != 0) &&  (ofGetEnv("PORTAL_Y").length() != 0) ){

        int portalX = ofToInt( ofGetEnv("PORTAL_X") );
        int portalY = ofToInt( ofGetEnv("PORTAL_Y") );

        translateX = portalX * ( SIZE_X + BORDER_X );
        translateY = portalY * ( SIZE_Y + BORDER_Y );

        ofLogNotice() << "My location, x: " << translateX << ", y: " << translateY;

        ofSetWindowShape( SIZE_X, SIZE_Y );
        ofSetWindowPosition( 32 + translateX, 32 + translateY );

    } else {

        translateX = 0;
        translateY = 0;

        ofLogNotice() << "No portal location received from env";
    }


    bgColor = ofColor::black;
    ofSetBackgroundColor(bgColor);

    ofxUDPSettings socketSettings;
    socketSettings.receiveOn( 7979 );
    socketSettings.blocking = false;
    udpConnection.Setup( socketSettings );

    font.load( "fonts/VT323-Regular.ttf", ofGetWindowHeight()/6 );
    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );
    string text = ofToString( ofGetTimestampString("%S.%i") );

    // textWidth doesn't seem to be constant, even for a mono font
    // so we get it once and reuse it
    textWidth = font.stringWidth(text);
    textHeight = font.stringHeight(text);

}

//--------------------------------------------------------------
void ofApp::update(){

    char udpMessage[1024];
    udpConnection.Receive( udpMessage, 1024 );
    message = udpMessage;
    if( message != "" ){
        ofLogVerbose() << "Received UDP message: " << message;

        vector<string> color = ofSplitString( message, "," );
        if( color.size() == 3) {
            bgColor = ofColor(ofToInt(color[0]), ofToInt(color[1]), ofToInt(color[2]));
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
        
    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );
    string text = ofToString( ofGetTimestampString("%S.%i") );

    ofSetColor( bgColor.getInverted() );
    font.drawString( text, (ofGetWindowWidth() - textWidth)/2, (ofGetWindowHeight() + textHeight)/2 );

    ofSetColor( ofColor::pink );
    ofSetCircleResolution(64);

    float freq = 0.2;
    float phase = freq * ofGetSystemTimeMillis()/1000 * TWO_PI;
    // float dt = 1.0 / 60.0;
    // phase += dt * freq * M_TWO_PI;

    //int x = ofMap( sin( phase ), -1, 1, 0, ofGetWindowWidth() );
    int x = ofMap( sin( 2*phase ), -1, 1, 0, TOTAL_X );

    //int y = ofMap( cos( phase ), -1, 1, 0, ofGetWindowHeight() );
    int y = ofMap( cos( phase ), -1, 1, 0, TOTAL_Y );

    ofPushMatrix();
        ofTranslate( -translateX, -translateY );
        ofDrawCircle( x, y, 64 );
    ofPopMatrix();

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
