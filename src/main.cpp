#include <ncurses.h>

#include <vector>

#include "playlist.hpp"
#include "song.hpp"

int main() {
    std::vector<Playlist> playlists;

    initscr();      // Start ncurses mode
    start_color();  // turns on colour
    // printw("Hello, ncurses!");
    // main playlist section

    // newwin(lines down, cols across, starting lines down, starting cols across)

    int screen_y, screen_x;
    getmaxyx(stdscr, screen_y, screen_x);

    WINDOW *playlist_window = newwin((screen_y - 3), 30, 1, 3);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    wattron(playlist_window, COLOR_PAIR(1));
    box(playlist_window, 0, 0);  // make box have borders
    wattroff(playlist_window, COLOR_PAIR(1));

    refresh();  // Print to screen

    mvwprintw(playlist_window, 0, 2, "Playlists");
    // print into box
    // plalists input here
    Song song1("song1", "somewhere", 654);
    // song1.render();

    Song song2("song2", "nowhere", 324);

    Playlist pl("some random name");
    playlists.push_back(pl);
    pl.add(song1);
    pl.add(song2);

    // pl.render();

    Playlist pl2("hello2");
    playlists.push_back(pl2);
    pl2.add(song2);

    std::string playlist_name;
    for (int i = 0; i < playlists.size(); i++) {
        playlist_name = playlists.at(i).render();
        mvwprintw(playlist_window, (i + 1), 3, "%s", playlist_name.c_str());
    }

    wrefresh(playlist_window);

    getch();  // Wait for key press

    // std::cout << "pl1 has: " << pl.size() << " songs" << std::endl;

    endwin();  // End ncurses mode
    return 0;
};