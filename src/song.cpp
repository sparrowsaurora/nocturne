#include "song.hpp"

Song::Song(const std::string& song_name, const std::string& location, const int& length_seconds) : name(song_name), file_loc(location), length_s(length_seconds) {}

std::string Song::render() const {
    return name;
}

const int Song::get_ID() {
    return ID;
}