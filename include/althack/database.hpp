#ifndef ALTHACK_DATABASE_HPP_
#define ALTHACK_DATABASE_HPP_

// Standard
#include <string>

namespace althack {

using EntityId = long long;

//! \brief Abstract base class for persistent database classes
/*!
   This base database class provides the interface for persistent data storage in server backend
   instances. It needs to be subclassed to add actual functionality.
 */
class Database {
 public:
  //! \brief Opens the database for reading/writing.
  virtual bool open() = 0;
  //! \brief Closes the database.
  virtual bool close() = 0;

  EntityId createUser(const std::string& user_name);

  void deleteUser(EntityId user_id);

  void setUserProperty(EntityId user_id, const std::string& key, const std::string& value);

  void deleteUserProperty(EntityId user_id, const std::string& key);

 protected:
  static std::string getISO8601Timestamp();

  virtual EntityId createEntity(const std::string& domain) = 0;

  virtual void deleteEntity(EntityId entity_id) = 0;

  virtual EntityId storeBlob(const std::string& value) = 0;

  virtual void associateBlobProperty(
      const std::string& domain, EntityId blob_id, EntityId entity_id, const std::string& key) = 0;

  virtual void deleteBlobProperty(
      const std::string& domain, EntityId entity_id, const std::string& key) = 0;
};

}  // namespace althack

#endif  // ALTHACK_DATABASE_HPP_
