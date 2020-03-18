/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofApp.h"

void ofApp::setup(){

    ofSetFrameRate( 60 );
    ofSetWindowTitle( "Mars Portal" );
    ofSetVerticalSync( true );
    //ofEnableAntiAliasing();

    ofSetLogLevel( OF_LOG_VERBOSE );
    //ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();

/*
#if OF_VERSION_MINOR >= 11
    if ( ofGetScreenWidth() >= 2560 ) {
        ofxGuiEnableHiResDisplay();
    }
#endif
*/

    if( (ofGetEnv("PORTAL").length() != 0) ){

        translateX = ofToInt( ofGetEnv("TRANSLATE_X") );
        translateY = ofToInt( ofGetEnv("TRANSLATE_Y") );

        sizeX = ofToInt( ofGetEnv("SIZE_X") );
        sizeY = ofToInt( ofGetEnv("SIZE_Y") );

        totalX = ofToInt( ofGetEnv("TOTAL_X") );
        totalY = ofToInt( ofGetEnv("TOTAL_Y") );

        ofLogNotice() << "My location, x: " << translateX << ", y: " << translateY;

        ofSetWindowShape( sizeX, sizeY );
        ofSetWindowPosition( 32 + translateX, 32 + translateY );


    } else {

        translateX = 0;
        translateY = 0;

        totalX = ofGetWindowWidth();
        totalY = ofGetWindowHeight();

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
    text = ofToString( ofGetTimestampString("%S.%i") );

    // textWidth doesn't seem to be constant, even for a mono font
    // so we get it once and reuse it
    textWidth = font.stringWidth(text);
    textHeight = font.stringHeight(text);
 
    sound.load( "e.wav");
    sound.setVolume( 0.0 );
    sound.setLoop( true );
    sound.setSpeed( 1.0 );

    myRectangle.setup();
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

    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );
    text = ofToString( ofGetTimestampString("%S.%i") );

    float freq = 1.0 / 5.0;
    float phase = freq * ofGetSystemTimeMillis()/1000 * TWO_PI;
    //float dt = 1.0 / 60.0;

    x = ofMap( sin( 2 * phase ), -1, 1, 0, totalX );
    //x = ofMap( sin( 2 * phase ), -1, 1, 0, ofGetWindowWidth() );

    y = ofMap( cos( phase ), -1, 1, 0, totalY );

/*
    pct += 0.01f;		// increase by a certain amount
    if (pct > 1) {
    	pct = 0;	// just between 0 and 1 (0% and 100%)
    }
    myRectangle.interpolateByPct(pct);	// go between pta and ptb
*/

    distance = sqrt ( pow((ofGetWindowWidth()/2-x-translateX),2) + pow((ofGetWindowHeight()/2-y-translateY),2) );
    volume = ofMap( distance, ofGetWindowWidth()/2, 0, 0, 1 );
    sound.setVolume( volume );

    if( ! sound.isPlaying() ) {
        if( ofToInt(ofGetTimestampString("%S")) == 0) {
            sound.play();
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
    ofSetColor( bgColor.getInverted() );
        
    font.drawString( text, (ofGetWindowWidth() - textWidth)/2, (ofGetWindowHeight() + textHeight)/2 );

    ofSetColor( ofColor::pink );
    ofSetCircleResolution( 64 );

    ofPushMatrix();
        ofDrawBitmapString( ofGetWindowWidth(), 10, 10 );
        ofDrawBitmapString( ofGetWindowHeight(), 10, 30 );
        ofDrawBitmapString( x, 10, 50 );
        ofDrawBitmapString( y, 10, 70 );
        ofDrawBitmapString( distance, 10, 90 );
        ofDrawBitmapString( volume, 10, 110 );
        ofTranslate( -translateX, -translateY );
        ofDrawCircle( x, y, 128*volume );
    ofPopMatrix();

    //myRectangle.draw();


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
