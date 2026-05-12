#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "playlist.hpp"
#include "song.hpp"

namespace fs = std::filesystem;

class Storage {
   private:
    const std::string file_name{"./build/app.toml"};

   public:
    Storage(void);
    bool load(void);
    bool add(const Song& song);
    bool add(const Playlist& playlist);
};