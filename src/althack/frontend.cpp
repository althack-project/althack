#include <althack/frontend.hpp>

namespace althack {

void Frontend::connect(std::shared_ptr<Backend> backend) {
  backend_ = backend;
}

void Frontend::step() {
  // TOOD: Implement frontend cycle work.
}

const std::list<visuals::AccountNode> Frontend::getAccounts() {
  return backend_->getAccounts();
}

}  // namespace althack
