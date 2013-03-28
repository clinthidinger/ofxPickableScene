
#include "ofxViewportCam.h"



//----------------------------------------
ofxViewportCam::ofxViewportCam()
{
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
   ofVec2f mousePosScreen = ofVec3f(ofGetMouseX() - viewport.width/2 - viewport.x, viewport.height/2 - (ofGetMouseY() - viewport.y), 0);

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
void ofxViewportCam::tumble(float yaw, float pitch)
{
    const float tumbleAmount = 0.25f;
    this->tiltAmount += pitch * tumbleAmount;
    this->panAmount += yaw * tumbleAmount;
    
    const ofVec3f targetPos(target.getGlobalPosition());
    
    // Reset transform to identity.
    setOrientation(ofQuaternion(0, 0, 0, 1));
    setPosition(targetPos);
    
    // Apply tumble.
    pan(this->panAmount);
    tilt(this->tiltAmount);
    
    // Re-apply pre-existing track and zoom.
    dolly(this->distance);
    truck(this->truckAmount);
    boom(this->boomAmount);
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
    this->distance += delta;
    dolly(delta);
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
    target.setPosition(0.0f, 0.0f, 0.0f);
    
    drawWireFrame = true;
    this->distance = 100.0f;
    this->truckAmount = 0.0f;
    this->boomAmount = 0.0f;
    this->tiltAmount = 0.0f;
    this->panAmount = 0.0f;
    setPosition(0.0f, 0.0f, 0.0f);
    move(0.0f, 0.0f, this->distance);
}
