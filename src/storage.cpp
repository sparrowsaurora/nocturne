#include "storage.hpp"

std::optional<Database> Storage::load(const path_t& directory) {
    Database db;
    const int duration{100};

    std::cout << directory.filename() << std::endl;  // reads dir filenames

    Playlist playlist(directory.filename());  // make playlist
    for (const auto& playlist : fs::directory_iterator(directory)) {
        // file.path() == whole path file name
        // file.path().filename() == file name only
        std::cout << "\t" << playlist.path().filename() << std::endl;

        for (const auto& song : fs::directory_iterator(playlist.path())) {
            std::cout << "\t\t" << song.path().filename() << std::endl;
        }
        // TODO: fill duration with actual value

        // read songs into memory
        // Song song(file.path(), duration);
        // db.playlists.add(song);
    }

    // if not return std::nullopt

    // open <music> Dir

    // read lines

    // store lines in memory

    // create classes from data

    // load into make program

    return db;
}
