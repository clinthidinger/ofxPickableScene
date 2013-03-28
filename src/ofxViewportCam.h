
#pragma once

#include <ofRectangle.h>
#include <ofVec3f.h>
#include <ofCamera.h>
#include <ofEasyCam.h>

//! @brief A camera for navigating a scene.
class ofxViewportCam : public ofCamera
{
public:
   //! @brief Constructor.
    ofxViewportCam();

    //! @brief Override of the begin to set up the camera.
    virtual void begin(ofRectangle viewport);
    
    //! @brief Set the camera target position.
    //! @param pos The target position.
    inline void setTargetPosition(const ofVec3f &pos) { this->target.setPosition(pos); }

    //! @brief Tumble (dolly) the camera.
    void tumble(float yaw, float pitch);

    //! @brief Track (pan) the camera.
    void track(float deltaX, float deltaY);

    //! @brief Zoom the camera.
    //! @param delte The amount to zoom.
    void zoom(float delta);

    //! @brief Frame a bounding box (possibly belonging to a scene object).
    //! @param minCorner Minimum corner of the bounding box.
    //! @param maxCorner Maximum corner of the bounding box.
    void frameBoundingBox(const ofVec3f &minCorner, const ofVec3f &maxCorner);

    //! @brief Reset the camera.
    void reset();
    
protected:
   //! @brief Previous mouse screen position.
	ofVec3f mousePosScreenPrev;

   //! @brief Whether to draw wire frame. ???
    bool drawWireFrame;

    //! @brief Camera target.
    ofNode target;

    //! @brief Camera distance.
    float distance;

    //! @brief Camera truck amount.
    float truckAmount;

    //! @brief Camera boom amount.
    float boomAmount;

    //! @brief Camera tilt amount.
    float tiltAmount;

    //! @brief Camera pan amount.
    float panAmount;
}; // end class ofViewportCamera
