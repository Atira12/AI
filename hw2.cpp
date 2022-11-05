#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string.h>

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
    int conflicts = 0;
    srand(time(0));
    for(int i = 0 ; i < rows ; i++ ) {
        int queenRow = nQueens[i];
        conflicts = (queensPerRow[queenRow] - 1) + (queensPerD1[i - queenRow + (rows - 1)] - 1) + (queensPerD2[i + queenRow] - 1);
        if(conflicts > maxConflicts) {
            maxConflicts = conflicts;
            maxCol = i;
        } else if( conflicts == maxConflicts) {
            isTaken = rand() % 2;
            if(isTaken) {
                maxCol = i;    
            } 
        }
    }
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
            }
        }
    }
    return minRow;
}
bool hasConflicts() {
    int conflicts = 0;
    for(int i = 0 ; i < rows ; i++) {
        int queenRow = nQueens[i];
        conflicts = (queensPerRow[queenRow] - 1) + (queensPerD1[i - queenRow + (rows - 1)] - 1) + (queensPerD2[i + queenRow] - 1);
        if(conflicts > 0 ) {
            return true;
        }
    }
    return false;
}  

void intialize() {
    srand(time(0));
    int row;

    memset(queensPerRow, 0, rows*sizeof(*queensPerRow));
    memset(queensPerD1,0, (2*rows-1)*sizeof(*queensPerD1));
    memset(queensPerD2,0, (2*rows-1)*sizeof(*queensPerD2));

    int pos = rand() % rows;
    nQueens[0] = pos;
    queensPerRow[pos]++;
    queensPerD1[ 0 - pos + (rows - 1)]++;
    queensPerD2[0 + pos]++;
    for(int i = 1 ; i < rows; i++ ) {
        row = getRowWithMinConflicts(i);
        nQueens[i] = row;
        // cout << "Row with min conflicts: " << row << endl; 
        queensPerRow[row]++;
        queensPerD1[ i - row + (rows - 1)]++;
        queensPerD2[i + row]++;
    }
}
void printWithWaiting() {
    int p;
    print();
    cout << "------------------------------------------------" <<endl;
    cin >> p;
}
void solve() {
    int col = 0;
    int row = 0;
    int prevRow;

    nQueens = new int[rows];
    queensPerRow = new int[rows]{0};
    queensPerD1 = new int[2*rows-1]{0};
    queensPerD2 = new int[2*rows-1]{0};
    for(int k = 1; true; k++) {
       
        intialize();
        for(int i = 0; i < k*rows; i++) {
            col = getColWithMaxConflicts();
            row = getRowWithMinConflicts(col);

            // remove one queen from possition and conflicts
            prevRow = nQueens[col];
            queensPerRow[prevRow] --;
            queensPerD1[((col - prevRow) + (rows - 1))]-- ;
            queensPerD2[col+prevRow]--;
            // add one queen to new possition and new conflicts
            queensPerRow[row]++;
            queensPerD1[((col - row) + (rows - 1))]++ ;
            queensPerD2[col+row]++;
            nQueens[col] = row;
            // printWithWaiting();
            if(!hasConflicts()) {
                cout << "Right here" <<endl;
                return;
            }
        }
        if(!hasConflicts()) {
            cout << "Right here 2" <<endl;
            return;
        }
    }
    cout << "COnflicts" << endl;
}

int main() {
    cin >> rows;
    nQueens = new int[rows];
    queensPerRow = new int[rows]{0};
    queensPerD1 = new int[2*rows-1]{0};
    queensPerD2 = new int[2*rows-1]{0};
    intialize();
    print();
    // solve();
    // print();
    return 0;
}