#include <ncurses.h>

#include <SFML/Audio.hpp>
#include <iostream>

#include "config.hpp"
#include "playlist.hpp"
#include "song.hpp"
#include "storage.hpp"
#include "tui.hpp"

#define playlists_window_width 30
#define playlists_starting_cols_across 3
#define songs_window_width 50
#define songs_starting_cols_across 33

#undef KEY_ENTER
#define KEY_ENTER 10

enum class Mode {
    PLAYLIST,
    SONG,
};

int main() {
    // initial setup of screen
    Tui ui{};

    // retrieve config
    std::optional<config_t> opt_config = Config::get_config();
    if (!opt_config.has_value()) {
        std::cerr << "Failed to load config\n";
        return 1;
    }
    config_t config = *opt_config;  // render config file to map

    // start db
    Database db;
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
    WINDOW* playlist_window = newwin((ui.get_screen_y() - 3), playlists_window_width, 1,
                                     playlists_starting_cols_across);  // Playlists
    keypad(playlist_window, TRUE);  // enable keyboard on playlist window

    WINDOW* song_window = newwin((ui.get_screen_y() - 3), songs_window_width, 1,
                                 songs_starting_cols_across);  // songs window
    keypad(song_window, TRUE);

    refresh();  // create playlists & songs window on screen

    int selected_playlist{}, selected_song{}, input{};
    Mode current_mode{Mode::PLAYLIST};

    // initial render of screen
    ui.render_window("Playlists", playlist_window, db.playlists, selected_playlist);
    ui.render_window("Songs", song_window, (db.playlists.at(selected_playlist).get_songs()),
                     selected_song);

    // Event loop
    while ((input = wgetch((current_mode == Mode::PLAYLIST) ? playlist_window : song_window)) !=
           'q') {  // get key press
        switch (input) {
            case KEY_UP:
                if (current_mode == Mode::PLAYLIST) {
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
                if (current_mode == Mode::PLAYLIST) {
                    if (selected_playlist < (int)db.playlists.size() - 1) {
                        selected_playlist++;
                    }

                } else {
                    if (selected_song <
                        (int)db.playlists.at(selected_playlist).get_songs().size() - 1) {
                        selected_song++;
                    }
                }
                break;

            case KEY_ENTER:  // 10
                // switch window to song navigation
                if (current_mode == Mode::PLAYLIST) {
                    current_mode = Mode::SONG;
                } else {
                    current_mode = Mode::PLAYLIST;
                    selected_song = 0;
                }
                break;

            default:
                break;
        }

        ui.render_window("Playlists", playlist_window, db.playlists, selected_playlist);
        ui.render_window("Songs", song_window, (db.playlists.at(selected_playlist).get_songs()),
                         selected_song);
    }

    ui.exit();  // End ncurses mode
    return 0;
};