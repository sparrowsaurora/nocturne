#pragma once

#include <iostream>
#include <string>

class Song {
   private:
    std::string name;
    std::string file_loc;
    int length_s;

   public:
    Song(const std::string& name, const std::string& location, const int& length_seconds);
    void render(void);
};