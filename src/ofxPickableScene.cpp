
#include <map>
#include <assert.h>
#include <ofLight.h>

#include "ofxPickableScene.h"



//-----------------------------------------------------------------------------
ofxPickableScene::ofxPickableScene()
   : pickPixelSize(4)
{
    int bufferSize = this->pickPixelSize * this->pickPixelSize * CHANNEL_COUNT;
    glGenBuffers(1, pboId);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboId[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, bufferSize, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}

//-----------------------------------------------------------------------------
ofxPickableScene::~ofxPickableScene()
{
    glDeleteBuffers(1, pboId);
}

//-----------------------------------------------------------------------------
bool ofxPickableScene::add(ofxIPickable *pickObj)
{
    if(pickObj == NULL)
    {
        return false;
    }
    
    this->pickableObjects.push_back(pickObj);
    
    return true;
}

//-----------------------------------------------------------------------------
void ofxPickableScene::drawForSelection(unsigned int componentMode)
{
    this->componentMap.clear();
    // @todo culling.
    
    // @note A short is used here so that the r channel can be used for components.
    //       a channel could also be used at some point.
    unsigned short selIdx = 1;
    std::list<ofxIPickable *>::iterator objIter = this->pickableObjects.begin();
    std::list<ofxIPickable *>::iterator objEnd = this->pickableObjects.end();
    for(; objIter != objEnd; ++objIter, ++selIdx)
    {
        ofxIPickable::PickableComponentMap objCompMap;
        ofxIPickable *pickObj = *objIter;
        ofColor selColor(indexToColor(static_cast<ColorIndex>(selIdx)));
        pickObj->setSelectionColor(selColor, objCompMap, componentMode); // @todo Cache if no new objects in scene.
        pickObj->drawForSelection(componentMode);
        pickObj->postSelectionRestore(componentMode);
        this->componentMap.insert(objCompMap.begin(), objCompMap.end());
    }
}

//-----------------------------------------------------------------------------
ofxIPickable *ofxPickableScene::pick(int x, int y, ofCamera &cam, unsigned int mode)
{
    ofxIPickable *selected = NULL;
    y = ofGetViewportHeight() - y;
    assert(y >= 0);
    ofPushStyle();
    ofDisableLighting();
    ofDisableBlendMode();
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DITHER);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glReadBuffer(GL_BACK);
    glDrawBuffer(GL_BACK);
    
    // render scene
    ofRectangle rect = ofGetCurrentViewport();
    cam.begin(rect);
    
    ofClear(0, 0, 0, 0);
    
    drawForSelection(mode);
    
    cam.end();
    
    int halfPickPixelSize = this->pickPixelSize * 0.5;
    int numPixels = this->pickPixelSize * this->pickPixelSize;
    
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboId[0]);
    glReadPixels(x - (halfPickPixelSize), y - (/*pickPixelSize +*/ halfPickPixelSize), this->pickPixelSize, this->pickPixelSize, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboId[0]);
    GLubyte *pixelBuffer = (GLubyte *)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    if (pixelBuffer != NULL)
    {
        // Use a voting technique to see who the winner is.
        int numBytes = numPixels * CHANNEL_COUNT;
        std::map<int, int> voteCount;  
        int winner = 0;
        int winningCount = -1;
        for(unsigned int byteIdx = 0; byteIdx < numBytes; byteIdx += CHANNEL_COUNT)
        {
            int colorNumber = ((int)pixelBuffer[byteIdx + 0]) | ((int)pixelBuffer[byteIdx + 1] << 8) |
            ((int)pixelBuffer[byteIdx + 2] << 16);// | ((int)pixelBuffer[byteIdx +3] << 24);
            if (colorNumber != 0)
            {
                if(voteCount.find(colorNumber) == voteCount.end())
                {
                    voteCount[colorNumber] = 1;
                }
                else
                {
                    voteCount[colorNumber]++;
                }
                if(voteCount[colorNumber] > winningCount)
                {
                    winningCount = voteCount[colorNumber];
                    winner = colorNumber;
                }
            }
        }// end for
        
        if(winner != 0)
        {
            ofColor winningColor(indexToColor(winner));
            ofxIPickable::PickableComponentMap::iterator iter = this->componentMap.find(colorToIndex(winningColor));
            if(iter != this->componentMap.end())
            {
                selected = iter->second;
            }
        }
        
//#define DEBUG_PICKING 1
#ifdef DEBUG_PICKING
        y = ofGetViewportHeight() - y;
        float scaleFactor = 10.0f;
        for(unsigned int byteIdx = 0; byteIdx < numBytes; ++byteIdx)
        {
            //pixelBuffer[byteIdx] ^= 0xFF;
            if(pixelBuffer[byteIdx] == 0x00)
            {
                pixelBuffer[byteIdx] = 0xFF;
            }
        }
        float zoom = 10.0f;
        glRasterPos2f(x - ((halfPickPixelSize) * zoom), y + ((halfPickPixelSize) * zoom));
        glPixelZoom(zoom, zoom);
        glDrawPixels(this->pickPixelSize, this->pickPixelSize, GL_BGRA,  GL_UNSIGNED_BYTE, pixelBuffer);
#endif
        
        glUnmapBuffer(GL_PIXEL_PACK_BUFFER);     // release pointer to the mapped buffer
    }// end if
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DITHER);
    glEnable(GL_COLOR_MATERIAL);
    ofPopStyle();
    
    return selected;
}


