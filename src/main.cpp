// Standard
#include <csignal>
#include <cstdlib>
#include <functional>

// spdlog
#include <spdlog/spdlog.h>

// TCLAP
#include <tclap/CmdLine.h>

// AltHack
#include <althack/althack.hpp>

namespace {

// ...
std::function<void(int)> shutdown_handler;

// ...
void signal_handler(int signal) { shutdown_handler(signal); }

}  // namespace

int main(int argc, char** argv) {
  std::string config_path;
  bool headless = false;

  althack::AltHack instance;

  // Parse command line options
  try {
    TCLAP::CmdLine cmd("AltHack command line", ' ', althack::AltHack::getVersion());

    TCLAP::ValueArg<std::string> config_path_arg(
        "c", "config", "Path of configuration file to use", false, "", "path");
    cmd.add(config_path_arg);
    TCLAP::SwitchArg headless_arg(
        "H", "headless", "Run in headless mode", false);
    cmd.add(headless_arg);

    cmd.parse(argc, argv);
    config_path = config_path_arg.getValue();
    headless = headless_arg.getValue();
  } catch (const TCLAP::ArgException& ex) {
    spdlog::error("TCLAP error (for argument \"" + std::string(ex.argId()) + "\": " + std::string(ex.error()));
    return EXIT_FAILURE;
  }

  if (config_path.empty()) {
    config_path = "../configs/default.cfg";
  }

  spdlog::info("Instantiating AltHack (version " + althack::AltHack::getVersion() + ")");
  instance.setHeadless(headless);

  if (headless) {
    spdlog::info("Running in headless mode");
  }

  spdlog::info("Loading configuration from file \"" + config_path + "\"");
  if (!instance.loadConfig(config_path)) {
    spdlog::error("Failed, quitting");
    return EXIT_FAILURE;
  }

  spdlog::info("Setting up environment");
  if (!instance.setup()) {
    spdlog::error("Failed, quitting");
    return EXIT_FAILURE;
  }

  std::signal(SIGINT, signal_handler);
  shutdown_handler = [&](int /*signal*/) { instance.stop(); };

  spdlog::info("Ready, entering main loop");
  if (instance.run()) {
    spdlog::info("Exited main loop cleanly");
  } else {
    spdlog::warn("Exited main loop uncleanly");
  }

  spdlog::info("Tearing down environment");
  if (!instance.teardown()) {
    spdlog::warn("Failed, quitting");
    return EXIT_FAILURE;
  }

  spdlog::info("Done, see you soon!");

  return EXIT_SUCCESS;
}
