#include "tictactoe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Dialog player_coroutine(shared_ptr<vector<char>> board, char symbol)
{
    while (true)
    {
        vector<int> empty;
        for (int i = 0; i < 9; i++)
            if ((*board)[i] == '.') empty.push_back(i);

        if (empty.empty())
            co_yield -1;

        int move = empty[rand() % empty.size()];
        co_yield move;
    }
}

void print_board(const vector<char>& board)
{
    cout << "Board:\n";
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++)
            cout << board[r * 3 + c] << ' ';
        cout << "\n";
    }
}

char check_winner(const vector<char>& board)
{
    const int L[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto &l : L)
        if (board[l[0]] != '.' &&
            board[l[0]] == board[l[1]] &&
            board[l[1]] == board[l[2]])
            return board[l[0]];

    return '.';
}

bool board_full(const vector<char>& board)
{
    for (char c : board) if (c == '.') return false;
    return true;
}
