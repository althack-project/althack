#include <althack/databases/soci_database.hpp>

#include <experimental/filesystem>

#include <soci/sqlite3/soci-sqlite3.h>

namespace althack {
namespace databases {

SociDatabase::SociDatabase(const std::string& database_file)
  : database_file_{database_file} {
}

bool SociDatabase::open() {
  const bool exists = std::filesystem::exists(database_file_);
  session_.open(soci::sqlite3, database_file_);

  if (!exists) {
    // Create users table
    session_ << "CREATE TABLE users ("
             << "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
             << "password_hash VARCHAR(64) NOT NULL, "
             << "user_name VARCHAR(255) NOT NULL"
             << ")";
    // Create stats table
    session_ << "CREATE TABLE stats ("
             << "stat_key varchar(255) PRIMARY KEY NOT NULL, "
             << "stat_value varchar(255) NOT NULL"
             << ")";

    // Insert initial data
    session_ << "INSERT INTO users(user_name, password_hash) VALUES('admin', 'somehash')";
    session_ << "INSERT INTO stats VALUES('created_at', '" << getISO8601Timestamp() << "')";
  }

  return true;
}

bool SociDatabase::close() {
  session_.close();
  return true;
}

}  // namespace databases
}  // namespace althack
