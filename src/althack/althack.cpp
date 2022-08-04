#include <althack/althack.hpp>

namespace althack {

bool AltHack::loadConfig(const std::string& filepath) {
  return true;
}

bool AltHack::setup() {
  spdlog::info("Version " + getVersion());

  return main_window_.setup("AltHack", 1024, 768);
}

bool AltHack::run() {
  using namespace std::chrono_literals;
  std::unique_lock<std::mutex> lock(run_mutex_);

  while (run_cv_.wait_for(lock, 1ms) == std::cv_status::timeout) {
    const bool goon = main_window_.processIo();
    if (!goon) {
      break;
    }
    main_window_.render();
  }

  std::cout << "\r";  // Move cursor back to line beginning after potential CTRL-C (to avoid ^C).
  spdlog::info("Mainloop exit requested");

  return true;
}

void AltHack::stop() {
  run_cv_.notify_all();
}

bool AltHack::teardown() {
  return main_window_.teardown();
}

std::string AltHack::getVersion() const {
  return
    std::to_string(AH_MAJOR_VERSION) + "." +
    std::to_string(AH_MINOR_VERSION) + "." +
    std::to_string(AH_PATCH_VERSION);
}

}  // namespace althack
