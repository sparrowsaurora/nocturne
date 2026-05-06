#pragma once

#include <iostream>
#include <string>

class Song {
   private:
    std::string name;      // song's name
    std::string file_loc;  // path to file
    int length_s;          // song length (in seconds)
    static int counter;    // static auto incrementation helper
    int ID;                // auto incrementation value + 1 on creation

   public:
    /**
     * constructor for Song
     *
     * const std::string& song_name = song's name,
     * const std::string& location = path to file,
     * const int& length_seconds = song's lngth in seconds
     *
     * @note
     * assigns ++counter to Self.ID
     */
    Song(const std::string& name, const std::string& location, const int& length_seconds);

    /**
     * Convert song to std::string
     */
    std::string to_string(void) const;

    /**
     * Get song's auto incremented ID
     */
    int get_ID(void) const;
};