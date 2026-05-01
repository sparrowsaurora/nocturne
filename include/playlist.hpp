#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "song.hpp"

class Playlist {
   private:
    std::string name;
    std::vector<Song> songs;

   public:
    Playlist(const std::string& playlist_name);
    void add(const Song& song);
    void remove(int song_ID);
    void render(void);
    unsigned short size(void);
};