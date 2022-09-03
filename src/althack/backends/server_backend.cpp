#include <althack/backends/server_backend.hpp>

#include <althack/databases/soci_database.hpp>

namespace althack {
namespace backends {

ServerBackend::ServerBackend(const std::string& database_file)
    : Backend("server_backend") {
  // Initialize the backend database for persistent storage.
  database_ = std::make_unique<databases::SociDatabase>(database_file);

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
