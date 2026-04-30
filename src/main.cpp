#include <ncurses.h>

#include "song.hpp"

int main() {
    // initscr();  // Start ncurses mode
    // printw("Hello, ncurses!");
    // refresh();  // Print to screen
    // getch();    // Wait for key press
    // endwin();   // End ncurses mode
    Song song1("song1", "somewhere", 654);
    song1.render();

    return 0;
};