#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <unordered_map>
#include <map>
#include "Pixel.h"
//#include <filesystem>
#include <stdlib.h>

using namespace std;
using namespace cv;

bool existsImage(Mat pColorImage){
    /*
    Purpose: 
        -Verify if an image exists or not.
    Paramateres: 
        -Recieves a Mat type variable, with the selected image.
    Returns: 
        -True or false, it depends if the image was found or not.
    */
    try{
        int rowsValue = pColorImage.rows;
        if(rowsValue > 0){
            cout<<"The image was found successfully"<<endl;
            return true;
        } 
        else{
            throw(rowsValue);
        }
            
    }
    catch(int pRowsValue){
        cout<<"The image does not exist, the size should be 3840x2160 but it is "<<pRowsValue<<"x"<<pRowsValue<<endl;
        return false;
    }
}

void uploadImageOneInfo(vector<vector<Pixel>> &pImageOneInfo){
    /*
    Purpose: 
        -Load the first image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: 
        -Recieves an empty matrix who is going to be filled with RGB colors.
    Returns: 
        -Nothing. Void
    */
    
    string imagePath = "C:/Users/luist/OneDrive/Escritorio/Proyecto1/Prueba1.png";
    Mat colorImage = imread(imagePath);
    if(existsImage(colorImage)){
        int blueChannel; int greenChannel; int redChannel;
        int rowsImageOneInfo =0;
        for (int imageRows = 0; imageRows < colorImage.rows; imageRows+=54){
            for (int imageColumns = 0; imageColumns < colorImage.cols; imageColumns++) {
                redChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[2];
                greenChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[1];
                blueChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[0];

                Pixel addingPixel = Pixel(redChannel,greenChannel,blueChannel);

                pImageOneInfo[rowsImageOneInfo][imageColumns] = addingPixel;
                
            }
            rowsImageOneInfo++;
        }
    }
    else{
        exit(1);
    }
    
}

void uploadImageTwoInfo(vector<vector<Pixel>> &pImageTwoInfo){
    /*
    Purpose:
        -Load the second image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: 
        -Recieves an empty matrix who is going to be filled with RGB colors.
    Returns:
        -Nothing. Void
    */

    string imagePath = "C:/Users/luist/OneDrive/Escritorio/Proyecto1/Prueba2.jpg";
    int blueChannel; int greenChannel; int redChannel;
    Mat colorImage = imread(imagePath);
    if(!existsImage(colorImage)){
        exit(1);
    }
    int rowsImageTwoInfo =0;
    for (int imageRows = 0; imageRows < colorImage.rows; imageRows+=54){
        for (int imageColumns = 0; imageColumns < colorImage.cols; imageColumns++) {
            redChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[2];
            greenChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[1];
            blueChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[0];

            Pixel addingPixel = Pixel(redChannel,greenChannel,blueChannel);
            pImageTwoInfo[rowsImageTwoInfo][imageColumns] = addingPixel;
        }
        rowsImageTwoInfo++;
    }
}

void  selectTop3Trends(unordered_map<Pixel, int> &pColorAppearence,vector<int> &pTrendsPerLine,vector<Pixel> &pAllTrends){
    /*
    Purpose: 
        -Select the top three trends in a line of the second image.
    Paramateres: 
        -Recieves a empty strings vector (pAllTrends)
        -A interger vector with all the color values of the line (pTrendsPerLine) 
        -A hash with all the appearences of a color. 
    Returns: 
        -No return value. Void
    */
    for(int trend = 0 ;trend < 3;trend++){

        int trendColor = pTrendsPerLine[0];
        size_t vectorSize = pTrendsPerLine.size();
        int removeElement= 0;
        for(int actualColor = 0;actualColor < vectorSize-1;actualColor++){
            if(trendColor < pTrendsPerLine[actualColor]){
                trendColor = pTrendsPerLine[actualColor];
                removeElement = actualColor;
            }
        }
        pTrendsPerLine.erase(pTrendsPerLine.begin()+removeElement);

        Pixel topTrend = Pixel();
        for(auto& hashColor : pColorAppearence){
            if(hashColor.second == trendColor){
                topTrend = hashColor.first;
                break;
            }
        }
        pColorAppearence.erase(topTrend);
        pAllTrends.push_back(topTrend);

    }
}

vector<Pixel> createSecondImageArrayTrend(){
    /*
    Purpose: 
        -Create an array fulled with the trend colors from each 54 lines of the second image.
    Parameters: 
        -No parameters
    Returns: 
        -The array of trend colors.
    */

    const int rows = 40 , columns = 3840;

    vector<vector<Pixel>> imageTwoInfo( rows , vector<Pixel> (columns));
    uploadImageTwoInfo(imageTwoInfo);
    vector<Pixel> allTrends;
    vector<int> trendsPerLine;
    vector<Pixel> top3TrendsPerLine;
    
    for(int lines = 0;lines<rows;lines++){
        unordered_map<Pixel, int> colorAppearence;
        Pixel actualColor = Pixel();
        for(int colors = 0;colors<columns;colors++){
            actualColor = imageTwoInfo[lines][colors];
            colorAppearence[actualColor]++;
        }
        for (auto& hashColor: colorAppearence){
            trendsPerLine.push_back(hashColor.second);
            
        }
        selectTop3Trends(colorAppearence,trendsPerLine,allTrends);
        trendsPerLine.clear();

    }
    return allTrends;
}

