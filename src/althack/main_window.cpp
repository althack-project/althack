#include <althack/main_window.hpp>

#include <iostream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace althack {

MainWindow::MainWindow()
  : window_{nullptr}
  , renderer_{nullptr} {
  addNode(std::make_shared<visuals::AccountNode>("node"), ImVec2(0, 0));
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

void MainWindow::canvas(const std::string& identifier, const ImVec2 size, const ImVec2 position) {
  ImGuiWindow* window = ImGui::GetCurrentWindow();
  if (window->SkipItems)
    return;

  const ImGuiID id = window->GetID(identifier.c_str());
  const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
  ImGui::PushClipRect(bb.Min, bb.Max, false);
  ImGuiContext& g = *GImGui;
  ImGui::ItemSize(size, g.Style.FramePadding.y);
  if (!ImGui::ItemAdd(bb, id))
    return;

  const ImU32 bg_col = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0, 1.0, 1.0, 1.0));
  // TODO: Implement additional rendering here (grid, objects, connections, effects).
  ImGui::RenderFrame(bb.Min, bb.Max, bg_col, true, g.Style.FrameRounding);

  // Draw grid
  const float stride_rows = 100.0f;
  const float stride_cols = 100.0f;
  const uint32_t substeps_rows = 5;
  const uint32_t substeps_cols = 5;

  const ImU32 grid_col_major = ImGui::ColorConvertFloat4ToU32(ImVec4(0.5, 0.5, 0.5, 0.1));
  const ImU32 grid_col_minor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.5, 0.5, 0.5, 0.05));

  const ImVec2 origin = (bb.Max - bb.Min) / 2.0 + bb.Min;
  // Draw two more (positive, negative direction) of each (rows, cols) to account for drag offset.
  const uint32_t rows = ((bb.Max - bb.Min).y / (stride_rows / static_cast<float>(substeps_rows))) + 2 * substeps_rows;
  const uint32_t cols = ((bb.Max - bb.Min).x / (stride_cols / static_cast<float>(substeps_cols))) + 2 * substeps_cols;

  float draw_position_x = position.x;
  while (draw_position_x >= stride_cols) { draw_position_x -= stride_cols; }
  while (draw_position_x <= -stride_cols) { draw_position_x += stride_cols; }
  float draw_position_y = position.y;
  while (draw_position_y >= stride_rows) { draw_position_y -= stride_rows; }
  while (draw_position_y <= stride_rows) { draw_position_y += stride_rows; }

  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  // Draw grid columns
  for (uint32_t col = 0; col < std::ceil(cols / 2.0); ++col) {
    const ImVec2 startp = ImVec2(origin.x + draw_position_x, bb.Min.y - 1.0f) + ImVec2(col * (stride_cols / substeps_cols), 0.0f);
    const ImVec2 endp = startp + ImVec2(0.0f, size.y);
    draw_list->AddLine(startp, endp, col % substeps_cols == 0 ? grid_col_major : grid_col_minor);

    // The center line is only drawn once.
    if (col == 0) { continue; }

    const ImVec2 startn = ImVec2(origin.x + draw_position_x, bb.Min.y - 1.0f) - ImVec2(col * (stride_cols / substeps_cols), 0.0f);
    const ImVec2 endn = startn + ImVec2(0.0f, size.y);
    draw_list->AddLine(startn, endn, col % substeps_cols == 0 ? grid_col_major : grid_col_minor);
  }

  // Draw grid rows
  for (uint32_t row = 0; row < std::ceil(rows / 2.0); ++row) {
    const ImVec2 startp = ImVec2(bb.Min.x - 1.0f, origin.y + draw_position_y) + ImVec2(0.0f, row * (stride_rows / substeps_rows));
    const ImVec2 endp = startp + ImVec2(size.x, 0.0f);
    draw_list->AddLine(startp, endp, row % substeps_rows == 0 ? grid_col_major : grid_col_minor);

    // The center line is only drawn once.
    if (row == 0) { continue; }

    const ImVec2 startn = ImVec2(bb.Min.x - 1.0f, origin.y + draw_position_y) - ImVec2(0.0f, row * (stride_rows / substeps_rows));
    const ImVec2 endn = startn + ImVec2(size.x, 0.0f);
    draw_list->AddLine(startn, endn, row % substeps_rows == 0 ? grid_col_major : grid_col_minor);
  }

  // Draw nodes
  for (const StatefulNode& node : nodes_) {
    node.node->draw(size / 2.0 + bb.Min + position + node.position);
  }

  // Handle UI interaction
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
    const ImVec2 clicked_pos = ImGui::GetIO().MouseClickedPos[0];
    if (bb.Contains(clicked_pos)) {
      canvas_position_ = drag_start_position_ + ImGui::GetMouseDragDelta();
    }
  } else {
    drag_start_position_ = canvas_position_;
  }

  ImGui::PopClipRect();

  IMGUI_TEST_ENGINE_ITEM_INFO(id, identifier.c_str(), g.LastItemData.StatusFlags);
}

void MainWindow::addNode(std::shared_ptr<visuals::Node> node, const ImVec2& position) {
  nodes_.push_back({node, position});
}

void MainWindow::rootWindow() {
  bool is_open;
  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
  ImGui::Begin("Root Window", &is_open,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
               ImGuiWindowFlags_NoDecoration);
  ImGui::Text("Framerate: %.2f fps", ImGui::GetIO().Framerate);
  ImGui::SameLine();
  ImGui::Text(" | ");
  ImGui::SameLine();
  ImGui::Text("Position: %.2f, %.2f", canvas_position_.x, canvas_position_.y);
  const ImVec2 window_size = ImGui::GetWindowSize();
  const ImGuiWindow* window = ImGui::GetCurrentWindow();
  ImGui::SetCursorPosX(0.0f);
  canvas("play_area", ImVec2(window_size.x, window_size.y - window->DC.CursorPos.y - 4.0f),
         canvas_position_);
  ImGui::End();
}

bool MainWindow::render() {
  // TODO: Implement switch for light/dark theme.
  ImGui::StyleColorsDark();

  ImGui_ImplSDLRenderer_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  // Render the root window.
  rootWindow();

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
