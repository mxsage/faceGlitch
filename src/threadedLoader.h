#pragma once

//  threadedLoader.h
//  faceGlitch
//
//  Created by Sage Jenson on 2/24/17.

#include "ofThread.h"

class ThreadedLoader: public ofThread{

public:
    ThreadedLoader() {}
    
    void start(){
        startThread();
    }
    
    
    void stop(){
        stopThread();
    }
    
    void threadedFunction(){
        while (isThreadRunning()){
            if (lock()){
                unlock();
                load_images();
            }
            sleep(1000);
        }
    }
    
    vector<ofImage*> get_pointers(){
        unique_lock<std::mutex> lock(mutex);
        return images;
    }
    
    int get_size(){
        unique_lock<std::mutex> lock(mutex);
        return images.size();
    }
    
protected:
    
    void load_images(void){
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
                ofImage img;
                img.setUseTexture(false);
                img.load(fname);
                img.resize(ofGetWidth(), ofGetHeight());
                
                names.insert(fname);
                images.push_back(&img);
                cout << "Loaded: " + ofToString(fname) + "." << endl;
            }
        }
}
    
    std::vector<ofImage*> images;
    std::set<std::string> names;
    
};