#include "testApp.h"

static const string IMG = "image/060.jpg";


//--------------------------------------------------------------
void testApp::setup(){
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
	
	img.loadImage(IMG);
	img_nature.loadImage(IMG);
	
	img.resize(img.width/50, img.height/50);
	img_nature.resize(img_nature.width/5, img_nature.height/5);
	img.setImageType(OF_IMAGE_COLOR);
	img_nature.setImageType(OF_IMAGE_COLOR);
	
	mouse_pressed  = false;
	mouse_img_inside = false;
	gravity = 0.1; //重力
    friction = 1;  //摩擦
	
    
	// imageの高さと幅を元に、ピクセル数だけスピード、座標、大きさをベクターに格納する
	pixels = img.getPixels();
	w = img.width;
	h = img.height;
	
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++) {
			
			//それぞれのピクセルのRGB情報をcharに格納
			unsigned char r = pixels[(j * w + i) * 3];
			unsigned char g = pixels[(j * w + i) * 3+1];
			unsigned char b = pixels[(j * w + i) * 3+2];
			
			speed_x.push_back(ofRandom(-10, 10)); //x軸方向スピード初期値
			speed_y.push_back(ofRandom(-10, 10)); //y軸方向スピード初期値
			loc_x.push_back(i*10); //円のx座標初期位置
			loc_y.push_back(j*10); //円のy座標初期位置
			loc_original_x.push_back(i*10); //円のx座標初期位置
			loc_original_y.push_back(j*10); //円のy座標初期位置
			circle_size_R.push_back(10.0*(float)r/255.0); //色：Rから演算する円の大きさ
			circle_size_G.push_back(10.0*(float)g/255.0); //色：Gから演算する円の大きさ
			circle_size_B.push_back(10.0*(float)b/255.0); //色：Bから演算する円の大きさ
			//imageを中央に持っていくvectorの初期化
			loc_x_forCenter.push_back(0);
			loc_y_forCenter.push_back(0);
		}
	}
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0,0,0);
	
	// 初期表示（ピクセルがimageを構成）
	
	if (!mouse_pressed) {
		
		for (int i=0; i < w; i++) {
			for (int j=0; j < h; j++) {
				
				//マウスの現在位置から円のスピードを再計算
				speed_x[j+h*i] = (loc_original_x[j+h*i] - loc_x[j+h*i])  / 8.0; //マウスのx座標と円のx座標の距離の1/8だけ接近
				speed_y[j+h*i] = (loc_original_y[j+h*i] - loc_y[j+h*i]) / 8.0;
				
				//　摩擦の計算
				speed_x[j+h*i] = speed_x[j+h*i] * friction;
				speed_y[j+h*i] = speed_y[j+h*i] * friction;
				// 重力の計算
				//speed_y[j+h*i] = speed_y[j+h*i] + gravity;
				
				loc_x[j+h*i] = loc_x[j+h*i] + speed_x[j+h*i]; //円のx座標を更新
				loc_y[j+h*i] = loc_y[j+h*i] + speed_y[j+h*i]; //円のy座標を更新
				
				// imageを画面中央に持っていく処理。現在のpointに、ディスプレイの半分を加算し、構成している最後のピクセルのpointの半分を減算する
				loc_x_forCenter[j+h*i] = loc_x[j+h*i] + (ofGetWidth()/2 - loc_x.back()/2);
				loc_y_forCenter[j+h*i] = loc_y[j+h*i] + (ofGetHeight()/2 - loc_y.back()/2);
			}
		}
	}
	else {
		for (int i=0; i < w; i++) {
			for (int j=0; j < h; j++) {
				
				speed_x[j+h*i] = speed_x[j+h*i] * friction;
				speed_y[j+h*i] = speed_y[j+h*i] * friction;
				//	speed_y[j+h*i] = speed_y[j+h*i] + gravity;
				
				loc_x[j+h*i] = loc_x[j+h*i] + speed_x[j+h*i]; //円のx座標を更新
				loc_y[j+h*i] = loc_y[j+h*i] + speed_y[j+h*i]; //円のy座標を更新
				
				// imageを画面中央に持っていく処理。現在のpointに、ディスプレイの半分を加算し、構成している最後のピクセルのpointの半分を減算する
				loc_x_forCenter[j+h*i] = loc_x[j+h*i] + (ofGetWidth()/2 - loc_x.back()/2);
				loc_y_forCenter[j+h*i] = loc_y[j+h*i] + (ofGetHeight()/2 - loc_y.back()/2);
				
				//円の跳ね返り条件
				if(loc_x_forCenter[j+h*i] - circle_size_R[j+h*i]/2 < 0){
					//loc_x_forCenter = 0;
					speed_x[j+h*i] = speed_x[j+h*i] * -1.0;
				}
				if(loc_x_forCenter[j+h*i] + circle_size_R[j+h*i]/2 > ofGetWidth()){
					//	loc_x_forCenter = ofGetWidth();
					speed_x[j+h*i] = speed_x[j+h*i] * -1.0;
				}
				if(loc_y_forCenter[j+h*i] - circle_size_R[j+h*i]/2 < 0){
					//loc_y_forCenter = 0;
					speed_y[j+h*i] = speed_y[j+h*i] * -1.0;
				}
				if(loc_y_forCenter[j+h*i] + circle_size_R[j+h*i]/2 > ofGetHeight()){
					//loc_y_forCenter = ofGetHeight();
					speed_y[j+h*i] = speed_y[j+h*i] * -1.0;
				}	
			}
		}
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	
	if (!mouse_img_inside) {
        
		img_nature.draw(ofGetWidth()/2 - img_nature.width/2,ofGetHeight()/2 - img_nature.height/2);
	}
	else {
		
        
		if (!mouse_pressed) {
			for (int i=0; i < w; i++) {
				for (int j=0; j < h; j++) {
                    
					if ( ((mouseX - 12) < loc_x_forCenter[j+h*i] && (mouseX + 12) > loc_x_forCenter[j+h*i]) &&
                        ((mouseY - 12) < loc_y_forCenter[j+h*i] && (mouseY + 12) > loc_y_forCenter[j+h*i]) 
						)
					{
						ofSetColor(255, 0, 0, 50);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_R[j+h*i]);
						ofSetColor(0, 255, 0, 50);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_G[j+h*i]);
						ofSetColor(0, 0, 255, 50);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_B[j+h*i]);
                        
					}
					else {
                        
						// ピクセルサークルの描画。それぞれの変数はdraw()内で定義されている
						ofSetColor(255, 0, 0, 100);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_R[j+h*i]);
						ofSetColor(0, 255, 0, 100);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_G[j+h*i]);
						ofSetColor(0, 0, 255, 100);
						ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_B[j+h*i]);
					}
                    
				}
			}
		}
		else {
			for (int i=0; i < w; i++) {
				for (int j=0; j < h; j++) {
                    
					ofSetColor(255, 0, 0, 100);
					ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_R[j+h*i]);
					ofSetColor(0, 255, 0, 100);
					ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_G[j+h*i]);
					ofSetColor(0, 0, 255, 100);
					ofCircle(loc_x_forCenter[j+h*i], loc_y_forCenter[j+h*i], circle_size_B[j+h*i]);
				}
			}
		}
	}
}

