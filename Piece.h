#ifndef PIECE_H
#define PIECE_H
#include "Constants.h"
#include <string>

using namespace std;

class Piece {
private:
    Color color;
    Rank rank;
    bool flipped;

public:
    Piece(Color c = NONE, Rank r = EMPTY);
    bool isFlipped() const;
    void flip();
    Color getColor() const;
    Rank getRank() const;
    string getName() const;
};
#endif