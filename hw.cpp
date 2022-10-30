#include <iostream>
#include <cmath>
#include <stack>
#include <list>
#include <set>
using namespace std;

class Node {
    public:
        int** matrix;
        int zeroRow;
        int zeroCol;
        Node* parent;

        Node(int** matrix, int zeroRow, int zeroCol, Node* parent) {
            this->matrix = matrix;
            this->zeroCol = zeroCol;
            this->zeroRow = zeroRow;
            this->parent = parent;
        }
};

int expectedEmptyRow;
int expectedEmptyCol;
int rows; 
set<Node*>* visited = nullptr;
stack<Node*>* pathToGoal = nullptr;

bool equals(int** node , int** node2) {
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < rows;j++) {
            if(node[i][j] != node2[i][j]) {
                return false;
            }
        }
    }
    return true;
} 

int manhattan(Node* node) {
    int total = 0;
    int row = 0;
    int col; 
    
     for(int i = 0 ; i < rows;i++){
        for(int j = 0 ; j < rows; j++) {
            col = node->matrix[i][j];
            if(col == 0) {
                row = expectedEmptyRow;
                col = expectedEmptyCol+1;
            } else {
                while(col > rows) {
                    row++;
                    col -= rows;
                }
            }
            total += (abs(i - row) + abs(j - (col-1)));
            row = 0;
        }
    }
    return total;
}

bool setContains(int** node) {
    for( set<Node*>::iterator it = visited->begin(); it != visited->end(); ++it) {
        if(equals(node,(*it)->matrix)) {
            return true ;
        } 
    }
    return false;
}

list<Node*> neightours(Node* node) {
    int swap;
    cout << (node != nullptr) <<endl;
    list<Node*> children;
    for(int posChange : {-1,1}) {

        int** newRowMatrix = new int*[rows];
        int** newColMatrix = new int*[rows];
        for(int i = 0 ; i < rows;i++) {
            newRowMatrix[i] = new int[rows];
            newColMatrix[i] = new int[rows];
        }

        if((node->zeroRow + posChange) < rows && (node->zeroRow + posChange) >= 0 ) {
            for(int i = 0; i < rows; i++){
               for(int j = 0 ; j < rows;j++) {
                   newRowMatrix[i][j] = node->matrix[i][j];
               }
            }
            swap = newRowMatrix[node->zeroRow+posChange][node->zeroCol] ;
            newRowMatrix[node->zeroRow+posChange][node->zeroCol] = newRowMatrix[node->zeroRow][node->zeroCol];
            newRowMatrix[node->zeroRow][node->zeroCol] = swap;
            if(!setContains(newColMatrix)) {
                Node* x = new Node(newRowMatrix,(node->zeroRow+posChange), node->zeroCol, node);
                children.push_front(x);
            }
        }
         if((node->zeroCol + posChange) < rows && (node->zeroCol + posChange) >= 0 ) {
            for(int i = 0; i < rows; i++){
               for(int j = 0 ; j < rows;j++) {
                   newColMatrix[i][j] = node->matrix[i][j];
               }
            }
            swap = newColMatrix[node->zeroRow][node->zeroCol + posChange] ;
            newColMatrix[node->zeroRow][node->zeroCol + posChange] = newColMatrix[node->zeroRow][node->zeroCol];
            newColMatrix[node->zeroRow][node->zeroCol] = swap;
            if(!setContains(newColMatrix)) {
                Node* x = new Node(newColMatrix,node->zeroRow, (node->zeroCol + posChange), node);
                children.push_front(x);
            }
        }
    }
    return children;
}

int countInversions(int** matrix) {
    int* array = new int[rows*rows];
    int c = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < rows;j++,c++) {
            array[c] = matrix[i][j];
        }
    }
    int inversionsCount = 0;
    for(int i = 0; i < rows*rows; i++){
        for(int j = i+1 ; j < rows*rows;j++) {
            if(array[i] == 0 || array[j] == 0) {
                continue;
            }
            if(array[i] > array[j]) {
                inversionsCount++;
            }
        }
    }
    return inversionsCount;
}

bool isSolvable(int** matrix, int zeroRow) {
    if(rows % 2 == 0) {
        return (countInversions(matrix) + zeroRow) % 2 != 0;
    }
    return countInversions(matrix) % 2 == 0;
}
bool isGoal(Node* node) {
      int num = 1;
      for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < rows;j++) {
            if(i == expectedEmptyRow && j == expectedEmptyCol) {
                if(node->matrix[i][j] != 0) {
                    return false;
                }
            }else {
                if(node->matrix[i][j] != num) {
                    return false;
                }
            }
            num++;
        }
    }
    return true;
}

