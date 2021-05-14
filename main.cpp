#include <iostream>
#include <map>
#include <stdlib.h>
#include "Divide&Conquer.h"
#include "Backtracking.h"

int main() {
    vector<MatchInfo> dataStructureN = createDataStructure();
    cout<<"Size of N: "<<sizeof(dataStructureN);
    cout<<"MIERDA DE DIVE AND CONQUER: "<<endl;
    cout<<endl;
    int hola = divideAndConquer(dataStructureN);
    return 0;
}