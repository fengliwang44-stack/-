#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

class Board {
private:
    Piece* grid[4][8];

public:
    Board();
    void display();
    Piece* getPiece(int r, int c);
    Color checkWinner(); // 回傳目前的贏家，若無則回傳 NONE
    bool flipPiece(int r, int c); // 處理翻牌邏輯，成功回傳 true
    bool isCannonPathClear(int r1, int c1, int r2, int c2);
    bool move(int r1, int c1, int r2, int c2, Color turn);
};
#endif