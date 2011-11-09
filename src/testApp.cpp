#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	eyeCamW = 640;
	eyeCamH = 480;
		
	eyeCam.initGrabber(eyeCamW, eyeCamH);
	eyeCam.setUseTexture(true);
	
	fuxShader.load("fuxShader.vert", "fuxShader.frag");
			
	ofSetVerticalSync(false);
	ofSetFrameRate(30);
	ofSetWindowShape(1024, 768);
	ofBackground(0, 0, 0, 0);
	
	gridCam.setMeshGrid(120, 120);
	gridCam.setMeshSize(1, 1);
	gridCam.updateMeshTexCoord();
	
	windowCamera.setDistance(400);
	
	enableAlpha = true;	
	
	ofToggleFullscreen();
	
}

//--------------------------------------------------------------
void testApp::update(){

	eyeCam.grabFrame();
		
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if(enableAlpha == true)
	{
	 ofEnableBlendMode(OF_BLENDMODE_ADD);
	}else{
	 ofDisableBlendMode();
	}

		windowCamera.begin();
		
			glPushMatrix();
			//unflip the camera
			//glScalef(1.0, -1.0, 1.0);
			glScalef(4.0, -3.0, 1);
	
				fuxShader.begin();
				fuxShader.setUniform1f("eyeMultiply", 800.0f);
				fuxShader.setUniformTexture("eyeTexDepth", eyeCam.getTextureReference(), 0);
	
				glPushAttrib(GL_POLYGON_BIT);
					glEnable( GL_POINT_SMOOTH );
					glFrontFace(GL_CW);
					glPolygonMode(GL_FRONT, GL_POINT);
					glPolygonMode(GL_BACK, GL_LINE);
					glPointSize(5.f);
					gridCam.draw(GL_POINTS);
				glPopAttrib();
			
				glPushAttrib(GL_POLYGON_BIT);
					//glEnable( GL_POINT_SMOOTH );
					glFrontFace(GL_CW);
					glPolygonMode(GL_FRONT, GL_LINE);
					glPolygonMode(GL_BACK, GL_LINE);
					//glPointSize(5.f);
					gridCam.draw(GL_TRIANGLE_STRIP);
				glPopAttrib();
	
				glPushAttrib(GL_POLYGON_BIT);
					glEnable( GL_POINT_SMOOTH );
					glFrontFace(GL_CW);
					glPolygonMode(GL_FRONT, GL_POINT);
					glPolygonMode(GL_BACK, GL_POINT);
					glPointSize(5.f);
					gridCam.draw(GL_TRIANGLE_STRIP);
				glPopAttrib();
	
				gridCam.draw(GL_LINES);

	
				glPushAttrib(GL_POLYGON_BIT);
					//glPolygonMode(GL_BACK, GL_LINE);
					//glPolygonMode(GL_FRONT, GL_LINE);
					glPushMatrix();
						//glTranslatef(0, 0, -30);
						eyeCam.getTextureReference().bind();	
						gridCam.draw(GL_LINES);
						eyeCam.getTextureReference().unbind();	
					glPopMatrix();
				glPopAttrib();
			
			glPopMatrix();
		
			fuxShader.end();

		windowCamera.end();
	
	ofDrawBitmapString("press f to fullscreen, n to normal, mouse x: " + ofToString(mouseX) + " mouseY:" + ofToString(mouseY), ofPoint(20,20));
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	printf("ascii:%i\n", key);
	
	if (key == 102) {
		ofToggleFullscreen();
	}else if (key ==  110) {
		ofSetFullscreen(false);
	}
	
	if (key == 97) {
		enableAlpha = !enableAlpha;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	mouseX	= x;
	mouseY  = y;
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
