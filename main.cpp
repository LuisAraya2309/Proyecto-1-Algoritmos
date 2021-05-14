#include <iostream>
#include <map>
#include <stdlib.h>
#include "Divide&Conquer.h"
#include "Backtracking.h"
#include <ctime>

int main() {
    vector<MatchInfo> dataStructureN = createDataStructure();
    if(dataStructureN.empty()){
        cout<<"The image has no matches"<<endl;
    }else{
        vector<MatchInfo> finalCuts;
        int beginTime, finalTime;
        beginTime = clock(); 
        size_t foundClipplings = divideAndConquer(dataStructureN, finalCuts);
        finalTime = clock();
        cout<<"Clips found by the Divide&Conquer: "<< foundClipplings <<endl;
        cout<<"The duration time of the Divide&Conquer: "<<(finalTime - beginTime)*1000/CLOCKS_PER_SEC <<" miliseconds."<<endl;

    }
    
    return 0;
}

/*
Algorithm Effectiveness and Analysis of It:

The algorithm, when working by trends, can present the case in which when making the data structure,
at the time of comparing the trends of each image, the comparison may be successful, however the the analysis
does not differentiate if the clipping is valid in the case that the trends of image 1 and 2 are similar or equal due to the absence of the conquer.



*/