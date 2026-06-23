#pragma once

#include <string>
#include <vector>

#include "ncurses.h"
#include "playlist.hpp"
#include "song.hpp"

class Tui {
   public:
    Tui();
    template <typename T>
    void render_window(const char* title, WINDOW* window, const std::vector<T>& list,
                       int selected_item);
    const int get_screen_x(void) const;
    const int get_screen_y(void) const;
    void exit(void);

   private:
    int _screen_y{}, _screen_x{};
};