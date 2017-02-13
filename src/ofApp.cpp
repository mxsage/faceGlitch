#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableDepthTest();


    if (SYPHON){
        /* Setup Syphon */
        individualTextureSyphonServer.setName("Texture Output");
        mClient.setup();
        //using Syphon app Simple Server, found at http://syphon.v002.info/
        mClient.set("","Simple Server");
    }
    
    /* load files */
    color_offset.load("shaders/glitch_1");
    pixel_shit.load("shaders/pixel_shit");
    loadImages();
    
    ofFbo::Settings s;
    s.width             = ofGetWidth();
    s.height			= ofGetHeight();
    s.internalformat    = GL_RGBA32F_ARB;
    s.useDepth			= false;
    fbo.allocate(s);
    screen.allocate(s);
    
    fbo.begin();
    ofBackground(0, 0, 255);
    fbo.end();
    
    screen.begin();
    ofBackground(0, 0, 255);
    screen.end();
    
    p.allocate(s.width, s.height, OF_IMAGE_COLOR);
    
    index = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetFrameNum() % 60 > 50){
        ofEnableAlphaBlending();
        fbo.begin();
        //images[index]->draw(0,0);
        color_offset.begin();
        color_offset.setUniform1f("random",
                                      ofRandom(1));
        color_offset.setUniform1i("time", ofGetFrameNum());
        
        
        for (int i = 0; i < ITERATIONS; i++){
            float x, y;

            x = ofRandom(ofGetWidth()) - (SLICE_RANGE / 2.0);
            y = ofRandom(SLICE_RANGE);
            images[index]->drawSubsection(x, 0, y, ofGetHeight(), x, 0);
            
            index++;
            index %= images.size();
        }
        color_offset.end();
        fbo.end();
    }
    
    screen.begin();
    color_offset.begin();
    color_offset.setUniform1f("random", ofRandom(1));
    color_offset.setUniform1i("time", ofGetFrameNum());
    fbo.draw(0, 0);
    color_offset.end();
    screen.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    screen.draw(0,0);
    if (SYPHON){
        individualTextureSyphonServer.publishTexture(&screen.getTexture());
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::loadImages(void){
    //some path, may be absolute or relative to bin/data
    string path = "./faces";
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("jpg");
    //populate the directory object
    dir.listDir();
    
    //go through and print out all the paths
    for(int i = 0; i < Max((int) dir.size(), MAX_IMAGES); i++){
        ofImage* img = new ofImage();
        img->load(dir.getPath(i));
        //img->resize(ofGetWidth(), ofGetHeight());
        images.push_back(img);
        cout << "loading: " + ofToString(dir.getPath(i)) << endl;
    }
    cout << ofToString(images.size()) + " images loaded." << endl;
    ofSetWindowShape(images[0]->getWidth(), images[0]->getHeight());
}

