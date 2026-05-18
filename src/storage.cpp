#include "storage.hpp"

Storage::Storage(void) {
    std::ofstream file(file_name);
};

std::optional<Database> Storage::load(Database database) {
    if (fs::exists(file_name) != true) {
        return std::nullopt;
    }

    // open file

    // read lines

    // store lines in memory

    // create classes from data

    // load into make program

    return database;
};

bool Storage::refresh_cache(const std::string& dir) {
    // reads <music> directory
    for (const auto& entry : fs::directory_iterator(dir)) {
        path_t playlist_path = entry.path();

        if (!Storage::add(playlist_path)) return false;
        // TODO: current logic returns false if ANY errors
    }

    return true;
}

bool Storage::add(const path_t& directory) {
    std::cout << directory.filename() << std::endl;  // reads dir filenames

    Playlist playlist(directory.filename());  // make playlist
    for (const auto& file : fs::directory_iterator(directory)) {
        // file.path() == whole path file name
        // file.path().filename() == file name only
        // std::cout << "\t" << file.path().filename() << std::endl;
        // TODO: fill duration with actual value
        const int duration{100};

        // read songs into memory
        Song song(file.path(), duration);
        playlist.add(song);

        // store songs
        Storage::add(song);
    }
    // store playlist
    // NOTE: playlists has to go after songs
    Storage::add(playlist);

    return true;
}

bool Storage::add(const Song& song) {
    /*
        [[songs]]
        id = 1
        file = "/<dir>/BIRDBRAIN.mp3"
        length = 245
    */
    if (fs::exists(file_name) != true) {
        return false;
    }

    {
        std::ofstream file(file_name, std::ios::app);
        file << "[[songs]]\n";
        file << "id = " + std::to_string(song.get_ID()) + "\n";
        file << "file = \"" + song.get_file_location() + "\"\n";
        file << "length = " + std::to_string(song.get_song_length_seconds()) + "\n";
        file.close();
    }

    return true;
};

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