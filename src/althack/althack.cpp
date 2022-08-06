#include <althack/althack.hpp>

namespace althack {

AltHack::AltHack()
  : should_run_{false}
  , headless_{false}
  , backend_{nullptr} {
}

bool AltHack::loadConfig(const std::string& filepath) {
  return true;
}

bool AltHack::setup() {
  if (!headless_ && !main_window_.setup("AltHack", 1024, 768)) {
    return false;
  }

  // TODO: Decide how server/client backend is determined.
  backend_ = std::make_unique<backends::ServerBackend>();

  spdlog::info("Using backend: " + backend_->getIdentifier());

  return true;
}

bool AltHack::run() {
  using namespace std::chrono_literals;
  std::unique_lock<std::mutex> lock(run_mutex_);
  should_run_ = true;

  while (run_cv_.wait_for(lock, 1ms, [&]{ return should_run_; })) {
    if (!headless_) {
      const bool goon = main_window_.processIo();
      if (!goon) {
        break;
      }
      main_window_.render();
    }
    backend_->step();

    // TODO: Do headless things here.
  }

  std::cout << "\r";  // Move cursor back to line beginning after potential CTRL-C (to avoid ^C).
  spdlog::info("Mainloop exit requested");

  return true;
}

void AltHack::stop() {
  should_run_ = false;
  run_cv_.notify_all();
}

bool AltHack::teardown() {
  if (!headless_ && !main_window_.teardown()) {
    return false;
  }

  return true;
}

std::string AltHack::getVersion() const {
  return
    std::to_string(AH_MAJOR_VERSION) + "." +
    std::to_string(AH_MINOR_VERSION) + "." +
    std::to_string(AH_PATCH_VERSION);
}

void AltHack::setHeadless(bool headless) {
  headless_ = headless;
}

}  // namespace althack
