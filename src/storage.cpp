#include "storage.hpp"

Storage::Storage(void){};

/**
 * Load file contents into app
 */
bool Storage::load(void) {
    // open json file

    // store lines in memory

    // create classes from data

    // load into make program
};

/**
 * add song to playlist in json file
 */
bool Storage::add(const Song& song) {
    if (fs::exists(json_file) != true) {
        return false;
    }
};

/**
 * add playlist to json file
 */
bool Storage::add(const Playlist& playlist) {
    if (fs::exists(json_file) != true) {
        return false;
    }

    // write to file
    // playlist.to_string();
};