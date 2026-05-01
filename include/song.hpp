#pragma once

#include <iostream>
#include <string>

class Song {
   private:
    std::string name;
    std::string file_loc;
    int length_s;
    int ID;

   public:
    Song(const std::string& name, const std::string& location, const int& length_seconds);
    void render(void);

    const std::string& get_name(void);
    const int get_ID(void);
};

// auto increment song ID when a new one is made