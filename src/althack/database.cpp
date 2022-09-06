#include <althack/database.hpp>

// Standard
#include <chrono>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace althack {

std::string Database::getISO8601Timestamp() {
  const auto now = std::chrono::system_clock::now();
  const std::time_t time = std::chrono::system_clock::to_time_t(now);
  const std::tm* now_tm = std::localtime(&time);
  const int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

  std::stringstream sts;
  sts << std::setfill('0')
      << std::put_time(now_tm, "%FT%H:%M:")
      << std::setw(2) << (timestamp / 1000) % 60 << '.'
      << std::setw(3) << timestamp % 1000
      << std::put_time(now_tm, "%z");

  return sts.str();
}

}  // namespace althack
