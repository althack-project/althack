#ifndef ALTHACK_BACKEND_HPP_
#define ALTHACK_BACKEND_HPP_

// Standard
#include <list>
#include <string>

// AltHack
#include <althack/visuals/account_node.hpp>

namespace althack {

class Backend {
 public:
  Backend(const std::string& identifier);

  const std::string& getIdentifier() const;

  virtual void step() = 0;

  virtual const std::list<visuals::AccountNode> getAccounts() = 0;

 private:
  const std::string identifier_;
};

}  // namespace althack

#endif  // ALTHACK_BACKEND_HPP_
