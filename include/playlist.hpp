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
    std::string render(void) const;
    unsigned short size(void);
    std::vector<Song>& get_songs(void);
};