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
	
	
	// DEFAULT / GLOBAL / GUI SETTINGS
	
		gui->setBorderColor(0x20bfe9);
		gui->setTextColor(0x20bfe9);
		gui->setCheckBoxColor(0xc0e0e9);
		gui->setSliderColor(0xc0e0e9);
		gui->setTabBoxSelColor(0xCCCCCC);	
		
		gui->setBackgroundColor	(0x333333);
		gui->setBorderColor		(0x000000);
		gui->setFillColor		(0x555555);
		gui->setAltFillColor	(0x557766);
		gui->setButtonShadowColor(0x999999);
		
		gui->setScrollHandleColor(0xDDDDDD);
		gui->setScrollButtonColor(0xDDDDDD);
		gui->setTextColor		(0xFFFFFF);
		gui->setTextColor2		(0x000000);
		gui->setAlertTextColor	(0xCCCCCC);
		
		gui->setDisableColor	(0x999999);
		gui->setEditTextColor	(0x113388);
		gui->setEditTextColor2	(0x113388);
		gui->setEditBackColor	(0xCCDDEE);
		gui->setCaretColor		(0x000000);
		
		gui->setLabelSelColor	(0xBBBBFF);
		gui->setItemSelColor	(0xBBBBBB);
		gui->setItemSelTextColor(0x333333);
		gui->setButtonBoxSelColor(0x44CC77);
		
		gui->setCheckBoxColor	(0x44CC77);
		gui->setSliderColor		(0x999999);
		gui->setTwoDSliderColor	(0x33BB66);
		gui->setCounterColor	(0x33BB66);
		
		gui->setDialogColor		(0xE5E5E5);
		gui->setMessageBoxColor	(0x77FFAA);
		gui->setAlertColor		(0xFF7777);
	
	//INITIATE MAIN PANEL
	
		hPanel * mainPanel = gui->addPanel("mainPanel", NULL, HGUI_ABSOLUTE_POSITION, gui->margin1, gui->margin1+gui->margin3+gui->margin1, 250, 0, false);
		mainPanel->setVisibleBackground(false);
		mainPanel->setBackgroundColor(0x000000);

		hPanel * mainPanel1 = gui->addPanel("mainPanel1", NULL, HGUI_ABSOLUTE_POSITION, gui->margin1, gui->margin1+gui->margin3+gui->margin1, 250, 0, false);
		mainPanel1->setVisibleBackground(false);
		mainPanel1->setBackgroundColor(0x000000);
	
	//INITIATE SUBPANEL FOR MAINPANEL
	
		//int panelSize1 = 200;
		//hPanel * subPanel = gui->addPanel("subPanel", mainPanel, HGUI_NEXT_ROW, gui->margin1, gui->margin1+gui->margin3+gui->margin1, panelSize1, panelSize1, true);
		//hPanel * subPanel1 = gui->addPanel("subPanel1", mainPanel, HGUI_NEXT_ROW, gui->margin1, gui->margin2, panelSize1, panelSize1, true);
	
	
	//BEGIN GUI FOR MAIN PANEL / VIDEO EFFECTS
	
		hLabel * sliderLabelInfo1 = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,  gui->margin2,  gui->margin2+gui->margin2+gui->margin2, "/// GPUFUXETTRA VIDEO EFFECTS");
		//hLabel * sliderLabelInfo2 = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,  gui->margin2,  gui->margin2, "PRESS F TO FULLSCREEN N TO NORMAL");
		
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

		//VIDEO / VISUAL effects checkbox
		
		hLabel * effectsLabelInfo = gui->addLabel("", mainPanel, HGUI_NEXT_ROW,  gui->margin2,  gui->margin2+gui->margin2, "/// EFFECTS TOGGLE");

		hCheckBox * checkEffects1 = gui->addCheckBox("effects1", mainPanel, HGUI_NEXT_ROW, gui->margin2, gui->margin2);
		hLabel * effectsLabel1 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 1");
		checkEffects1->setBoolVar(&enableEffects1);
		
		hCheckBox * checkEffects2 = gui->addCheckBox("effects2", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
		hLabel * effectsLabel2 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 2");
		checkEffects2->setBoolVar(&enableEffects2);

		hCheckBox * checkEffects3 = gui->addCheckBox("effects3", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
		hLabel * effectsLabel3 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 3");
		checkEffects3->setBoolVar(&enableEffects3);

		hCheckBox * checkEffects4 = gui->addCheckBox("effects4", mainPanel, HGUI_NEXT_ROW, gui->margin2, 0);
		hLabel * effectsLabel4 = gui->addLabel("", mainPanel, HGUI_RIGHT,  gui->margin2,  0, "EFFECTS 4");
		checkEffects4->setBoolVar(&enableEffects4);
	
		//adapt panel depend on content
		mainPanel->adaptPanelSize(gui->margin2, gui->margin2);

	//BEGIN GUI FOR AUDIO EFFECTS // mainPanel1
	
		hLabel * sliderLabelAudioInfo1 = gui->addLabel("", mainPanel1, HGUI_NEXT_ROW,  gui->margin2,  gui->margin2+gui->margin2+gui->margin2, "/// GPUFUXETTRA AUDIO EFFECTS");

		hSlider* sliderAudio1 = gui->addSlider("audio1", mainPanel1, HGUI_NEXT_ROW, gui->margin2, gui->margin2, 100);
		hLabel * audioLabel1 = gui->addLabel("", mainPanel1, HGUI_RIGHT,  gui->margin2,  0, "Audio 1");

		hSlider* sliderAudio2 = gui->addSlider("audio2", mainPanel1, HGUI_NEXT_ROW, gui->margin2, 0, 100);
		hLabel * audioLabel2 = gui->addLabel("", mainPanel1, HGUI_RIGHT,  gui->margin2,  0, "Audio 2");
	
		hSlider* sliderAudio3 = gui->addSlider("audio3", mainPanel1, HGUI_NEXT_ROW, gui->margin2, 0, 100);
		hLabel * audioLabel3 = gui->addLabel("", mainPanel1, HGUI_RIGHT,  gui->margin2,  0, "Audio 3");
	
		mainPanel1->adaptPanelSize(gui->margin2, gui->margin2);
	
	//GUI TAB MENU
	
		int mainTabBoxWidth = mainPanel->getWidth();
		
		// hTabBox *  hGui::addTabBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
		hTabBox *  mainTabBox = gui->addTabBox("mainTabBox", NULL, HGUI_ABSOLUTE_POSITION, gui->margin1, gui->margin1+gui->margin3, mainTabBoxWidth);
	
		// NULL: the main tabBox has no parent panel
		// HGUI_ABSOLUTE_POSITION : the only possibility for the main tabBox
		// -1: no need to show the upper line
	
		//mainTabBox->setBackgroundColor(0xFFFFFF);
	
		mainTabBox->addItems(2); // Add the needed number of items (tabs) to the tabBox
		// (item numbers start always with #1)
		
		// Set the name of the different tabs
		mainTabBox->setItemLabel(1, "+ VIDEO EFFECTS");
		mainTabBox->setItemLabel(2, "+ AUDIO EFFECTS");
		
		mainTabBox->setItemPanel(1, mainPanel); // Let our main panel to be the fist tab
		mainTabBox->setItemPanel(2, mainPanel1); // Let our main panel to be the fist tab
		
		mainTabBox->selectItem(1);				// and select it
	
	
	gui->setRootWidget(mainTabBox); // Let the gui engine know that now its mainTabBox our root widget
	
	
	
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
	
	#ifndef DONT_USE_ARDUINO
	cout << "rgbvertexnoize 0.1 - load settings then connecting to arduino";
	xmlVertexSettings.loadFile("arduino.xml");
	ard.connect(xmlVertexSettings.getValue("arduino_settings:device:", "/dev/tty.usbmodemfa131"), 57600);
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bArduinoSetup = false;
	#else
	cout << "rgbvertexnoize 0.1 - running without arduino";
	#endif
	
	btnShutdown   = false;
	
	int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
	ofSoundStreamSetup(2, 2, this, 44100, ofxPd::getBlockSize()*ticksPerBuffer, 4);
	pdEngine.setup(2, 2, 44100, ticksPerBuffer);
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	#ifndef DONT_USE_ARDUINO
	ard.update();
	
	effectsTranslate1 = ofMap(ard.getAnalog(0), 0, 1023, -200, 200, false);
	effectsTranslate2 = ofMap(ard.getAnalog(1), 0, 1023, -200, 200, false);
	effectsTranslate3 = ofMap(ard.getAnalog(2), 0, 1023, -200, 200, false);
	effectsTranslate4 = ofMap(ard.getAnalog(3), 0, 1023, -200, 200, false);
	
	eyeCamZoom		  = ofMap(ard.getAnalog(4), 0, 1023, -500, 800, false);
	shaderMultiply    = ofMap(ard.getAnalog(5), 0, 1023, -500, 800, false);
	
	if (ard.getDigital(2) == 1){ enableEffects1 = true; }else{ enableEffects1 = false;};
	if (ard.getDigital(3) == 1){ enableEffects2 = true; }else{ enableEffects2 = false;};
	if (ard.getDigital(4) == 1){ enableEffects3 = true; }else{ enableEffects3 = false;};
	if (ard.getDigital(5) == 1){ enableEffects4 = true; }else{ enableEffects4 = false;};
	
	if	(ard.getDigital(6) == 1)
	{
		OSErr error = SendAppleEventToSystemProcess(kAEShutDown);  
	}
	
	#endif
	
	//sound fx
	
	if (enableEffects1) {
		pdEngine.pd.sendFloat("vertexfx1", effectsTranslate1);	
	}
	
	if (enableEffects2) {
		pdEngine.pd.sendFloat("vertexfx2", effectsTranslate2);	
	}
	
	if (enableEffects3) {
		pdEngine.pd.sendFloat("vertexfx3", effectsTranslate3);	
	}
	
	if (enableEffects4) {
		pdEngine.pd.sendFloat("vertexfx4", effectsTranslate4);	
	}
	
	
	//update webcam picture

	eyeCam.grabFrame();
	
	//zooming function from gui
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


void testApp::audioReceived(float * input, int bufferSize, int nChannels) {
	pdEngine.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::audioRequested(float * output, int bufferSize, int nChannels) {
	pdEngine.audioRequested(output, bufferSize, nChannels);
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


#ifndef DONT_USE_ARDUINO

void testApp::setupArduino(const int & version) {
	
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
	ard.sendAnalogPinReporting(0, ARD_ANALOG);
	ard.sendAnalogPinReporting(1, ARD_ANALOG);
	
	ard.sendDigitalPinMode(2, ARD_INPUT);
	ard.sendDigitalPinMode(3, ARD_INPUT);
	ard.sendDigitalPinMode(4, ARD_INPUT);
	ard.sendDigitalPinMode(5, ARD_INPUT);
	ard.sendDigitalPinMode(6, ARD_INPUT);
	
	bArduinoSetup = true;
}

#endif