#include "playlist.hpp"

Playlist::Playlist(const std::string& playlist_name) : name(playlist_name) {}

void Playlist::add(const Song& song) {
    songs.push_back(song);
}

void Playlist::remove(int song_ID) {
    // find song by ID

    // remove song
}

void Playlist::render(void) {
    std::cout << name << " contains: " << std::endl;
    for (Song song : songs) {
        std::cout << "\t- " << song.get_name() << std::endl;
    }
}

unsigned short Playlist::size() {
    return songs.size();
}