#ifndef ALTHACK_FRONTEND_HPP_
#define ALTHACK_FRONTEND_HPP_

// Standard
#include <memory>

// Althack
#include <althack/backend.hpp>

namespace althack {

class Frontend {
 public:
  void connect(std::shared_ptr<Backend> backend);

  void step();

  const std::list<visuals::AccountNode> getAccounts();

 private:
  std::shared_ptr<Backend> backend_;
};

}  // namespace althack

#endif  // ALTHACK_FRONTEND_HPP_
