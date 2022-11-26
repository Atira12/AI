#include <iostream>
#include <list>
#include <array>
#include <string.h>
#include <algorithm> 
#include <vector>

using namespace std;

#define WIN INT32_MAX
#define	DRAW 0
#define LOSS INT32_MIN

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

void print_board(char board[3][3])
{
	cout << endl;
	cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "----------" << endl;
	cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "----------" << endl;
	cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

std::vector<std::pair<int, int>> get_legal_moves(char board[3][3])
{
	std::vector<std::pair<int, int>> legal_moves;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER)
			{
				legal_moves.push_back(std::make_pair(i, j));
			}
		}
	}

	return legal_moves;
}
bool board_is_full(char board[3][3])
{
	std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

	if (0 == legal_moves.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}
std::vector<std::vector<std::pair<int, int>>> winning_states
{
	// Every row
	{ std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2) },
	{ std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2) },
	{ std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2) },

	// Every column
	{ std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0) },
	{ std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(2, 1) },
	{ std::make_pair(0, 2), std::make_pair(1, 2), std::make_pair(2, 2) },

	// Every diagonal
	{ std::make_pair(0, 0), std::make_pair(1, 1), std::make_pair(2, 2) },
	{ std::make_pair(2, 0), std::make_pair(1, 1), std::make_pair(0, 2) }

};
bool game_is_won(std::vector<std::pair<int, int>> occupied_positions)
{
	bool game_won;

	for (int i = 0; i < winning_states.size(); i++)
	{
		game_won = true;
		std::vector<std::pair<int, int>> curr_win_state = winning_states[i];
		for (int j = 0; j < 3; j++)
		{
			if (!(std::find(std::begin(occupied_positions), std::end(occupied_positions), curr_win_state[j]) != std::end(occupied_positions)))
			{
				game_won = false;
				break;
			}
		}

		if (game_won)
		{
			break;
		}
	}
	return game_won;
}

