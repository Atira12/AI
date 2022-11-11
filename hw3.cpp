#include <iostream>
using namespace std;



class Pair {
    public: 
        int weight;
        int value;
        Pair() {}
        Pair(int w, int v) {
            weight = w;
            value = v;
        }
};

int itemCount;
int valueSum = 0;
int maxWight;
Pair** items = nullptr;
const int populationCount = 700;
const int oldPopulationSelected = 0.2 * populationCount;
const int childrenCount = populationCount - oldPopulationSelected;
const int mutationCount = 20;
const int improvementThreshold = 200;
bool** population = nullptr;
int* fitness = nullptr;
int** selected = nullptr;

void init() {
    bool taken;
    population = new bool*[populationCount];
    for(int i =0 ; i < populationCount; i++) {
        population[i] = new bool[itemCount];
        for(int j =  0; j < itemCount; j++ ) {
            taken = rand() % 100 < 0.25;
            population[i][j] = taken; 
        }
    }
}
void fitnessFunc() {
    int value = 0;
    int weight = 0; 
    for(int i =0 ; i < populationCount; i++) {
        for(int j = 0; j < itemCount; j++ ) {
            if(population[i][j]) {
                weight += items[j]->weight;
                value += items[j]->value;
            }
        }

        if(weight > maxWight) {
            fitness[i] = 0;
        } else {
            fitness[i] = value;
        }
        value = 0;
        weight = 0;
    }
}

void selection() {
    int maxIndex = 0;
    int maxValue = 0;
    int swap;
    bool* swapIndex = nullptr;
    for(int i = 0 ; i < childrenCount; i++) {
        maxIndex = i;
        maxValue = fitness[i];
        for(int j = i+1; j < populationCount;j++) {
            if(fitness[j] > maxValue) {
                maxIndex = j;
                maxValue = fitness[j];
            }
        }
        swap = fitness[i];
        fitness[i] = fitness[maxIndex];
        fitness[maxIndex] = swap;

        swapIndex = population[i];
        population[i] = population[maxIndex];
        population[maxIndex] = swapIndex;
    }
}
void crossover() {
    bool probability1;
    bool probability2;
    int p1Index = 0;
    int p2Index = 0;
    bool take;
    bool** children = new bool*[childrenCount];
    for(int i = 0 ; i < childrenCount; i++) {
        children[i] = new bool[itemCount];
    }
    for(int i = 0; i < childrenCount; i++ ) {
            p1Index = rand() % oldPopulationSelected;
            p2Index = rand() % oldPopulationSelected;
            if(p1Index == p2Index) {
                i = i - 1;
                continue;
            }
            for(int j = 0; j < itemCount;j++) {
                take = rand() % 2;
                if(take) {
                    children[i][j] = population[p1Index][j]; 
                } else {
                    children[i][j] = population[p2Index][j]; 
                }
            }

    }
    for(int i = 0; i < childrenCount;i++) {
        population[i + oldPopulationSelected] = children[i];
    }
    delete[] children;
}
void mutation() {
    int mutationIndex = 0;
    for(int i = oldPopulationSelected; i < childrenCount;i++) {
        for(int j = 0; j < mutationCount; j++) {
            mutationIndex = rand() % itemCount;
            population[i][mutationIndex] = !population[i][mutationIndex];
        }
    }
}

