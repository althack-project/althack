#ifndef ALTHACK_VISUALS_NODE_HPP_
#define ALTHACK_VISUALS_NODE_HPP_

// Standard
#include <string>

// ImGui
#include <imgui.h>

namespace althack {
namespace visuals {

//! \brief Abstract base class for visual node elements.
class Node {
 public:
  //! \brief Initializes this instance.
  /*!
    \param identifier The internal string identifier of this node.
   */
  Node(const std::string& identifier);

  //! \brief Returns the internal string identifier of this node.
  const std::string& getIdentifier() const;

  //! \brief Draws this node on the current canvas.
  /*!
    \param position At which canvas position to draw this node
    \param hovered Denotes whether this node is currently hovered over
    \param dragged Denotes whether this node is currently being dragged
   */
  virtual void draw(const ImVec2 position, bool hovered, bool dragged) = 0;

  //! \brief Returns the visual size of this node.
  /*!
    Needs to be overridden by subclasses. The return value of this function
    affects the hit() test for this node.
    \returns The two-dimensional area representing the visual size of this node.
   */
  virtual ImVec2 size() const = 0;

  //! \brief Determines whether a hit position is within the visual area of this node.
  /*!
    \param node_position The position at which the node visual is located at
    \param hit_position The position to test for in the hit test
    \returns A boolean flag denoting whether hit_position is within the visual node area.
   */
  virtual bool hit(const ImVec2 node_position, const ImVec2 hit_position) const;

 private:
  //! \brief The internal string identifier of this node.
  const std::string identifier_;
};

}  // namespace visuals
}  // namespace althack

#endif  // ALTHACK_VISUALS_NODE_HPP_
