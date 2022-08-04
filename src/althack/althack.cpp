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
  return false;
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
