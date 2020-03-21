/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "Clock.h"

void Clock::setup(){

    font.load( "fonts/VT323-Regular.ttf", ofGetWindowHeight()/6 );
    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") );
    text = ofToString( ofGetTimestampString("%S.%i") );

    // textWidth doesn't seem to be constant, even for a mono font
    // so we get it once and reuse it
    textWidth = font.stringWidth(text);
    textHeight = font.stringHeight(text);
}

void Clock::update(){
    //string text = ofToString( ofGetTimestampString("%H:%M:%S.%i") )
    text = ofToString( ofGetTimestampString("%S.%i") );

}

void Clock::draw(){
    font.drawString( text, (ofGetWindowWidth() - textWidth)/2, (ofGetWindowHeight() + textHeight)/2 );
}