// imageを描画する無意味な関数
void testApp::imageDraw2(int size, ofImage img){
	ofSetColor(255, 255, 255);
	int w = size;
	
	img.resize(img.width*size, img.height*size);
	img.draw(0, img.height);
	img.resize(img.width/size, img.height/size);
}
void testApp::setTest(int setTest){
	test = setTest;
}
int testApp::getTest(){
	return test;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}




//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	if ((x >= ofGetWidth()/2 - img_nature.width/2 && x <= ofGetWidth()/2 + img_nature.width/2) &&
        y >= ofGetHeight()/2 - img_nature.height/2 && y <= ofGetHeight()/2 + img_nature.height/2) {
        
		mouse_img_inside = true;
	}
	else if (!mouse_pressed){
		mouse_img_inside = false;
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
	if (mouse_pressed){
		mouse_pressed = false;
	}else if( (x >= ofGetWidth()/2 - img_nature.width/2 && x <= ofGetWidth()/2 + img_nature.width/2) &&
             y >= ofGetHeight()/2 - img_nature.height/2 && y <= ofGetHeight()/2 + img_nature.height/2) {
		mouse_pressed = true;
		
		// speedのinitialize
		for (int i=0; i < w; i++) {
			for (int j=0; j < h; j++) {
				
				speed_x[j+h*i] = ofRandom(-10, 10); //x軸方向スピード初期値
				speed_y[j+h*i] = ofRandom(-10, 10); //y軸方向スピード初期値
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

