#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<vector>
#include <unordered_map>

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

    string imagePath = "C:/Users/Sebastian/Pictures/Prueba2.jpg";
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
        int vectorSize = trendsPerLine.size();
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

vector<string> createFirtImageSegments(){

    /*
    Purpose: Create an array fulled with the trend colors from each segment of the first image.
    Parameters: Nothing
    Returns: The array of trend colors
    */
    


}


void createDataStructure(){
    //const int rows = 40 ; const int columns = 3840;
    //vector<vector<string>> imageOneInfo( rows , vector<string> (columns));
    //uploadImageOneInfo(imageOneInfo);
    cout<<"Iniciar el proceso"<<endl;
    vector<string> allTrends = createSecondImageArrayTrend();

}

int main() {
    createDataStructure();

    return 0;
}