void solve() {
    int bestValue = 0;
    int thresholdCount = 0;
    int t;
    srand(time(NULL));

    init();
    for(int i = 1 ;i < 10000;i++) {
        fitnessFunc();
         
        if(fitness[0] <= bestValue) {
            thresholdCount++;          
        } else {
            thresholdCount = 0;
            bestValue = fitness[0];
        }
        if(i == 10 || i == 15 ||i == 20 ||i == 30 ) {
            cout <<fitness[0] << endl;
        }
        if(thresholdCount >= improvementThreshold) {
            cout << "Threshold reacted: "  << i << endl;
            
            cout << fitness[0] << endl;
            return;
        }
        selection();
        
        
        crossover();
           
        mutation();

        
    }
}
/* void solve() {
    int bestValue = 0;
    int thresholdCount = 0;
    int t;

    init();
    for(int i = 1 ;i < 10000;i++) {
        fitnessFunc();
        if(fitness[0] <= bestValue) {
            thresholdCount++;          
        } else {
            thresholdCount = 0;
            bestValue = fitness[0];
        }
        if(i == 10 || i == 15 ||i == 20 ||i == 30 ) {
            cout <<fitness[0] << endl;
        }
        if(thresholdCount == improvementThreshold) {
            cout << "Threshold reacted: "  << i << endl;
            break;
        }
        for(int i = 0 ; i< populationCount;i++) {
            for(int j = 0 ; j< itemCount;j++) {
                cout << population[i][j] << ' ';
            }
            cout << "fitness = " << fitness[i] << endl;
            cout << endl;
        }
        cout << "--------------------------------" << endl;
        selection();
             for(int i = 0 ; i< populationCount;i++) {
            for(int j = 0 ; j< itemCount;j++) {
                cout << population[i][j] << ' ';
            }
            cout << "fitness = " << fitness[i] << endl;
            cout << endl;
        }
        cout << "--------------------------------" << endl;
        crossover();
             for(int i = 0 ; i< populationCount;i++) {
            for(int j = 0 ; j< itemCount;j++) {
                cout << population[i][j] << ' ';
            }
            cout << "fitness = " << fitness[i] << endl;
            cout << endl;
        }
        cout << "--------------------------------" << endl;
        mutation();
             for(int i = 0 ; i< populationCount;i++) {
            for(int j = 0 ; j< itemCount;j++) {
                cout << population[i][j] << ' ';
            }
            cout << "fitness = " << fitness[i] << endl;
            cout << endl;
        }
        cout << "--------------------------------" << endl;
        cin >> t;

        
    }
    cout << fitness[0] << endl;
} */
int main() {
     cin >> maxWight;
    cin >> itemCount;
    items = new Pair*[itemCount];
    int weight;
    int value;
    for(int i = 0 ; i < itemCount; i++) {
        cin >> weight;
        cin >> value;
        items[i] = new Pair(weight, value);
        valueSum += value;
    }
    fitness = new int[populationCount];
    solve();
}
/* int main () {

    cin >> maxWight;
    cin >> itemCount;
    items = new Pair*[itemCount];
    int weight;
    int value;
    for(int i = 0 ; i < itemCount; i++) {
        cin >> weight;
        cin >> value;
        items[i] = new Pair(weight, value);
    }
    fitness = new int[populationCount];
    init();
    fitnessFunc();
    for(int i = 0 ; i< populationCount;i++) {
        for(int j = 0 ; j< itemCount;j++) {
            cout << population[i][j] << ' ';
        }
        cout << "fitness = " << fitness[i] << endl;

        cout << endl;
    }
    cout << "--------------------------------" << endl;
    selection();
    // crossover();
    for(int i = 0 ; i< populationCount;i++) {
        for(int j = 0 ; j< itemCount;j++) {
            cout << population[i][j] << ' ';
        }
        cout << "fitness = " << fitness[i] << endl;

        cout << endl;
    }
     cout << "--------------------------------" << endl;
    crossover();
    for(int i = 0 ; i< populationCount;i++) {
        for(int j = 0 ; j< itemCount;j++) {
            cout << population[i][j] << ' ';
        }
        cout << "fitness = " << fitness[i] << endl;

        cout << endl;
    }
    cout << "--------------------------------" << endl;
    mutation();
    for(int i = 0 ; i< populationCount;i++) {
        for(int j = 0 ; j< itemCount;j++) {
            cout << population[i][j] << ' ';
        }
        cout << "fitness = " << fitness[i] << endl;

        cout << endl;
    }
    return 0;
} */