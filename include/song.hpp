#pragma once

#include <iostream>
#include <string>

class Song {
   private:
    std::string name;
    std::string file_loc;
    int length_s;        // song length (in seconds)
    static int counter;  // static auto incrementation helper
    int ID;              // auto incrementation value + 1 on creation

   public:
    Song(const std::string& name, const std::string& location, const int& length_seconds);
    std::string to_string(void) const;
    int get_ID(void) const;
};