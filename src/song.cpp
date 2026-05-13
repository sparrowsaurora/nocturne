#include "song.hpp"

int Song::counter = 0;  // start counter for auto incrementing ID

Song::Song(const std::string& song_name, const std::string& location, const int& length_seconds) : name(song_name), file_loc(location), length_s(length_seconds) {
    ID = ++counter;
}

std::string Song::to_string() const {
    return name;
}

int Song::get_ID() const {
    return ID;
}

const std::string& Song::get_file_location(void) const {
    return file_loc;
}

const int Song::get_song_length_seconds(void) const {
    return length_s;
}