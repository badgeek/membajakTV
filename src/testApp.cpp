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
	
	gridCam.setMeshGrid(150, 150);
	gridCam.setMeshSize(0.25, 0.25);
	gridCam.updateMeshTexCoord();
	
	windowCamera.setDistance(100);
	
	enableAlpha = true;
	
	enableEffects1 = true;
	enableEffects2 = true;
	enableEffects3 = true;
	enableEffects4 = true;

	ofToggleFullscreen();
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	//glEnable( GL_POINT_SMOOTH );

	
	//mouse click
	//CGPoint point;
	//point.x = 100;
	//point.y = 100;
	//CGWarpMouseCursorPosition(point);
	//CGPostMouseEvent(point, FALSE, 1, TRUE);   //mouse down
	//CGPostMouseEvent(point, FALSE, 1, FALSE);//mouse up
	
}

//--------------------------------------------------------------
void testApp::update(){

	eyeCam.grabFrame();
		
}

//--------------------------------------------------------------
void testApp::draw(){
	
	/*if(enableAlpha == true)
	{
	 ofEnableBlendMode(OF_BLENDMODE_ADD);
	}else{
	 ofDisableBlendMode();
	}*/

		windowCamera.begin();
		
			glPushMatrix();
			//unflip the camera
			//glScalef(1.0, -1.0, 1.0);
			glScalef(4.0, -3.0, 1);
	
				fuxShader.begin();
				fuxShader.setUniform1f("eyeMultiply", 100.0f);
				fuxShader.setUniformTexture("eyeTexDepth", eyeCam.getTextureReference(), 0);
	
			if	(enableEffects1)
			{
				gridCam.draw(GL_LINES);				
			}

			if	(enableEffects2)
			{
				glPushAttrib(GL_POLYGON_BIT);
					glFrontFace(GL_CW);
					glPointSize(2.5f);
					gridCam.draw(GL_POINTS);
				glPopAttrib();
			}
	
			
			if	(enableEffects3)
			{
				 glPushAttrib(GL_POLYGON_BIT);
					 glFrontFace(GL_CW);
					 glPolygonMode(GL_FRONT, GL_LINE);
					 glPolygonMode(GL_BACK, GL_LINE);
					 gridCam.draw(GL_TRIANGLE_STRIP);
				 glPopAttrib();
			}
			
			if	(enableEffects4)
			{
				glPushAttrib(GL_POLYGON_BIT);
					glPushMatrix();
						glTranslatef(0, 0, 20);
						//glPolygonMode(GL_FRONT, GL_LINE);
						//glPolygonMode(GL_BACK, GL_LINE);
						glPointSize(5.f);
						gridCam.draw(GL_POINTS);
					glPopMatrix();
				glPopAttrib();				
			}


			glPopMatrix();
		
			fuxShader.end();


		windowCamera.end();
	
	
	
	ofDrawBitmapString("press f to fullscreen, n to normal, cam roll: " + ofToString(windowCamera.getOrientationEuler().x) + " cam pitch:" + ofToString(windowCamera.getOrientationEuler().y) + " cam z: " + ofToString(windowCamera.getPosition().z) , ofPoint(20,20));

	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	printf("ascii:%i\n", key);
	
	if (key == 97) {
		OSErr error = SendAppleEventToSystemProcess(kAEShutDown);  
	}
	
	switch (key) {
		case 102:
			ofToggleFullscreen();
			break;
		case 43:
			enableEffects1 = !enableEffects1;
			break;
		case 57:
			enableEffects2 = !enableEffects2;
			break;
		case 56:
			enableEffects3 = !enableEffects3;
			break;
		case 55:
			enableEffects4 = !enableEffects4;
			break;			
		default:
			break;
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


OSStatus testApp::SendAppleEventToSystemProcess(AEEventID EventToSend)  
{  
    AEAddressDesc targetDesc;  
    static const ProcessSerialNumber  
	kPSNOfSystemProcess = { 0, kSystemProcess };  
    AppleEvent eventReply = {typeNull, NULL};  
    AppleEvent appleEventToSend = {typeNull, NULL};  
	
    OSStatus error = noErr;  
	
    error = AECreateDesc(typeProcessSerialNumber,  
						 &kPSNOfSystemProcess, sizeof(kPSNOfSystemProcess),  
						 &targetDesc);  
	
    if (error != noErr)  
    {  
        return(error);  
    }  
	
    error = AECreateAppleEvent(kCoreEventClass, EventToSend,  
							   &targetDesc, kAutoGenerateReturnID,  
							   kAnyTransactionID, &appleEventToSend);  
	
    AEDisposeDesc(&targetDesc);  
	
    if (error != noErr)  
    {  
        return(error);  
    }  
	
    error = AESend(&appleEventToSend, &eventReply, kAENoReply,  
				   kAENormalPriority, kAEDefaultTimeout,  
				   NULL, NULL);  
	
    AEDisposeDesc(&appleEventToSend);  
	
    if (error != noErr)  
    {  
        return(error);  
    }  
	
    AEDisposeDesc(&eventReply);  
	
    return(error); //if this is noErr then we are successful  
}  
