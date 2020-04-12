/* vim: set tabstop=4 shiftwidth=4 expandtab: */

#include "Ball.h"

void Ball::setup( PortalSettings _portal ){
    portal = _portal;

    // center of *this* screen at z=0
    screenCenter = ofPoint( portal.sizeX/2 + portal.translateX, portal.sizeY/2 + portal.translateY, 0 );

    // calculate 3D box far corners corners
    int i = 0;
    for ( int _x = 0; _x <= portal.totalX; _x += portal.totalX ){
        for ( int _y = 0; _y <= portal.totalY; _y += portal.totalY ){
            for ( int _z = MIN_Z; _z <= (MAX_Z-MIN_Z); _z += (MAX_Z-MIN_Z) ){
                //ofLogNotice() << "i: " << i << ", x: " << _x << ", y: " << _y << ", z: " <<_z;
                corners[i++] = ofPoint( _x, _y, _z );
            }
        }
    }

    // max distance from screen center to all corners
    maxDistance = 0;
    for ( int j = 0; j < i; j++ ){
        maxDistance = max( maxDistance, screenCenter.distance(corners[j]) );
    }

    sound.load( "h.mp3");
    sound.setVolume( 0.0 );
    sound.setLoop( true );
    sound.setSpeed( 0.6 );

}

void Ball::update(){
    float freq = 1.0 / 10.0;
    //float phase = freq * ofGetSystemTimeMillis()/1000 * TWO_PI;
    float phase = freq * (ofToFloat(ofGetTimestampString("%S.%i"))) * TWO_PI;
    //float dt = 1.0 / 60.0;

    x = ofMap( sin( 2 * phase ), -1, 1, 0, portal.totalX );
    //x = ofMap( sin( 4 * phase ), -1, 1, 0, ofGetWindowWidth() );
    if (portal.side == 1) x = portal.totalX-x;

    y = ofMap( cos( phase ), -1, 1, 0, portal.totalY );

    z = ofMap( sin( phase / PI ), -1, 1, MIN_Z, MAX_Z );

    distance = screenCenter.distance( ofPoint(x, y, z) );

    volume = ofMap( distance, 0, maxDistance, 1, 0 );
    volume *= volume;

    if(portal.side == 0) {
        if ( z >= 0 ) {
            sound.setVolume( volume );
        } else {
            sound.setVolume( 0 );
        }
    } else {
        if ( z <= 0 ) {
            sound.setVolume( volume );
        } else {
            sound.setVolume( 0 );
        }
    }

    if( ! sound.isPlaying() ) {
        if( ofToInt(ofGetTimestampString("%S")) == 0) {
            sound.play();
            ofLog() << "Playing sound...";
            //video.setVolume( 0.66 );
            //video.play();
        }
    }


}

void Ball::draw(){
    if( portal.side == 0) {
        if( z>= 0 ) ofDrawCircle( x, y, ofMap(abs(z), 0, MAX_Z, 256, 8 ) );
    } else if( portal.side == 1) {
        if( z<= 0) ofDrawCircle( x, y, ofMap(abs(z), 0, MAX_Z, 256, 8 ) );
    }

    ofPushMatrix();
        ofTranslate( portal.translateX, portal.translateY );

        // my info
        ofDrawBitmapString( "volume: " + ofToString(volume), 10, ofGetWindowHeight()-90 );
        ofDrawBitmapString( "phase: " + ofToString( 1.0/5.0 * ofGetSystemTimeMillis()/1000 * TWO_PI ), 10, ofGetWindowHeight()-70 );
        ofDrawBitmapString( "center: " + ofToString(screenCenter), 10, ofGetWindowHeight()-50 );
        ofDrawBitmapString( "dist to center (max): " + ofToString(distance) + " (" + ofToString(maxDistance) + ")", 10, ofGetWindowHeight()-30 );
        ofDrawBitmapString( "x, y, z: " + ofToString(x) + ", " + ofToString(y) + ", " + ofToString(z), 10, ofGetWindowHeight()-10 );

    ofPopMatrix();
}
