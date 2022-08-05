#include <althack/backend.hpp>

namespace althack {

Backend::Backend(const std::string& identifier)
  : identifier_{identifier} {
}

const std::string& Backend::getIdentifier() const {
  return identifier_;
}

}  // namespace althack
