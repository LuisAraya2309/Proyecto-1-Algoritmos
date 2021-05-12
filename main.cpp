#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <unordered_map>
#include <map>
#include <filesystem>
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

void uploadImageOneInfo(vector<vector<string>> &pImageOneInfo){
    /*
    Purpose: 
        -Load the first image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: 
        -Recieves an empty matrix who is going to be filled with RGB colors.
    Returns: 
        -Nothing. Void
    */
    
    string imagePath = "C:/Users/Sebastian/Pictures/Prueba5.png";
    Mat colorImage = imread(imagePath);
    if(!existsImage(colorImage)){
        exit(1);
    }
    int blueChannel; int greenChannel; int redChannel;
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
    Purpose:
        -Load the second image information and converts it to a matrix of colors for futures functionalities.
    Paramateres: 
        -Recieves an empty matrix who is going to be filled with RGB colors.
    Returns:
        -Nothing. Void
    */

    string imagePath = "C:/Users/Sebastian/Pictures/Prueba6.png";
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

            string rgbValue = to_string(redChannel) +","+ to_string(greenChannel)  +","+ to_string(blueChannel);
            pImageTwoInfo[rowsImageTwoInfo][imageColumns] = rgbValue;
        }
        rowsImageTwoInfo++;
    }
}

void  selectTop3Trends(unordered_map<string, int> &pColorAppearence,vector<int> &pTrendsPerLine,vector<string> &pAllTrends){
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

        unordered_map<string, int>:: iterator hashColor;
        string topTrend;
        for(hashColor = pColorAppearence.begin(); hashColor != pColorAppearence.end(); hashColor++){
            if(hashColor->second == trendColor){
                topTrend = hashColor->first;
                break;
            }
        }
        pColorAppearence.erase(topTrend);
        pAllTrends.push_back(topTrend);

    }
}

vector<string> createSecondImageArrayTrend(){
    /*
    Purpose: 
        -Create an array fulled with the trend colors from each 54 lines of the second image.
    Parameters: 
        -No parameters
    Returns: 
        -The array of trend colors.
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
    string finalTrend = "";
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
    Purpose:
        -Create an array fulled with the trend colors from each segment of the first image.
    Parameters: 
        -Nothing
    Returns:
        -The array of trend colors
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
    /*
    Purpose:
        -Convert the trend color value (red,green,blue) to intergers, and store it in a vector.
    Parameters: 
        -A string with the color values of the trend. 
    Returns:
        -A vector that stores the three color values with the RGB order.
    */

    string delimiter = ",";
    vector<int> rgbValues;

    while ((pTrends.find(delimiter)) != string::npos) {
        rgbValues.push_back(stoi(pTrends.substr(0, pTrends.find(delimiter))));
        pTrends.erase(0, pTrends.find(delimiter) + delimiter.length());
    }
    rgbValues.push_back(stoi(pTrends.substr(0, pTrends.find(delimiter))));

    return rgbValues;
}

string returnColor(string pFullInfo){
     /*
    Purpose:
        -Return the color trend.
    Parameters: 
        -A string with all the information of a posible match.
    Returns:
        -A string with only the color trend at the continue order: redValue,greenValue,blueVale.
    */
    return pFullInfo.substr(0,pFullInfo.find("|"));
}

vector<int> returnPositions(string pFullInfo){
    /*
    Purpose: 
        - Convert the position information into a interger and return it.
    Parameters: 
        - A string with all the ingormation about the matched segement.
    Returns: 
        - An interger vector that stores the begin , end and row position of the segment.
    */
    vector<int> positionValues;
    string allPositionValues = pFullInfo.substr(pFullInfo.find("|")+1, pFullInfo.size()-1);
    for(int positionInfoRequired = 0; positionInfoRequired<3;positionInfoRequired++){
        positionValues.push_back(stoi(allPositionValues.substr(0,allPositionValues.find("|"))));
        allPositionValues.erase(0,allPositionValues.find("|")+1);
    }
    positionValues.push_back(stoi(allPositionValues.substr(0,allPositionValues.find("|"))));
    return positionValues;
}

vector<int> joinPositionalInfo(vector<int> pPositionValues){
    /*
    Purpose: 
        - Add the position information to a vector.
    Parameters:
        -  An empty vector.
    Returns:
        - A vector that stores the values ​​of the segment position.
    */
    vector<int> positionalInfo;
    positionalInfo.push_back(pPositionValues[0]);
    positionalInfo.push_back(pPositionValues[1]);
    positionalInfo.push_back(pPositionValues[2]);

    return positionalInfo;
}

vector<string> matchTrends(vector<string> &pImageOneTrendsVector , vector<string> &pImageTwoTrendsVector){
     /*
    Purpose: 
        - Analyze the matches between the trends in the first image and the trend sampling in the second image.
    Parameters: 
        - Two string vectors that contain the information of the trends of the image one and two respectively.
    Returns:
        - A vector that stores all the segments information whose trends matched.
    */
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
        - Create the data structure of the program, the structure is a hash , who store the color values of the trend,
        the begin and end of the segment where the trend matched and the row position of the segement.
    Parameters: 
        - Nothing
    Returns:
        - A multimap hash with all the information of the matched segment.
    */

    cout<<"-------System startup-------"<<endl;
    vector<string> imageOneTrends = divideLinesBySegments();
    cout<<"First image uploaded successfully"<<endl;
    vector<string> imageTwoTrends = createSecondImageArrayTrend();
    cout<<"Second image uploaded successfully"<<endl;
    vector<string> matchedTrends = matchTrends(imageOneTrends, imageTwoTrends);

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

int main() {
    multimap<string,vector<int>> dataStructureN = createDataStructure();
    cout<<"Size of N: "<<sizeof(dataStructureN);
    return 0;
}