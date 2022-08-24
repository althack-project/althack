#ifndef ALTHACK_VISUALS_ACCOUNT_NODE_HPP_
#define ALTHACK_VISUALS_ACCOUNT_NODE_HPP_

// AltHack
#include <althack/visuals/node.hpp>

namespace althack {
namespace visuals {

//! \brief Funds holding account node class.
class AccountNode : public Node {
 public:
  AccountNode(const std::string& identifier);

  void draw(const ImVec2 position, bool hovered, bool dragged) override;

  ImVec2 size() const override;

  bool hit(const ImVec2 node_position, const ImVec2 hit_position) const override;
};

}  // namespace visuals
}  // namespace althack

#endif  // ALTHACK_VISUALS_ACCOUNT_NODE_HPP_
