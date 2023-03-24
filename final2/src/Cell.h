#pragma once
#include "ofMain.h"
#include <vector>

class Cell
{
    public:
        void resetWT(float _wT);

        void runAway(ofVec2f mousePos);

        void update();

        void display();

        ofVec2f pos;
        ofVec2f acc;
        ofVec2f spd;
        ofVec2f target;
        float w, wT;
        int currentTime, triggerTime;
        bool changingW;

        Cell();
        Cell(float x, float y, int _triggerTime);
};

