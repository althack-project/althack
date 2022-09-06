#ifndef ALTHACK_DATABASE_HPP_
#define ALTHACK_DATABASE_HPP_

// Standard
#include <string>

namespace althack {

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

 protected:
  static std::string getISO8601Timestamp();
};

}  // namespace althack

#endif  // ALTHACK_DATABASE_HPP_
