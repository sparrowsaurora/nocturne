#include <ncurses.h>

#include <vector>

#include "playlist.hpp"
#include "song.hpp"
#include "storage.hpp"

enum Mode {
    PLAYLIST,
    SONG,
};

template <typename T>
void render_window(
    const char* title,
    WINDOW* window,
    const std::vector<T>& list,
    int selected_item) {
    std::string name;

    werase(window);  // clear playlist window

    wattron(window, COLOR_PAIR(1));
    box(window, 0, 0);  // make box have borders
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 2, "%s", title);  // playlist word still white

    for (int i = 0; i < (int)list.size(); i++) {
        if (i == selected_item) {
            wattron(window, COLOR_PAIR(2));
        }

        name = list.at(i).to_string();
        mvwprintw(window, (i + 1), 3, "%s", name.c_str());

        if (i == selected_item) {
            wattroff(window, COLOR_PAIR(2));
        }
    }

    // refresh once per frame
    wrefresh(window);
}

int main() {
    std::vector<Playlist> playlists;

    // setup
    initscr();      // Start ncurses mode
    start_color();  // turns on colour
    cbreak();
    noecho();

    // colour pairs
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    int screen_y, screen_x;
    getmaxyx(stdscr, screen_y, screen_x);

    // Prep default data
    Song song1("song1", "somewhere", 654);
    Song song2("song2", "nowhere", 324);
    Song song3("song3", "everywhere", 68);

    Playlist pl("Playlist:1");
    pl.add(song1);
    pl.add(song2);
    playlists.push_back(pl);

    Playlist pl2("Playlist:2");
    pl2.add(song2);
    pl2.add(song3);
    playlists.push_back(pl2);

    // Storage storage{};  // () here causes an error c++ thinks it is a function
    // storage.add(pl2);

    // main playlist section
    // newwin(lines down, cols across, starting lines down, starting cols across)
    WINDOW* playlist_window = newwin((screen_y - 3), 30, 1, 3);  // Playlists
    keypad(playlist_window, TRUE);                               // enable keyboard on playlist window

    WINDOW* song_window = newwin((screen_y - 3), 30, 1, 33);  // songs window
    keypad(song_window, TRUE);

    refresh();  // create playlists & songs window on screen

    int selected_playlist = 0;
    int selected_song = 0;
    int input;
    Mode current_mode = PLAYLIST;

    // initial render
    render_window("Playlists", playlist_window, playlists, selected_playlist);
    render_window("Songs", song_window, (playlists.at(selected_playlist).get_songs()), selected_song);

    // main loop
    while ((input = wgetch(
                (current_mode == PLAYLIST)
                    ? playlist_window
                    : song_window)) != 'q') {  // get key press
        switch (input) {
            case KEY_UP:
                if (current_mode == PLAYLIST) {
                    if (selected_playlist > 0) {
                        selected_playlist--;
                    }

                } else {
                    if (selected_song > 0) {
                        selected_song--;
                    }
                }
                break;

            case KEY_DOWN:
                if (current_mode == PLAYLIST) {
                    if (selected_playlist == (int)playlists.size() - 1) {
                        continue;
                    }
                    selected_playlist++;
                } else {
                    if (selected_song == (int)playlists.at(selected_playlist).get_songs().size() - 1) {
                        continue;
                    }
                    selected_song++;
                }
                break;

            case 10:  // KEY_ENTER
                // switch window to song navigation
                if (current_mode == PLAYLIST) {
                    current_mode = SONG;
                } else {
                    current_mode = PLAYLIST;
                    selected_song = 0;
                }
                break;

            default:
                break;
        }

        render_window("Playlists", playlist_window, playlists, selected_playlist);
        render_window("Songs", song_window, (playlists.at(selected_playlist).get_songs()), selected_song);
    }

    endwin();  // End ncurses mode
    return 0;
};