bool contains(Node* node, stack<Node*> path) {
    while(!path.empty()) {
        if(equals(node->matrix, path.top()->matrix)) {
            return true;
        }
        path.pop();
    }
    return false;
}

bool setContains(Node* node) {
    for( set<Node*>::iterator it = visited->begin(); it != visited->end(); ++it) {
        if(equals(node->matrix,(*it)->matrix)) {
            return true ;
        } 
    }
    return false;
}

int search(stack<Node*> path, int g, int bound) {
    cout << "G = " << g <<endl;
    Node* node = path.top();
    cout << (node != nullptr) << " : " << g << " : " << bound << endl;
    visited->insert(path.top());
    pathToGoal->push(path.top());
    path.pop();
    int f = g + manhattan(node);
    if (f > bound) {
        return f;
    }
    if(isGoal(node)) {
        cout << "Number of steps: " << g << endl;
        return 0;
    }
    
    int min = INT32_MAX;
    list<Node*> children = neightours(node); 
 /*    cout << "---------Current Node--------------------"<<endl;
     for(int i = 0; i < rows; i ++) {
            for(int j = 0; j < rows;j ++) {
                cout << node->matrix[i][j] << " ";
            }
            cout << endl;
        }
    cout << "-----------------------------"<<endl; */

    cout << "Bound: "<< bound << endl;
  /*   for(Node* x : children) {
        cout << "Manhattan: " << manhattan(x) << endl;
        for(int i = 0; i < rows; i ++) {
            for(int j = 0; j < rows;j ++) {
                cout << x->matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-----------------------------"<<endl;
    } */
    for(Node* succ : children) {
        if(!setContains(succ)) {
            path.push(succ);
            int t = search(path,g+1, bound );
            if(t == 0 ) {
                return t;
            }
            if(t < min) {
                min = t;
                visited->insert(path.top());
                pathToGoal->pop();
                path.pop();
            } else {
                pathToGoal->pop(); 
            }
       }
    }
    if(min == INT32_MAX) {
        pathToGoal->pop();
    }
    return min;
}
int ida_star(Node* root) {
    int bound = manhattan(root);
    stack<Node*> path;
    path.push(root);
    int t;
    while(true) {
        pathToGoal = new stack<Node*>();
        visited = new set<Node*>();
        t = search(path, 0, bound);
        if(t == 0) {
            return 0;
        }
        bound = t;
    }
    return 0;
}
void printPath() {
    Node* next = pathToGoal->top();
    pathToGoal->pop();
    Node* prev = nullptr;
    do {
        prev = pathToGoal->top();
        if(pathToGoal->size() > 0) {
            pathToGoal->pop();
        }
        if(prev->zeroRow - next->zeroRow == -1) {
            cout << "Up" << endl;
        } else if(prev->zeroRow - next->zeroRow == 1) {
            cout << "DOWN" << endl;
        }else if(prev->zeroCol - next->zeroCol == -1) {
            cout << "LEFT" << endl;
        }else {
            cout << "RIGHT" << endl;
        }
        next = prev;
        
    } while(!pathToGoal->empty());
}
int main() {
    int size;
    int elem;
    int pos;
    int** matrix;
    cin >> size;
    cin >> pos;
    rows = sqrt(size+1);
    if(pos == -1) {
        expectedEmptyRow = (rows - 1);
        expectedEmptyCol = (rows - 1);
    } else if(pos == 0) {
        expectedEmptyRow = 0;
        expectedEmptyCol = 0;
    }
    matrix = new int*[rows];
    for(int i = 0 ; i < rows; i++ ) {
        matrix[i] = new int[rows];
    }
    int currRow = 0;
    int i = 0;
    int emptyCurrentRow;
    int emptyCurrentCol;

    for(int currCol = 0; i < (size + 1); i++) {
        cin >> elem;
        if(elem == 0) {
            emptyCurrentCol = currCol;
            emptyCurrentRow = currRow;
        }
        matrix[currRow][currCol] = elem;
        if(currCol == (rows-1)) {
            currRow++;
            currCol = 0;
        } else {
            currCol++;
        }
    }
    if(isSolvable(matrix, emptyCurrentRow)) {
        ida_star(new Node(matrix, emptyCurrentRow, emptyCurrentCol,nullptr));
        cout << endl;
        printPath();
        /* while(!pathToGoal->empty()) {
            for(int i = 0; i < rows; i++){
                for(int j = 0 ; j < rows;j++) {
                    cout << pathToGoal->top()->matrix[i][j];
                }
                cout << endl;
            }
            cout <<" ---------------------------------------- "<<endl;
            pathToGoal->pop();
        } */
    } else {
        cout << "Unsolvable matrix" <<endl;
    }

    return 0;
}