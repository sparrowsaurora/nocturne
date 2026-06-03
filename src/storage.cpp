#include "storage.hpp"

std::optional<Database> Storage::load(const path_t& directory) {
    // if not exists return std::nullopt

    Database db;
    const int duration{100};

    // std::cout << directory.filename() << std::endl;  // reads dir filenames

    for (const auto& playlist : fs::directory_iterator(directory)) {
        // file.path() == whole path file name
        // file.path().filename() == file name only
        // std::cout << "\t" << playlist.path().filename() << std::endl;
        Playlist pl(directory.filename());  // make playlist

        for (const auto& song : fs::directory_iterator(playlist.path())) {
            // std::cout << "\t\t" << song.path().filename() << std::endl;
            Song sg(song.path().filename(), duration);
            pl.add(sg);
        }

        db.playlists.push_back(pl);
        // TODO: fill duration with actual value

        // read songs into memory
        // Song song(file.path(), duration);
        // db.playlists.add(song);
    }

    return db;
}
