/*
 *  pdSound.cpp
 *  membajakTV
 *
 *  Created by Budi Prakosa on 11/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "pdSound.h"
#include <Poco/Path.h>

// main
void pdSound::setup(const int numOutChannels, const int numInChannels, const int sampleRate, const int ticksPerBuffer)
{
	if(!pd.init(numOutChannels, numInChannels, sampleRate, ticksPerBuffer)) {
		ofLog(OF_LOG_ERROR, "Could not init pd");
		OF_EXIT_APP(1);
	}
	
	Patch patch = pd.openPatch("vertexnoize_sound.pd");

	pd.dspOn();

}

// audio callbacks
void pdSound::audioReceived(float * input, int bufferSize, int nChannels)
{
	pd.audioIn(input, bufferSize, nChannels);
}

void pdSound::audioRequested(float * output, int bufferSize, int nChannels)
{
	pd.audioOut(output, bufferSize, nChannels);	
}
