#include <ncurses.h>

// #include <vector>
#include <iostream>

#include "config.hpp"
#include "playlist.hpp"
#include "song.hpp"
#include "storage.hpp"

#define playlists_window_width 30
#define playlists_starting_cols_across 3
#define songs_window_width 50
#define songs_starting_cols_across 33

#define KEY_ENTER 10

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
    werase(window);  // clear playlist window

    wattron(window, COLOR_PAIR(1));
    box(window, 0, 0);  // make box have borders
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 2, "%s", title);  // playlist word still white

    std::string name;
    for (int i = 0; i < (int)list.size(); i++) {
        if (i == selected_item) {
            wattron(window, COLOR_PAIR(2));
        }

        if (title == "Playlists") {
            name = list.at(i).to_string();
        } else if (title == "Songs") {
            name = list.at(i).to_string();
        }

        mvwprintw(window, (i + 1), 3, "%s", name.c_str());

        if (i == selected_item) {
            wattroff(window, COLOR_PAIR(2));
        }
    }
    // refresh once per frame
    wrefresh(window);
}

int main() {
    Database db;

    std::optional<config_t> opt_config = Config::get_config();

    if (!opt_config.has_value()) {
        std::cerr << "Failed to load config\n";
        return 1;
    }
    config_t config = *opt_config;

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

    Storage storage{};  // () here causes an error c++ thinks it is a function

    std::string music_dir = std::get<std::string>(config.at("music_dir"));
    std::optional<Database> odb = storage.load(music_dir);
    if (!odb.has_value()) {
        std::cerr << "Failed to load database\n";
        return 1;
    }
    db = *odb;

    // main playlist section
    // newwin(lines down, cols across, starting lines down, starting cols across)
    WINDOW* playlist_window = newwin(
        (screen_y - 3),
        playlists_window_width,
        1,
        playlists_starting_cols_across);  // Playlists
    keypad(playlist_window, TRUE);        // enable keyboard on playlist window

    WINDOW* song_window = newwin(
        (screen_y - 3),
        songs_window_width,
        1,
        songs_starting_cols_across);  // songs window
    keypad(song_window, TRUE);

    refresh();  // create playlists & songs window on screen

    int selected_playlist = 0;
    int selected_song = 0;
    int input;
    Mode current_mode = PLAYLIST;

    // initial render
    render_window("Playlists", playlist_window, db.playlists, selected_playlist);
    render_window("Songs", song_window, (db.playlists.at(selected_playlist).get_songs()), selected_song);

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
                    if (selected_playlist < (int)db.playlists.size() - 1) {
                        selected_playlist++;
                    }

                } else {
                    if (selected_song < (int)db.playlists.at(selected_playlist).get_songs().size() - 1) {
                        selected_song++;
                    }
                }
                break;

            case KEY_ENTER:  // 10
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

        render_window("Playlists", playlist_window, db.playlists, selected_playlist);
        render_window("Songs", song_window, (db.playlists.at(selected_playlist).get_songs()), selected_song);
    }

    endwin();  // End ncurses mode
    return 0;
};