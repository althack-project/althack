#ifndef DUNGEON_MINER_DUNGEON_MINER_HPP_
#define DUNGEON_MINER_DUNGEON_MINER_HPP_

#include <string>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include <SDL.h>

#include <libconfig.h++>

#include <spdlog/spdlog.h>

#include <dungeon_miner/config.hpp>
#include <dungeon_miner/configuration.hpp>

namespace dungeon_miner {

// ...
class DungeonMiner {
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
};

}  // namespace dungeon_miner

#endif  // DUNGEON_MINER_DUNGEON_MINER_HPP_
