#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(50);
    ofDisableDepthTest();
    
    ofEnableAlphaBlending();


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
    //loadImages();
    
    ofFbo::Settings s;
    s.width             = ofGetWidth();
    s.height			= ofGetHeight();
    s.internalformat    = GL_RGBA32F_ARB;
    s.useDepth			= false;
    s.wrapModeVertical  = GL_MIRRORED_REPEAT_ARB;
    s.wrapModeHorizontal= GL_MIRRORED_REPEAT_ARB;
    
    fbo.allocate(s);
    pong.allocate(s);
    final.allocate(s);
    
    fbo.begin();
    ofBackground(0, 0, 255);
    fbo.end();
    
    pong.begin();
    ofBackground(0, 0, 255);
    pong.end();
    
    index = 0;
    
    /*
    loader.start();
    do {
        updateImages();
    } while (images.size() == 0);
    */
    
    while (not images.size()){
        updateImages();
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetFrameNum() % 300 == 0){
        updateImages();
    }
    
    if (ofGetFrameNum() %  PERIOD == 0){
        if (cycle_count == 0){
            slice_range = 2000;
            slide_offset = (int) ofRandom(HEIGHT);
        }
        else {
            slice_range = 3;
        }
        
        cycle_count = (cycle_count + 1) % CYCLES;
    }
    
    if (ofGetFrameNum() % PERIOD > PERIOD - 10){
        fbo.begin();
        color_offset.begin();
        color_offset.setUniform1f("random", 0.2);
        color_offset.setUniform1i("time", ofGetFrameNum());
        
        
        for (int i = 0; i < ITERATIONS; i++){
            float x, y;

            x = ofRandom(ofGetWidth()) - (slice_range / 2.0);
            y = ofRandom(slice_range);
            images[index]->drawSubsection(x, 0, y, ofGetHeight(), x, 0);
            
            //index++;
            index = (int)ofRandom(images.size());
        }
        color_offset.end();
        fbo.end();
    }
   
    
    pong.begin();
    color_offset.begin();
    color_offset.setUniform1f("random", ofRandom(0.1));
    color_offset.setUniform1i("time", ofGetFrameNum());
    fbo.draw(0, 0);
    color_offset.end();
    pong.end();
    
    final.begin();
    pixel_shit.begin();
    pixel_shit.setUniform1f("random", fmod((ofGetFrameNum()/(slide_offset*10.7)+slide_offset), (float)HEIGHT));
    pong.draw(0,0);
    pixel_shit.end();
    final.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    final.draw(0,0);
    
    if (SYPHON){
        individualTextureSyphonServer.publishTexture(&final.getTexture());
    }
    
}

/*
void ofApp::updateImages(void){
    int new_images = loader.get_size();
    if (new_images > images.size()){
        vector<ofImage*> all_images = loader.get_pointers();
        
        for (int i=images.size(); i<new_images; i++){
            all_images[i]->setUseTexture(true);
            all_images[i]->update();
            images.push_back(all_images[i]);
        }
    }
    cout << images.size() << endl;
}
 */

void ofApp::updateImages(void){
    //some path, may be absolute or relative to bin/data
    string path = "./faces";
    ofDirectory dir(path);
    
    //only show jpg files
    dir.allowExt("jpg");
    //populate the directory object
    dir.listDir();
    
    for(int i = 0; i < dir.size(); i++){
        std::string fname = dir.getPath(i);
        if (names.empty() or names.find(fname) == names.end()){
            ofImage* img = new ofImage();
            img->load(dir.getPath(i));
            img->resize(ofGetWidth(), ofGetHeight());
            
            images.push_back(img);
            names.insert(fname);
            cout << "Loaded: " + ofToString(fname) + "." << endl;
        }
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
    for(int i = 0; i < dir.size(); i++){
        ofImage* img = new ofImage();
        img->load(dir.getPath(i));
        img->resize(ofGetWidth(), ofGetHeight());
        images.push_back(img);
        cout << "loading: " + ofToString(dir.getPath(i)) << endl;
    }
    cout << ofToString(images.size()) + " images loaded." << endl;
}

