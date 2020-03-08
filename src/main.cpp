/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    //ofSetupOpenGL( 1024, 768, OF_WINDOW );

    ofGLFWWindowSettings settings;

    //settings.width = 1024;
    //settings.height = 768;
    settings.setSize( 1024, 768 );
    settings.decorated = false;
    settings.windowMode = OF_WINDOW;

    ofCreateWindow( settings );

    ofRunApp( new ofApp() );

}
