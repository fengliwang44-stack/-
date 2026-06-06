#include "Piece.h"

Piece::Piece(Color c, Rank r) {
    color = c;
    rank = r;
    flipped = false;
}

bool Piece::isFlipped() const {
    return flipped; 
}
// piece flipped ?
void Piece::flip() {
    flipped = true; 
}
//piece on
Color Piece::getColor() const {
    return color; 
}
//piece's team
Rank Piece::getRank() const {
    return rank; 
}
// piece's rank
string Piece::getName() const {
    if (!flipped)    //if not flipped cout this
        return " [■] ";
    if (color == NONE)     //no color represent no piece here
        return "  -  ";

    if (color == RED) {    //cout  piece's name
        switch (rank) {
        case GENERAL: return " 帥 "; case ADVISOR: return " 仕 "; case HORSE: return " 相 ";
        case ROOK:    return " 陣 "; case KNIGHT:  return " 傌 "; case CANNON: return " 炮 ";
        case SOLDIER: return " 兵 "; default: return "  -  ";
        }
    }
    else {
        switch (rank) {
        case GENERAL: return " 將 "; case ADVISOR: return " 士 "; case HORSE: return " 象 ";
        case ROOK:    return " 車 "; case KNIGHT:  return " 馬 "; case CANNON: return " 包 ";
        case SOLDIER: return " 卒 "; default: return "  -  ";
        }
    }
}