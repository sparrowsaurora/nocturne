#include "playlist.hpp"

int Playlist::counter = 0;

Playlist::Playlist(const std::string& playlist_name) : name(playlist_name) {
    ID = ++counter;
}

void Playlist::add(const Song& song) {
    songs.push_back(song);
}

void Playlist::remove(int song_ID) {
    // find song by ID

    // remove song
}

std::string Playlist::to_string(void) const {
    return name;
}

unsigned short Playlist::size() {
    return songs.size();
}

const std::vector<Song>& Playlist::get_songs(void) const {
    return songs;
}

const int Playlist::get_id(void) const {
    return ID;
}

const std::string Playlist::get_song_ids(void) const {
    std::string song_ids;
    std::string delimiter = ", ";

    for (auto song : songs) {
        song_ids += std::to_string(song.get_ID());
        song_ids += delimiter;
    }

    song_ids.erase(song_ids.length() - 2);  // remove last delimiter

    return song_ids;
}