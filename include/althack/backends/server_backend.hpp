#ifndef ALTHACK_BACKENDS_SERVER_BACKEND_HPP_
#define ALTHACK_BACKENDS_SERVER_BACKEND_HPP_

#include <althack/backend.hpp>

namespace althack {
namespace backends {

class ServerBackend : public Backend {
 public:
  ServerBackend();

  void step() override;

  const std::list<visuals::AccountNode> getAccounts() override;

 private:
  std::list<visuals::AccountNode> accounts_cache_;
};

}  // namespace backends
}  // namespace althack

#endif  // ALTHACK_BACKENDS_SERVER_BACKEND_HPP_
