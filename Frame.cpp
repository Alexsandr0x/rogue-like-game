//
// Created by alexsandro on 07/03/18.
//
#include "Frame.h"
#include "PerlinNoise.h"

Frame::Frame(int nr_rows, int nr_cols, int row_0, int col_0) {
    _has_super = FALSE;
    _super = NULL;
    _w = newwin(nr_rows, nr_cols, row_0, col_0);
    _height = nr_rows;
    _width = nr_cols;
    _row = row_0;
    _col = col_0;
};

Frame::Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0) {
    _has_super = TRUE;
    _super = sw.win();
    _w = derwin(sw.win(), nr_rows, nr_cols, row_0, col_0);
    _height = nr_rows;
    _width = nr_cols;
    _row = row_0;
    _col = col_0;
}

Frame::~Frame() {
    delwin(_w);
}

void Frame::add(Character &x) {
    mvwaddch(_w, x.row(), x.col(), x.symbol());
}

void Frame::erase(Character &x) {
    mvwaddch(_w, x.row(), x.col(), ' ');
}

void Frame::add(Character &x, int row_0, int col_0) {

    char target = mvwinch(_w, row_0, col_0);

    if (target == '~' || target == '#' || target == 'S') {
        return;
    }

    if((row_0 >= 0 && row_0 < _height) && (col_0 >= 0 && col_0 < _width)) {
        erase(x);
        mvwaddch(_w, row_0, col_0, x.symbol());
        x.pos(row_0, col_0);
    }
}

void Frame::center(Character &x) {
    if(_has_super) {
        int rr = _row, cc = _col, hh, ww;
        int _r = x.row() - _height/2;
        int _c = x.col() - _width/2;

        getmaxyx(_super, hh, ww);

        if(_c + _width >= ww) {
            int delta = ww - (_c + _width);
            cc = _c + delta;
        }
        else {
            cc = _c;
        }

        if(_r + _height >= hh) {
            int delta = hh - (_c + _width);
            rr = _r + delta;
        }
        else {
            rr = _r;
        }

        if (_r < 0) {
            rr = 0;
        }

        if (_c < 0) {
            cc = 0;
        }


        move(rr, cc);
    }
}

void Frame::refresh() {
    if(_has_super) {
        touchwin(_super);
    }
    wrefresh(_w);
}

// Move a window in a new position (r, c)
void Frame::move(int r, int c) {
    if(_has_super) {
        mvderwin(_w, r, c);
        _row = r;
        _col = c;
        refresh();
    }
}

void Frame::gen_Perlin(const unsigned int &seed) {
    PerlinNoise pn(seed);
    for(int i = 0; i < _height; ++i) {
        for(int j = 0; j < _width; ++j) {
            double x = (double)j/((double) _width);
            double y = (double)i/((double) _height);

            double n = pn.noise(10 * x, 10 * y, 0.8);

            // Water
            if(n < 0.35) {
                mvwaddch(_w, i, j, '~');
            }
            // Floor
            else if (n >= 0.35 && n < 0.6) {
                mvwaddch(_w, i, j, '.');
            }
            // Walls
            else if (n >= 0.6 && n < 0.8) {
                mvwaddch(_w, i, j, '#');
            }
            // Ice
            else {
                mvwaddch(_w, i, j, 'S');
            }
        }
    }
}

void Frame::fill_window() {
    int max_x = _width/2;
    int max_y = _height/2;
    // Fill the first region with 0's
    for(int y = 0; y < max_y; ++y) {
        for(int x = 0; x < max_x; ++x) {
            mvwaddch(_w, y, x, '0');
        }
    }

    // Fill the second region with 1's
    for(int y = 0; y < max_y; ++y) {
        for(int x = max_x; x < _width; ++x) {
            mvwaddch(_w, y, x, '1');
        }
    }

    // Fill the third region with 2's
    for(int y = max_y; y < _height; ++y) {
        for(int x = 0; x < max_x; ++x) {
            mvwaddch(_w, y, x, '2');
        }
    }

    // Fill the fourth region with 3's
    for(int y = max_y; y < _height; ++y) {
        for(int x = max_x; x < _width; ++x) {
            mvwaddch(_w, y, x, '3');
        }
    }

    for(int y = 0; y < _height; ++y) {
        mvwaddch(_w, y, 0, '-');
        mvwaddch(_w, y, _width - 1, '-');
    }

    for(int x = 0; x < _width; ++x) {
        mvwaddch(_w, 0, x, '|');
        mvwaddch(_w, _height - 1, x, '|');
    }
}

// Get the window
WINDOW* Frame::win() {
    return _w;
}

// Get the parent window
WINDOW* Frame::super() {
    return _super;
}

// Get window type, if TRUE we have a subwindow, if FALSE we have a main window
bool Frame::has_super() {
    return _has_super;
}

// Get the height of the window
int Frame::height() {
    return _height;
}

// Get the width of the window
int Frame::width() {
    return _width;
}

// Get the row (y) position of the window
int Frame::row() {
    return _row;
}

// Get the row (y) position of the window
int Frame::col() {
    return _col;
}