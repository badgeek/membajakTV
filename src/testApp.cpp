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
	
	
	gridCam.setMeshGrid(40, 30);
	gridCam.setMeshSize(20, 20);
	gridCam.updateMeshTexCoord();
	
	windowCamera.setDistance(400);
	
	enableAlpha = false;
	enableRawAlpha = false;
	//windowCamera.setScale(1, -1, 1);
	
	
}

//--------------------------------------------------------------
void testApp::update(){

	eyeCam.grabFrame();
		
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if(enableRawAlpha == true)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(GL_FALSE);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.f);
		
	}else if(enableAlpha == false){
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glDisable(GL_ALPHA_TEST);
	}
	
	
	if(enableAlpha == true)
	{
	 ofEnableBlendMode(OF_BLENDMODE_ADD);
	}else if(enableRawAlpha == false){
	 ofDisableBlendMode();
	}
	 
	


		windowCamera.begin();
		
			glPushMatrix();
			//unflip the camera
			glScalef(1.0, -1.0, 1.0);

				glPushAttrib(GL_POLYGON_BIT);
					glEnable( GL_POINT_SMOOTH );
					glFrontFace(GL_CW);
					glPolygonMode(GL_FRONT, GL_POINT);
					glPolygonMode(GL_BACK, GL_LINE);
					glPointSize(5.f);
					eyeCam.getTextureReference().bind();	
					gridCam.draw(GL_TRIANGLE_STRIP);
					eyeCam.getTextureReference().unbind();
				glPopAttrib();
			
				glPushAttrib(GL_POLYGON_BIT);
					glPolygonMode(GL_BACK, GL_LINE);
					glPolygonMode(GL_FRONT, GL_LINE);
					glPushMatrix();
						glTranslatef(0, 0, -30);
						eyeCam.getTextureReference().bind();	
						gridCam.draw(GL_TRIANGLE_STRIP);
						eyeCam.getTextureReference().unbind();	
					glPopMatrix();
				glPopAttrib();
			
			glPopMatrix();
		
		windowCamera.end();
	
	//if(enableAlpha == true)
	//{

	//}
	
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
	
	
	if (key == 97)
	{
		enableAlpha = !enableAlpha;
		//printf("alpha:%i\n", enableAlpha);
	}
	
	if	(key == 115)
	{
		enableRawAlpha = !enableRawAlpha;
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
