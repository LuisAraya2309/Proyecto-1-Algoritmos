#include <iostream>
#include <map>
#include <stdlib.h>
#include "Divide&Conquer.h"
#include "Backtracking.h"

int main() {
    vector<MatchInfo> dataStructureN = createDataStructure();
    cout<<"-----------Lista dataStructureN-----------"<<endl;
    for(int i = 0; i<dataStructureN.size()-1; i++){
        dataStructureN[i].printMatchInfo();
    }
    cout<<"Size of N: "<<sizeof(dataStructureN)<<endl;
    cout<<endl;
    vector<MatchInfo> finalCuts;
    int contador = 0;
    int hola = divideAndConquer(dataStructureN, finalCuts, contador);
    cout<<"Recortes encontrados por el Divide&Conquer: "<<hola<<endl;
    return 0;
}