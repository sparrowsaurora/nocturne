#pragma once

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <variant>

using config_t = std::map<std::string, std::variant<int, std::string, double>>;
namespace fs = std::filesystem;

class Config {
   private:
    inline static const std::string config_file = "./config/config.toml";

   public:
    static std::optional<config_t> get_config(void);
};