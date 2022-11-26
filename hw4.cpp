#include <iostream>
#include <vector>

using namespace std;

#define WIN INT32_MAX
#define	DRAW 0
#define LOSE INT32_MIN

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
						return board[0][i] == symbol ? WIN : LOSE;
					 } else {
						return board[0][i] == symbol ? LOSE : WIN;
					 }
				}
				
		}
		for(int i = 0; i < 3; i++) {
				if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY) {
					if( symbol == AI) {
						return board[i][0] == symbol ? WIN : LOSE;
					 } else {
						return board[i][0] == symbol ? LOSE : WIN;
					 }
				}
		}
		if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != EMPTY) {
					 if( symbol == AI) {
						return board[0][0] == symbol ? WIN : LOSE;
					 } else {
						return board[0][0] == symbol ? LOSE : WIN;
					 }
		}
		if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != EMPTY) {
					  if( symbol == AI) {
						return board[0][2] == symbol ? WIN : LOSE;
					 } else {
						return board[0][2] == symbol ? LOSE : WIN;
					 }
		}
		return DRAW;
	
}
pair<int, pair<int, int>> minValue(char board[3][3],int depth, int alpha, int beta) ;
pair<int, pair<int, int>>  maxValue(char board[3][3], int depth, int alpha, int beta)  {
    pair<int, int> bestMove = make_pair(-1, -1);
    int bestScore = LOSE ;

	if (isTerminated(board))
	{	
		bestScore = getEndState(board, AI);
		return make_pair(bestScore, bestMove);
	}
	vector<pair<int, int>> suc = getSuccessorMoves(board);

	for (int i = 0; i < suc.size(); i++)
	{
		pair<int, int> curMove = suc[i];
		board[curMove.first][curMove.second] = AI;

		
			int newScore = minValue(board, depth + 1, alpha, beta).first;

			
			if (bestScore < newScore)
			{
				bestScore = newScore - depth*10;
				bestMove = curMove;
					
				
				
				alpha = max(alpha, bestScore);
				board[curMove.first][curMove.second] = EMPTY;
				if (alpha >= beta) 
				{ 
					break; 
				}
			}
		board[curMove.first][curMove.second] = EMPTY; 

	}
	return make_pair(bestScore, bestMove);
}




pair<int, pair<int, int>> minValue(char board[3][3], int depth, int alpha, int beta)  {
    pair<int, int> bestMove = make_pair(-1, -1);
    int bestScore = WIN;

	if (isTerminated(board))
	{
		bestScore = getEndState(board,PLR);
		return make_pair(bestScore, bestMove);
	}
    vector<pair<int, int>> suc = getSuccessorMoves(board);

	for (int i = 0; i < suc.size(); i++){
		pair<int, int> curMove = suc[i];
		board[curMove.first][curMove.second] = PLR;

		
			int newScore = maxValue(board, depth + 1, alpha, beta).first;
		
			
			if (bestScore > newScore)
			{
				bestScore = newScore + depth* 10;
				bestMove = curMove;

				
				
				beta = min(beta, bestScore);
				board[curMove.first][curMove.second] = EMPTY;
				if (alpha >= beta) 
				{ 
					break; 
				}
			}
			
		board[curMove.first][curMove.second] = EMPTY; 
			
    }
	return make_pair(bestScore, bestMove);
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
			pair<int, pair<int, int>> aiMove = maxValue(board, 0, LOSE, WIN);
			board[aiMove.second.first][aiMove.second.second] = AI;
			printBoard(board);
		}	
	} else {
		while(!isTerminated(board)) {
		pair<int, pair<int, int>> aiMove = maxValue(board, 0, LOSE, WIN);
		board[aiMove.second.first][aiMove.second.second] = AI;
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