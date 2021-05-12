#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<vector>
#include <unordered_map>
#include <map>

using namespace std;
using namespace cv;


void uploadImageOneInfo(vector<vector<string>> &pImageOneInfo){
    /*
    Purpose: Load the first image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: Recieves an empty matrix who is going to be filled with RGB colors.
    Returns: Nothing. Void
    */
    string imagePath = "C:/Users/luist/OneDrive/Escritorio/Proyecto1/Prueba1.png";
    int blueChannel; int greenChannel; int redChannel;
    Mat colorImage; colorImage = imread(imagePath);
     int rowsImageOneInfo =0;

    for (int imageRows = 0; imageRows < colorImage.rows; imageRows+=54){
        for (int imageColumns = 0; imageColumns < colorImage.cols; imageColumns++) {
            redChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[2];
            greenChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[1];
            blueChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[0];

            string rgbValue = to_string(redChannel) +","+ to_string(greenChannel)  +","+ to_string(blueChannel);
            pImageOneInfo[rowsImageOneInfo][imageColumns] = rgbValue;
            
        }
        rowsImageOneInfo++;
    }
}

void uploadImageTwoInfo(vector<vector<string>> &pImageTwoInfo){
    /*
    Purpose: Load the second image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: Recieves an empty matrix who is going to be filled with RGB colors.
    Returns: Nothing. Void
    */

    string imagePath = "C:/Users/luist/OneDrive/Escritorio/Proyecto1/Prueba2.jpg";
    int blueChannel; int greenChannel; int redChannel;
    Mat colorImage; colorImage = imread(imagePath);
    int rowsImageTwoInfo =0;
    for (int imageRows = 0; imageRows < colorImage.rows; imageRows+=54){
        for (int imageColumns = 0; imageColumns < colorImage.cols; imageColumns++) {
            redChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[2];
            greenChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[1];
            blueChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[0];

            string rgbValue = to_string(redChannel) +","+ to_string(greenChannel)  +","+ to_string(blueChannel);
            pImageTwoInfo[rowsImageTwoInfo][imageColumns] = rgbValue;
        }
        rowsImageTwoInfo++;
    }
}

void  selectTop3Trends(unordered_map<string, int> &colorAppearence,vector<int> &trendsPerLine,vector<string> &allTrends){
    for(int trend = 0 ;trend < 3;trend++){

        int trendColor = trendsPerLine[0];
        size_t vectorSize = trendsPerLine.size();
        int removeElement= 0;
        for(int actualColor = 0;actualColor < vectorSize-1;actualColor++){
            if(trendColor < trendsPerLine[actualColor]){
                trendColor = trendsPerLine[actualColor];
                removeElement = actualColor;
            }
        }
        trendsPerLine.erase(trendsPerLine.begin()+removeElement);

        unordered_map<string, int>:: iterator hashColor;
        string topTrend;
        for(hashColor = colorAppearence.begin(); hashColor != colorAppearence.end(); hashColor++){
            if(hashColor->second == trendColor){
                topTrend = hashColor->first;
                break;
            }
        }
        colorAppearence.erase(topTrend);
        allTrends.push_back(topTrend);

    }
}

vector<string> createSecondImageArrayTrend(){

    /*
    Purpose: Create an array fulled with the trend colors from each 54 lines of the second image.
    Parameters: Nothing
    Returns: The array of trend colors.
    */

    const int rows = 40 , columns = 3840;

    vector<vector<string>> imageTwoInfo( rows , vector<string> (columns));
    uploadImageTwoInfo(imageTwoInfo);
    vector<string> allTrends;
    vector<int> trendsPerLine;
    vector<string> top3TrendsPerLine;
    
    for(int lines = 0;lines<rows;lines++){
        unordered_map<string, int> colorAppearence;
        string actualColor;
        for(int colors = 0;colors<columns;colors++){
            actualColor = imageTwoInfo[lines][colors];
            colorAppearence[actualColor]++;
        }
        unordered_map<string, int>:: iterator hashColor;
        for (hashColor = colorAppearence.begin(); hashColor != colorAppearence.end(); hashColor++){
            trendsPerLine.push_back(hashColor->second);
            
        }
        selectTop3Trends(colorAppearence,trendsPerLine,allTrends);
        trendsPerLine.clear();

    }
    return allTrends;
}

string selectSegmentsTrends(vector<vector<string>> &pImageOneInfo,int pSegment,int pImageRow){
    const int segmentLimit = 192;
    vector<string> lineSegment;
    vector<int> colorCount;
    for(int startSegment = pSegment; startSegment < pSegment + segmentLimit;startSegment++){
        lineSegment.push_back(pImageOneInfo[pImageRow][startSegment]);

    }
    unordered_map<string,int> colorAppearence;
    for(int pixelIndex = 0; pixelIndex<segmentLimit;pixelIndex++){
        colorAppearence[lineSegment[pixelIndex]]++;
    }

    for(auto& hashColor:colorAppearence){
        colorCount.push_back(hashColor.second);
    }

    int trendColor = colorCount[0];
    size_t colorCountLength = colorCount.size();
    for(int actualColor = 0;actualColor<colorCountLength-1;actualColor++){
        if(trendColor<colorCount[actualColor]){
            trendColor = colorCount[actualColor];
        }
    }
    string finalTrend="";
    for(auto& hashKey:colorAppearence){
        if(hashKey.second == trendColor){
            finalTrend = hashKey.first;
            break;
        }
    }
    return finalTrend;
}

