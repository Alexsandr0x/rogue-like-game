//
// Created by alexsandro on 07/03/18.
//

#ifndef ROGUE_LIKE_CHARACTER_H
#define ROGUE_LIKE_CHARACTER_H


class Character {
    int _row, _col;
    char _symbol;
public:
    // Create a Character
    Character(char symbol, int row_0, int col_0);
    // Change Character position
    void pos(int row_0, int col_0);
    // Get Char's row (Y) position
    int row();
    // Get Char's col (X) position
    int col();
    // Get Char's symbol
    char symbol();
};


#endif //ROGUE_LIKE_CHARACTER_H
