#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <unordered_map>
#include <map>
#include "MatchInfo.h"
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
    
    string imagePath = "C:/Users/Sebastian/Pictures/Prueba1.png";
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

    string imagePath = "C:/Users/Sebastian/Pictures/Prueba2.jpg";
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

void  selectTop3Trends(vector<Pixel> &pPixels,vector<int> &pPixelAppearence,vector<int> &pTrendsPerLine,vector<Pixel> &pAllTrends){
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
        for(int pixel = 0; pixel< pPixelAppearence.size();pixel++){
            if(pPixelAppearence[pixel] == trendColor){
                topTrend = pPixels[pixel];
                removeElement = pixel;
                break;
            }
        }
        pPixels.erase(pPixels.begin() + removeElement);
        pAllTrends.push_back(topTrend);

    }
}

int getElementPosition(vector<Pixel> &pixels, Pixel &searchElement){

    size_t pixelsLength = pixels.size();
    for(int iteratePixels = 0; iteratePixels<pixelsLength;iteratePixels++){
        Pixel actualPixel = Pixel();
        actualPixel= pixels[iteratePixels];
        bool isRedEqual = actualPixel.getRed() == searchElement.getRed(); 
        bool isBlueEqual =  actualPixel.getBlue() == searchElement.getBlue();
        bool isGreenEqual =  actualPixel.getGreen() == searchElement.getGreen();
        if((isRedEqual)&&(isBlueEqual)&&(isGreenEqual)){
            return iteratePixels;
        }
    }
    return -1;    

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

        vector<Pixel> pixels;
        vector<int> pixelAppearence;
        Pixel actualColor = Pixel();
        for(int colors = 0;colors<columns;colors++){
            actualColor = imageTwoInfo[lines][colors];
            int addPosition = getElementPosition(pixels,actualColor);
            if(addPosition!=-1){
                pixelAppearence[addPosition]++;
                continue;
            }
            pixels.push_back(actualColor);
            pixelAppearence.push_back(1);
            
        }

        for (int countedPixel = 0;countedPixel<pixelAppearence.size();countedPixel++){
            trendsPerLine.push_back(pixelAppearence[countedPixel]);
            
        }
        selectTop3Trends( pixels, pixelAppearence,trendsPerLine,allTrends);
        trendsPerLine.clear();
    }
    return allTrends;
}

Pixel selectSegmentsTrends(vector<vector<Pixel>> &pImageOneInfo,int pSegment,int pImageRow, const int pSegmentLimit){
    /*
    Purpose: 
        -Analize and select the trend of a specific segment.
    Paramateres: 
        -A matrix with all the color values about ImageOne
        -An interger that specify the position of the segment 
        -An interger that specify the row position of the segment.
        -An interger with the leght of the segment.
    Returns: 
        -A Pixel with the segment trend.
    */

    vector<Pixel> lineSegment, pixels;
    vector<int> pixelAppearence;

    for(int startSegment = pSegment; startSegment < pSegment + pSegmentLimit;startSegment++){
        lineSegment.push_back(pImageOneInfo[pImageRow][startSegment]);
    }

    Pixel actualColor = Pixel();
    int addPosition;
    for(int pixelIndex = 0; pixelIndex < pSegmentLimit;pixelIndex++){
        actualColor = lineSegment[pixelIndex];
        addPosition = getElementPosition(pixels,actualColor);
        if(addPosition!=-1){
            pixelAppearence[addPosition]++;
            continue;
        }
        pixels.push_back(actualColor);
        pixelAppearence.push_back(1);
    }

    int trendColor = pixelAppearence[0];
    size_t pixelAppearenceLength = pixelAppearence.size();
    for(int actualColor = 0;actualColor<pixelAppearenceLength-1;actualColor++){
        if(trendColor<pixelAppearence[actualColor]){
            trendColor = pixelAppearence[actualColor];
        }
    }

    Pixel finalTrend = Pixel();
    for(int pixelTimes = 0; pixelTimes<pixelAppearenceLength;pixelTimes++){
        if(pixelAppearence[pixelTimes] == trendColor){
            finalTrend = pixels[pixelTimes];
            break;
        }
    }
    return finalTrend;
}

vector<Pixel> returnSpecificSegment(vector<vector<Pixel>> &pImageOneInfo, int pSegment, int pImageRow, const int pSegmentLimit){
    vector<Pixel> specificSegment;
    for(int startSegment = pSegment; startSegment < pSegment + pSegmentLimit; startSegment++){
        specificSegment.push_back(pImageOneInfo[pImageRow][startSegment]);
    }
    return specificSegment;
}

