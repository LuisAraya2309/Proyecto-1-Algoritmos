#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <unordered_map>
#include "MatchInfo.h"
#include <stdlib.h>

using namespace std;

/*

    Objective: To carry out an exhaustive search among the vector of solutions,
    in search of the final answers.

*/




int divideAndConquer(vector<MatchInfo> &pDataStructureN){

    vector<MatchInfo> dividedInfo;
    MatchInfo pivot = pDataStructureN[0];
    int pivotBegin = pivot.getBegin();
    int pivotEnd = pivot.getEnd();
    pDataStructureN.erase(pDataStructureN.begin());
    for(int actualInfo = 0; actualInfo<pDataStructureN.size();actualInfo++){

        MatchInfo sample = pDataStructureN[actualInfo];
        int sampleBegin = sample.getBegin();
        int sampleEnd = sample.getEnd();
        
        if(sampleBegin==pivotBegin && sampleEnd==pivotEnd){
            dividedInfo.push_back(sample);
        }
        
    }
    return divideAndConquer(); // + Conquer(dividenInfo,);

}

