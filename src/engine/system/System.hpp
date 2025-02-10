#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

#define ASSETS_PATH "/home/crative/dev/cpp/pixel-engine/assets"
#define LOG_FILE_PATH "/home/crative/dev/cpp/pixel-engine/log_file.log"

namespace sys {
static std::string getAssetPath(const std::string &asset) {
  return std::string(ASSETS_PATH) + "/" + asset;
}

} // namespace sys

#endif // SYSTEM_HPP
