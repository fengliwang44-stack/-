#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Piece.h"

using namespace std;

int main() {

 
    Board game;
    Color turn = RED;
    char cmd;

    while (true) {
        game.display();
        cout << "\nTurn: " << (turn == RED ? "紅方 (R)" : "黑方 (B)") << endl;
        cout << " " << endl;
        cout << " 翻牌按 f   輸入  (行,列)  " << "\n\n";
        cout << " 移動按 m   輸入  (行1 列1  to  行2 列2)  " << "\n\n";
        cout << " 投降輸一半按 q" << "\n\n";
        cout << " 輸入下一步 :";
        cin >> cmd;

        if (cmd == 'q') {
            cout << (turn == RED ? "\n 黑方(B) WIN" : "\n 紅方(R) WIN")  << endl;
            break;
        }

        if (cmd == 'f') {
            int r, c;
            if (cin >> r >> c) {
                // 直接呼叫 board 內部的翻牌函式
                if (game.flipPiece(r, c)) {
                    turn = (turn == RED ? BLACK : RED); // 成功翻牌才換人
                }
                else {
                    cout << "\n\n";
                    cout << "Invalid Move!" << endl; // 失敗時顯示提示
                }
            }
        }
        else if (cmd == 'm') {
            int r1, c1, r2, c2;
            if (cin >> r1 >> c1 >> r2 >> c2) {
                if (game.move(r1, c1, r2, c2, turn)) {
                    Color winner = game.checkWinner();
                    if (winner != NONE) {
                        game.display();
                        cout << (winner == RED ? "RED WINS!" : "BLACK WINS!") << endl;
                        break; // 跳出 while 迴圈，結束遊戲
                    }
                    turn = (turn == RED ? BLACK : RED);
                }
                else {
                    cout << "\n\n";
                    cout << "Invalid Move!" << endl;
                }
            }
        }
    }
    return 0;
}