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

    cout<<"-----------Lista Entrante-----------"<<endl;
    for(int i = 0; i<pDividedInfo.size(); i++){
        pDividedInfo[i].printMatchInfo();
    }
    cout<<"Cantidad de recortes antes de evaluar:"<<pDividedInfo.size()<<endl;

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
    cout<<"-----------Lista Resultante-----------"<<endl;
    for(int i = 0; i<finalCuts.size(); i++){
        finalCuts[i].printMatchInfo();
    }
    return finalCuts;
}

int conquer(vector<MatchInfo> &pFinalCuts){
    return pFinalCuts.size();
}

int divideAndConquer(vector<MatchInfo> &pDataStructureN, vector<MatchInfo> &pFinalCuts, int &contador){

    if(pDataStructureN.size()<=1){
        return conquer(eraseDuplicatedColumnCuts(pFinalCuts));
    }
    
    vector<MatchInfo> dividedInfo;
    vector<MatchInfo> pInfoToEvaluate;
    MatchInfo pivot = pDataStructureN[0];
    int pivotBegin = pivot.getBegin(), pivotEnd = pivot.getEnd();
    dividedInfo.push_back(pivot);

    for(int actualInfo = 1; actualInfo < pDataStructureN.size(); actualInfo++){

        MatchInfo sample = pDataStructureN[actualInfo];
        int sampleBegin = sample.getBegin(), sampleEnd = sample.getEnd();
        //cout<<"Se evlauan: "<<pivot.getRowPosition()<<" contra "<<sample.getRowPosition()<<endl;
        //cout<<"Condicion: "<<pivotBegin<<" == "<<sampleBegin<<" and "<<pivotEnd<<" == "<<sampleEnd<<endl;
        if(pivotBegin == sampleBegin && pivotEnd == sampleEnd){
            //cout<<"Se ingresa a dividedInfo para ser evaluado"<<endl;
            dividedInfo.push_back(sample);
        }else{
            //cout<<"Se ingresa a pInfoToEvaluate"<<endl;
            pInfoToEvaluate.push_back(sample);
        }
    }
    //cout<<"Termino la busqueda, crea la lista: "<<endl;
    pDataStructureN = pInfoToEvaluate;
    eraseDuplicatedRowCuts(dividedInfo, pFinalCuts);
    contador++;
    return divideAndConquer(pDataStructureN , pFinalCuts, contador) ;
}