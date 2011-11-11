#include "testApp.h"

#include "hEvents.h"
// The event system used by hGui
// Can also be used to create new events and listeners

#include "hObject.h"
// Base object that contain virtual functions
// Objects that inherit from hObject can use its event listeners for free

//--------------------------------------------------------------
void testApp::setup(){
	
	eyeCamW = 640;
	eyeCamH = 480;
		
	eyeCam.initGrabber(eyeCamW, eyeCamH);
	eyeCam.setUseTexture(true);
	
	fuxShader.load("shaders/fuxShader.vert", "shaders/fuxShader.frag");
			
	ofSetVerticalSync(false);
	ofSetFrameRate(30);
	ofSetWindowShape(1024, 768);
	ofBackground(0, 0, 0, 0);
	
	//mesh grid size
	gridCam.setMeshGrid(150, 150);
	
	//spacing between mesh square
	gridCam.setMeshSize(0.25, 0.25);
	
	//calculate mesh vertex and texture coordinate
	gridCam.updateMeshTexCoord();
	gridCam.updateMeshVerCoord();
	
	//compile display list
	gridCam.updateDisplayList();
	
	windowCamera.setDistance(100);
	
	//initiate effects
	
	enableAlpha = true;
	enableGui	= false;
	
	enableEffects1 = true;
	enableEffects2 = true;
	enableEffects3 = true;
	enableEffects4 = true;

	effectsTranslate1 = 0;
	effectsTranslate2 = 0;
	effectsTranslate3 = 0;
	effectsTranslate4 = 0;
	
	shaderMultiply = 100.0f;
	
	//start in fullscreen mode
	ofToggleFullscreen();
	
	//blend mode for eye candy
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	//ofEnableSmoothing();
	
	//!! GUI STUFF BELOW
	//!! GUI STUFF BELOW
	//!! GUI STUFF BELOW
	//!! GUI STUFF BELOW
	//!! GUI STUFF BELOW
	//!! GUI STUFF BELOW

	
	hGui * gui = hGui::getInstance();
	
	gui->setup("fonts/DIN.otf", 9);  // ... but test yourself which one is better for you
	
	hPanel * mainPanel = gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, gui->margin1, gui->margin1+gui->margin3, 250, 0, false);
	
	
	mainPanel->setVisibleBackground(true);
	
	mainPanel->setBackgroundColor(0x000000);
	
	gui->setRootWidget(mainPanel);

	gui->setFillColor(0x20bfe9);
	gui->setBorderColor(0x20bfe9);
	gui->setTextColor(0x20bfe9);
	gui->setCheckBoxColor(0xc0e0e9);
	gui->setSliderColor(0xc0e0e9);
	
	//gui->addListeners();
	
	
	hLabel * sliderLabel0 = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,  gui->margin2,  gui->margin2, "PRESS F TO FULLSCREEN N TO NORMAL");
	
	//camera zoom
	
	hSlider* sliderZoom1 = gui->addSlider("slider1", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 100);
	hLabel * zoomLabel1 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "ZOOM");
	sliderZoom1->setFloatVar(&eyeCamZoom);
	sliderZoom1->setRange(-500, 800);
	
	//shader multiply
	
	hSlider* sliderMultiplier1 = gui->addSlider("slider2", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0, 100);
	hLabel * multiplierLabel1 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "VERTEX MULTIPLIER");
	sliderMultiplier1->setRange(-500, 500);
	sliderMultiplier1->setFloatVar(&shaderMultiply);
	
	//vertex displace effects 1-4
	
	hSlider* sliderVertex1 = gui->addSlider("sliderVertex1", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0, 100);
	hLabel * vertexLabel1 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "VERTEX TRANSLATE 1");
	sliderVertex1->setFloatVar(&effectsTranslate1);
	
	hSlider* sliderVertex2 = gui->addSlider("sliderVertex2", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0, 100);
	hLabel * vertexLabel2 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "VERTEX TRANSLATE 2");
	sliderVertex2->setFloatVar(&effectsTranslate2);

	hSlider* sliderVertex3 = gui->addSlider("sliderVertex3", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0, 100);
	hLabel * vertexLabel3 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "VERTEX TRANSLATE 3");
	sliderVertex3->setFloatVar(&effectsTranslate3);

	hSlider* sliderVertex4 = gui->addSlider("sliderVertex4", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0, 100);
	hLabel * vertexLabel4 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "VERTEX TRANSLATE 4");
	sliderVertex4->setFloatVar(&effectsTranslate4);

	//effects checkbox
	
	hCheckBox * checkEffects1 = gui->addCheckBox("effects1", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
	hLabel * effectsLabel1 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 1");
	checkEffects1->setBoolVar(&enableEffects1);
	//checkEffects1->setBackgroundColor(0x000000);
	
	hCheckBox * checkEffects2 = gui->addCheckBox("effects2", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
	hLabel * effectsLabel2 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 2");
	checkEffects2->setBoolVar(&enableEffects2);
	//checkEffects2->setBackgroundColor(0x000000);

	hCheckBox * checkEffects3 = gui->addCheckBox("effects3", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
	hLabel * effectsLabel3 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 3");
	checkEffects3->setBoolVar(&enableEffects3);
	//checkEffects3->setBackgroundColor(0x000000);

	hCheckBox * checkEffects4 = gui->addCheckBox("effects4", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
	hLabel * effectsLabel4 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 4");
	checkEffects4->setBoolVar(&enableEffects4);
	//checkEffects4->setBackgroundColor(0x000000);
	//checkEffects4->setColor(0xFFFFFF);
	
	//adapt panel depend on content
	
	mainPanel->adaptPanelSize(gui->margin2, gui->margin2);

	
	hEvents * events = hEvents::getInstance();
	events->setup();
	events->addObject("testApp", this);
	
	//load settings
	gui->loadSettings("settings.xml");
	
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
	
	if (eyeCamZoom != eyeCamZoomPrev) {
		windowCamera.setDistance(eyeCamZoom);
		eyeCamZoomPrev = eyeCamZoom;
	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	

	
			windowCamera.begin();
		
			glPushMatrix();
			//unflip the camera
			//glScalef(1.0, -1.0, 1.0);
			glScalef(4.0, -3.0, 1);
	
			fuxShader.begin();
			
			fuxShader.setUniform1f("eyeMultiply", shaderMultiply);
			fuxShader.setUniformTexture("eyeTexDepth", eyeCam.getTextureReference(), 0);
	
			if	(enableEffects1)
			{
				glPushMatrix();
					glTranslatef(0, 0, effectsTranslate1);
					gridCam.draw(GL_LINES);
				glPopMatrix();
			}

			if	(enableEffects2)
			{
				glPushMatrix();
					glTranslatef(0, 0, effectsTranslate2);
						glPushAttrib(GL_POLYGON_BIT);
							glFrontFace(GL_CW);
							glPointSize(2.5f);
							gridCam.drawDisplayList(GL_POINTS);
						glPopAttrib();
				glPopMatrix();
			}
	
			
			if	(enableEffects3)
			{
				glPushMatrix();
					glTranslatef(0, 0, effectsTranslate3);
						glPushAttrib(GL_POLYGON_BIT);
							 glFrontFace(GL_CW);
							 glPolygonMode(GL_FRONT, GL_LINE);
							 glPolygonMode(GL_BACK, GL_LINE);
							 gridCam.drawDisplayList(GL_TRIANGLE_STRIP);
						glPopAttrib();
				glPopMatrix();
			}
			
			if	(enableEffects4)
			{
				glPushMatrix();
					glTranslatef(0, 0, effectsTranslate4);
						glPushAttrib(GL_POLYGON_BIT);
								glPointSize(5.f);
								gridCam.drawDisplayList(GL_POINTS);
						glPopAttrib();	
				glPopMatrix();
			}


			glPopMatrix();
		
			fuxShader.end();


		windowCamera.end();
	
	
		if (enableGui == true) {
			ofDisableBlendMode();
		hGui * gui = hGui::getInstance();
		gui->draw();
			ofEnableBlendMode(OF_BLENDMODE_ADD);
		}	
	

	
	
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
		case 103:
			enableGui = !enableGui;
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
	hGui * gui = hGui::getInstance();
	gui->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	hGui * gui = hGui::getInstance();
	gui->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	hGui * gui = hGui::getInstance();
	gui->mouseReleased(x, y, button);

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

void testApp::exit()
{
	hGui * gui = hGui::getInstance();
	gui->saveSettings("settings.xml"); // You can of course call that elsewhere
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
