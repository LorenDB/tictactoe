// TicTacToe.cpp: This file contains code for a tic-tac-toe game.
//
// Copyright (c) 2020, Loren Burkholder
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <unistd.h>

class Board
{
public:
	short m_board[3][3];
	Board()
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_board[i][j] = 0;
	}
};

void drawBoard(Board &);
char getXO(short);
void getMove(Board &, int);
bool gameOver(Board &, bool = false);
void aiMove(Board &, int, int);

int main()
{
	char humanPieceType = '\0';
	int modForHumanValue = 0; // this basically lets us determine when the player moves
	std::cout << "Do you want to be X or O";
	while ((tolower(humanPieceType) != 'x') && (tolower(humanPieceType) != 'o'))
	{
		std::cout << "? ";
		std::cin >> humanPieceType;
		if (tolower(humanPieceType) == 'x')
			modForHumanValue = 1;
		else if (tolower(humanPieceType) == 'o')
			modForHumanValue = 0;
	}
	// seed the PRNG for random moves
    std::srand(static_cast<unsigned int>(std::time(0)));
	Board board;
	drawBoard(board);
	// there are 9 moves total
	for (int i = 0; i < 9; ++i)
	{
		if ((i % 2) == modForHumanValue)
		{
			if (tolower(humanPieceType) == 'x')
				getMove(board, 1);
			else
				getMove(board, 3);
		}
		else
		{
			if (tolower(humanPieceType) == 'x')
				aiMove(board, 3, i);
			else
				aiMove(board, 1, i);
		}
		drawBoard(board); // draw the board befor declaration of game over
		if (gameOver(board))
			break; // exit the loop since the game is over
	}
    if (!gameOver(board, true)) // true makes gameOver be quiet
        std::cout << "It's a tie!\n";
	return 0;
}

void drawBoard(Board &board)
{
	std::cout << "\n\n";
	std::cout << " * * * * * * * * * * * * * \n";
	std::cout << " *       *       *       * \n";
	std::cout << " *   " << getXO(board.m_board[0][0]);
	std::cout << "   *   " << getXO(board.m_board[0][1]);
	std::cout << "   *   " << getXO(board.m_board[0][2]);
	std::cout << "   *\n";
	std::cout << " *       *       *       * \n";
	std::cout << " * * * * * * * * * * * * * \n";
	std::cout << " *       *       *       * \n";
	std::cout << " *   " << getXO(board.m_board[1][0]);
	std::cout << "   *   " << getXO(board.m_board[1][1]);
	std::cout << "   *   " << getXO(board.m_board[1][2]);
	std::cout << "   *\n";
	std::cout << " *       *       *       * \n";
	std::cout << " * * * * * * * * * * * * * \n";
	std::cout << " *       *       *       * \n";
	std::cout << " *   " << getXO(board.m_board[2][0]);
	std::cout << "   *  " << getXO(board.m_board[2][1]);
	std::cout << "    *  " << getXO(board.m_board[2][2]);
	std::cout << "    *\n";
	std::cout << " *       *       *       * \n";
	std::cout << " * * * * * * * * * * * * * \n";
}

char getXO(short num)
{
	if (num == 0)
		return ' ';
	else if (num == 1)
		return 'X';
	else if (num == 3)
		return 'O';
	else
		return '!';
}

void getMove(Board &board, int pieceValue)
{
	short column, row;
	bool validMove = false;
	std::cout << "Your turn. Enter the row number and then the column number.\n";
	while (!validMove)
	{
		std::cout << "Row: ";
		std::cin >> row;
		std::cout << "Column: ";
		std::cin >> column;
        column -= 1;
        row -= 1;
		if ((column < 3 && column >= 0) && (row < 3 && column >= 0) && board.m_board[row][column] == 0)
		{
			validMove = true;
			board.m_board[row][column] = pieceValue;
			break;
		}
		std::cout << "Invalid move. ";
	}
}

