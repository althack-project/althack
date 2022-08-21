#include <althack/main_window.hpp>

#include <iostream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

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

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (!renderer_) {
    spdlog::error("Failed to initialize renderer.");
    return false;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Setup renderer backend
  ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
  ImGui_ImplSDLRenderer_Init(renderer_);

  return true;
}

bool MainWindow::processIo() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT ||
        (event.type == SDL_WINDOWEVENT &&
         event.window.event == SDL_WINDOWEVENT_CLOSE &&
         event.window.windowID == SDL_GetWindowID(window_))) {
      return false;
    }
  }

  return true;
}

void MainWindow::canvas(const std::string& identifier, ImVec2 size) {
  ImGuiWindow* window = ImGui::GetCurrentWindow();
  if (window->SkipItems)
    return;

  const ImGuiID id = window->GetID(identifier.c_str());
  const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
  ImGuiContext& g = *GImGui;
  ImGui::ItemSize(size, g.Style.FramePadding.y);
  if (!ImGui::ItemAdd(bb, id))
    return;

  // TODO: Implement interaction here.
  /*bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);*/

  const ImU32 bg_col = ImGui::ColorConvertFloat4ToU32(ImVec4(0.75, 0.75, 0.75, 1.0));
  // TODO: Implement additional rendering here (grid, objects, connections, effects).
  ImGui::RenderFrame(bb.Min, bb.Max, bg_col, true, g.Style.FrameRounding);

  IMGUI_TEST_ENGINE_ITEM_INFO(id, identifier.c_str(), g.LastItemData.StatusFlags);
}

bool MainWindow::render() {
  // TODO: Implement switch for light/dark theme.
  ImGui::StyleColorsDark();

  const float controls_window_fraction = 200.0f;

  ImGui_ImplSDLRenderer_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSize(ImVec2(controls_window_fraction, ImGui::GetIO().DisplaySize.y));
  bool is_open;
  ImGui::Begin("Control Window", &is_open,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
               ImGuiWindowFlags_NoDecoration);
  ImGui::TreeNode("Node 1");
  ImGui::TreePop();
  ImGui::End();

  ImGui::SetNextWindowPos(ImVec2(controls_window_fraction - 1.0f, 0.0f));
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
  ImGui::Begin("Central Window", &is_open,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
               ImGuiWindowFlags_NoDecoration);
  ImGui::Text("Framerate: %.2f fps", ImGui::GetIO().Framerate);
  const ImVec2 size_min = ImGui::GetWindowContentRegionMin();
  const ImVec2 size_max = ImGui::GetWindowContentRegionMax();
  const ImGuiWindow* window = ImGui::GetCurrentWindow();
  canvas("canvas", ImVec2(size_max.x - size_min.x - controls_window_fraction - 1.0f,
                          size_max.y - size_min.y - window->DC.CursorPos.y + 5.0f));
  ImGui::End();

  // ...
  // ImGui::Begin("Some Window!");
  // ImGui::Text("Hello from another window!");
  // ImGui::End();
  // ...

  ImGui::Render();
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
  SDL_RenderClear(renderer_);
  ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
  SDL_RenderPresent(renderer_);

  return true;
}

bool MainWindow::teardown() {
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_) {
    SDL_DestroyWindow(window_);
  }

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
