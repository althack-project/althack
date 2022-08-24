#include <althack/visuals/node.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace althack {
namespace visuals {

Node::Node(const std::string& identifier)
  : identifier_{identifier} {
}

const std::string& Node::getIdentifier() const {
  return identifier_;
}

bool Node::hit(const ImVec2 node_position, const ImVec2 hit_position) const {
  const ImVec2 node_size = size();
  const ImRect node_rect{node_position - node_size / 2.0, node_position + node_size / 2.0};
  return node_rect.Contains(hit_position);
}

}  // namespace visuals
}  // namespace althack
