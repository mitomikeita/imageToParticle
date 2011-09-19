#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

class testApp : public ofBaseApp{
private:
    int test;
    
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
    void imageDraw2(int size, ofImage img);
	void setTest(int setTest);
	int getTest();
	
    
    
	ofImage img;
	ofImage img_nature;
	bool mouse_pressed;
	bool mouse_img_inside;
	
	bool firstTime;
	int w;
	int h;
	unsigned char * pixels;
	
	float gravity;
	float friction;
	vector<float> loc_x_forCenter;
	vector<float> loc_y_forCenter;
	
	vector<float> loc_x;
	vector<float> loc_y;
	vector<float> loc_original_x;
	vector<float> loc_original_y;
	vector<float> speed_x;
	vector<float> speed_y;
	vector<float> circle_size_R;
	vector<float> circle_size_G;
	vector<float> circle_size_B;
	
    
};

#endif
