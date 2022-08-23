#include <althack/visuals/node.hpp>

namespace althack {
namespace visuals {

Node::Node(const std::string& identifier)
  : identifier_{identifier} {
}

const std::string& Node::getIdentifier() const {
  return identifier_;
}

}  // namespace visuals
}  // namespace althack
