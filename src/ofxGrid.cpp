
#include "ofxGrid.h"

//--------------------------------------------------------------
void ofxGrid::draw()
{
    ofPushStyle();
    ofDisableLighting();
    //ofEnableSmoothing();
    int xSize = static_cast<int>(this->size.x);
    int zSize = static_cast<int>(this->size.z);
    const int xMax = xSize + this->spacing;
    const int zMax = zSize + this->spacing;
    ofPushMatrix();
    ofTranslate(this->offset);

    // Draw central glid lines first.
    ofPushStyle();
    ofSetLineWidth(3);
    ofSetColor(0.0f, 0.0f, 0.0f);
    ofLine(0, 0, -zSize, 0, 0, zSize);
    ofLine(xSize, 0, 0, -xSize, 0, 0);
    ofPopStyle();

    ofSetColor(this->color);

    for (int xVal = -xSize; xVal < xMax; xVal += this->spacing)
    {
        if (xVal == 0)
        {
            continue;
        }
        ofLine(xVal, 0, -zSize, xVal, 0, zSize);
        for (int zVal = -zSize; zVal < zMax; zVal += this->spacing)
        {
            if (zVal == 0)
            {
                continue;
            }
            ofLine(xSize, 0, zVal, -xSize, 0, zVal);
        }// end for each z dir line
    }// end for each x dir line

    ofPopMatrix();
    ofPopStyle();
}