#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

#define ASSETS_PATH "/home/crative/dev/cpp/pixel-engine/assets"
#define LOG_FILE_PATH "/home/crative/dev/cpp/pixel-engine/log_file.log"

class sys {
public:
  static std::string getAssetPath(const std::string &asset) {
    return std::string(ASSETS_PATH) + "/" + asset;
  };
};

#endif // SYSTEM_HPP
