#ifndef ALTHACK_ALTHACK_HPP_
#define ALTHACK_ALTHACK_HPP_

#include <string>

#include <libconfig.h++>

#include <spdlog/spdlog.h>

#include <althack/config.hpp>
#include <althack/configuration.hpp>
#include <althack/main_window.hpp>

namespace althack {

// ...
class AltHack {
 public:
  // ...
  bool loadConfig(const std::string& filepath);

  // ...
  bool setup();

  // ...
  bool run();

  // ...
  bool teardown();

  std::string getVersion() const;

 private:
  Configuration configuration_;
  MainWindow main_window_;
};

}  // namespace althack

#endif  // ALTHACK_ALTHACK_HPP_
