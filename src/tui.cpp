#include "tui.hpp"

template <typename T>
void Tui::render_window(const char* title, WINDOW* window, const std::vector<T>& list,
                        int selected_item) {
    werase(window);  // clear playlist window

    wattron(window, COLOR_PAIR(1));
    box(window, 0, 0);  // make box have borders
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 2, "%s", title);  // playlist word still white

    std::string name;
    for (int i{}; i < (int)list.size(); i++) {
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

// force compiler to acknowledge types
template void Tui::render_window<Playlist>(const char*, WINDOW*, const std::vector<Playlist>&, int);

template void Tui::render_window<Song>(const char*, WINDOW*, const std::vector<Song>&, int);