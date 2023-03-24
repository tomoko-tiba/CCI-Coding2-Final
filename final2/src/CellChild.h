#pragma once
#include "Cell.h"
#include "ofMain.h"

class CellChild : public Cell{
    public:
        void display();
        CellChild();
        CellChild(float x, float y, int _triggerTime);
};

