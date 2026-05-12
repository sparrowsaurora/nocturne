#include "storage.hpp"

Storage::Storage(void) {
    std::ofstream file(file_name);
};

/**
 * Load file contents into app
 */
bool Storage::load(void) {
    // open json file

    // store lines in memory

    // create classes from data

    // load into make program

    return true;
};

/**
 * add song to playlist in json file
 */
bool Storage::add(const Song& song) {
    if (fs::exists(file_name) != true) {
        return false;
    }
    return true;
};

/**
 * add playlist to json file
 */
bool Storage::add(const Playlist& playlist) {
    /*
        Example structure:
        [[playlists]]
        id = 1
        name = "Favourites"
        songs = [1, 2] # list of song IDs
    */
    if (fs::exists(file_name) != true) {
        return false;
    }

    // write to file
    {  // context manager

        std::ofstream file(file_name, std::ios::app);
        file << "[[playlists]]\n";
        file << "id = " + std::to_string(playlist.get_id()) + "\n";
        file << "name = \"" + playlist.to_string() + "\"\n";
        file << "songs = [" + playlist.get_song_ids() + "]\n";
        file.close();
    }

    return true;
};