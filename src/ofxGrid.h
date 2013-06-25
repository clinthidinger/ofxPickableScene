
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
    void draw();
    
    //! @brief Get the grid color.
    //! @reurn The grid color.
    const ofColor &getColor() const;
    
    //! @brief Get the grid offset.
    //! @return The grid offset.
    const ofVec3f &getOffset() const;
    
    //! @brief Get the grid size.
    //! @return The grid size.
    const ofVec3f &getSize() const;
    
    //! @brief Get the grid spacing.
    //! @return The grid spacing.
    const float &getSpacing() const;
    
    //! @brief Set the color.
    //! @param color The color.
    void setColor(const ofColor &color);
    
    //! @brief Set the grid offset from origin.
    //! @param offset The offset.
    void setOffset(const ofVec3f &offset);
    
    //! @brief Set the grid size.
    //! @param size The size.
    void setSize(const ofVec3f &size);
    
    //! @brief Set the grid spacing between lines.
    //! @param spacing The spacing.
    void setSpacing(const float spacing);

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


inline const ofColor &ofxGrid::getColor() const { return this->color; }

inline const ofVec3f &ofxGrid::getOffset() const { return this->offset; }

inline const ofVec3f &ofxGrid::getSize() const { return this->size; }

inline const float &ofxGrid::getSpacing() const { return this->spacing; }

inline void ofxGrid::setColor(const ofColor &color) { this->color = color; }

inline void ofxGrid::setOffset(const ofVec3f &offset) { this->offset = offset; }

inline void ofxGrid::setSize(const ofVec3f &size) { this->size = size; }

inline void ofxGrid::setSpacing(const float spacing) { this->spacing = spacing; }

