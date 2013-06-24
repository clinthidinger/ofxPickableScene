#pragma once

#include <list>
#include <ofCamera.h>
#include "ofxIPickable.h"

//! @brief Implements back buffer selection upgraded with a pixel buffer object (pbo)
//         that allows for direct memory access (dma).
//! @todo Add hardware checks to make sure pbo's are supported.
//! @see http://www.3dkingdoms.com/selection.html (A bit dated, though.)
class ofxPickableScene
{
public:

   //! @brief Constructor.
   ofxPickableScene();

   //! @brief Destructor.
   virtual ~ofxPickableScene();

   //! @brief Add a pickable object.
   //! @param pickObj The pickable object to add.
   bool add(ofxIPickable *pickObj);

   //! @brief Perform picking on the pickable objects that have been added.
   //! @param x Mouse x location.
   //! @param y Mouse y location.
   //! @param cam Current camera.
   //! @param mode Component mode to be passed  to all pickable objects during selection.
   ofxIPickable *pick(int x, int y, ofCamera &cam, unsigned int mode = 0);

   //! @brief Get the pickable objects.
   //! @return The pickable objects.
   const std::list<ofxIPickable *> &getPickableObjects() const;

   //! @brief Clear pickable objects.
   void clearPickableObjects();

   //! @brief Get the pixel size around the cursor used during picking.
   //! @return The pixel size around the cursor used during picking.
   int getPickPixelSize() const;

   //! @brief Set the pixel size around the cursor used during picking.
   //! @param The pixel size around the cursor used during picking.
   void setPickPixelSize(int size);

private:
   //! @brief Number of channels used during picking.
   enum { CHANNEL_COUNT = 4, };
   
   //! @brief Pixel buffer id.
   GLuint pboId[1];

   //! @brief The pixel size around the cursor used during picking.
   int pickPixelSize;

   //! @brief Map of color indices to pickable objects.
   ofxIPickable::PickableComponentMap componentMap;

   //! @brief Draw used during back buffer selection.
   //! @param componentMode Component mode used for during picking.
   virtual void drawForSelection(unsigned int componentMode);

protected:
   //! @brief The list of pickable objects.
   std::list<ofxIPickable *> pickableObjects;
};

inline const std::list<ofxIPickable *> &ofxPickableScene::getPickableObjects() const { return this->pickableObjects; }

inline void ofxPickableScene::clearPickableObjects() { this->pickableObjects.clear(); }

inline int ofxPickableScene::getPickPixelSize() const { return this->pickPixelSize; }

inline void ofxPickableScene::setPickPixelSize(int size) { this->pickPixelSize = size; }