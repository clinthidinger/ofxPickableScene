
#include "ofxViewportCam.h"


//----------------------------------------
ofxViewportCam::ofxViewportCam()
    : isTargetSet(false),
      drawWireFrame(true),
      distance(100.0f),
      truckAmount(0.0f),
      boomAmount(0.0f),
      tiltAmount(0.0f),
      panAmount(0.0f)
{
    target.setPosition(0.0f, 0.0f, 0.0f);
    setPosition(0.0f, 0.0f, 0.0f);
    move(0.0f, 0.0f, this->distance);
    reset();
}

//----------------------------------------
void ofxViewportCam::begin(ofRectangle viewport)
{
    ofPushStyle();
    if(drawWireFrame)
    {
        ofNoFill();
    }
    else
    {
        ofFill();
    }
    
    ofVec3f pos = getPosition();
    ofVec2f mousePosScreen = ofVec3f(ofGetMouseX() - viewport.width / 2 - viewport.x, viewport.height / 2 - (ofGetMouseY() - viewport.y), 0);
    
#ifdef TARGET_LINUX
    if(ofGetKeyPressed(OF_KEY_SHIFT))
#else
    if(ofGetKeyPressed(OF_KEY_ALT))
#endif
    {
        ofVec2f trans(mousePosScreenPrev - mousePosScreen);
        if(ofGetMousePressed(0))
        {
            tumble(trans.x, -trans.y);
        }
        else if(ofGetMousePressed(1))
        {
            track(trans.x, trans.y);
        }
        else if(ofGetMousePressed(2))
        {
            float zoomAmount = trans.y;
            zoom(zoomAmount);
        }
    }
    
    mousePosScreenPrev = mousePosScreen;
    ofCamera::begin(viewport);
    
    ofPopStyle();
}

//----------------------------------------
void ofxViewportCam::setTargetPosition(const ofVec3f &pos)
{
	this->target.setPosition(pos);
	this->isTargetSet = true;

    // Move to tumble point.
    const ofVec3f targetPos(target.getGlobalPosition());
    setPosition(targetPos);

    // Reset orientation to identity.
    setOrientation(ofQuaternion(0, 0, 0, 1));

    // Apply tumble.
    pan(this->panAmount);
    tilt(this->tiltAmount);

    // Re-apply pre-existing track and zoom.
    dolly(this->distance);
    truck(this->truckAmount);
    boom(this->boomAmount);
}

//----------------------------------------
void ofxViewportCam::tumble(float yaw, float pitch)
{
    const float tumbleAmount = 0.25f;
    this->tiltAmount += pitch * tumbleAmount;
    this->panAmount += yaw * tumbleAmount;
        
    if(this->isTargetSet)
    {
        // Move to tumble point.
        const ofVec3f targetPos(target.getGlobalPosition());
        setPosition(targetPos);

        // Reset orientation to identity.
        setOrientation(ofQuaternion(0, 0, 0, 1));

        // Apply tumble.
        pan(this->panAmount);
        tilt(this->tiltAmount);

        // Re-apply pre-existing track and zoom.
        dolly(this->distance);
        truck(this->truckAmount);
        boom(this->boomAmount);
    }
    else
    {
        // Move to tumble point.
        dolly(-this->distance);

        // Reset orientation to identity.
        setOrientation(ofQuaternion(0, 0, 0, 1));

        // Apply tumble.
        pan(this->panAmount);
        tilt(this->tiltAmount);

        // Move back.
        dolly(this->distance);
    }
}

//----------------------------------------
void ofxViewportCam::track(float deltaX, float deltaY)
{
    truck(deltaX);
    boom(deltaY);
    this->truckAmount += deltaX;
    this->boomAmount += deltaY;
    
}

//----------------------------------------
void ofxViewportCam::zoom(float delta)
{
    this->distance -= delta;
    dolly(-delta);
}

//----------------------------------------
void ofxViewportCam::frameBoundingBox(const ofVec3f &minCorner,
                                     const ofVec3f &maxCorner)
{
    ofVec3f center((minCorner + maxCorner) * 0.5f);
    setTargetPosition(center);
    this->distance = minCorner.distance(maxCorner);
    
    setPosition(target.getGlobalPosition());
    dolly(this->distance);
}

//----------------------------------------
void ofxViewportCam::reset()
{
    reset(ofVec3f(0.0f, 0.0f, 100.0f), ofVec3f::zero());
}

//----------------------------------------
void ofxViewportCam::reset(ofVec3f translation, ofVec3f orientation)
{
    this->distance    = translation.z;  
    this->truckAmount = translation.x; 
    this->boomAmount  = translation.y;      
    //this->tiltAmount  = orientation.x; 
    //this->panAmount   = orientation.y;  
    setOrientation(orientation);
    if(this->isTargetSet)
    {
        setPosition(target.getGlobalPosition());
    }
    else
    {
        setPosition(0.0f, 0.0f, 0.0f);
    }
    //pan(this->panAmount);
    //tilt(this->tiltAmount);
    //dolly(this->distance);
    this->move(translation);
    //truck(this->truckAmount);
    //boom(this->boomAmount);
}

//----------------------------------------
void ofxViewportCam::clearTargetPosition() 
{ 
    this->target.setPosition(0.0f, 0.0f, 0.0f);
    this->isTargetSet = false;
}



