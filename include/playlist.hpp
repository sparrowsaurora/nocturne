#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "song.hpp"

class Playlist {
   private:
    std::string name;         // name of playlist
    std::vector<Song> songs;  // songs in the playlist
    static int counter;
    int ID;

   public:
    /**
     * constructor for Playlist
     *
     * const std::string& playlist_name = name
     */
    Playlist(const std::string& playlist_name);

    /**
     * adds a song to the 'songs' vector
     *
     * @note
     * adds as const reference
     */
    void add(const Song& song);

    /**
     * removes a song from the 'songs' vector
     *
     * @note
     * removal requires getting the song's ID first
     */
    void remove(int song_ID);

    /**
     * Convert song to std::string
     */
    std::string to_string(void) const;

    /**
     * returns the number of songs in the vector
     */
    unsigned short size(void);

    /**
     * returns a reference to the songs vector
     */
    const std::vector<Song>& get_songs(void) const;

    const int get_id(void) const;

    const std::string get_song_ids(void) const;
};