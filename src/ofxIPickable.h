#pragma once

#include <map>
#include <ofColor.h>

//! @typedef Color index number used as an identifier during picking.
typedef long ColorIndex;

//! @brief Helper functin for converting a color to an index value.
//! @param color Color value to convert.
//! @return The converted index.
inline ColorIndex colorToIndex(const ofColor &color) { return ((color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b)); }

//! @brief Helper functin for coneverting an index to a color.
//! @param index Index value to convert.
//! @return The converted color.
inline ofColor indexToColor(ColorIndex index) { return ofColor(((index >> 16) & 0xFF), ((index >> 8) & 0xFF), (index & 0xFF), ((index >> 24) & 0xFF)); }

//! @brief Interface for pickable objects.
class ofxIPickable
{
public:
   //! @typedef Map of color indices to pickable objects.
   typedef std::map<ColorIndex, ofxIPickable *> PickableComponentMap;

   //! @brief Destructor.
   virtual ~ofxIPickable() { }
    
   //! @param color Must use the selection color for drawing.
   //! @param componentMap Must fill the component map with all the components that could be selected.
   //         If the object is not broken down into components, just add the top level pickable object.
   //! @param componentMode Optional mode param for the user to know how the object should add to the component map.
   virtual void setSelectionColor(const ofColor &color,
                                  PickableComponentMap &componentMap,
                                  unsigned int componentMode) = 0;

   //! @brief Draw the object for back buffer selection.
   //! @param componentMode An index representing a component mode used during selection for this object.
   virtual void drawForSelection(unsigned int componentMode) = 0;

   //! @brief Restore the object after a selection has been made.
   //! @param componentMode An index representing a component mode used during selection for this object
   virtual void postSelectionRestore(int componentMode) = 0;

   //! @brief Return whether this object is visible.
   //! @return Whether this object is visible.
   virtual bool isVisible() = 0;

   //! @brief Set whether this object is visible.
   //! @param state The state of visibility.
   virtual void setVisible(bool state) = 0;

   //! @brief Get this object's color.
   //! @return This objects color.
   virtual const ofColor &getColor() const = 0;

   //! @brief Set this object's color.
   //! @param colorValue The new color for this object. 
   virtual void setColor(const ofColor &colorValue) = 0;

   //! @brief Set whether this object is selected.
   //! @param selectionState The selection state for this object.
   virtual void setSelected(bool selectionState) = 0;

   //! @brief Get whether this object is selected.
   //! @return Whether this object is selected.
   virtual bool isSelected() = 0;
};




