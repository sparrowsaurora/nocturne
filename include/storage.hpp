#pragma once

#include <filesystem>
#include <fstream>

#include "playlist.hpp"
#include "song.hpp"

namespace fs = std::filesystem;

class Storage {
   private:
    const fs::path json_file{"./app.json"};

   public:
    Storage(void);
    bool load(void);
    bool add(const Song& song);
    bool add(const Playlist& playlist);
};