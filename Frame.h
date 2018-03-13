//
// Created by alexsandro on 07/03/18.
//

#ifndef ROGUE_LIKE_FRAME_H
#define ROGUE_LIKE_FRAME_H


#include <curses.h>
#include "Character/Character.h"

class Frame {
    // Frame dimensions
    int _height, _width;
    // Frame position
    int _row, _col;
    // Boolean - FALSE for a window and TRUE for a subwindow (viewport)
    bool _has_super;
    // Pointer to an ncurses WINDOW
    WINDOW *_w;
    // Pointer to an ncurses WINDOW, this will be null for a Window and will point
    // to for a subwindow
    WINDOW *_super;

public:
    // Initialize a main window (no parent)
    Frame(int nr_rows, int nr_cols, int row_0, int col_0);
    // Initialize a subwindow (viewport) with a parent window
    Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
    ~Frame();
    // Fill a window with numbers - the window is split in four equal regions,
    // each region is filled with a single number, so 4 regions and 4 numbers.
    // This is a suggestion of how this will look:
    //         0 | 1
    //         -----
    //         2 | 3
    // This function is used only for debugging purposes.
    void fill_window();
    // Add a character to the window
    void add(Character &x);

    // Add a character to the window with a initial position
    void add(Character &x, int row_0, int col_0);

    void erase(Character &x);
    // Center the viewport around a character
    void center(Character &x);

    int height();
    int width();

    void refresh();

    void move(int r, int c);

    WINDOW *win();

    WINDOW *super();

    bool has_super();

    int col();

    int row();

    void gen_Perlin(const unsigned int &seed);
};


#endif //ROGUE_LIKE_FRAME_H
