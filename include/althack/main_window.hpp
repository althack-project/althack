#ifndef ALTHACK_MAINWINDOW_HPP_
#define ALTHACK_MAINWINDOW_HPP_

// Standard
#include <list>
#include <memory>
#include <string>

// spdlog
#include <spdlog/spdlog.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

// SDL
#include <SDL.h>

// AltHack
#include <althack/visuals/node.hpp>
#include <althack/visuals/account_node.hpp>

namespace althack {

//! \brief Represents the main UI window to interact with the current AltHack instance.
/*!
  The current AltHack instance is controlled through its singleton MainWindow instance. The entire
  game state and possible player actions are presented to the user through a series of widgets
  defined within the scope of the MainWindow. When the MainWindow instance is closed, the game is
  shut down.
 */
class MainWindow {
 public:
  //! \brief Initializes the internal main window members.
  MainWindow();

  //! \brief Sets up this window instance with the specified settings.
  /*!
    \param title The window title string to show in the title bar.
    \param width The window width in pixels.
    \param height The window height in pixels.
    \sa teardown()
    \returns A boolean flag denoting whether the setup was completed successfully.
   */
  bool setup(const std::string& title, uint32_t width, uint32_t height);

  //! \brief Processes high level I/O signals to allow window interaction.
  /*!
    \returns A boolean flag denoting whether I/O was processed successfully.
   */
  bool processIo();

  //! \brief Renders this window instance based on its current state.
  /*!
    \returns A boolean flag denoting whether rendering was processed successfully.
   */
  bool render();

  //! \brief Tears down this window instance.
  /*!
    Internal clean-up mechanisms are executed to ensure a clean teardown.
    \sa setup()
    \returns A boolean flag denoting whether teardown was processed successfully.
   */
  bool teardown();

  //! \brief Returns the semantic version string of the compiled SDL libraries.
  /*!
    \sa getSdlVersionLinked()
    \returns A string representation of the semantic SDL version (compile version).
   */
  std::string getSdlVersionCompiled() const;

  //! \brief Returns the semantic version string of the linked SDL libraries.
  /*!
    \sa getSdlVersionCompiled()
    \returns A string representation of the semantic SDL version (link version).
   */
  std::string getSdlVersionLinked() const;

 private:
  //! \brief Reference to a node visual, alongside its current visual state.
  typedef struct StatefulNode {
    //! \brief Reference to the node visual
    std::shared_ptr<visuals::Node> node;
    //! \brief The drawing position of the node visual
    ImVec2 position;
    //! \brief Denotes whether the node is currently being dragged
    bool dragged;
  } StatefulNode;

  //! \brief Creates the main canvas widget based on the specified parameters.
  /*!
    \param identifier The string identifier of this widget.
    \param size The size of this widget in pixels.
    \param position The scroll position to use as drawing origin in canvas coordinates.
   */
  void canvas(const std::string& identifier, const ImVec2 size, const ImVec2 position);

  //! \brief Adds a visual node element.
  /*!
    \param node The node instance to add.
    \param position The canvas coordinates this node is positioned at initially.
   */
  void addNode(std::shared_ptr<visuals::Node> node, const ImVec2& position);

  //! \brief Renders the root window.
  /*!
    Called by render().
    \sa render()
   */
  void rootWindow();

  //! \brief The SDL window handle for this instance.
  SDL_Window* window_;

  //! \brief The SDL renderer handle for this instance.
  SDL_Renderer* renderer_;

  //! \brief The current display position of the canvas.
  ImVec2 canvas_position_;

  //! \brief The canvas position when dragging started.
  ImVec2 drag_start_position_;

  //! \brief Denotes whether an element was being dragged in the past frame.
  bool was_dragging_;

  //! \brief Stores a pointer to the currently dragged node.
  StatefulNode* dragged_node_;

  //! \brief Stores a pointer to the currently hovered node.
  StatefulNode* hovered_node_;

  //! \brief List of node visuals to draw, alongside their state data.
  std::list<StatefulNode> nodes_;
};

}  // namespace althack

#endif  // ALTHACK_MAINWINDOW_HPP_