vector<MatchInfo> divideLinesBySegments(){
    /*
    Purpose:
        -Create an array fulled with the trend colors from each segment of the first image.
    Parameters: 
        -Nothing.
    Returns:
        -An array of trend colors.
    */
    const int rows = 40,columns = 3840, segmentLimit=192;
    vector<vector<Pixel>> imageOneInfo( rows , vector<Pixel> (columns));
    uploadImageOneInfo(imageOneInfo);
    vector<MatchInfo> imageOneTrends;

    for(int imageRows =0;imageRows<rows;imageRows++){
        for(int segment=0;segment<columns;segment+=segmentLimit){
            Pixel trendColor = selectSegmentsTrends(imageOneInfo,segment,imageRows, segmentLimit);
            vector<Pixel> specificSegment = returnSpecificSegment(imageOneInfo,segment,imageRows,segmentLimit);
            MatchInfo totalInfo = MatchInfo(trendColor,specificSegment,segment, segment+segmentLimit, imageRows*54);
            imageOneTrends.push_back(totalInfo);
        }
    }
    return imageOneTrends;
    
}

vector<MatchInfo> matchTrends(vector<MatchInfo> &pImageOneTrendsVector , vector<Pixel> &pImageTwoTrendsVector){
    /*
    Purpose: 
        - Analyze the matches between the trends in the first image and the trend sampling in the second image.
    Parameters: 
        - Two vectors one of Pixels and other of MatchInfo that contain the information of the trends of the image one and two respectively.
    Returns:
        - A vector that stores all the segments information whose trends matched.
    */

    vector<MatchInfo> matchTrendVector;
    for(int imageOneIndex = 0; imageOneIndex<pImageOneTrendsVector.size(); imageOneIndex++){
        
        for(int imageTwoIndex = 0; imageTwoIndex < pImageTwoTrendsVector.size(); imageTwoIndex++){

            bool compareRedValue = (-2 <= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getRed() - pImageTwoTrendsVector[imageTwoIndex].getRed()) && (2 >= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getRed() - pImageTwoTrendsVector[imageTwoIndex].getRed()); 
            bool compareGreenValue = (-2 <= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getGreen() - pImageTwoTrendsVector[imageTwoIndex].getGreen()) && (2 >= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getGreen() - pImageTwoTrendsVector[imageTwoIndex].getGreen());
            bool compareBlueValue = (-2 <= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getBlue() - pImageTwoTrendsVector[imageTwoIndex].getBlue()) && (2 >= pImageOneTrendsVector[imageOneIndex].getSegmentTrend().getBlue() - pImageTwoTrendsVector[imageTwoIndex].getBlue());
            
            if(compareRedValue && compareGreenValue && compareBlueValue){
                pImageOneTrendsVector[imageOneIndex].setSegmentTrend(pImageTwoTrendsVector[imageTwoIndex]);
                matchTrendVector.push_back(pImageOneTrendsVector[imageOneIndex]);
                break;
            }

        }
    }
    return matchTrendVector;
}

void printDataStructure(vector<MatchInfo> &pDataStructure){
    const size_t dataStructureLenght = pDataStructure.size();
    for(int dataStructureIndex = 0; dataStructureIndex < dataStructureLenght; dataStructureIndex++){
        pDataStructure[dataStructureIndex].printMatchInfo();
    }
}

vector<MatchInfo> createDataStructure(){
     /*
    Purpose: 
        - Create the data structure of the program, the structure is a vector of MatchInfo , the pixels of the entire segment, 
        who stores the color values of the trend, the begin and end of the segment where the trend matched and
        the row position of the segement.
    Parameters: 
        - Nothing
    Returns:
        - A vector of MatchInfo with all the information of the matched segments.
    */

    cout<<"-------System startup-------"<<endl;
    vector<MatchInfo> imageOneTrends = divideLinesBySegments();
    cout<<"First image uploaded successfully"<<endl;
    vector<Pixel> imageTwoTrends = createSecondImageArrayTrend();
    cout<<"Second image uploaded successfully"<<endl;
    vector<MatchInfo> matchedTrends = matchTrends(imageOneTrends, imageTwoTrends);
    cout<<"Data structure created successfully"<<endl;
    printDataStructure(matchedTrends);
    return matchedTrends;
}