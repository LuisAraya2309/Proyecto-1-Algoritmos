#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include "dataStructure.h"
#include <cmath>

using namespace std;

/*

    Objective: To carry out an exhaustive search among the vector of solutions,
    in search of the final answers.

*/

void eraseDuplicatedCuts(vector<MatchInfo> &pDividedInfo){
    
    for(int cutIndex=0;cutIndex<pDividedInfo.size()-1;cutIndex++){
        if(abs(pDividedInfo[cutIndex].getRowPosition() - pDividedInfo[cutIndex+1].getRowPosition())    <   216    ){
            pDividedInfo.erase(pDividedInfo.begin()+(cutIndex+1));
        }
    }
    for(int i = 0; i<pDividedInfo.size();i++){
        cout<<"Lista: "<<i<<endl;
        pDividedInfo[i].printMatchInfo();
    }
    
}


int divideAndConquer(vector<MatchInfo> &pDataStructureN){

    if(pDataStructureN.empty()){
        return 0;
    }
    vector<MatchInfo> dividedInfo;
    MatchInfo pivot = pDataStructureN[0];
    int pivotBegin = pivot.getBegin();
    int pivotEnd = pivot.getEnd();
    pDataStructureN.erase(pDataStructureN.begin()+0);
    for(int actualInfo = 0; actualInfo<pDataStructureN.size();actualInfo++){

        MatchInfo sample = pDataStructureN[actualInfo];
        int sampleBegin = sample.getBegin();
        int sampleEnd = sample.getEnd();
        
        if(sampleBegin==pivotBegin && sampleEnd==pivotEnd){
            dividedInfo.push_back(sample);
            pDataStructureN.erase(pDataStructureN.begin() + actualInfo);
        }
        
    }
    cout<<"RESULTADO DEL DIVIDE -------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    eraseDuplicatedCuts(dividedInfo);
    return divideAndConquer(pDataStructureN) ;

}

