#pragma once
#include "dialog.h"
#include <vector>
#include <memory>

Dialog player_coroutine(std::shared_ptr<std::vector<char>> board, char symbol);

void print_board(const std::vector<char>& board);

char check_winner(const std::vector<char>& board);

bool board_full(const std::vector<char>& board);
