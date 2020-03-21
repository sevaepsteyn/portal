/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofApp.h"

// When not running portal mode
#define DEBUG_SCREEN_BUFFER 32

#define MIN_Z 0
#define MAX_Z ofGetWindowWidth()

void ofApp::setup(){

    ofSetFrameRate( 60 );
    ofSetWindowTitle( "Mars Portal" );
    ofSetVerticalSync( true );
    ofEnableAntiAliasing();

    ofSetLogLevel( OF_LOG_VERBOSE );
    //ofLogNotice() << "OF version " << ofGetVersionMajor() << "." << ofGetVersionMinor() << "." << ofGetVersionPatch() << " " << ofGetVersionPreRelease();

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

        shiftX = 0;
        borderX = 0;

        sizeX = ofGetWindowWidth();
        sizeY = ofGetWindowHeight();

        totalX = ofGetWindowWidth();
        totalY = ofGetWindowHeight();

        portalId = "";
        mapId = "";

        ofLogNotice() << "No portal location received from env";
    }

    // Center of *this* screen at z=0
    screenCenter = ofPoint( sizeX/2 + translateX, sizeY/2 + translateY, 0 );

    // Calculate 3D box corners
    int i = 0;
    for ( int _x = 0; _x <= totalX; _x += totalX ){
        for ( int _y = 0; _y <= totalY; _y += totalY ){
            for ( int _z = MIN_Z; _z <= (MAX_Z-MIN_Z); _z += (MAX_Z-MIN_Z) ){
                //ofLogNotice() << "i: " << i << ", x: " << _x << ", y: " << _y << ", z: " <<_z;
                corners[i++] = ofPoint( _x, _y, _z );
            }
        }
    }

    // Max distance from screen center to all corners
    maxDistance = 0;
    for ( int j = 0; j < i; j++ ){
        maxDistance = max( maxDistance, screenCenter.distance(corners[j]) );
    }

    bgColor = ofColor::black;
    ofSetBackgroundColor(bgColor);

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
    sound.setSpeed( 0.66 );

    //video.load( "/home/pi/media/portal-movies/out.mp4" );
    //video.load( "out.mp4" );

    myRectangle.setup();
}

//--------------------------------------------------------------
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

    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );
    text = ofToString( ofGetTimestampString("%S.%i") );

    float freq = 1.0 / 5.0;
    //float phase = freq * ofGetSystemTimeMillis()/1000 * TWO_PI;
    float phase = freq * (ofToFloat(ofGetTimestampString("%S.%i"))) * TWO_PI;
    //float dt = 1.0 / 60.0;

    x = ofMap( sin( 2 * phase ), -1, 1, 0, totalX );
    //x = ofMap( sin( 4 * phase ), -1, 1, 0, ofGetWindowWidth() );

    y = ofMap( cos( phase ), -1, 1, 0, totalY );

    z = ofMap( sin( 1 * phase), -1, 1, MIN_Z, MAX_Z );
    z = 0;

    /*
    distance = sqrt( 0
        + pow( x - translateX - sizeX/2, 2)
        + pow( y - translateY - sizeY/2, 2)
        + pow( z, 2)
    );
    */
    distance = screenCenter.distance( ofPoint(x, y, z) );

    volume = ofMap( distance, 0, maxDistance, 1, 0 );

    sound.setVolume( volume );

    if( ! sound.isPlaying() ) {
        if( ofToInt(ofGetTimestampString("%S")) == 0) {
            sound.play();
            //video.setVolume( 0.66 );
            //video.play();
        }
    }

    //video.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor( bgColor );
    ofSetColor( bgColor.getInverted() );
        
    font.drawString( text, (ofGetWindowWidth() - textWidth)/2, (ofGetWindowHeight() + textHeight)/2 );

    ofSetColor( ofColor::pink );
    ofSetCircleResolution( 64 );

    ofDrawBitmapString( "x, y, z: " + ofToString(x) + ", " + ofToString(y) + ", " + ofToString(z), 10, 10 );
    ofDrawBitmapString( "screen width, height: " + ofToString(ofGetWindowWidth()) + ", " + ofToString(ofGetWindowHeight()), 10, 30 );
    ofDrawBitmapString( "total width, total height: " + ofToString(totalX) + ", " + ofToString(totalY), 10, 50 );
    ofDrawBitmapString( "translate x, y: " + ofToString(translateX) + ", " + ofToString(translateY), 10, 70 );
    ofDrawBitmapString( "center: " + ofToString(screenCenter), 10, 90 );
    ofDrawBitmapString( "dist to center (max): " + ofToString(distance) + " (" + ofToString(maxDistance) + ")", 10, 110 );
    ofDrawBitmapString( "volume: " + ofToString(volume), 10, 130 );
    ofDrawBitmapString( "portalId (mapId): " + portalId + " (" + mapId + ")", 10, 150 );
    ofDrawBitmapString( "phase: " + ofToString( 1.0/5.0 * ofGetSystemTimeMillis()/1000 * TWO_PI ), 10, 170 );

    ofPushMatrix();
        ofTranslate( -translateX, -translateY );
            ofDrawCircle( x, y, 256 * ofMap( z, MIN_Z, MAX_Z, 1, 0.1 ) );
    ofPopMatrix();

    //ofSetColor( 255 );
    //video.draw( 0, 0, totalX, totalY );


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
