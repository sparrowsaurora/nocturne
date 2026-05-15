#include "song.hpp"

int Song::counter = 0;  // start counter for auto incrementing ID

Song::Song(const std::string& location, const int& length_seconds) : file_loc(location), length_s(length_seconds) {
    ID = ++counter;
    name = location;
    name.erase(name.length() - 4);                     // removes .mp3 from string or any 3 letter video format
    std::replace(name.begin(), name.end(), '_', ' ');  // replace '_' with ' '
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