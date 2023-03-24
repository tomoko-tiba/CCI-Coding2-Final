#pragma once
#include "ofMain.h"
#include "Cell.h"
#include "CellChild.h"
#include <vector>
#include "maximilian.h"
#include <ofxMaxim.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void attachPtn(ofImage img);
		void resetPtn();
		//void audioOut(float* output, int bufferSize, int nChannels);
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

		ofImage imageBili, imageGit, imageText;
		ofPixels pixels;

		int width = 1200;
		int height = 1200;

		vector<vector<Cell>> cells;
		vector<vector<CellChild>> childCells;
		int cols, rows;
		float cellSize;

		//音乐
		ofSoundStream soundStream;
		void audioOut(ofSoundBuffer &output) override;
		maxiOsc osc, osc2;
		double phase; // 用于控制音高
		double freq; // 频率变量
		double amp; // 音量变量

		//display mode
		int currCellMode = 0; //0 rect; 1 circle;

		//font
		ofTrueTypeFont myfont;

};


