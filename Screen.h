//
// Created by alexsandro on 07/03/18.
//

#ifndef ROGUE_LIKE_SCREEN_H
#define ROGUE_LIKE_SCREEN_H


class Screen {
    int _height, _width;
public:
    // Initialize ncurses library
    Screen();
    // Clear ncurses
    ~Screen();
    // Print message on the screen
    void add(const char *message);

    int height();
    int width();
};


#endif //ROGUE_LIKE_SCREEN_H
