#pragma once

#include <algorithm>
#include <iostream>
#include <string>

class Song {
   private:
    std::string name;      // song's name ( made from filename)
    std::string file_loc;  // path to file
    int length_s;          // song length (in seconds)
    static int counter;    // static auto incrementation helper
    int ID;                // auto incrementation value + 1 on creation

   public:
    /**
     * constructor for Song
     *
     * const std::string& location = path to file,
     * const int& length_seconds = song's lngth in seconds
     *
     * @note
     * assigns ++counter to Self.ID
     *
     * @name
     * name is filename where _ = ' '
     */
    Song(const std::string& location, const int& length_seconds);

    /**
     * Convert song to std::string
     */
    std::string to_string(void) const;

    /**
     * Get song's auto incremented ID
     */
    int get_ID(void) const;

    /**
     * Get file path + file and extension
     */
    const std::string& get_file_location(void) const;

    /**
     * Get song's length in seconds
     */
    const int get_song_length_seconds(void) const;
};