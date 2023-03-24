#include "Cell.h"
#include "ofMain.h"

Cell::Cell() {
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

Cell::Cell(float x, float y, int _triggerTime) {
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

void Cell::resetWT(float _wT) {
    wT = _wT;
    currentTime = 0;
    changingW = false;
}

void Cell::runAway(ofVec2f mousePos) {
    //如果和鼠标的距离小于阈值，转身逃跑
    if (mousePos.distance(pos) < 100) {
        acc = pos - mousePos;
        acc *= 0.2;
        spd += acc;
        pos += spd;
    }
}

void Cell::update() {

    acc = target - pos;
    acc *= 0.01;
    spd += acc;
    pos += spd;
    spd *= 0.6;

    if (currentTime >= triggerTime) {
        changingW = true;
    }
    else {
        currentTime++;
    }

    if (changingW) w = ofLerp(w, wT, .025);
}

void Cell::display() {

    ofSetColor(255);

    //基于中心点画矩形
    int rectLeft = pos.x - w / 2;  // 矩形左上角x坐标
    int rectTop = pos.y - w / 2;  // 矩形左上角y坐标
    ofDrawRectangle(rectLeft, rectTop, w, w);

    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(rectLeft, rectTop, w, w);
    ofFill();
}

