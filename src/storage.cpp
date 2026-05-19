#include "storage.hpp"

static inline std::string trim(std::string s) {
    auto not_space = [](unsigned char c) {
        return !std::isspace(c);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());

    return s;
}

Storage::Storage(void) {
    std::ofstream file(file_name);
};

std::optional<Database> Storage::load(Database db) {
    if (fs::exists(file_name) != true) {
        return std::nullopt;
    }

    // open file
    {  // context manager
        std::ifstream ifile(Storage::file_name);

        if (!ifile.is_open()) {
            std::cerr << "Error: Could not open the file!" << std::endl;
            return std::nullopt;
        }

        std::string line, key, value;
        while (std::getline(ifile, line)) {
            svec_t values;
            if (line.empty()) continue;
            if (line == "[[songs]]") {
                for (int i = 0; i < 3; i++) {
                    std::getline(ifile, line);
                    auto pos = line.find('=');
                    if (pos == std::string::npos) continue;

                    // std::string key = trim(line.substr(0, pos));
                    std::string value = trim(line.substr(pos + 1));

                    if (value[0] == '"') {
                        std::erase(value, '"');  // if string in config file remove extra " pair
                    }

                    values.push_back(value);
                }

                std::string file_loc = values.at(1);
                int length = std::stoi(values.at(2));
                Song song(file_loc, length);

                db.songs.push_back(song);

            } else if ("[[playlists]]") {
                for (int i = 0; i < 3; i++) {
                    std::getline(ifile, line);
                    auto pos = line.find('=');
                    if (pos == std::string::npos) continue;

                    std::string value = trim(line.substr(pos + 1));

                    if (value[0] == '"') {
                        std::erase(value, '"');  // if string in config file remove extra " pair
                    }

                    values.push_back(value);
                }
                std::vector<int> song_ids = Playlist::to_song_ids(values.at(2));

                Playlist playlist(values.at(1), song_ids);

                db.playlists.push_back(playlist);
            }
        }
    }
    // read lines

    // store lines in memory

    // create classes from data

    // load into make program

    return db;
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
    // std::cout << directory.filename() << std::endl;  // reads dir filenames

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