#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    
    colorPalette.loadPalletes();
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(colorPalette.getColor(0));
    
    int totalPaletteColors = colorPalette.getNumColors();
    
    for(int i = 1; (int) i < totalPaletteColors; i++){
        ofSetColor(colorPalette.getColor(i));
        ofFill();
        ofCircle(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight()/2-(i*80));
        ofNoFill(); // This fix circle smooth borders:
        ofCircle(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight()/2-(i*80));
    }
    
    ofDrawBitmapString("Press +/- to cycle through palettes", ofPoint(10,20));
    ofDrawBitmapString("q,w move colors foward & backward :: r, randomize color order", ofPoint(10,35));
    ofDrawBitmapString("s, saves palette", ofPoint(10,50));
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == '+'){
        colorPalette.nextPalette();
    }
    
    if(key == '-'){
        colorPalette.prevPalette();
    }
    
    if(key == 'r'){
        colorPalette.randomizePalette();
    }
    
    if(key == 'q'){
        colorPalette.moveColorsBackwards(1);
    }
    
    if(key == 'w'){
        colorPalette.moveColorsFoward(1);
    }
    
    if(key == 'r'){
        colorPalette.randomizePalette();
    }
    
    if(key == 's'){
        colorPalette.savePalette();
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}