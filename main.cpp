#include <ncurses.h>
#include "Screen.h"
#include "Frame.h"


void game_loop(Frame &game_map, Frame &viewport, Character &main_char, int ch) {
    if (ch == 'q' || ch == 'Q')
        return;

    game_map.add(main_char);
    viewport.center(main_char);
    viewport.refresh();

    while(true) {
       ch = getch();
       switch (ch) {
           case KEY_LEFT:
               game_map.add(main_char, main_char.row(), main_char.col() - 1);
               viewport.center(main_char);
               viewport.refresh();
               break;
           case KEY_RIGHT:
               game_map.add(main_char, main_char.row(), main_char.col() + 1);
               viewport.center(main_char);
               viewport.refresh();
               break;
           case KEY_UP:
               game_map.add(main_char, main_char.row() - 1, main_char.col());
               viewport.center(main_char);
               viewport.refresh();
               break;
           case KEY_DOWN:
               game_map.add(main_char, main_char.row() + 1, main_char.col());
               viewport.center(main_char);
               viewport.refresh();
               break;
           default:
               break;
       }
        if(ch == 'q' || ch == 'Q') {
            break;
        }
    }
}

int main() {
    // Initialize ncurses
    Screen scr;

    // Print a welcome message on screen
    scr.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");

    int ch = getch();

    // Create an ncurses window to store the game map. This will be twice the size
    // of the screen and it will be positioned at (0,0) in screen coordinates
    Frame game_map(2*scr.height(), 2*scr.width(), 0, 0);

    // Create an ncurses subwindow of the game map. This will have the size
    // of the user screen and it will be initially postioned at (0, 0)
    Frame viewport(game_map, scr.height(), scr.width(), 0, 0);

    // Initialize the main character. We are going to put this in the middle of
    // the game map (for now)
    Character main_char('@', game_map.height()/2, game_map.width()/2);

    // Fill the game map with numbers
    game_map.gen_Perlin(245);

    game_loop(game_map, viewport, main_char, ch);

    return 0;
}

