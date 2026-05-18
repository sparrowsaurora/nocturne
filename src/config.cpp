#include "config.hpp"

static inline std::string trim(std::string s) {
    auto not_space = [](unsigned char c) {
        return !std::isspace(c);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());

    return s;
}

std::optional<config_t> Config::get_config() {
    config_t map;

    if (fs::exists(Config::config_file) != true) {
        return std::nullopt;
    }

    {  // context manager
        // open file
        std::ifstream file(Config::config_file);

        // confirm open file
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file!" << std::endl;
            return std::nullopt;
        }

        // convert data to map
        std::string line, content, key, value;
        std::string_view text;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));

            if (value[0] == '"') {
                std::erase(value, '"');  // if string in config file remove extra " pair
            }

            map[key] = value;
        }
    }

    return map;
}