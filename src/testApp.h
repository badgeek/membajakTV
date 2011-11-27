#pragma once

#define	DONT_USE_ARDUINO

#include <Carbon/Carbon.h>  
#include "ofMain.h"
#include "eyeMesh.h"
#include "pdSound.h"
#include "hGui_all.h"


class testApp : public ofBaseApp, public hObject {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
		#ifndef DONT_USE_ARDUINO
		void setupArduino(const int & version);
		#endif
	
		//audio callback
		void audioReceived(float * input, int bufferSize, int nChannels);
		void audioRequested(float * output, int bufferSize, int nChannels);

		OSStatus SendAppleEventToSystemProcess(AEEventID EventToSend);  
	
		ofEasyCam		windowCamera;
		ofTexture		eyeCamTexture;
		ofVideoGrabber	eyeCam;
		ofShader		fuxShader;
		ofFbo			eyeCamFBO;
	
		#ifndef DONT_USE_ARDUINO
		ofArduino		ard;
		#endif
		
		bool bArduinoSetup;
	
		bool enableAlpha;
		bool enableGui;
	
		//shutdown
		bool btnShutdown;
	
		//effects switch
		bool enableEffects1;
		bool enableEffects2;
		bool enableEffects3;
		bool enableEffects4;

		//effects translate
		float effectsTranslate1;
		float effectsTranslate2;
		float effectsTranslate3;
		float effectsTranslate4;
	
		//effects shader multiplier
		float shaderMultiply;
	
		//camera zoom
		float eyeCamZoom;
		float eyeCamZoomPrev;
	
		float eyeMeshTexCoord[640][480][2];
	
		int eyeCamW;
		int eyeCamH;
	
		int mouseX;
		int mouseY;
		
		eyeMesh gridCam;
	
		//sound
	
		pdSound pdEngine;
	
};
