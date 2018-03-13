//
// Created by alexsandro on 10/03/18.
//

#ifndef ROGUE_LIKE_MAINPLAYER_H
#define ROGUE_LIKE_MAINPLAYER_H

#include "Character.h"

class MainPlayer : public Character {
public:
    MainPlayer(char symbol, int row_0, int col_0) : Character(symbol, row_0, col_0) {}

private:
    int _field_of_view;
};


#endif //ROGUE_LIKE_MAINPLAYER_H
