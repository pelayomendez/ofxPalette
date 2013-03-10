//
//  ofxPalette.cpp
//  emptyExample
//
//  Created by Pelayo M. on 09/03/13.
//
//

#include "ofxPalette.h"

//--------------------------------------------------------------
ofxPalette::ofxPalette(){
	
    activePalette = -1;
    
    saveFbo.allocate(1024, 768, GL_RGBA32F_ARB);
    saveFbo.begin();
	ofClear(255,255,255, 0);
    saveFbo.end();
    
	
}

//--------------------------------------------------------------
ofColor& ofxPalette::getColor(int colornum) {
    
    ofColor defaultcolor = ofColor(0,0,0);
    
    if (activePalette < 0) return;
    
    if(colornum < palettes[activePalette].colors.size()) {
        return palettes[activePalette].colors[colornum];
    } else {
        return;
    }

}

//--------------------------------------------------------------
int& ofxPalette::getNumColors() {
    return palettes[activePalette].size;
}

//--------------------------------------------------------------
void ofxPalette::nextPalette() {
   
    if(activePalette<palettes.size()-1) {
        activePalette +=1;
    } else {
        activePalette = 0;
    }
    
}

//--------------------------------------------------------------
void ofxPalette::prevPalette() {
    
    if(activePalette > 0) {
        activePalette -=1;
    } else {
        activePalette = palettes.size()-1;
    }
    
}

//--------------------------------------------------------------
void ofxPalette::randomizePalette() {
    
    std::random_shuffle(palettes[activePalette].colors.begin(), palettes[activePalette].colors.end());

}

//--------------------------------------------------------------
void ofxPalette::moveColorsFoward(int steps) {
    
    size_t start = 0;
    size_t length = steps;
    size_t dst = palettes[activePalette].colors.size();
    vector<ofColor> &v = palettes[activePalette].colors;
    
    const size_t final_dst = dst > start ? dst - length : dst;
    
    vector<ofColor> tmp(v.begin() + start, v.begin() + start + length);
    v.erase(v.begin() + start, v.begin() + start + length);
    v.insert(v.begin() + final_dst, tmp.begin(), tmp.end());
    
       
}

//--------------------------------------------------------------
void ofxPalette::moveColorsBackwards(int steps) {
    
    size_t start = 0;
    size_t length = steps;
    size_t dst = palettes[activePalette].colors.size();
    vector<ofColor> &v = palettes[activePalette].colors;
    
    const size_t final_dst = dst-steps;
    
    vector<ofColor> tmp(v.begin()+final_dst, v.end());
    v.erase(v.begin()+final_dst, v.end());
    v.insert(v.begin(), tmp.begin(), tmp.end());
   
}

//--------------------------------------------------------------
void ofxPalette::savePalette() {
    
    string _timestamp = ofToString(ofGetDay()) +
	ofToString(ofGetMonth()) +
	ofToString(ofGetYear()) +
	ofToString(ofGetHours()) +
	ofToString(ofGetMinutes()) +
	ofToString(ofGetSeconds());
    
    saveFbo.begin();
        ofClear(0,0,0, 255);
        int totalPaletteColors = getNumColors();
        ofPushStyle();
        ofFill();
        int colorStep = 1024/totalPaletteColors;
        for(int i = 0; (int) i < totalPaletteColors; i++){
            ofSetColor(getColor(i));
            if(i < totalPaletteColors-1) {
                ofRect(0+(i*colorStep),0,colorStep,768);
            } else {
                ofRect(0+(i*colorStep),0,1024,768);
            }
        }
        ofPopStyle();
    saveFbo.end();
    
    ofPixels pixels;
    saveFbo.readToPixels(pixels);
    imgSave.setFromPixels(pixels);
    
    //imgSave.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    string fileName = "palette_"+_timestamp+".png";
    imgSave.saveImage(fileName);
    ofLogNotice("PALETTE SAVED:" + fileName);
    
}

//--------------------------------------------------------------
void ofxPalette::loadPalletes() {
    
    string path = ofToDataPath("palettes");
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.listDir();
    
    int numFiles = dir.numFiles();
    
    if(numFiles > 0) {
    
        palettes.resize(numFiles);
    
        vector<ofImage> iLoader;
        iLoader.resize(numFiles);
    
        // To do: More complex threaded image loader:
        for(int i = 0; (int) i < numFiles; i++){
            iLoader[i].loadImage(dir.getPath(i));
            //ofLogNotice(dir.getPath(i));
        }
    
        for(int i = 0; (int) i < numFiles; i++){
            palettes[i].colors = parseColors(iLoader[i]);
            palettes[i].size = palettes[i].colors.size();
        }
    
        activePalette = 0;
        
        ofLogNotice("PALETTES LOADED: " + ofToString(numFiles));
        
    } else {
        
        ofLogNotice("PALETTES NOT FOUND");
        
    }
    
}

//--------------------------------------------------------------
vector<ofColor> ofxPalette::parseColors(ofImage& img) {

    ofPixels pixelsRef = img.getPixelsRef();
    const int sampleCount = img.getWidth();
	//unsigned char * pixels = pixelsRef.getPixels();
    
    ofColor sampleColor;
    vector<ofColor> finalColors;
    
    for(int i=0; i<sampleCount; i++){
		ofColor c = pixelsRef.getColor(i, 1);
        if(c != sampleColor) {
            finalColors.push_back(c);
            sampleColor = c;
        }
	}
    
    //ofLogNotice("COLORS LOADED: " + ofToString(finalColors.size()));
    return finalColors;
    
}