#include <althack/backends/server_backend.hpp>

namespace althack {
namespace backends {

ServerBackend::ServerBackend()
    : Backend("server_backend") {
  accounts_cache_.push_back(visuals::AccountNode("node1", "rainforest", "acc123", 100.0, "$"));
  accounts_cache_.push_back(visuals::AccountNode("node2", "paybuddy", "acc@pb.domain", 52.75, "EUR"));
}

void ServerBackend::step() {
  // TODO(fairlight1337): This is currently a stub. Implement proper backend functionality.
}

const std::list<visuals::AccountNode> ServerBackend::getAccounts() {
  return accounts_cache_;
}

}  // namespace backends
}  // namespace althack
