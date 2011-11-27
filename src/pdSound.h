/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxPd for documentation
 *
 */
#pragma once

#include "ofMain.h"

#include "ofxPd.h"

class pdSound : public ofxPdListener {
	
public:
	
	// main
	void setup(const int numOutChannels, const int numInChannels, const int sampleRate, const int ticksPerBuffer);		
	// audio callbacks
	void audioReceived(float * input, int bufferSize, int nChannels);
	void audioRequested(float * output, int bufferSize, int nChannels);
	// pd callbacks	
	ofxPd pd;
};
