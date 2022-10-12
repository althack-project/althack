#include <althack/database.hpp>

// Standard
#include <chrono>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace althack {

namespace {
//! \brief The database domain for user account related data.
const std::string DB_ENTITY_DOMAIN_USER = "user";
//! \brief The database user account property key for usernames.
const std::string DB_USER_PROPERTY_USERNAME = "name";
}  // namespace

EntityId Database::createUser(const std::string& user_name) {
  const EntityId user_id = createEntity(DB_ENTITY_DOMAIN_USER);
  setUserProperty(user_id, DB_USER_PROPERTY_USERNAME, user_name);
  return user_id;
}

void Database::deleteUser(EntityId user_id) {
  deleteEntity(user_id);
}

void Database::setUserProperty(EntityId user_id, const std::string& key, const std::string& value) {
  const EntityId blob_id = storeBlob(value);
  associateBlobProperty(DB_ENTITY_DOMAIN_USER, blob_id, user_id, key);
}

void Database::deleteUserProperty(EntityId user_id, const std::string& key) {
  deleteBlobProperty(DB_ENTITY_DOMAIN_USER, user_id, key);
}

std::string Database::getISO8601Timestamp() {
  const auto now = std::chrono::system_clock::now();
  const std::time_t time = std::chrono::system_clock::to_time_t(now);
  const std::tm* now_tm = std::localtime(&time);
  const int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

  std::stringstream sts;
  sts << std::setfill('0')
      << std::put_time(now_tm, "%FT%H:%M:")
      << std::setw(2) << (timestamp / 1000) % 60 << '.'
      << std::setw(3) << timestamp % 1000
      << std::put_time(now_tm, "%z");

  return sts.str();
}

}  // namespace althack
