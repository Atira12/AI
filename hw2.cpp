#include <iostream>
#include <string.h>
#include <random>
#include <chrono>  

int* nQueens = nullptr;
int* queensPerRow = nullptr;
int* queensPerD1 = nullptr;
int* queensPerD2 = nullptr;
int rows; 

std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<int> booleanDistribution(0, 1);

void print() {

    for(int i = 0; i < rows; i++ ) {
        for(int j = 0; j < rows; j++ ) {
            if(i == nQueens[j]) {
                std::cout << " + ";
            }else {
                std::cout << " - ";
            }
        }    
        std::cout << std::endl;
    }
    std::cout << std::endl;
   /*  for(int j = 0; j < rows; j++ ) {
        std::cout << queensPerRow[j] << std::endl;
    }   
    std::cout << std::endl;
    for(int j = 0; j < 2*rows-1; j++ ) {
        std::cout << queensPerD1[j] << std::endl;
    }  
    std::cout << std::endl;

    for(int j = 0; j < 2*rows-1; j++ ) {
        std::cout << queensPerD2[j] << std::endl;
    }   */
}
int getColWithMaxConflicts() {
    int maxCol = 0;
    int maxConflicts = 0;
    bool isTaken;
    int conflicts = 0;
    for(int i = 0 ; i < rows ; i++ ) {
        int queenRow = nQueens[i];
        conflicts = (queensPerRow[queenRow] - 1) + (queensPerD1[i - queenRow + (rows - 1)] - 1) + (queensPerD2[i + queenRow] - 1);
        if(conflicts > maxConflicts) {
            maxConflicts = conflicts;
            maxCol = i;
        } else if( conflicts == maxConflicts) {
            isTaken = booleanDistribution(gen);
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
    int minConflicts = rows;
    bool isTaken;


    for(int row = 0; row < rows; row++) {
        if(row  == nQueens[col]) {
            continue;
        }
        conflicts  = (queensPerRow[row] - 1) + (queensPerD1[col - row + (rows - 1)] - 1) + (queensPerD2[col + row] - 1);
        if(conflicts < minConflicts) {
            minConflicts = conflicts;
            minRow = row;
        } else if( conflicts == minConflicts) {
            isTaken = booleanDistribution(gen);
             if(isTaken) {
                minRow = row;    
            }
        }
    }
    return minRow;
}
bool hasConflicts() {
    int* queenRow = nullptr;
    
    for(int i = 0 ; i < rows ; i++) {
        queenRow = &nQueens[i];
        if(queensPerRow[*queenRow] != 1  || queensPerD1[(i - *queenRow)+ (rows-1)] > 1 || queensPerD2[i + *queenRow] > 1) {
            return true;
        }
    }
    return false;
}  

void intialize() {
    srand(time(NULL));
    for(int i = 0 ; i < rows; i++ ) {
        int row = rand() % rows;

        nQueens[i] = row;
        queensPerRow[row]++;
        queensPerD1[ i - row + (rows - 1)]++;
        queensPerD2[i + row]++;
    }
}
void printWithWaiting() {
    int p;
    print();
    std::cout << "------------------------------------------------" << std::endl;
    std::cin >> p;
}
void solve() {
    int col = 0;
    int row = 0;
    int* prevRow = nullptr;

    nQueens = new int[rows];
    queensPerRow = new int[rows];
    queensPerD1 = new int[2*rows-1];
    queensPerD2 = new int[2*rows-1];
    
    for(int k = 1; k < rows; k++) {
       
        intialize();
        for(int i = 0; i <= k*rows; i++) {
            col = getColWithMaxConflicts();
            row = getRowWithMinConflicts(col);

            // remove one queen from possition and conflicts
            prevRow = &nQueens[col];
            queensPerRow[*prevRow] --;
            queensPerD1[((col - *prevRow) + (rows - 1))]-- ;
            queensPerD2[col+*prevRow]--;
            // add one queen to new possition and new conflicts
            queensPerRow[row]++;
            queensPerD1[((col - row) + (rows - 1))]++ ;
            queensPerD2[col+row]++;
            nQueens[col] = row;
            // printWithWaiting();
            if(!hasConflicts()) {
                std::cout << "Right here" << std::endl;
                return;
            }
        }
        memset(queensPerRow, 0, rows*sizeof(int));
        memset(queensPerD1, 0, (2*rows-1)*sizeof(int));
        memset(queensPerD2, 0, (2*rows-1)*sizeof(int));

    }
    std::cout << "Conflicts" << std::endl;
}

int main() {
    std:: cin >> rows;
    // nQueens = new int[rows];
    // queensPerRow = new int[rows]{0};
    // queensPerD1 = new int[2*rows-1]{0};
    // queensPerD2 = new int[2*rows-1]{0};
    // intialize();
    // print();
    auto start = std::chrono::steady_clock::now();
    solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std:: cout << "Time: " << elapsed_seconds.count() << std::endl;
    if(rows < 20) {
        print();
    }
    return 0;
}