Pixel selectSegmentsTrends(vector<vector<Pixel>> &pImageOneInfo,int pSegment,int pImageRow){
    /*
    Purpose: 
        -Analize and select the trend of a specific segment.
    Paramateres: 
        -A matrix with all the color values about ImageOne
        -An interger that specify the position of the segment 
        -An interger that specify the row position of the segment.
    Returns: 
        -A string variable with the segment trend.
    */

    const int segmentLimit = 192;
    vector<Pixel> lineSegment;
    vector<int> colorCount;

    for(int startSegment = pSegment; startSegment < pSegment + segmentLimit;startSegment++){
        lineSegment.push_back(pImageOneInfo[pImageRow][startSegment]);
    }

    unordered_map<Pixel,int> colorAppearence;
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

    Pixel finalTrend = Pixel();
    for(auto& hashKey:colorAppearence){
        if(hashKey.second == trendColor){
            finalTrend = hashKey.first;
            break;
        }
    }
    return finalTrend;
}

vector<Pixel> divideLinesBySegments(){
    /*
    Purpose:
        -Create an array fulled with the trend colors from each segment of the first image.
    Parameters: 
        -Nothing
    Returns:
        -The array of trend colors
    */
    const int rows = 40,columns = 3840, segmentLimit=192;
    vector<vector<Pixel>> imageOneInfo( rows , vector<Pixel> (columns));
    uploadImageOneInfo(imageOneInfo);
    vector<Pixel> imageOneTrends;

    for(int imageRows =0;imageRows<rows;imageRows++){
        for(int segment=0;segment<columns;segment+=segmentLimit){
            Pixel trendColor = selectSegmentsTrends(imageOneInfo,segment,imageRows);
            imageOneTrends.push_back(trendColor);
        }
    }
    return imageOneTrends;
    


}



vector<Pixel> matchTrends(vector<Pixel> &pImageOneTrendsVector , vector<Pixel> &pImageTwoTrendsVector){
     /*
    Purpose: 
        - Analyze the matches between the trends in the first image and the trend sampling in the second image.
    Parameters: 
        - Two string vectors that contain the information of the trends of the image one and two respectively.
    Returns:
        - A vector that stores all the segments information whose trends matched.
    */
    vector<Pixel> matchTrendVector;
    for(int imageOneIndex = 0; imageOneIndex<pImageOneTrendsVector.size(); imageOneIndex++){
        Pixel trend = pImageOneTrendsVector[imageOneIndex];
        string trendColor = trend.substr(0, trend.find("|"));
        vector<int> imageOneTrend = trendColorToInt(trendColor);
        

        for(int imageTwoIndex = 0; imageTwoIndex<pImageTwoTrendsVector.size(); imageTwoIndex++){
            vector<int> imageTwoTrend = trendColorToInt(pImageTwoTrendsVector[imageTwoIndex]);
            bool compareRedValue = (-2 <= imageOneTrend[0]-imageTwoTrend[0]) && (2>=imageOneTrend[0]-imageTwoTrend[0]); 
            bool compareGreenValue = (-2 <=  imageOneTrend[1]-imageTwoTrend[1]) && (2>=imageOneTrend[1]-imageTwoTrend[1]);
            bool compareBlueValue = (-2 <= imageOneTrend[2]-imageTwoTrend[2]) && (2>=imageOneTrend[2]-imageTwoTrend[2]);
            
            if(compareRedValue && compareGreenValue && compareBlueValue){
                matchTrendVector.push_back(pImageTwoTrendsVector[imageTwoIndex]  + trend.substr(trend.find("|"), trend.length()-1));
                break;
            }

        }
    }
    return matchTrendVector;
}

multimap<string,vector<int>> createDataStructure(){
     /*
    Purpose: 
        - Create the data structure of the program, the structure is a multimap  , who stores the color values of the trend,
        the begin and end of the segment where the trend matched and the row position of the segement.
    Parameters: 
        - Nothing
    Returns:
        - A multimap hash with all the information of the matched segment.
    */

    cout<<"-------System startup-------"<<endl;
    vector<Pixel> imageOneTrends = divideLinesBySegments();
    cout<<"First image uploaded successfully"<<endl;
    vector<Pixel> imageTwoTrends = createSecondImageArrayTrend();
    cout<<"Second image uploaded successfully"<<endl;
    vector<Pixel> matchedTrends = matchTrends(imageOneTrends, imageTwoTrends);

    multimap <string,vector<int>> dataStructure;

    for(size_t trendInfo = 0;trendInfo<matchedTrends.size();trendInfo++){
        string trendColor;
        vector<int> positionValues = returnPositions(matchedTrends[trendInfo]);
        trendColor = returnColor(matchedTrends[trendInfo]);
        vector<int> positionInfo = joinPositionalInfo(positionValues);
        dataStructure.emplace(trendColor,positionInfo);
    }
    cout<<"Data structure created successfully"<<endl;
    return dataStructure;
}