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
 

void eraseDuplicatedRowCuts(vector<MatchInfo> &pDividedInfo,  vector<MatchInfo> &pFinalCuts ){
    /*
    Purpose:
        -Erases the cuts that are part of a same cut in the vertical position
    Paramateres: 
    A vector of type matchInfo thas has info that needs to be cleaned in vertical position
    Returns:
        A MatchInfo vector cleaned from duplicated cuts
    */
    size_t dividedInfoLenght = pDividedInfo.size();
    int dividedInfoIndex = 0 , indexCompareRows= 1;
    if(pDividedInfo.size()==1){
        pFinalCuts.push_back(pDividedInfo[0]);
    }else{
        while(dividedInfoIndex < dividedInfoLenght){
            if(abs(pDividedInfo[dividedInfoIndex].getRowPosition() - pDividedInfo[indexCompareRows].getRowPosition()) < 216){
                indexCompareRows++;
                if(indexCompareRows >= dividedInfoLenght){
                    pFinalCuts.push_back(pDividedInfo[dividedInfoIndex]);
                    break;
                }
            }
            else{
                pFinalCuts.push_back(pDividedInfo[dividedInfoIndex]);
                dividedInfoIndex = indexCompareRows;
            }
        }
    }
}

vector<MatchInfo> eraseDuplicatedColumnCuts(vector<MatchInfo> &pDividedInfo){
    /*
    Purpose:
        -Erases the cuts that are part of a same cut in the horizontal position
    Paramateres: 
    A vector of type matchInfo thas has info that needs to be cleaned in horizontal position
    Returns:
        A MatchInfo vector cleaned from duplicated cuts
    */
    vector<MatchInfo> finalCuts;
    size_t dividedInfoLenght = pDividedInfo.size()-1;
    int dividedInfoIndex = 0 , indexCompareRows= 1;
    if(pDividedInfo.size()==1){
        finalCuts.push_back(pDividedInfo[0]);
    }else{
        while(dividedInfoIndex < dividedInfoLenght){
            if(pDividedInfo[dividedInfoIndex].getRowPosition() == pDividedInfo[indexCompareRows].getRowPosition()){
                if(pDividedInfo[dividedInfoIndex].getEnd() == pDividedInfo[indexCompareRows].getBegin()){
                    finalCuts.push_back(pDividedInfo[dividedInfoIndex]);
                    pDividedInfo.erase(pDividedInfo.begin()+indexCompareRows);
                    dividedInfoLenght--;
                }
                dividedInfoIndex++;
                indexCompareRows = dividedInfoIndex+1;
            }else{
                if(indexCompareRows == dividedInfoLenght){
                    finalCuts.push_back(pDividedInfo[dividedInfoIndex]);
                    dividedInfoIndex++;
                    indexCompareRows = dividedInfoIndex+1;
                }else{
                    indexCompareRows++;
                }
            }
        }
    }
    return finalCuts;
}

int conquer(vector<MatchInfo> &pFinalCuts){
    /*
    Purpose:
        -Selects a pivot which is going to be always the first element of the dataStructure. Then it begins to divide the data structure by the begin and end  pivot's value. 
        -It is a recursive function that divides the dataStrucure for each recursion.
    Paramateres: 
        -The data structure, a vector with the final cuts that is going to be used in the recursion
    Returns:
        -An integer with the amount of the definitive matches.
    
    vector<MatchInfo> compareCuts; 
    int  pFinalCutsIndex = 0, IndexCompareTrends = 1 ,pFinalCutsLenght = pFinalCuts.size()-1;
    bool redCondition, greenCondition, blueCondition;
    while(pFinalCutsIndex < pFinalCutsLenght){
        redCondition =  10 >= abs(pFinalCuts[pFinalCutsIndex].getSegmentTrend().getTrend().getRed() - pFinalCuts[IndexCompareTrends].getSegmentTrend().getTrend().getRed());
        greenCondition =  10 >= abs(pFinalCuts[pFinalCutsIndex].getSegmentTrend().getTrend().getGreen() - pFinalCuts[IndexCompareTrends].getSegmentTrend().getTrend().getGreen());
        blueCondition =  10 >= abs(pFinalCuts[pFinalCutsIndex].getSegmentTrend().getTrend().getBlue() - pFinalCuts[IndexCompareTrends].getSegmentTrend().getTrend().getBlue());
        if(redCondition && greenCondition && blueCondition){
            //Comparo si sus segmentos tienen similitudes.
            if(Si eran parecidos){
                compareCuts.push_back(pFinalCuts[pFinalCutsIndex]);
                compareCuts.push_back(pFinalCuts[IndexCompareTrends]);
                pFinalCutsIndex++;
            }else{
                if(IndexCompareTrends >= pFinalCutsLenght){
                    pFinalCutsIndex++;
                }
                IndexCompareTrends++;
            }
        }else{
            pFinalCutsIndex++;
        }
    }
    */
   return 0;
}

size_t divideAndConquer(vector<MatchInfo> &pDataStructureN, vector<MatchInfo> &pFinalCuts){
     /*
    Purpose:
        -Selects a pivot which is going to be always the first element of the dataStructure. Then it begins to divide the data structure by the begin and end  pivot's value. 
        -It is a recursive function that divides the dataStrucure for each recursion.
    Paramateres: 
        -The data structure, a vector with the final cuts that is going to be used in the recursion
    Returns:
        -An integer with the amount of the definitive matches.
    */

    if(pDataStructureN.size()<=1){
        return eraseDuplicatedColumnCuts(pFinalCuts).size();
    }
    
    vector<MatchInfo> dividedInfo;
    vector<MatchInfo> pInfoToEvaluate;
    MatchInfo pivot = pDataStructureN[0];
    int pivotBegin = pivot.getBegin(), pivotEnd = pivot.getEnd();
    dividedInfo.push_back(pivot);

    for(int actualInfo = 1; actualInfo < pDataStructureN.size(); actualInfo++){

        MatchInfo sample = pDataStructureN[actualInfo];
        int sampleBegin = sample.getBegin(), sampleEnd = sample.getEnd();
        if(pivotBegin == sampleBegin && pivotEnd == sampleEnd){
            dividedInfo.push_back(sample);
        }else{
            pInfoToEvaluate.push_back(sample);
        }
    }
    pDataStructureN = pInfoToEvaluate;
    eraseDuplicatedRowCuts(dividedInfo, pFinalCuts);
    return divideAndConquer(pDataStructureN , pFinalCuts) ;
}