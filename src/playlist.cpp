#include "playlist.hpp"

Playlist::Playlist(const std::string& playlist_name) : name(playlist_name) {}

void Playlist::add(const Song& song) {
    songs.push_back(song);
}

void Playlist::remove(int song_ID) {
    // find song by ID

    // remove song
}

std::string Playlist::render(void) {
    return name;
}

unsigned short Playlist::size() {
    return songs.size();
}