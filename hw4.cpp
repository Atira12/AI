#include <iostream>
#include <vector>

using namespace std;

#define WIN INT32_MAX
#define	DRAW 0
#define LOSS INT32_MIN

#define AI 'O'
#define PLR 'X'
#define EMPTY '-'

void printBoard(char board[3][3])
{
	for(int i = 0; i < 3;i++) {
		for(int j = 0; j < 3 ;j++) {
			cout << ' ' << board[i][j] << ' ';
		}
		cout <<endl;
		if(i != 2) {
			cout << " -------" << endl;
		}
	}
		cout <<endl;
		cout <<endl;

}

vector<pair<int,int>> getSuccessorMoves(char board[3][3]) {
	vector<pair<int,int>> moves;
	for(int i = 0;i < 3;i++) {
		for(int j = 0 ; j < 3 ;j++ ) {
			if(board[i][j] == EMPTY) {
				moves.push_back(make_pair(i,j));
			}
		}
	}
	return moves;
}

int isTerminated(char board[3][3]) {
	for(int i = 0; i < 3; i++) {
			if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != EMPTY) {
				return true;
			}
	}
	for(int i = 0; i < 3; i++) {
			if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY) {
				return true;
			}
	}
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != EMPTY) {
		return true;
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != EMPTY) {
		return true;
	}
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] == EMPTY) {
				return false;
			}
		}
	}
	return true;
} 
int getEndState(char board[3][3], char symbol) {

		for(int i = 0; i < 3; i++) {
				if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != EMPTY) {
					 if( symbol == AI) {
						return board[0][i] == symbol ? WIN : LOSS;
					 } else {
						return board[0][i] == symbol ? LOSS : WIN;
					 }
				}
				
		}
		for(int i = 0; i < 3; i++) {
				if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY) {
					if( symbol == AI) {
						return board[i][0] == symbol ? WIN : LOSS;
					 } else {
						return board[i][0] == symbol ? LOSS : WIN;
					 }
				}
		}
		if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != EMPTY) {
					 if( symbol == AI) {
						return board[0][0] == symbol ? WIN : LOSS;
					 } else {
						return board[0][0] == symbol ? LOSS : WIN;
					 }
		}
		if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != EMPTY) {
					  if( symbol == AI) {
						return board[0][2] == symbol ? WIN : LOSS;
					 } else {
						return board[0][2] == symbol ? LOSS : WIN;
					 }
		}
		return DRAW;
	
}
std::pair<int, std::pair<int, int>> minValue(char board[3][3], char symbol, int depth, int alpha, int beta) ;
std::pair<int, std::pair<int, int>>  maxValue(char board[3][3], char symbol, int depth, int alpha, int beta)  {
    std::pair<int, int> bestMove = std::make_pair(-1, -1);
    int bestValue = LOSS ;

	if (isTerminated(board))
	{	
		bestValue = getEndState(board, AI);
		return std::make_pair(bestValue, bestMove);
	}
	std::vector<std::pair<int, int>> legal_moves = getSuccessorMoves(board);

	for (int i = 0; i < legal_moves.size(); i++)
	{
		std::pair<int, int> curMove = legal_moves[i];
		board[curMove.first][curMove.second] = symbol;

		
			int newScore = minValue(board,PLR, depth + 1, alpha, beta).first;

			
			if (bestValue < newScore)
			{
				bestValue = newScore - depth*10;
				bestMove = curMove;
					
				
				
				alpha = std::max(alpha, bestValue);
				board[curMove.first][curMove.second] = EMPTY;
				if (alpha >= beta) 
				{ 
					break; 
				}
			}
		board[curMove.first][curMove.second] = EMPTY; 

	}
	return std::make_pair(bestValue, bestMove);
}




std::pair<int, std::pair<int, int>> minValue(char board[3][3], char symbol, int depth, int alpha, int beta)  {
    std::pair<int, int> bestMove = std::make_pair(-1, -1);
    int bestValue = WIN;

	if (isTerminated(board))
	{
		bestValue = getEndState(board,PLR);
		return std::make_pair(bestValue, bestMove);
	}
    std::vector<std::pair<int, int>> legal_moves = getSuccessorMoves(board);

	for (int i = 0; i < legal_moves.size(); i++){
		std::pair<int, int> curMove = legal_moves[i];
		board[curMove.first][curMove.second] = symbol;

		
			int newScore = maxValue(board, AI, depth + 1, alpha, beta).first;
		
			
			if (bestValue > newScore)
			{
				bestValue = newScore + depth* 10;
				bestMove = curMove;

				
				
				beta = std::min(beta, bestValue);
				board[curMove.first][curMove.second] = EMPTY;
				if (alpha >= beta) 
				{ 
					break; 
				}
			}
			
		board[curMove.first][curMove.second] = EMPTY; 
			
    }
	return std::make_pair(bestValue, bestMove);
}


int main () {
	char board[3][3] = { EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY};
	bool playerFirst;
	int row;
	int col;
	bool whoFirst;

	cout << "Player first - 1 || AI first - 0" << endl;
	cin >> whoFirst;
	printBoard(board);
	if(whoFirst) {
		while(!isTerminated(board)) {
			cout << "row: ";
			cin >> row;
			cout << "col: ";
			cin >> col;
			board[row][col] = PLR;
			std::pair<int, std::pair<int, int>> ai_move = maxValue(board, AI, 0, LOSS, WIN);
			board[ai_move.second.first][ai_move.second.second] = AI;
			printBoard(board);
		}	
	} else {
		while(!isTerminated(board)) {
		std::pair<int, std::pair<int, int>> ai_move = maxValue(board, AI, 0, LOSS, WIN);
		board[ai_move.second.first][ai_move.second.second] = AI;
		printBoard(board);
		if(isTerminated(board)) {
			break;
		}
		cout << "row: ";
		cin >> row;
		cout << "col: ";
		cin >> col;
		board[row][col] = PLR;
		}
	}
	
}