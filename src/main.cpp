// Standard
#include <cstdlib>

// spdlog
#include <spdlog/spdlog.h>

// TCLAP
#include <tclap/CmdLine.h>

// AltHack
#include <althack/althack.hpp>

int main(int argc, char** argv) {
  std::string config_path = "";

  // Parse command line options
  try {
    TCLAP::CmdLine cmd("AltHack command line", ' ', "0.1");

    TCLAP::ValueArg<std::string> config_path_arg(
        "c", "config", "Configuration file to use", false, "", "string");
    cmd.add(config_path_arg);

    cmd.parse(argc, argv);
    config_path = config_path_arg.getValue();
  } catch(const TCLAP::ArgException& ex) {
    spdlog::error("TCLAP error (for argument \"" + std::string(ex.argId()) + "\": " + std::string(ex.error()));
    return EXIT_FAILURE;
  }

  if (config_path.empty()) {
    config_path = "../configs/default.cfg";
  }

  spdlog::info("Instantiating AltHack");
  althack::AltHack instance;

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
