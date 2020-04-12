/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    //ofSetupOpenGL( 1024, 768, OF_WINDOW );

    ofGLFWWindowSettings settings;

    settings.setSize( 1280, 720 );
    settings.decorated = false;
    settings.windowMode = OF_WINDOW;

    ofCreateWindow( settings );

    ofRunApp( new ofApp() );

}
