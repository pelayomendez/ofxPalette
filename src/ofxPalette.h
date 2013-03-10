/*
 *  ofxPalette.h
 *
 *  Created by Pelayo Méndez on 09/10/13.
 *  No rights reserved.
 *
 *  Simple addon to use and test palettes from colourlovers.com website, but it
 *  should work with other popular palette generators or you can build your own.
 *
 *  Original idea based on Alba Corral´s Janebeta7 Processing color library.
 *  Source: https://github.com/janebeta7/janebeta7Libs
 *
 *	Dependencies: ---
 *
 *  Created with OpenFrameworks 0074
 */

#pragma once

#include "ofMain.h"

class Palette {
    
    public:
    
        int size;
        vector<ofColor> colors;

};

class ofxPalette {
    
    public:
    
        ofxPalette();
    
        void loadPalletes();
        ofColor& getColor(int colornum);
        int& getNumColors();
        void prevPalette();
        void nextPalette();
    
        void randomizePalette();
        void moveColorsFoward(int steps);
        void moveColorsBackwards(int steps);
        void savePalette();
    
        int activePalette;
	
    private:
    
        vector<ofColor> parseColors(ofImage& img);
    
        ofDirectory fileHelper;
        vector<Palette> palettes;
        ofImage imgSave;
        ofFbo saveFbo;
    
    
};