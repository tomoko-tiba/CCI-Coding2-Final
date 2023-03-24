#include "CellChild.h"
#include "ofMain.h"

CellChild::CellChild() {
    pos = ofVec2f(0, 0);
    acc = ofVec2f(0, 0);
    spd = ofVec2f(0, 0);
    target = pos;
    triggerTime = 0;
    w = 0;
    wT = 0;
    currentTime = 0;
    triggerTime = 0;
    changingW = false;
}

CellChild::CellChild(float x, float y, int _triggerTime) {
    pos = ofVec2f(x, y);
    acc = ofVec2f(0, 0);
    spd = ofVec2f(0, 0);
    target = pos;
    triggerTime = _triggerTime;
    w = 0;
    wT = 0;
    currentTime = 0;
    triggerTime = 0;
    changingW = false;
}

void CellChild::display() {

    ofSetColor(255);

    //基于中心点画矩形
    int rectLeft = pos.x - w / 2;  // 矩形左上角x坐标
    int rectTop = pos.y - w / 2;  // 矩形左上角y坐标
    ofDrawCircle(rectLeft, rectTop, w);
}