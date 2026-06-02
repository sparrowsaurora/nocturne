#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "playlist.hpp"
#include "song.hpp"

typedef struct database {
    std::vector<Playlist> playlists;
    std::vector<Song> songs;
} Database;

namespace fs = std::filesystem;
using path_t = fs::__cxx11::path;

class Storage {
   public:
    /**
     * Load Songs into database
     */
    static std::optional<Database> load(const path_t& directory);
};