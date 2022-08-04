#include <althack/main_window.hpp>

namespace althack {

MainWindow::MainWindow()
  : window_{nullptr}
  , renderer_{nullptr} {
}

bool MainWindow::setup(const std::string& title, uint32_t width, uint32_t height) {
  spdlog::info("SDL version: compiled " + getSdlVersionCompiled() + ", linked " + getSdlVersionLinked());

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    spdlog::error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    return false;
  }
    
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  window_ = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height,
      window_flags);

  SDL_SetWindowMinimumSize(window_, 500, 300);

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  ImGui::CreateContext();

  return true;
}

bool MainWindow::teardown() {
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_) {
    SDL_DestroyWindow(window_);
  }
  
  ImGui::DestroyContext();

  return true;
}

std::string MainWindow::getSdlVersionCompiled() const {
  SDL_version version;
  SDL_VERSION(&version);

  return
    std::to_string(version.major) + "." +
    std::to_string(version.minor) + "." +
    std::to_string(version.patch);
}

std::string MainWindow::getSdlVersionLinked() const {
  SDL_version version;
  SDL_GetVersion(&version);

  return
    std::to_string(version.major) + "." +
    std::to_string(version.minor) + "." +
    std::to_string(version.patch);
}
  
}  // namespace althack
