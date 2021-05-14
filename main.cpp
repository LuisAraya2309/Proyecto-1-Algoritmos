#include <iostream>
#include <map>
#include <stdlib.h>
#include "Divide&Conquer.h"
#include "Backtracking.h"

int main() {
    vector<MatchInfo> dataStructureN = createDataStructure();
    if(dataStructureN.empty()){
        cout<<"The image has no matches"<<endl;
    }else{
        vector<MatchInfo> finalCuts;
        size_t foundClipplings = divideAndConquer(dataStructureN, finalCuts);
        cout<<"Recortes encontrados por el Divide&Conquer: "<< foundClipplings <<endl;
    }
    
    return 0;
}