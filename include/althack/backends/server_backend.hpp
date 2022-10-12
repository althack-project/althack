#ifndef ALTHACK_BACKENDS_SERVER_BACKEND_HPP_
#define ALTHACK_BACKENDS_SERVER_BACKEND_HPP_

// Standard
#include <memory>
#include <string>

// AltHack
#include <althack/backend.hpp>
#include <althack/crypto_service.hpp>
#include <althack/database.hpp>

namespace althack {
namespace backends {

class ServerBackend : public Backend {
 public:
  ServerBackend(const std::string& database_file);

  ~ServerBackend();

  void step() override;

  const std::list<visuals::AccountNode> getAccounts() override;

 private:
  std::list<visuals::AccountNode> accounts_cache_;

  //! \brief The database instance to use for persistent storage.
  std::unique_ptr<Database> database_;
};

}  // namespace backends
}  // namespace althack

#endif  // ALTHACK_BACKENDS_SERVER_BACKEND_HPP_
