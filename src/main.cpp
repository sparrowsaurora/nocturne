#include <ncurses.h>

#include "playlist.hpp"
#include "song.hpp"

int main() {
    // initscr();  // Start ncurses mode
    // printw("Hello, ncurses!");
    // refresh();  // Print to screen
    // getch();    // Wait for key press
    // endwin();   // End ncurses mode
    Song song1("song1", "somewhere", 654);
    song1.render();

    Song song2("song2", "nowhere", 324);

    Playlist pl("some random name");
    pl.add(song1);
    pl.add(song2);

    pl.render();
    std::cout << "pl1 has: " << pl.size() << " songs" << std::endl;

    return 0;
};