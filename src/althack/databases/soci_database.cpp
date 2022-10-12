#include <althack/databases/soci_database.hpp>

#include <filesystem>

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
    // Create entities table
    session_ << "CREATE TABLE entities ("
             << "entity_id INTEGER PRIMARY KEY AUTOINCREMENT, "
             << "domain VARCHAR(255) NOT NULL"
             << ")";
    // Create blob storage table
    session_ << "CREATE TABLE blobs (blob_id INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT)";
    // Create blob association table
    session_ << "CREATE TABLE blobs_entities ("
             << "domain VARCHAR(255) NOT NULL, "
             << "blob_id INTEGER NOT NULL, "
             << "entity_id INTEGER NOT NULL, "
             << "key VARCHAR(255) NOT NULL"
             << ")";
    // Create stats table
    session_ << "CREATE TABLE stats ("
             << "stat_key varchar(255) PRIMARY KEY NOT NULL, "
             << "stat_value varchar(255) NOT NULL"
             << ")";

    // Insert initial data
    session_ << "INSERT INTO users(user_name) VALUES('admin', 'somehash')";
    session_ << "INSERT INTO stats VALUES('created_at', '" << getISO8601Timestamp() << "')";
  }

  return true;
}

bool SociDatabase::close() {
  session_.close();
  return true;
}
 
EntityId SociDatabase::createEntity(const std::string& domain) {
  session_ << "INSERT INTO entities(domain) VALUES(" << domain << ")";
  EntityId id = 0;
  if (!session_.get_last_insert_id("entities", id)) {
    throw std::runtime_error("Failed to get entities last inserted id");
  }
  return id;
}

void SociDatabase::deleteEntity(EntityId entity_id) {
  // Delete all blobs related to the entity to delete
  session_ << "DELETE b FROM blobs b JOIN blobs_entities b_e ON b.blob_id = b_e.blob_id WHERE b_e.entity_id = " << entity_id;
  // Delete all the blob/entity associations of the entity to delete
  session_ << "DELETE FROM blobs_entities WHERE entity_id = " << entity_id;
  // Delete the actual entity to delete
  session_ << "DELETE FROM entities WHERE entity_id = " << entity_id;
}

EntityId SociDatabase::storeBlob(const std::string& value) {
  session_ << "INSERT INTO blobs(value) VALUES(" << value << ")";
  EntityId id = 0;
  if (!session_.get_last_insert_id("blobs", id)) {
    throw std::runtime_error("Failed to get blobs last inserted id");
  }
  return id;
}

void SociDatabase::associateBlobProperty(const std::string& domain, EntityId blob_id, EntityId entity_id, const std::string& key) {
  session_ << "INSERT INTO blobs_entities(domain, blob_id, entity_id, key) VALUES(" << domain << ", " << blob_id << ", " << entity_id << ", " << key << ")";
}

void SociDatabase::deleteBlobProperty(const std::string& domain, EntityId entity_id, const std::string& key) {
  session_ << "DELETE b FROM blobs b JOIN blobs_entities b_e ON b.blob_id = b_e.blob_id WHERE b_e.entity_id = " << entity_id << " AND b_e.key = " << key << " AND b_e.domain = " << domain;
  session_ << "DELETE FROM blobs_entities WHERE domain = " << domain << " AND entity_id = " << entity_id << " AND key = " << key;
}

}  // namespace databases
}  // namespace althack
