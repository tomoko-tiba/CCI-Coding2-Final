#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myfont.load("Anton.ttf", 45);

	imageBili.load("bilibili.jpg");
	imageGit.load("github.jpg");
	imageText.load("bw.png");

	ofSetWindowShape(width, height+80);
	ofBackground(0, 0, 0);

	cols = 50;
	rows = 50;
	cellSize = width * 1.0 / cols;
	cells = vector<vector<Cell>>(rows, vector<Cell>(cols));
	childCells = vector<vector<CellChild>>(rows, vector<CellChild>(cols));

	// 遍历初始化二维动态数组中的每一个Cell
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			float x = ofMap(j, 0, cols - 1, cellSize * .5, width - cellSize * .5);
			float y = ofMap(i, 0, rows - 1, cellSize * .5, height - cellSize * .5);
			float d = ofDist(x, y, width * .5, height * .5);
			int triggerTime = floor(ofNoise(x * .01, y * .01) * 240);
			cells[i][j] = Cell(x, y, triggerTime);
			childCells[i][j] = CellChild(x, y, triggerTime);
		}
	}
	
	int sampleRate = 44100; // Sampling Rate 
    int initialBufferSize = 512; // Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method 
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    ofSoundStreamSettings settings;
    
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = initialBufferSize;
    soundStream.setup(settings);
	
	phase = 0; // 初始化相位
	freq = 0;
	amp = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ofVec2f mousePos = ofVec2f(ofGetMouseX(), ofGetMouseY());
			if (currCellMode == 0) {
				cells[i][j].runAway(mousePos);
				cells[i][j].update();
			}

			if (currCellMode == 1) {
				childCells[i][j].runAway(mousePos);
				childCells[i][j].update();
			}
		}
	}

	ofBackground(0, 0, 0);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (currCellMode == 0) cells[i][j].display();
			if (currCellMode == 1) childCells[i][j].display();
		}
	}

	ofSetColor(255, 255, 255);
	if (currCellMode == 0) myfont.drawString("DISPLAY MODE: RECTANGLE", width*0.25+80, height+60);
	if (currCellMode == 1) myfont.drawString("DISPLAY MODE: DOT", width*0.31+80, height+60);

	myfont.drawString(" [1] [2] [3]", 0, height + 60);
	myfont.drawString("[R]", width*0.93, height + 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1') attachPtn(imageBili);
	else if (key == '2') attachPtn(imageGit);
	else if (key == '3') attachPtn(imageText);
	else if (key == 'r') resetPtn();
}

//--------------------------------------------------------------
void ofApp::attachPtn(ofImage img) {
	pixels = img.getPixels();

	//rectangle mode
	if (currCellMode == 0) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {

				int pxCol = floor(ofMap(j, 0, cols - 1, 0, img.getWidth() - 1));
				int pxRow = floor(ofMap(i, 0, rows - 1, 0, img.getHeight() - 1));
				ofColor pxColor = pixels.getColor(pxCol, pxRow);
				float wT = ofMap(pxColor.getBrightness(), 0, 255, cellSize * 2, cellSize * .1);
				cells[i][j].resetWT(wT);
			}
		}
	} //dot mode
	else {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {

				int pxCol = floor(ofMap(j, 0, cols - 1, 0, img.getWidth() - 1));
				int pxRow = floor(ofMap(i, 0, rows - 1, 0, img.getHeight() - 1));
				ofColor pxColor = pixels.getColor(pxCol, pxRow);
				float wT = ofMap(pxColor.getBrightness(), 0, 255, cellSize * 0.8, cellSize * .02);
				childCells[i][j].resetWT(wT);
			}
		}
	}
}

void ofApp::resetPtn() {

	if (currCellMode == 0) {
		// 缩小方块
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cells[i][j].resetWT(0.1);
			}
		}
		currCellMode = 1;
	}
	else {
		// 缩小圆点
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				childCells[i][j].resetWT(0.1);
			}
		}
		currCellMode = 0;
	}

}

//------------------------------audio--------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
	std::size_t outChannels = output.getNumChannels();

	for (int i = 0; i < output.getNumFrames(); i++) {
		freq = 100 + sin(phase * 0.1) * 50; // 频率随时间变化
		amp = 0.2 + sin(phase * 0.2) * 0.1; // 幅度随时间变化

		double wave = osc.triangle(freq + ofGetMouseX()*0.075) * amp; // 生成三角波形
		output[i * output.getNumChannels()] = wave; // left channel
		output[i * output.getNumChannels() + 1] = wave; // right channel

		phase += 0.05; // 更新相位
	}
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
