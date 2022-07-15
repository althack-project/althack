#include <dungeon_miner/dungeon_miner.hpp>

namespace dungeon_miner {

bool DungeonMiner::loadConfig(const std::string& filepath) {
  return true;
}

bool DungeonMiner::setup() {
  spdlog::info("Version " + getVersion());
  return false;
}

bool DungeonMiner::run() {
  return false;
}

bool DungeonMiner::teardown() {
  return false;
}

std::string DungeonMiner::getVersion() const {
  return
    std::to_string(DM_MAJOR_VERSION) + "." +
    std::to_string(DM_MINOR_VERSION) + "." +
    std::to_string(DM_PATCH_VERSION);
}

}  // namespace dungeon_miner
