#include <iostream>
#include <map>
#include <stdlib.h>
#include "dataStructure.h"


int main() {
    multimap<string,vector<int>> dataStructureN = createDataStructure();
    cout<<"Size of N: "<<sizeof(dataStructureN);
    return 0;
}