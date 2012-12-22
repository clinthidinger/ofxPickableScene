
#pragma once

#include <ofColor.h>
#include <ofLight.h>
#include <ofVec3f.h>

//! @brief Grid for a scene.
class ofxGrid
{
public:

   //! @brief Constructor.
   ofxGrid(ofColor inColor, ofVec3f inOffset, ofVec3f inSize, float inSpacing)
      : color(inColor),
        offset(inOffset),
        size(inSize),
        spacing(inSpacing)
   {
   }
    
   //! @brief Draw the grid.
    inline void draw()
    {
        ofPushStyle();
        ofDisableLighting();
        ofSetColor(this->color);
        int xSize = static_cast<int>(this->size.x);
        int zSize = static_cast<int>(this->size.z);
        const int xMax = xSize + this->spacing;
        const int zMax = zSize + this->spacing;
        ofPushMatrix();
        ofTranslate(this->offset);
        for (int xVal = -xSize; xVal < xMax; xVal += this->spacing)
        {
            if (xVal == 0)
            {
                ofSetLineWidth(3);
                ofSetColor(0.0, 0.0, 0.0);
            }
            ofLine(xVal, 0, -zSize, xVal, 0, zSize);
            if (xVal == 0)
            {
                ofSetLineWidth(1);
                ofSetColor(this->color);
            }
            for (int zVal = -zSize; zVal < zMax; zVal += this->spacing)
            {
                if (zVal == 0)
                {
                    ofSetLineWidth(3);
                    ofSetColor(0.0f, 0.0f, 0.0f);
                }
                ofLine(xSize, 0, zVal, -xSize, 0, zVal);
                if (zVal == 0)
                {
                    ofSetLineWidth(1);
                    ofSetColor(this->color);
                }
            }// end for each z dir line
            ofPopMatrix();
            ofPopStyle();
        }// end for each x dir line
    }
    
    //! @brief Get the grid color.
    //! @reurn The grid color.
    inline const ofColor &getColor() const { return this->color; }
    
    //! @brief Get the grid offset.
    //! @return The grid offset.
    inline const ofVec3f &getOffset() const { return this->offset; }
    
    //! @brief Get the grid size.
    //! @return The grid size.
    inline const ofVec3f &getSize() const { return this->size; }
    
    //! @brief Get the grid spacing.
    //! @return The grid spacing.
    inline const float &getSpacing() const { return this->spacing; }
    
private:
   // @brief Color of the grid lines.
    ofColor color;
    
    //! @brief Offset of the whole grid.
    ofVec3f offset;
    
    //! @brief Size of x, y, and z dimensions of the grid.
    ofVec3f size;

    //! @brief Spacing between the lines of the grid.
    float spacing;
};