vector<string> divideLinesBySegments(){
    /*
    Purpose: Create an array fulled with the trend colors from each segment of the first image.
    Parameters: Nothing
    Returns: The array of trend colors
    */
    const int rows = 40,columns = 3840, segmentLimit=192;
    vector<vector<string>> imageOneInfo( rows , vector<string> (columns));
    uploadImageOneInfo(imageOneInfo);
    vector<string> imageOneTrends;

    for(int imageRows =0;imageRows<rows;imageRows++){
        for(int segment=0;segment<columns;segment+=segmentLimit){
            string trendColor = selectSegmentsTrends(imageOneInfo,segment,imageRows);
            string trendInfo = trendColor + "|" + to_string(segment) + "|" + to_string(segment+segmentLimit) + "|" + to_string(imageRows*54);
            imageOneTrends.push_back(trendInfo);
        }
    }
    return imageOneTrends;
    


}


vector<int> trendColorToInt(string pTrends){
    string delimiter = ",";
    vector<int> rgbValues;
    while ((pTrends.find(delimiter)) != string::npos) {
        rgbValues.push_back(stoi(pTrends.substr(0, pTrends.find(delimiter))));
        pTrends.erase(0, pTrends.find(delimiter) + delimiter.length());
    } rgbValues.push_back(stoi(pTrends.substr(0, pTrends.find(delimiter))));
    return rgbValues;
}

//  R,G,B|xi|xf|y

string returnColor(string fullInfo){
    return fullInfo.substr(0,fullInfo.find("|"));
}

int returnRequiredPosition(string fullInfo,int requiredPosition){
    for(int data = 0; data<=requiredPosition;data++){
        fullInfo = fullInfo.substr(fullInfo.find("|"),fullInfo.length()-1);
        if(data==3){
            return stoi(fullInfo);
        }   
    }

    return stoi(fullInfo.substr(0,fullInfo.find("|")));

}

vector<int> joinPositionalInfo(int beginPosition,int endPosition, int verticalPosition){
    vector<int> positionalInfo;
    positionalInfo.push_back(beginPosition);
    positionalInfo.push_back(endPosition);
    positionalInfo.push_back(verticalPosition);

    return positionalInfo;
}



vector<string> matchTrends(vector<string> &pImageOneTrendsVector , vector<string> &pImageTwoTrendsVector){
    vector<string> matchTrendVector;
    for(int imageOneIndex = 0; imageOneIndex<pImageOneTrendsVector.size(); imageOneIndex++){
        string trend = pImageOneTrendsVector[imageOneIndex];
        string trendColor = trend.substr(0, trend.find("|"));
        vector<int> imageOneTrend = trendColorToInt(trendColor);
        

        for(int imageTwoIndex = 0; imageTwoIndex<pImageTwoTrendsVector.size(); imageTwoIndex++){
            vector<int> imageTwoTrend = trendColorToInt(pImageTwoTrendsVector[imageTwoIndex]);
            bool compareRedValue = (-2 <= imageOneTrend[0]-imageTwoTrend[0]) && (2>=imageOneTrend[0]-imageTwoTrend[0]); 
            bool compareGreenValue = (-2 <=  imageOneTrend[1]-imageTwoTrend[1]) && (2>=imageOneTrend[1]-imageTwoTrend[1]);
            bool compareBlueValue = (-2 <= imageOneTrend[2]-imageTwoTrend[2]) && (2>=imageOneTrend[2]-imageTwoTrend[2]);
            //cout<<"Primera imagen: "<< imageOneTrend[0]<< "," << imageOneTrend[1]<<"," << imageOneTrend[2]<<" Segunda imagen: " << imageTwoTrend[0]<< "," << imageTwoTrend[1]<<"," << imageTwoTrend[2]<<endl;
            if(compareRedValue && compareGreenValue && compareBlueValue){
                matchTrendVector.push_back(pImageTwoTrendsVector[imageTwoIndex]  + trend.substr(trend.find("|"), trend.length()-1));
                //cout<<"Vector: "<<matchTrendVector[matchTrendVector.size()-1]<<endl<<endl;
                break;
            }

        }
    }
    /*
    cout<<matchTrendVector.size()<<endl;
    for(size_t i=0;i<matchTrendVector.size();i++){
        cout<<"Trend: "<<matchTrendVector[i]<<endl;
    }
    */
    return matchTrendVector;
}

multimap<string,vector<int>> createDataStructure(){
    cout<<"Iniciar el proceso"<<endl;
    vector<string> imageOneTrends = divideLinesBySegments();
    cout<<"Primera imagen cargada"<<endl;
    vector<string> imageTwoTrends = createSecondImageArrayTrend();
    cout<<"Segunda imagen cargada"<<endl;
    vector<string> matchedTrends = matchTrends(imageOneTrends, imageTwoTrends);

    multimap <string,vector<int>> dataStructure;

    for(size_t trendInfo = 0;trendInfo<matchedTrends.size();trendInfo++){
        int beginPosition, endPosition, verticalPosition;
        string trendColor;

        trendColor = returnColor(matchedTrends[trendInfo]);
        beginPosition = returnRequiredPosition(matchedTrends[trendInfo],0);
        endPosition= returnRequiredPosition(matchedTrends[trendInfo],1);    
        verticalPosition= returnRequiredPosition(matchedTrends[trendInfo],2);  
        vector<int> positionInfo;
        dataStructure.emplace(trendColor,positionInfo);
        //cout<<"Trend Color: "<<trendColor<<" , BP: "<<beginPosition<<" ,EP: "<<endPosition<<" ,VP: "<<verticalPosition<<endl;
    }
    return dataStructure;
}

int main() {
    multimap<string,vector<int>> dataStructureN = createDataStructure();
    cout<<"Size of N: "<<sizeof(dataStructureN);
    return 0;
}