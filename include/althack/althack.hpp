#ifndef ALTHACK_ALTHACK_HPP_
#define ALTHACK_ALTHACK_HPP_

// Standard
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>

// libconfig
#include <libconfig.h++>

// spdlog
#include <spdlog/spdlog.h>

// AltHack
#include <althack/config.hpp>
#include <althack/configuration.hpp>
#include <althack/backend.hpp>
#include <althack/backends/server_backend.hpp>
#include <althack/main_window.hpp>

namespace althack {

// ...
class AltHack {
 public:
  AltHack();

  // ...
  bool loadConfig(const std::string& filepath);

  // ...
  bool setup();

  // ...
  bool run();

  // ...
  void stop();

  // ...
  bool teardown();

  std::string getVersion() const;

  void setHeadless(bool headless);

 private:
  void backendWorker(std::atomic<bool>& run_flag);

  Configuration configuration_;
  MainWindow main_window_;

  bool should_run_;
  std::mutex run_mutex_;
  std::condition_variable run_cv_;

  bool headless_;

  std::unique_ptr<Backend> backend_;
};

}  // namespace althack

#endif  // ALTHACK_ALTHACK_HPP_