char get_opponent_marker(char marker)
{
	char opponent_marker;
	if (marker == PLAYER_MARKER)
	{
		opponent_marker = AI_MARKER;
	}
	else
	{
		opponent_marker = PLAYER_MARKER;
	}

	return opponent_marker;
}
std::vector<std::pair<int, int>> get_occupied_positions(char board[3][3], char marker)
{
	std::vector<std::pair<int, int>> occupied_positions;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (marker == board[i][j])
			{
				occupied_positions.push_back(std::make_pair(i, j));
			}
		}
	}

	return occupied_positions;
}
int get_board_state(char board[3][3], char marker)
{

	char opponent_marker = get_opponent_marker(marker);

	std::vector<std::pair<int, int>> occupied_positions = get_occupied_positions(board, marker);

	bool is_won = game_is_won(occupied_positions);

	if (is_won)
	{
		return WIN;
	}

	occupied_positions = get_occupied_positions(board, opponent_marker);
	bool is_lost = game_is_won(occupied_positions);

	if (is_lost)
	{
		return LOSS;
	}

	bool is_full = board_is_full(board);
	if (is_full)
	{
		return DRAW;
	}

	return DRAW;

}
bool isEnd(char board[3][3]) {
	for(int i = 0; i < 3; i++) {
			if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != EMPTY_SPACE) {
				return true;
			}
	}
	for(int i = 0; i < 3; i++) {
			if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY_SPACE) {
				return true;
			}
	}
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != EMPTY_SPACE) {
		return true;
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != EMPTY_SPACE) {
		return true;
	}
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] == EMPTY_SPACE) {
				return false;
			}
		}
	}
	return true;
} 
int getUtility(char board[3][3], char marker) {
	int score = 0;
	for(int i = 0; i < 3 ;i ++ ) {
			if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == marker ) {
				score+=10;
			} else if(board[i][0] == board[i][1] && EMPTY_SPACE == board[i][2] && board[i][0] == marker ) {
				score +=4;
			} else if(board[i][0] == board[i][1] && EMPTY_SPACE == board[i][2] && board[i][0] == marker ) {
				score+=4;
			} else if(board[i][0] == EMPTY_SPACE &&  board[i][1]== board[i][2] && board[i][1] == marker ) {
				score +=4;
			} else if(board[i][1] == EMPTY_SPACE &&  board[i][0]== board[i][2] && board[i][0] == marker ) {
				score+=4;
			} else if(board[i][1] == EMPTY_SPACE &&  board[i][1]== board[i][2] && board[i][0] == marker ) {
				score+=1;
			} else if(board[i][0] == EMPTY_SPACE &&  board[i][0]== board[i][2] && board[i][1] == marker ) {
				score+=1;
			} else if(board[i][0] == EMPTY_SPACE &&  board[i][0]== board[i][1] && board[i][2] == marker ) {
				score+=1;
			}

			if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == marker ) {
				score+=10;
			} else if(board[0][i] == board[1][i] && EMPTY_SPACE == board[2][i] && board[0][i] == marker ) {
				score +=4;
			} else if(board[0][i] == board[1][i] && EMPTY_SPACE == board[2][i] && board[0][i] == marker ) {
				score+=4;
			} else if(board[0][i] == EMPTY_SPACE &&  board[1][i]== board[2][i] && board[1][i] == marker ) {
				score +=4;
			} else if(board[1][i] == EMPTY_SPACE &&  board[0][i]== board[2][i] && board[0][i] == marker ) {
				score+=4;
			} else if(board[1][i] == EMPTY_SPACE &&  board[1][i]== board[2][i] && board[0][i] == marker ) {
				score+=1;
			} else if(board[0][i] == EMPTY_SPACE &&  board[0][i]== board[2][i] && board[1][i] == marker ) {
				score+=1;
			} else if(board[0][i] == EMPTY_SPACE &&  board[0][i]== board[1][i] && board[2][i] == marker ) {
				score+=1;
			}

	}

		if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == marker ) {
			score+=10;
		} else if(board[0][0] == board[1][1] && EMPTY_SPACE == board[2][2] && board[0][0] == marker ) {
			score +=4;
		} else if(board[0][0] == board[1][1] && EMPTY_SPACE == board[2][2] && board[0][0] == marker ) {
			score+=4;
		} else if(board[0][0] == EMPTY_SPACE &&  board[1][1]== board[2][2] && board[1][1] == marker ) {
			score +=4;
		} else if(board[1][1] == EMPTY_SPACE &&  board[0][0]== board[2][2] && board[0][0] == marker ) {
			score+=4;
		} else if(board[1][1] == EMPTY_SPACE &&  board[1][1]== board[2][2] && board[0][0] == marker ) {
			score+=1;
		} else if(board[0][0] == EMPTY_SPACE &&  board[0][0]== board[2][2] && board[1][1] == marker ) {
			score+=1;
		} else if(board[0][0] == EMPTY_SPACE &&  board[0][0]== board[1][1] && board[2][2] == marker ) {
			score+=1;
		}

		if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == marker ) {
			score+=10;
		} else if(board[0][2] == board[1][1] && EMPTY_SPACE == board[2][0] && board[0][2] == marker ) {
			score +=4;
		} else if(board[0][2] == board[1][1] && EMPTY_SPACE == board[2][0] && board[0][2] == marker ) {
			score+=4;
		} else if(board[0][2] == EMPTY_SPACE &&  board[1][1]== board[2][0] && board[1][1] == marker ) {
			score +=4;
		} else if(board[1][1] == EMPTY_SPACE &&  board[0][2]== board[2][0] && board[0][2] == marker ) {
			score+=4;
		} else if(board[1][1] == EMPTY_SPACE &&  board[1][1]== board[2][0] && board[0][2] == marker ) {
			score+=1;
		} else if(board[0][2] == EMPTY_SPACE &&  board[0][2]== board[2][0] && board[1][1] == marker ) {
			score+=1;
		} else if(board[0][2] == EMPTY_SPACE &&  board[0][2]== board[1][1] && board[2][0] == marker ) {
			score+=1;
		}
		return marker == AI_MARKER ? score : (score * -1);
}
std::pair<int, std::pair<int, int>> minValue(char board[3][3], char marker, int depth, int alpha, int beta) ;
std::pair<int, std::pair<int, int>>  maxValue(char board[3][3], char marker, int depth, int alpha, int beta)  {
    std::pair<int, int> best_move = std::make_pair(-1, -1);
    int best_score = LOSS ;
	if (isEnd(board))
	{
		best_score = get_board_state(board, AI_MARKER);
		return std::make_pair(best_score, best_move);
	}
	std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

	for (int i = 0; i < legal_moves.size(); i++)
	{
		std::pair<int, int> curr_move = legal_moves[i];
		board[curr_move.first][curr_move.second] = marker;

		// Maximizing player's turn
			int score = minValue(board,PLAYER_MARKER, depth + 1, alpha, beta).first;

			// Get the best scoring move
			if (best_score < score)
			{
				best_score = score - depth*10;
				best_move = curr_move;
					
				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = std::max(alpha, best_score);
				board[curr_move.first][curr_move.second] = EMPTY_SPACE;
				if (alpha >= beta) 
				{ 
					break; 
				}
			}
		board[curr_move.first][curr_move.second] = EMPTY_SPACE; // Undo move

	}
	return std::make_pair(best_score, best_move);
}




std::pair<int, std::pair<int, int>> minValue(char board[3][3], char marker, int depth, int alpha, int beta)  {
    std::pair<int, int> best_move = std::make_pair(-1, -1);
    int best_score = WIN;

	if (isEnd(board))
	{
		best_score = get_board_state(board,AI_MARKER);
		return std::make_pair(best_score, best_move);
	}
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

	for (int i = 0; i < legal_moves.size(); i++){
		std::pair<int, int> curr_move = legal_moves[i];
		board[curr_move.first][curr_move.second] = marker;

		// Maximizing player's turn
			int score = maxValue(board, AI_MARKER, depth + 1, alpha, beta).first;
		
			// Get the best scoring move
			if (best_score > score)
			{
				best_score = score +  depth* 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = std::min(beta, best_score);
				board[curr_move.first][curr_move.second] = EMPTY_SPACE;
				if (beta <= alpha) 
				{ 
					break; 
				}
			}
			
		board[curr_move.first][curr_move.second] = EMPTY_SPACE; // Undo move
			
    }
	return std::make_pair(best_score, best_move);
}


int main () {
	char board[3][3] = { EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE,EMPTY_SPACE};
	bool playerFirst;
	int row;
	int col;
	print_board(board);
	while(!isEnd(board)) {
		cin >> row;
		cin >> col;
		board[row][col] = PLAYER_MARKER;
		std::pair<int, std::pair<int, int>> ai_move = maxValue(board, AI_MARKER, 0, LOSS, WIN);
		board[ai_move.second.first][ai_move.second.second] = AI_MARKER;
		print_board(board);
	}
}