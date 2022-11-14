#include <iostream>
#include <chrono>
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
const int populationCount = 6700; // 300 
const int oldPopulationSelected = 0.4 * populationCount;
const int childrenCount = populationCount - oldPopulationSelected;
const int mutationCount = 400; // 20
const int improvementThreshold = 500 ; // 200
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
    swapIndex = population[oldPopulationSelected-1];
    population[oldPopulationSelected-1] = population[childrenCount];
    population[childrenCount] = swapIndex;
}

void crossover2() {
    bool probability1;
    bool probability2;
    int p1Index = 0;
    int p2Index = 0;
    bool take;
    int offsprintCount = 0;
    bool** children = new bool*[childrenCount];
    for(int i = 0 ; i < childrenCount; i++) {
        children[i] = new bool[itemCount];
    }
    while(offsprintCount < childrenCount ) {
            p1Index = rand() % oldPopulationSelected;
            p2Index = rand() % oldPopulationSelected;
            if(p1Index == p2Index) {
                continue;
            }
            probability1 = rand() % 100 < (float(fitness[p1Index])/valueSum * 100);
            probability2 = rand() % 100 < (float(fitness[p2Index])/valueSum * 100);
            if(!probability1 || !probability2) {
                continue;
            }
            for(int j = 0; j < itemCount;j++) {
                take = rand() % 2;
                if(take) {
                    children[offsprintCount][j] = population[p1Index][j]; 
                } else {
                    children[offsprintCount][j] = population[p2Index][j]; 
                }
            }
            offsprintCount++;

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
        selection();
         if(fitness[0] <= bestValue) {
            thresholdCount++;          
        } else {
            thresholdCount = 0;
            bestValue = fitness[0];
        }
        if(i == 10 || i == improvementThreshold / 4 ||i == improvementThreshold / 3 ||i == improvementThreshold / 2 ) {
            cout <<fitness[0] << endl;
        }
        if(thresholdCount >= improvementThreshold) {
            cout << "Threshold reacted: "  << i << endl;
            
            cout << fitness[0] << endl;
            return;
        }
        crossover2();
        mutation();
    }
}

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
    
    auto start = std::chrono::steady_clock::now();
    solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
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