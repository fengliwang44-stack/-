#include "Board.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Board::Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = nullptr;   //初始化

    vector<Piece*> pool;    //暫時放旗子的array
    Rank rks[] = { GENERAL, ADVISOR, ADVISOR, HORSE, HORSE, ROOK, ROOK, KNIGHT, KNIGHT, CANNON, CANNON, SOLDIER, SOLDIER, SOLDIER, SOLDIER, SOLDIER };

    for (int i = 0; i < 16; i++) {      //put in piece
        pool.push_back(new Piece(RED, rks[i]));
        pool.push_back(new Piece(BLACK, rks[i]));
    }

    random_device rd;       //亂數產生器
    mt19937 g(rd());        //梅森旋轉演算法
    shuffle(pool.begin(), pool.end(), g);       //執行洗牌

    int k = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = pool[k++];
}

void Board::display() {
    cout << "\n   ";
    for (int j = 0; j < 8; j++) {
        cout << setw(6) << j;
    }
    cout << "\n   " << string(55, '-') << endl;

    // 2. 印出棋盤內容
    for (int i = 0; i < 4; i++) {
    
        cout << " " << i << " | ";

        for (int j = 0; j < 8; j++) {
            cout << setw(6) << grid[i][j]->getName();
        }
        cout << "\n   |" << endl; 
    }
    cout << "   " << string(55, '-') << endl;
}
bool Board::flipPiece(int r, int c) {
    // 1. 檢查範圍是否合法
    if (r < 0 || r > 3 || c < 0 || c > 7) {
        return false;
    }

    Piece* p = grid[r][c];

    // 2. 檢查：必須有棋子 且 該棋子目前是「蓋著的」
    // (如果已經翻開，或者那格是空的，就不能翻)
    if (p != nullptr && !p->isFlipped()) {
        p->flip();
        return true; // 翻牌成功
    }

    return false; // 翻牌失敗 (位置錯誤、已翻開、或是空的)
}

Color Board::checkWinner() {
    bool hasRed = false;
    bool hasBlack = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = grid[i][j];
            // 只統計「已翻開」且「不是空位」的棋子
            if (p && p->isFlipped() && p->getRank() != EMPTY && p->getColor() != NONE) {
                if (p->getColor() == RED) hasRed = true;
                if (p->getColor() == BLACK) hasBlack = true;
            }
        }
    }

    if (!hasRed) return BLACK; // 紅方沒棋了，黑方獲勝
    if (!hasBlack) return RED; // 黑方沒棋了，紅方獲勝
    return NONE;               // 遊戲繼續
}

//取得棋子的指標
Piece* Board::getPiece(int r, int c) {
    if (r < 0 || r >= 4 || c < 0 || c >= 8) return nullptr;
    return grid[r][c];
}

bool Board::isCannonPathClear(int r1, int c1, int r2, int c2) {
    if (r1 != r2 && c1 != c2) return false; // 必須直線

    int count = 0;
    if (r1 == r2) { // 水平
        int start = min(c1, c2) + 1;
        int end = max(c1, c2);
        for (int j = start; j < end; j++)
            if (grid[r1][j]->getRank() != EMPTY) count++;
    }
    else { // 垂直
        int start = min(r1, r2) + 1;
        int end = max(r1, r2);
        for (int i = start; i < end; i++)
            if (grid[i][c1]->getRank() != EMPTY) count++;
    }
    return (count == 1); // 必須隔著一顆
}
//棋子移動跟吃棋子判定 use pointer
bool Board::move(int r1, int c1, int r2, int c2, Color turn) {
    // 1. 檢查是否在棋盤中
    if (r1 < 0 || r1 > 3 || c1 < 0 || c1 > 7 || r2 < 0 || r2 > 3 || c2 < 0 || c2 > 7) 
        return false;
    Piece* src = grid[r1][c1];
    Piece* dst = grid[r2][c2];
    if (!src || !src->isFlipped() || src->getColor() != turn) 
        return false;

    // 2. 定義兩種合法的移動模式
    bool isAdjacent = (abs(r1 - r2) + abs(c1 - c2) == 1);
    bool isCannonJump = (src->getRank() == CANNON &&
        dst->isFlipped() &&
        dst->getColor() != NONE &&
        dst->getColor() != turn &&
        isCannonPathClear(r1, c1, r2, c2));

    // 3. 如果不是炮，也不相鄰，則不能移動
    if (!isAdjacent && !isCannonJump)
        return false;

    // 4. 吃子規則判斷 (若為炮飛吃，直接跳過比大小)
    if (dst->isFlipped() && dst->getColor() != NONE) {
        if (dst->getColor() == turn)
            return false; // 吃自己人

        // 若不是炮飛吃，才進行大小比較
        if (!isCannonJump) {
            if (src->getRank() == SOLDIER && dst->getRank() == GENERAL) { 
            //兵吃將 就不會進else if
            }
            else if (src->getRank() < dst->getRank() && src->getRank() != CANNON) return false;
        }
    }

    // 5. 執行移動
    grid[r2][c2] = src;
    grid[r1][c1] = new Piece(NONE, EMPTY);
    grid[r1][c1] ->flip();
    return true;
}