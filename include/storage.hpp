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
   private:
    inline static const std::string file_name{"./build/cache.toml"};

   public:
    Storage(void);

    /**
     * read toml file to quickload songs
     */
    std::optional<Database> load(Database database);

    /**
     * utility to refresh cache with any songs and playlists added without the app
     */
    bool refresh_cache(const std::string& dir);

    /**
     * add song to playlist in json file
     */
    static bool add(const Song& song);

    /**
     * add song to playlist in json file
     */
    static bool add(const Playlist& playlist);

    /**
     * use directory to add entire playlist with songs
     */
    static bool add(const path_t& directory);
};