bool gameOver(Board &board, bool silent)
{
	bool won = false;
	short tmp[3];
	short winner;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tmp[j] = board.m_board[i][j];
		}
		if ((tmp[0] == tmp[1] && tmp[1] == tmp[2]) && tmp[1] != 0)
		{
			won = true;
			winner = tmp[1];
            break;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tmp[j] = board.m_board[j][i];
		}
		if ((tmp[0] == tmp[1] && tmp[1] == tmp[2]) && tmp[1] != 0)
		{
			won = true;
			winner = tmp[1];
            break;
		}
	}
	for (int i = 0, j = 0; i < 3, j < 3; ++i, ++j)
	{
		tmp[i] = board.m_board[i][j];
	}
	if ((tmp[0] == tmp[1] && tmp[1] == tmp[2]) && tmp[1] != 0)
	{
		won = true;
		winner = tmp[1];
	}
	for (int i = 0, j = 2; i < 3, j >= 0; ++i, --j)
	{
		tmp[i] = board.m_board[i][j];
	}
	if ((tmp[0] == tmp[1] && tmp[1] == tmp[2]) && tmp[1] != 0)
	{
		won = true;
		winner = tmp[1];
	}
	if (won && !silent)
		std::cout << "\n" << getXO(winner) << " won!\n";
	return won;
}

