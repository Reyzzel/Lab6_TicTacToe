#include "tictactoe.h"
#include <iostream>

using namespace std;

int main()
{
    srand((unsigned)time(nullptr));

    auto board = make_shared<vector<char>>(9, '.');

    Dialog p0 = player_coroutine(board, 'X');
    Dialog p1 = player_coroutine(board, 'O');
    Dialog p2 = player_coroutine(board, 'T');

    vector<Dialog*> players = { &p0, &p1, &p2 };
    vector<char> symbols = { 'X', 'O', 'T' };

    int current = 0;
    int move = 0;

    cout << "Start Tic-Tac-Toe for 3 players\n";
    print_board(*board);

    while (true)
    {
        int chosen = players[current]->ask(move);

        if (chosen >= 0 && chosen < 9 && (*board)[chosen] == '.') {
            (*board)[chosen] = symbols[current];
            cout << "Player " << symbols[current]
                 << " -> " << chosen << "\n";
        }
        else {
            cout << "Player " << symbols[current] << " invalid/passed\n";
        }

        print_board(*board);

        char w = check_winner(*board);
        if (w != '.') {
            cout << "Winner: " << w << "\n";
            break;
        }

        if (board_full(*board)) {
            cout << "Draw!\n";
            break;
        }

        current = (current + 1) % 3;
        move++;
    }

    cout << "Game over\n";
    return 0;
}
