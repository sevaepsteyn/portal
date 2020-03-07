/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofSetWindowTitle( "Brahman portal" );
    //ofEnableAntiAliasing();
    ofSetLogLevel( OF_LOG_VERBOSE );

    //ofSetBackgroundAuto(false);
    bgColor = ofColor::black;
    ofSetBackgroundColor(bgColor);

    ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();

/*
#if OF_VERSION_MINOR >= 11
    if ( ofGetScreenWidth() >= 2560 ) {
        ofxGuiEnableHiResDisplay();
    }
#endif
*/

    ofLogNotice() << "Hello!\n";

    //create the socket and set to send to 127.0.0.1:11999
    ofxUDPSettings settings;
    //settings.sendTo( "127.0.0.1", 7979 );
    settings.receiveOn( 7979 );
    settings.blocking = false;

    udpConnection.Setup( settings );

    font.load( "fonts/VT323-Regular.ttf", ofGetWindowHeight()/6 );

    textWidth = textHeight = 0;

//portal01    DC:A6:32:01:16:F0    10.79.103.101
//portal02    DC:A6:32:75:E4:4E    10.79.103.102
//portal03    DC:A6:32:76:3A:6E    10.79.103.103
//portal04    DC:A6:32:75:D6:E4    10.79.103.104
//portal05    DC:A6:32:75:D6:F3    10.79.103.105
//portal06    DC:A6:32:75:E1:D3    10.79.103.106
//portal07    DC:A6:32:01:18:6A    10.79.103.107
//portal08    DC:A6:32:01:0F:38    10.79.103.108
//portal09    DC:A6:32:01:19:35    10.79.103.109
//portal10    DC:A6:32:76:39:ED    10.79.103.110
//portal11    DC:A6:32:75:FF:D0    10.79.103.111
//portal12    DC:A6:32:76:2D:DA    10.79.103.112
//portal13    DC:A6:32:75:E3:38    10.79.103.113
//portal14    DC:A6:32:75:E2:0D    10.79.103.114
//portal15    DC:A6:32:76:05:0D    10.79.103.115
//portal16    DC:A6:32:01:00:0B    10.79.103.116
//portal17    DC:A6:32:01:0F:23    10.79.103.117
//portal18    DC:A6:32:75:E4:43    10.79.103.118

}

//--------------------------------------------------------------
void ofApp::update(){

    char udpMessage[1024];
    udpConnection.Receive( udpMessage, 1024 );
    message = udpMessage;
    if( message != "" ){
        //atoi(message.c_str());
        ofLogVerbose() << "Got: " << message;

        vector<string> color = ofSplitString( message, "," );
        if( color.size() == 3) {
            bgColor = ofColor(ofToInt(color[0]), ofToInt(color[1]), ofToInt(color[2]));
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
        
    //ofPushMatrix();
    //ofDrawBitmapString( ofToString(ofGetFrameRate(), 2 ), 100, 100);
        //ofScale( 2, 2 );
        //ofDrawBitmapString( ofToString( ofGetSystemTimeMicros() ), 100, 200);
    //ofPopMatrix();

    // MAC address /sys/class/net/eth0/address
    
    string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );

    // textWidth doesn't seem to be constant, even for a mono font
    // so get it once and reuse it...
    if( textWidth == 0 ) textWidth = font.stringWidth(text);
    if( textHeight == 0 ) textHeight = font.stringHeight(text);

    ofSetColor( bgColor.getInverted() );
    font.drawString( text, (ofGetWindowWidth() - textWidth)/2, (ofGetWindowHeight() + textHeight)/2 );

    ofSetColor( ofColor::pink );
    ofSetCircleResolution(64);

    float freq = 0.2;
    float phase = freq * ofGetSystemTimeMillis()/1000 * TWO_PI;
    // float dt = 1.0 / 60.0;
    // phase += dt * freq * M_TWO_PI;

    int x = ofMap( sin( phase ), -1, 1, 0, ofGetWindowWidth() );
    //int y = ofMap( cos( phase ), -1, 1, 0, ofGetWindowHeight() );

    int y = ofMap( cos( phase ), -1, 1, 0, 2*ofGetWindowHeight() );
    y -= ofGetWindowHeight();

    ofDrawCircle( x, y, 64 );

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch ( key ) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        case 'p':
        case 'P':
        case OF_KEY_RETURN:
            ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();
            ofSaveScreen( "screenshot-" + ofToString( ofGetUnixTime() ) + ".png");
            break;
        case 'q':
        case 'Q':
            ofExit();
            break;
        case '?':
#ifdef SERIAL_PORT
            serial.listDevices();
#endif
#ifdef MIDI_PORT
            midiIn.listInPorts();
#endif
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
