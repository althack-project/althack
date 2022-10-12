#ifndef ALTHACK_DATABASES_SOCI_DATABASE_HPP_
#define ALTHACK_DATABASES_SOCI_DATABASE_HPP_

// Standard
#include <string>

// AltHack
#include <althack/database.hpp>

// SOCI
#include <soci/soci.h>

namespace althack {
namespace databases {

//! \brief Implements the SOCI database library as AltHack database
/*!
  SOCI is a database abstraction layer that provides modern C++ functionality to proven database
  interfaces like DB2, Oracle, MySQL, or SQLITE. AltHack uses the file-based SQLITE interface
  through SOCI (v4.0.3).

  SOCI's documentation can be found on SourceForge here:
  http://soci.sourceforge.net/doc/release/4.0/
 */
class SociDatabase : public Database {
 public:
  //! \brief Initializes this database instance, using the specified filename for storage.
  /*!
    \param database_file The filepath to use for reading/writing the database contents.
   */
  SociDatabase(const std::string& database_file);

  bool open() override;

  bool close() override;

 private:
  EntityId createEntity(const std::string& domain) override;

  void deleteEntity(EntityId entity_id) override;

  EntityId storeBlob(const std::string& value) override;

  void associateBlobProperty(
      const std::string& domain, EntityId blob_id, EntityId entity_id,
      const std::string& key) override;

  void deleteBlobProperty(
      const std::string& domain, EntityId entity_id, const std::string& key) override;

  //! \brief The database session to use.
  soci::session session_;
  //! \brief The database file to use.
  const std::string database_file_;
};

}  // namespace databases
}  // namespace althack

#endif  // ALTHACK_DATABASES_SOCI_DATABASE_HPP_