void aiMove(Board &board, int pieceValue, int move)
{
	// make it look like the computer is thinking
	sleep(1);
	short tmp[3];
	int opponentVal;
	if (pieceValue == 1)
		opponentVal = 3;
	else opponentVal = 1;

    
    // thwart possible wins by opponents and look for ways we can win with 2 copies of the same code
	// but you can't get 2 in a row in one move, so we can skip this the first time around
	// the first moves by the players have the numbers 0 and 1, so only run this code if 
	// it's greater than 1
	if (move > 1)
	{	
		// check for possible wins by us
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[i][j];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue * 2)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (board.m_board[i][k] == 0)
					{
						board.m_board[i][k] = pieceValue;
						return;
					}
				}
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[j][i];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue * 2)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (board.m_board[k][i] == 0)
					{
						board.m_board[k][i] = pieceValue;
						return;
					}
				}
			}
		}
		for (int i = 0, j = 0; i < 3, j < 3; ++i, ++j)
		{
			tmp[i] = board.m_board[i][j];
		}
		if (tmp[0] + tmp[1] + tmp[2] == pieceValue * 2)
		{
			for (int k = 0, l = 0; k < 3, l < 3; ++k, ++l)
			{
				if (board.m_board[k][l] == 0)
				{
					board.m_board[k][l] = pieceValue;
					return;
				}
			}
		}
		for (int i = 0, j = 2; i < 3, j >= 0; ++i, --j)
		{
			tmp[i] = board.m_board[i][j];
		}
		if (tmp[0] + tmp[1] + tmp[2] == pieceValue * 2)
		{
			for (int k = 0, l = 2; k < 3, l >= 0; ++k, --l)
			{
				if (board.m_board[l][k] == 0)
				{
					board.m_board[l][k] = pieceValue;
					return;
				}
			}
		}	

		// check for possible opponent wins
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[i][j];
			}
			if (tmp[0] + tmp[1] + tmp[2] == opponentVal * 2)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (board.m_board[i][k] == 0)
					{
						board.m_board[i][k] = pieceValue;
						return;
					}
				}
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[j][i];
			}
			if (tmp[0] + tmp[1] + tmp[2] == opponentVal * 2)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (board.m_board[k][i] == 0)
					{
						board.m_board[k][i] = pieceValue;
						return;
					}
				}
			}
		}
		for (int i = 0, j = 0; i < 3, j < 3; ++i, ++j)
		{
			tmp[i] = board.m_board[i][j];
		}
		if (tmp[0] + tmp[1] + tmp[2] == opponentVal * 2)
		{
			for (int k = 0, l = 0; k < 3, l < 3; ++k, ++l)
			{
				if (board.m_board[k][l] == 0)
				{
					board.m_board[k][l] = pieceValue;
					return;
				}
			}
		}
		for (int i = 0, j = 2; i < 3, j >= 0; ++i, --j)
		{
			tmp[i] = board.m_board[i][j];
		}
		if (tmp[0] + tmp[1] + tmp[2] == opponentVal * 2)
		{
			for (int k = 0, l = 2; k < 3, l >= 0; ++k, --l)
			{
				if (board.m_board[l][k] == 0)
				{
					board.m_board[l][k] = pieceValue;
					return;
				}
			}
		}
	}
	// end thwart possible wins
	// if we're here, we haven't found a recommended course of action yet
	// let's get a bit offensive

	if (move == 0) // our first move, remember?
	{
		board.m_board[0][0] = pieceValue; // we'll try to pull the 3-corners trick on them
		return;
	}
	else if (move == 1) // second move, somebody moved already
	{
		// the middle square is always a good place to start out in
		if (board.m_board[1][1] == 0)
		{
			board.m_board[1][1] = pieceValue;
			return;
		}
		else
		{
			board.m_board[0][0] = pieceValue; // we'll try to pull the 3-corners trick on them
			return;
		}
	}
	else // both players have moved at least one time, try to determine a good move to pull
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[i][j];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue)
			{
				if (tmp[0] == pieceValue)
				{
					board.m_board[i][2] = pieceValue; // tmp[0] is like board.m_board[i][0], so make the [i][2] value our move
					return; // the above comment applies to similar code throughout this function
				}
				else if (tmp[2] == pieceValue)
				{
					board.m_board[i][0] = pieceValue; // we're trying to work on the ends of the row
					return;
				}
				else // well, the middle of the row has been claimed. Let's analyze which end to take.
				{
					board.m_board[i][0] = pieceValue; // placeholder code, first of the row
					return;
				}
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			int j;
			for (j = 0; j < 3; ++j)
			{
				tmp[j] = board.m_board[j][i];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue)
			{
				if (tmp[0] == pieceValue)
				{
					board.m_board[2][i] = pieceValue;
					return;
				}
				else if (tmp[2] == pieceValue)
				{
					board.m_board[0][i] = pieceValue;
					return;
				}
				else
				{
					board.m_board[0][i] = pieceValue; // placeholder code
					return;
				}
			}
		}
		{ // this block and the next block are designed to keep variables separate
			int i, j;
			for (i = 0, j = 0; i < 3, j < 3; ++i, ++j)
			{
				tmp[i] = board.m_board[i][j];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue)
			{
				if (tmp[0] == pieceValue)
				{
					board.m_board[2][2] = pieceValue;
					return;
				}
				else if (tmp[2] == pieceValue)
				{
					board.m_board[0][0] = pieceValue;
					return;
				}
				else
				{
					board.m_board[0][0] = pieceValue; // placeholder code
					return;
				}
			}
		}
		{
			int i, j;
			for (i = 0, j = 2; i < 3, j >= 0; ++i, --j)
			{
				tmp[i] = board.m_board[i][j];
			}
			if (tmp[0] + tmp[1] + tmp[2] == pieceValue)
			{
				if (tmp[0] == pieceValue)
				{
					board.m_board[2][0] = pieceValue;
					return;
				}
				else if (tmp[2] == pieceValue)
				{
					board.m_board[0][2] = pieceValue;
					return;
				}
				else
				{
					board.m_board[0][2] = pieceValue; // placeholder code
					return;
				}
			}
		}
	}

	// this will give us a move if nothing else has
    while (true)
    {
        short column = std::rand() % 3;
        short row = std::rand() % 3;
        if (board.m_board[row][column] == 0)
        {
            board.m_board[row][column] = pieceValue;
			return;
        }
    }
}


