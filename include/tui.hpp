#pragma once

#include <string>
#include <vector>

#include "ncurses.h"
#include "playlist.hpp"
#include "song.hpp"

class Tui {
   public:
    template <typename T>
    void render_window(const char* title, WINDOW* window, const std::vector<T>& list,
                       int selected_item);
};