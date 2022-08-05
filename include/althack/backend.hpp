#ifndef ALTHACK_BACKEND_HPP_
#define ALTHACK_BACKEND_HPP_

#include <string>

namespace althack {

class Backend {
 public:
  Backend(const std::string& identifier);

  const std::string& getIdentifier() const;

 private:
  const std::string identifier_;  
};

}  // namespace althack

#endif  // ALTHACK_BACKEND_HPP_
