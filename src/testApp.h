#pragma once

#include "ofMain.h"
#include "eyeMesh.h"

class testApp : public ofBaseApp{

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
	
		void setTexCoord(int texW, int texH);
	
		ofEasyCam		windowCamera;
		ofTexture		eyeCamTexture;
		ofVideoGrabber	eyeCam;
		ofShader		fuxShader;
		ofFbo			eyeCamFBO;
	
		bool enableAlpha;
	
		float eyeMeshTexCoord[640][480][2];
	
		int eyeCamW;
		int eyeCamH;
	
		int mouseX;
		int mouseY;
		
		eyeMesh gridCam;
	
};
