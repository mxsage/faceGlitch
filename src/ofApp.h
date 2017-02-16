#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxThreadedImageLoader.h"

#define ITERATIONS 40
#define SLICE_RANGE 420
#define WIDTH 1920
#define HEIGHT 1080
#define MAX_IMAGES 20
#define SYPHON 1

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void loadImages(void);
    
        ofFbo fbo, pong, final; // with alpha
        std::vector<ofImage*> images;
        int index;
    
        ofShader color_offset, pixel_shit;
    
    	ofxSyphonServer individualTextureSyphonServer;
        ofxSyphonClient mClient;
    
        template<typename T>
        T const& Max(T const& a, T const& b);

        };

template <typename T>
inline T const& ofApp::Max(T const& a, T const& b){return a < b? a : b;}
