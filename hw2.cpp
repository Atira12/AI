#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int* nQueens = nullptr;
int* queensPerRow = nullptr;
int* queensPerD1 = nullptr;
int* queensPerD2 = nullptr;
int rows; 

void print() {
    for(int i = 0; i < rows; i++ ) {
        for(int j = 0; j < rows; j++ ) {
            if(i == nQueens[j]) {
                cout << " . ";
            }else {
                cout << " _ ";
            }
        }    
        cout << endl;
    }
    for(int j = 0; j < rows; j++ ) {
        cout << queensPerRow[j] << endl;
    }   
    cout << endl;
    for(int j = 0; j < 2*rows-1; j++ ) {
        cout << queensPerD1[j] << endl;
    }  
    cout << endl;

    for(int j = 0; j < 2*rows-1; j++ ) {
        cout << queensPerD2[j] << endl;
    }  
}

int getColWithMaxConflicts() {
    int maxCol = 0;
    int maxConflicts = 0;
    bool isTaken;
    srand(time(0));
    for(int i = 0 ; i < rows ; i++ ) {
        int queenRow = nQueens[i];
        int conflicts  = (queensPerRow[queenRow] - 1) + (queensPerD1[i - queenRow + (rows - 1)] - 1) + (queensPerD2[i + queenRow] - 1);
        if(conflicts > maxConflicts) {
            maxConflicts = conflicts;
            maxCol = i;
        } else if( conflicts == maxConflicts) {
            isTaken = rand() % 2;
            if(isTaken) {
                maxCol = i;    
            } else {
                cout << "is False" <<endl;
            }
        }
    }
    cout << "max Conflicts: " << maxConflicts << endl; 
    return maxCol;
}
int getRowWithMinConflicts(int col) {
    int conflicts;
    int minRow = 0;
    int minConflicts = INT32_MAX;
    int queenRow = nQueens[col];
    bool isTaken;

    srand(time(0));

    for(int row = 0; row < rows; row++) {
        if(row  == queenRow) {
            continue;
        }
        conflicts  = (queensPerRow[row] - 1) + (queensPerD1[col - row + (rows - 1)] - 1) + (queensPerD2[col + row] - 1);
        if(conflicts < minConflicts) {
            minConflicts = conflicts;
            minRow = row;
        } else if( conflicts == minConflicts) {
            isTaken = rand() % 2;
             if(isTaken) {
                minRow = row;    
            } else {
                cout << "is False in MinConflicts" <<endl;
            }
        }
    }
    
    cout << "Min conflicts is: "<< minConflicts <<endl;
    return minRow;
}
bool hasConflicts() {
    int conflicts = 0;
    for(int i = 0 ; i < rows ; i++) {
        int queenRow = nQueens[i];
        conflicts = (queensPerRow[queenRow] - 1) + (queensPerD1[i - queenRow + (rows - 1)] - 1) + (queensPerD2[i + queenRow] - 1);
        if(conflicts != 0 ) {
            return true;
        }
    }
    return false;
}  

void solve() {
    int col = 0;
    int row = 0;
    for(int k = 0; k < rows; k++) {
        nQueens = new int[rows];
        queensPerRow = new int[rows]{0};
        queensPerD1 = new int[2*rows-1]{0};
        queensPerD2 = new int[2*rows-1]{0};
        for(int i = 0; i < k*rows; i++) {
            col = getColWithMaxConflicts();
            row = getRowWithMinConflicts(col);
        }
        if(hasConflicts()) {
            delete[] nQueens;
            delete[] queensPerRow;
            delete[] queensPerD1;
            delete[] queensPerD2;
        } else {
            return;
        }
    }
}
void intialize() {
    srand(time(0));
    
    for(int i = 0 ; i < rows; i++ ) {
        int pos = rand() % rows;
        nQueens[i] = pos;
        queensPerRow[pos]++;
        queensPerD1[ i - pos + (rows - 1)]++;
        queensPerD2[i + pos]++;
    }
}
int main() {
    cin >> rows;
    
    intialize();
    print();
    cout <<"Conflicts = " <<hasConflicts() << endl;
    // int x =  getColWithMaxConflicts() ;
    // cout << "Col with max conflicts is = " << x << endl;
    // cout << "---------------------------------------------------------" << endl;
    // int y = getRowWithMinConflicts(x);
    // cout << "Row with min conflicts is = " << y << endl;

    return 0;
}